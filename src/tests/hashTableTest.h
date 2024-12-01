#pragma once

#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking
#include <log4cxx/logger.h>

#include "../utils/include/hashTable.h"

TEST(hashTableTest, createSingleHashTableAndDestroyIt)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    const size_t capacity = 16;
    LOG4CXX_INFO(rootLogger, "about to create a hash table with capacity:" << capacity);
    /*
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
    */
	LOG4CXX_INFO(rootLogger, "test ended successfully");
}

