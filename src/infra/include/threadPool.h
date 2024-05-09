#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool
{
public:
    ThreadPool(const uint32_t numOfThreads);
    void Start();
    void QueueJobItem(const int num);
    void Stop();
    bool Busy();

private:
    void ThreadLoop();

    bool m_should_terminate;                 // Tells threads to stop looking for jobs
    std::mutex queue_mutex;                  // Prevents data races to the job queue
    std::condition_variable mutex_condition; // Allows threads to wait on new jobs or termination 
    std::vector<std::thread> m_workerThreadsVec;
    std::queue<int> jobsItems;
};