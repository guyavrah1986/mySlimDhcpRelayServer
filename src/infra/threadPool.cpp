#include "include/threadPool.h"

using namespace std;

ThreadPool::ThreadPool(const uint32_t numOfThreads)
    : m_should_terminate(false)
{
    size_t sizeOfWorkerThreadsVector = numOfThreads;

    // In case user provided 0 or number greater then the maximum possible
    // set the HW concurrency maximum
    if (0 == numOfThreads || thread::hardware_concurrency() < numOfThreads)
    {
        sizeOfWorkerThreadsVector = thread::hardware_concurrency();
    }

    m_workerThreadsVec.reserve(sizeOfWorkerThreadsVector);
}


void ThreadPool::Start()
{

}

void ThreadPool::QueueJobItem(const int num)
{

}

void ThreadPool::Stop()
{

}

bool ThreadPool::Busy()
{
    return false;
}