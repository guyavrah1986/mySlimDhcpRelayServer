#pragma once

#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking
#include <log4cxx/logger.h>

#include "../infra/include/threadPool.h"

template<typename T> void workerFuncSample(T arg)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "got argument:" << arg);
}

TEST(threadPoolTest, createSingleThreadPoolWithValidNumOfThreads)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    size_t numOfThreads = 2, threadsCapacity = 2;
    LOG4CXX_INFO(rootLogger, "about to create a thread pool with:" << numOfThreads << " threads");
    unsigned int numOfHwCon = std::thread::hardware_concurrency();
    LOG4CXX_INFO(rootLogger, "numOfHwCon is:" << numOfHwCon);
	HeapLeakChecker heap_checker("test_threadPool");
    {
        ThreadPool<int> threadPool(numOfThreads, workerFuncSample<int>);
        EXPECT_EQ(threadsCapacity, threadPool.GetThreadsCapacity());
        EXPECT_EQ(0, threadPool.GetNumOfThreads());

        // Try to copy the ThreadPool object -- this should NOT compile
        // ThreadPool tp(threadPool);
        // ThreadPool tp(std::move(threadPool));
        // ThreadPool tp = threadPool;
        // ThreadPool tp = std::move(threadPool);
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");

	LOG4CXX_INFO(rootLogger, "test ended successfully");
}

TEST(threadPoolTest, createThreadPoolWithInValidNumOfThreads)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    unsigned int numOfHwCon = std::thread::hardware_concurrency();
    LOG4CXX_INFO(rootLogger, "numOfHwCon is:" << numOfHwCon);
    ThreadPool<int> threadPool1(numOfHwCon + 1, workerFuncSample<int>);
    EXPECT_EQ(numOfHwCon, threadPool1.GetThreadsCapacity());
    EXPECT_EQ(0, threadPool1.GetNumOfThreads());

    ThreadPool<int> threadPool2(0, workerFuncSample<int>);
    EXPECT_EQ(numOfHwCon, threadPool2.GetThreadsCapacity());
    EXPECT_EQ(0, threadPool2.GetNumOfThreads());

    ThreadPool<int> threadPool3(-1, workerFuncSample<int>);
    EXPECT_EQ(numOfHwCon, threadPool3.GetThreadsCapacity());
    EXPECT_EQ(0, threadPool3.GetNumOfThreads());
	LOG4CXX_INFO(rootLogger, "test ended successfully");
}

TEST(threadPoolTest, checkBusyFunctionWhenPoolIsNotBusy)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    ThreadPool<int> threadPool(std::thread::hardware_concurrency(), workerFuncSample<int>);

    // At first, the work items queue is empty, so the Busy method
    // should return false
    bool expectedRes = false;
    EXPECT_EQ(expectedRes, threadPool.Busy());
    EXPECT_EQ(0, threadPool.GetNumOfWorkItems());
	LOG4CXX_INFO(rootLogger, "test ended successfully");
}

TEST(threadPoolTest, checkQueueWorkItemFunction)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    ThreadPool<int> threadPool1(std::thread::hardware_concurrency(), workerFuncSample<int>);

    // At first, the work items queue is empty, so the Busy method
    // should return false
    int workItem1 = 1;
    int workItem2 = 2;
    size_t numOfWorkItems = 0;
    EXPECT_EQ(true, threadPool1.QueueWorkItem(workItem1));
    ++numOfWorkItems;
    EXPECT_EQ(true, threadPool1.Busy());
    EXPECT_EQ(numOfWorkItems, threadPool1.GetNumOfWorkItems());

    EXPECT_EQ(true, threadPool1.QueueWorkItem(workItem2));
    ++numOfWorkItems;
    EXPECT_EQ(true, threadPool1.Busy());
    EXPECT_EQ(numOfWorkItems, threadPool1.GetNumOfWorkItems());

    ThreadPool<std::string> threadPool2(std::thread::hardware_concurrency(), workerFuncSample<std::string>);

    // At first, the work items queue is empty, so the Busy method
    // should return false
    std::string workItemStr1 = "work-item-1";
    std::string workItemStr2 = "work-item-2";
    numOfWorkItems = 0;
    EXPECT_EQ(true, threadPool2.QueueWorkItem(workItemStr1));
    ++numOfWorkItems;
    EXPECT_EQ(true, threadPool2.Busy());
    EXPECT_EQ(numOfWorkItems, threadPool2.GetNumOfWorkItems());

    EXPECT_EQ(true, threadPool2.QueueWorkItem(workItemStr2));
    ++numOfWorkItems;
    EXPECT_EQ(true, threadPool2.Busy());
    EXPECT_EQ(numOfWorkItems, threadPool2.GetNumOfWorkItems());

	LOG4CXX_INFO(rootLogger, "test ended successfully");
}

TEST(threadPoolTest, checkStartAndStopFunctions)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    size_t numOfThreads = 2; //std::thread::hardware_concurrency();
    HeapLeakChecker heap_checker("test_threadPool");
    {
        ThreadPool<int> threadPool(numOfThreads, workerFuncSample<int>);

        // At first, the work items queue is empty, so the Busy method
        // should return false
        bool expectedRes = false;
        EXPECT_EQ(expectedRes, threadPool.Busy());
        EXPECT_EQ(0, threadPool.GetNumOfWorkItems());

        // Start the pool
        threadPool.Start();
        EXPECT_EQ(numOfThreads, threadPool.GetThreadsCapacity());
        EXPECT_EQ(numOfThreads, threadPool.GetNumOfThreads());
        threadPool.Stop();
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");

	LOG4CXX_INFO(rootLogger, "test ended successfully");
}

TEST(threadPoolTest, createThreadPoolWithTwoThreadsAndStopThemAfterSometime)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    size_t numOfThreads = 2;
    LOG4CXX_INFO(rootLogger, "the MAIN thread that runs the unit test function is:" << std::this_thread::get_id());
    HeapLeakChecker heap_checker("test_threadPool");
    {
        ThreadPool<int> threadPool(numOfThreads, workerFuncSample<int>);
        LOG4CXX_INFO(rootLogger, "created thread pool with:" << numOfThreads << " threads");

        // At first, the work items queue is empty, so the Busy method
        // should return false
        bool expectedRes = false;
        EXPECT_EQ(expectedRes, threadPool.Busy());
        EXPECT_EQ(0, threadPool.GetNumOfWorkItems());

        // Start the pool
        threadPool.Start();
        EXPECT_EQ(numOfThreads, threadPool.GetThreadsCapacity());
        EXPECT_EQ(numOfThreads, threadPool.GetNumOfThreads());
        std::this_thread::sleep_for(std::chrono::seconds(1));
        threadPool.Stop();
    } 
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
}

TEST(threadPoolTest, createThreadPoolWithTwoThreadsAddWorkItemAndStopThemAfterSometime)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    size_t numOfThreads = 2;
    HeapLeakChecker heap_checker("test_threadPool");
    {
        ThreadPool<int> threadPool(numOfThreads, workerFuncSample<int>);

        // At first, the work items queue is empty, so the Busy method
        // should return false
        bool expectedRes = false;
        EXPECT_EQ(expectedRes, threadPool.Busy());
        EXPECT_EQ(0, threadPool.GetNumOfWorkItems());

        // Start the pool
        threadPool.Start();
        EXPECT_EQ(numOfThreads, threadPool.GetThreadsCapacity());
        EXPECT_EQ(numOfThreads, threadPool.GetNumOfThreads());

        // Add one work item
        EXPECT_EQ(true, threadPool.QueueWorkItem(17));
        // Note: It is not possible to test here the size of the work item queue
        // because by the time we reach here, the work item might be "poped-out"
        // from the queue

        threadPool.Stop();
    } 
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
}

TEST(threadPoolTest, addWorkItemBeforeThreadPoolIsStarted)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    ThreadPool<int> threadPool(std::thread::hardware_concurrency(), workerFuncSample<int>);
    size_t numOfWorkItems = 0;

    int workItem1 = 1;
    EXPECT_EQ(true, threadPool.QueueWorkItem(workItem1));
    ++numOfWorkItems;
    EXPECT_EQ(true, threadPool.Busy());
    EXPECT_EQ(numOfWorkItems, threadPool.GetNumOfWorkItems());

    threadPool.Start();
    int workItem2 = 2;
    EXPECT_EQ(true, threadPool.QueueWorkItem(workItem2));
    threadPool.Stop();
}

TEST(threadPoolTest, addWorkItemAfterThreadPoolIsStopped)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    HeapLeakChecker heap_checker("test_threadPool");
    {
        ThreadPool<int> threadPool(std::thread::hardware_concurrency(), workerFuncSample<int>);

        LOG4CXX_INFO(rootLogger, "about to START the thread pool");
        threadPool.Start();

        LOG4CXX_INFO(rootLogger, "about to STOP the thread pool");
        threadPool.Stop();

        LOG4CXX_INFO(rootLogger, "about to add work item to the thread pool");

        int workItem1 = 1;
        EXPECT_EQ(false, threadPool.QueueWorkItem(workItem1));
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
}
