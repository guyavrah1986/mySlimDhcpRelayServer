#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking
#include <log4cxx/logger.h>

#include "../infra/include/threadPool.h"

TEST(threadPoolTest, createSingleThreadPoolWithValidNumOfThreads)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    uint32_t numOfThreads = 2;
    LOG4CXX_INFO(rootLogger, "about to create a thread pool with:" << numOfThreads << " threads");
    unsigned int numOfHwCon = std::thread::hardware_concurrency();
    LOG4CXX_INFO(rootLogger, "numOfHwCon is:" << numOfHwCon);
    ThreadPool tp(numOfThreads);
    
    /*
	HeapLeakChecker heap_checker("test_posixCpp11ThreadWrapper");
    {
	    std::thread sampleThread;
		Cpp11ThreadWrapper::RAIIAction action;
		PosixCpp11ThreadWrapper sampleWrappedThread(std::move(sampleThread), action);
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	*/
	LOG4CXX_INFO(rootLogger, "test ended successfully");
}