#include <thread> 						// applicble since C++11
#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking
#include <log4cxx/logger.h>

#include "../infra/include/cpp11ThreadWrapper.h"

TEST(cpp11ThreadWrapperTest, createSingleThreadAndRunTillCompletion)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to create single cpp11ThreadWrapper object \
		and check for leaks");
	HeapLeakChecker heap_checker("test_singleCpp11ThreadWrapperTest");
    {
	    std::thread sampleThread;
		cpp11ThreadWrapper::RAIIAction action;
		cpp11ThreadWrapper sampleWrappedThread(std::move(sampleThread), action);
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	LOG4CXX_INFO(rootLogger, "test ended successfully");
}