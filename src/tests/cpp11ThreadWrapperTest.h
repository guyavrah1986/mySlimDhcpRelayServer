#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking
#include <log4cxx/logger.h>
#include <vector>
#include <thread>

#include "../infra/include/posixCpp11ThreadWrapper.h"

TEST(posixCpp11ThreadWrapperTest, createSingleThreadOnTheStack)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to create single posixCpp11ThreadWrapperTest object and check for leaks");

	HeapLeakChecker heap_checker("test_posixCpp11ThreadWrapper");
    {
	    std::thread sampleThread;
		Cpp11ThreadWrapper::RAIIAction action;
		PosixCpp11ThreadWrapper sampleWrappedThread(std::move(sampleThread), action);

		// Try to copy it - should not compile!
		//PosixCpp11ThreadWrapper sampleWrappedThreadCopy1 = sampleWrappedThread;
		//PosixCpp11ThreadWrapper sampleWrappedThreadCopy2(sampleWrappedThread);

    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	
	LOG4CXX_INFO(rootLogger, "test ended successfully");
}

void dummyFuncToRun(int num)
{
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "got num:" << num);
}

TEST(posixCpp11ThreadWrapperTest, createSingleThreadAndRunTillCompletionJoin)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to create single posixCpp11ThreadWrapperTest run its function and join it");

	HeapLeakChecker heap_checker("test_posixCpp11ThreadWrapper");
    {
		PosixCpp11ThreadWrapper sampleWrappedThread(std::move(std::thread(dummyFuncToRun, 17)), &std::thread::join);
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	
	LOG4CXX_INFO(rootLogger, "thread ran its function and was joined successfully");
}

TEST(posixCpp11ThreadWrapperTest, createSingleThreadMoveItThenRunTillCompletionJoin)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to create single posixCpp11ThreadWrapperTest run its function and join it");

	HeapLeakChecker heap_checker("test_posixCpp11ThreadWrapper");
    {
		PosixCpp11ThreadWrapper sampleWrappedThread(std::move(std::thread(dummyFuncToRun, 17)), &std::thread::join);
		std::vector<PosixCpp11ThreadWrapper> threadsVec;
		threadsVec.emplace_back(std::move(sampleWrappedThread));
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	
	LOG4CXX_INFO(rootLogger, "thread ran its function and was joined successfully");
}