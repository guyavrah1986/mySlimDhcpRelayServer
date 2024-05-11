#pragma once

#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking
#include <log4cxx/logger.h>

#include "../infra/include/threadPool.h"

TEST(threadPoolTest, createSingleThreadPoolWithValidNumOfThreads)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    size_t numOfThreads = 2, threadsCapacity = 2;
    LOG4CXX_INFO(rootLogger, "about to create a thread pool with:" << numOfThreads << " threads");
    unsigned int numOfHwCon = std::thread::hardware_concurrency();
    LOG4CXX_INFO(rootLogger, "numOfHwCon is:" << numOfHwCon);
	HeapLeakChecker heap_checker("test_threadPool");
    {
        ThreadPool<int> threadPool(numOfThreads);
        EXPECT_EQ(threadsCapacity, threadPool.GetThreadsCapacity());
        EXPECT_EQ(0, threadPool.GetNumOfThreads());

        // Try to copy the ThreadPool object -- this should NOT compile
        // ThreadPool tp(threadPool);
        // ThreadPool tp(std::move(threadPool));
        // ThreadPool tp = threadPool;
        // ThreadPool tp(std::move(threadPool));
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");

	LOG4CXX_INFO(rootLogger, "test ended successfully");
}

TEST(threadPoolTest, createThreadPoolWithInValidNumOfThreads)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    unsigned int numOfHwCon = std::thread::hardware_concurrency();
    LOG4CXX_INFO(rootLogger, "numOfHwCon is:" << numOfHwCon);
    ThreadPool<int> threadPool1(numOfHwCon + 1);
    EXPECT_EQ(numOfHwCon, threadPool1.GetThreadsCapacity());
    EXPECT_EQ(0, threadPool1.GetNumOfThreads());

    ThreadPool<int> threadPool2(0);
    EXPECT_EQ(numOfHwCon, threadPool2.GetThreadsCapacity());
    EXPECT_EQ(0, threadPool2.GetNumOfThreads());

    ThreadPool<int> threadPool3(-1);
    EXPECT_EQ(numOfHwCon, threadPool3.GetThreadsCapacity());
    EXPECT_EQ(0, threadPool3.GetNumOfThreads());
	LOG4CXX_INFO(rootLogger, "test ended successfully");
}

TEST(threadPoolTest, checkBusyFunction)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    ThreadPool<int> threadPool(std::thread::hardware_concurrency());

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
    ThreadPool<int> threadPool1(std::thread::hardware_concurrency());

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

    ThreadPool<std::string> threadPool2(std::thread::hardware_concurrency());

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
    size_t numOfThreads = std::thread::hardware_concurrency();
    HeapLeakChecker heap_checker("test_threadPool");
    {
        ThreadPool<int> threadPool(numOfThreads);

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