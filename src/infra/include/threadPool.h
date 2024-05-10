#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool
{
public:
    explicit ThreadPool(const uint32_t numOfThreads);

    // Non copyable
    ThreadPool(const ThreadPool& other) = delete;
    ThreadPool& operator=(const ThreadPool& rhs) = delete;
    ThreadPool(ThreadPool&& other) = delete;
    ThreadPool& operator=(const ThreadPool&& rhs) = delete;
    
    // Public API
    void Start();
    bool QueueJobItem(const int num);
    void Stop();
    bool Busy();

    // Getters & setters
    size_t GetNumOfWorkItems();
    size_t GetNumOfThreads() const;
    size_t GetThreadsCapacity() const;

private:
    void ThreadLoop();

    bool m_shouldTerminate;                         // Tells threads to stop looking for jobs
    std::condition_variable m_condVar;              // Allows threads to wait on new jobs or termination 
    std::vector<std::thread> m_workerThreadsVec;
    
    std::mutex m_queueMutex;                        // Prevents data races to the job queue
    std::queue<int> m_jobsItems;
};