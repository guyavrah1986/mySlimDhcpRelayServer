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

	HeapLeakChecker heap_checker("test_posixCpp11ThreadWrapper");
    {
        ThreadPool threadPool(numOfThreads);
        EXPECT_EQ(threadsCapacity, threadPool.GetThreadsCapacity());
        EXPECT_EQ(0, threadPool.GetNumOfThreads());
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");

	LOG4CXX_INFO(rootLogger, "test ended successfully");
}