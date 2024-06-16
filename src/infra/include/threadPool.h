#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <vector>

#include "posixCpp11ThreadWrapper.h"

template<typename T> class ThreadPool
{
public:
    explicit ThreadPool(const uint32_t numOfThreads, std::function<void(T)> workerThreadFunc)
        : m_shouldTerminate(false),
        m_workerThreadFunc(workerThreadFunc)
    {
        auto rootLogger = log4cxx::Logger::getRootLogger();
        size_t sizeOfWorkerThreadsVector = numOfThreads;

        // In case user provided 0 or number greater then the maximum possible
        // set the HW concurrency maximum
        if (0 == numOfThreads || std::thread::hardware_concurrency() < numOfThreads)
        {
            sizeOfWorkerThreadsVector = std::thread::hardware_concurrency();
            LOG4CXX_WARN(rootLogger, "user wanted to have:" << numOfThreads
                << ", but instead " << sizeOfWorkerThreadsVector << " threads were allocated");
        }

        m_workerThreadsVec.reserve(sizeOfWorkerThreadsVector);
    }

    // Non copyable and non movable
    ThreadPool(const ThreadPool& other) = delete;
    ThreadPool& operator=(const ThreadPool& rhs) = delete;
    ThreadPool(ThreadPool&& other) = delete;
    ThreadPool& operator=(const ThreadPool&& rhs) = delete;
    
    // Public API
    // ==========
    void Start()
    {   
        auto rootLogger = log4cxx::Logger::getRootLogger();
        size_t numOfThreads = this->GetThreadsCapacity();
        LOG4CXX_INFO(rootLogger, "thread:" << std::this_thread::get_id() << " is about to create " << numOfThreads << " worker threads");
        for (uint32_t i = 0; i < numOfThreads; ++i)
        {
            // PosixCpp11ThreadWrapper(
            m_workerThreadsVec.emplace_back(std::move(std::thread(&ThreadPool::workerThreadLoop, this)), &std::thread::join);
            LOG4CXX_INFO(rootLogger, "thread:" << std::this_thread::get_id() << " created worker thread:" << i + 1);
        }

        LOG4CXX_INFO(rootLogger, "Created " << numOfThreads << " worker threads");
    }

    bool QueueWorkItem(const T& workItem)
    {
        auto rootLogger = log4cxx::Logger::getRootLogger();
        LOG4CXX_INFO(rootLogger, "about to add item:" << workItem << " to the queue");
        {
            std::unique_lock<std::mutex> lock(m_workItemQueueMutex);

            // TODO: should we check for maximum capacity???
            if (false == m_shouldTerminate)
            {
                m_workItemsQueue.emplace(workItem);
            }
            else
            {
                return false;
            }
        }

        m_condVar.notify_one();
        return true;
    }

    void Stop()
    {
        auto rootLogger = log4cxx::Logger::getRootLogger();
        LOG4CXX_INFO(rootLogger, "About to stop the thread pool");
        {
            std::unique_lock<std::mutex> lock(m_workItemQueueMutex);
            m_shouldTerminate = true;
        }

        m_condVar.notify_all();

        // Before terminating we must join all threads so that when the 
        // destructor gets called, the they will be un-joinable
        // TODO: when using the wrapperThread class this is probably not needed...
        /*
        for (std::thread& workerThread : m_workerThreadsVec)
        {
            workerThread.join();
        }
        */

        m_workerThreadsVec.clear();
    }

    bool Busy()
    {
        bool isPoolBusy;
        {
            std::unique_lock<std::mutex> lock(m_workItemQueueMutex);
            isPoolBusy = !m_workItemsQueue.empty();
        }

        return isPoolBusy;
    }
    
    // Getters & setters
    // =================
    size_t GetNumOfWorkItems()
    {
        size_t numOfWorkItems;
        {
            std::unique_lock<std::mutex> lock(m_workItemQueueMutex);
            numOfWorkItems = m_workItemsQueue.size();
        }

        return numOfWorkItems;
    }

    size_t GetNumOfThreads() const
    {
        return m_workerThreadsVec.size();
    }

    size_t GetThreadsCapacity() const
    {
        return m_workerThreadsVec.capacity();
    }

private:
    void workerThreadLoop()
    {
        auto rootLogger = log4cxx::Logger::getRootLogger();
        LOG4CXX_DEBUG(rootLogger, "thread:" << std::this_thread::get_id() << " about to enter infinte loop");
        while (true)
        {
            T workItem;
            {
                LOG4CXX_DEBUG(rootLogger, "thread:" << std::this_thread::get_id() << " BEFORE cond var");
                std::unique_lock<std::mutex> lock(m_workItemQueueMutex);
                m_condVar.wait(lock, [this] {
                        return !m_workItemsQueue.empty() || m_shouldTerminate;
                });
                
                LOG4CXX_DEBUG(rootLogger, "thread:" << std::this_thread::get_id() << " AFTER cond var");
                if (true == m_shouldTerminate)
                {
                    LOG4CXX_WARN(rootLogger, "terminating infine loop for thread:" << std::this_thread::get_id());
                    return;
                }

                // Extract the next work item from the queue
                workItem = m_workItemsQueue.front();
                m_workItemsQueue.pop();   
            }

            LOG4CXX_INFO(rootLogger, "thread:" << std::this_thread::get_id() << " BEFORE handling work item");
            m_workerThreadFunc(workItem);
            LOG4CXX_INFO(rootLogger, "thread:" << std::this_thread::get_id() << " AFTER handling work item");
        }
    }

    bool m_shouldTerminate;                         // Tells threads to stop looking for jobs
    std::condition_variable m_condVar;              // Allows threads to wait on new jobs or termination 
    std::vector<PosixCpp11ThreadWrapper> m_workerThreadsVec;
    
    std::mutex m_workItemQueueMutex;                // Prevents data races to the job queue
    std::queue<T> m_workItemsQueue;
    std::function<void(T)> m_workerThreadFunc;      // Points to the common worker threads function
};