#include <log4cxx/logger.h>

#include "include/threadPool.h"

using namespace std;

ThreadPool::ThreadPool(const uint32_t numOfThreads)
    : m_shouldTerminate(false)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    size_t sizeOfWorkerThreadsVector = numOfThreads;

    // In case user provided 0 or number greater then the maximum possible
    // set the HW concurrency maximum
    if (0 == numOfThreads || thread::hardware_concurrency() < numOfThreads)
    {
        sizeOfWorkerThreadsVector = thread::hardware_concurrency();
        LOG4CXX_DEBUG(rootLogger, "user wanted to have:" << numOfThreads
            << ", but instead " << sizeOfWorkerThreadsVector << " threads were allocated");
    }

    m_workerThreadsVec.reserve(sizeOfWorkerThreadsVector);
}

void ThreadPool::Start()
{

}

bool ThreadPool::QueueJobItem(const int workItem)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to add item:" << workItem << " to the queue");
    {
        unique_lock<mutex> lock(m_queueMutex);

        // TODO: should we check for maximum capacity???
        m_jobsItems.emplace(workItem);
    }

    m_condVar.notify_one();
    return true;
}

void ThreadPool::Stop()
{

}

bool ThreadPool::Busy()
{
    bool isPoolBusy;
    {
        unique_lock<mutex> lock(m_queueMutex);
        isPoolBusy = !m_jobsItems.empty();
    }

    return isPoolBusy;
}

size_t ThreadPool::GetNumOfWorkItems()
{
    size_t numOfWorkItems;
    {
        unique_lock<mutex> lock(m_queueMutex);
        numOfWorkItems = m_jobsItems.size();
    }

    return numOfWorkItems;
}

size_t ThreadPool::GetNumOfThreads() const
{
    return m_workerThreadsVec.size();
}

size_t ThreadPool::GetThreadsCapacity() const
{
    return m_workerThreadsVec.capacity();
}