#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking
#include <log4cxx/logger.h>
#include <vector>

#include "../infra/include/posixCpp11ThreadWrapper.h"

void dummyFuncToRun(int num)
{
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "got num:" << num);
}

TEST(posixCpp11ThreadWrapperTest, createSingleThreadAndRunTillCompletionJoin)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to create single PosixCpp11ThreadWrapper run its function and join it");
	HeapLeakChecker heap_checker("test_posixCpp11ThreadWrapper");
    {
		PosixCpp11ThreadWrapper<pthread_t> sampleWrappedThread(std::move(std::thread(dummyFuncToRun, 17)), &std::thread::join);
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	
	LOG4CXX_INFO(rootLogger, "thread ran its function and was joined successfully");
}

TEST(posixCpp11ThreadWrapperTest, createSingleThreadMoveIntoVectorAndThenRunTillCompletionJoin)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to create single PosixCpp11ThreadWrapper run its function and join it");
	HeapLeakChecker heap_checker("test_posixCpp11ThreadWrapper");
    {
		PosixCpp11ThreadWrapper<pthread_t> sampleWrappedThread(std::move(std::thread(dummyFuncToRun, 17)), &std::thread::join);
		std::vector<PosixCpp11ThreadWrapper<pthread_t>> threadsVec;
		threadsVec.emplace_back(std::move(sampleWrappedThread));
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	
	LOG4CXX_INFO(rootLogger, "thread ran its function and was joined successfully");
}

