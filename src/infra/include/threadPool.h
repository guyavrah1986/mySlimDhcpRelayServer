#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

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

    // Non copyable
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
        for (uint32_t i = 0; i < numOfThreads; ++i)
        {
            m_workerThreadsVec.emplace_back(std::thread(&ThreadPool::ThreadLoop, this));
        }

        LOG4CXX_INFO(rootLogger, "Created " << numOfThreads << " worker threads");
    }

    bool QueueWorkItem(const T& workItem)
    {
        auto rootLogger = log4cxx::Logger::getRootLogger();
        LOG4CXX_INFO(rootLogger, "about to add item:" << workItem << " to the queue");
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);

            // TODO: should we check for maximum capacity???
            m_jobsItems.emplace(workItem);
        }

        m_condVar.notify_one();
        return true;
    }

    void Stop()
    {
        auto rootLogger = log4cxx::Logger::getRootLogger();
        LOG4CXX_INFO(rootLogger, "About to stop the thread pool");
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_shouldTerminate = true;
        }

        m_condVar.notify_all();

        // Before terminating we must join all threads so that when the 
        // destructor gets called, the they will be un-joinable
        // TODO: when using the wrapperThread class this is probably not needed...
        for (std::thread& workerThread : m_workerThreadsVec)
        {
            workerThread.join();
        }

        m_workerThreadsVec.clear();
    }

    bool Busy()
    {
        bool isPoolBusy;
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            isPoolBusy = !m_jobsItems.empty();
        }

        return isPoolBusy;
    }
    
    // Getters & setters
    // =================
    size_t GetNumOfWorkItems()
    {
        size_t numOfWorkItems;
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            numOfWorkItems = m_jobsItems.size();
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
    void ThreadLoop()
    {

    }

    bool m_shouldTerminate;                         // Tells threads to stop looking for jobs
    std::condition_variable m_condVar;              // Allows threads to wait on new jobs or termination 
    std::vector<std::thread> m_workerThreadsVec;
    
    std::mutex m_queueMutex;                        // Prevents data races to the job queue
    std::queue<T> m_jobsItems;
    std::function<void(T)> m_workerThreadFunc;      // Points to the common worker threads function
};