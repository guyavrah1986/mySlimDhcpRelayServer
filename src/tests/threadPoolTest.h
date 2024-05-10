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
        ThreadPool threadPool(numOfThreads);
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
    ThreadPool threadPool1(numOfHwCon + 1);
    EXPECT_EQ(numOfHwCon, threadPool1.GetThreadsCapacity());
    EXPECT_EQ(0, threadPool1.GetNumOfThreads());

    ThreadPool threadPool2(0);
    EXPECT_EQ(numOfHwCon, threadPool2.GetThreadsCapacity());
    EXPECT_EQ(0, threadPool2.GetNumOfThreads());

    ThreadPool threadPool3(-1);
    EXPECT_EQ(numOfHwCon, threadPool3.GetThreadsCapacity());
    EXPECT_EQ(0, threadPool3.GetNumOfThreads());
	LOG4CXX_INFO(rootLogger, "test ended successfully");
}

TEST(threadPoolTest, checkBusyFunction)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    ThreadPool threadPool(std::thread::hardware_concurrency());

    // At first, the work items queue is empty, so the Busy method
    // should return false
    bool expectedRes = false;
    EXPECT_EQ(expectedRes, threadPool.Busy());
    EXPECT_EQ(0, threadPool.GetNumOfWorkItems());

	LOG4CXX_INFO(rootLogger, "test ended successfully");
}

TEST(threadPoolTest, checkQueueJobItemFunction)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    ThreadPool threadPool(std::thread::hardware_concurrency());

    // At first, the work items queue is empty, so the Busy method
    // should return false
    int workItem1 = 1;
    int workItem2 = 2;
    size_t numOfWorkItems = 0;
    EXPECT_EQ(true, threadPool.QueueJobItem(workItem1));
    ++numOfWorkItems;
    EXPECT_EQ(true, threadPool.Busy());
    EXPECT_EQ(numOfWorkItems, threadPool.GetNumOfWorkItems());

    EXPECT_EQ(true, threadPool.QueueJobItem(workItem2));
    ++numOfWorkItems;
    EXPECT_EQ(true, threadPool.Busy());
    EXPECT_EQ(numOfWorkItems, threadPool.GetNumOfWorkItems());

	LOG4CXX_INFO(rootLogger, "test ended successfully");
}