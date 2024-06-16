#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking
#include <log4cxx/logger.h>
#include <vector>

#include "../infra/include/posixCpp11ThreadWrapper.h"

void dummyFuncToRun(int num)
{
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "got num:" << num);
}

TEST(posixCpp11ThreadWrapperTest, createSingleThreadOnTheStack)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to create single PosixCpp11ThreadWrapper on the stack");
	HeapLeakChecker heap_checker("test_posixCpp11ThreadWrapper");
    {
		PosixCpp11ThreadWrapper sampleWrappedThread(std::move(std::thread(dummyFuncToRun, 17)), &std::thread::join);
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	
	LOG4CXX_INFO(rootLogger, "thread ran its function and was joined successfully");
}

TEST(posixCpp11ThreadWrapperTest, createSingleThreadMoveIntoVector)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to create single PosixCpp11ThreadWrapper and insert it into an std::vector");
	HeapLeakChecker heap_checker("test_posixCpp11ThreadWrapper");
    {
		PosixCpp11ThreadWrapper sampleWrappedThread(std::move(std::thread(dummyFuncToRun, 17)), &std::thread::join);
		std::vector<PosixCpp11ThreadWrapper> threadsVec;
		threadsVec.emplace_back(std::move(sampleWrappedThread));
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	
	LOG4CXX_INFO(rootLogger, "thread ran its function and was joined successfully");
}

TEST(posixCpp11ThreadWrapperTest, setCpuCoreNumberForAffinity)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to create single PosixCpp11ThreadWrapper and set its affinity");
	HeapLeakChecker heap_checker("test_posixCpp11ThreadWrapper");
    {
		PosixCpp11ThreadWrapper sampleWrappedThread(std::move(std::thread(dummyFuncToRun, 17)), &std::thread::join);
		unsigned int numOfCpuLogicalCores = std::thread::hardware_concurrency();
		LOG4CXX_INFO(rootLogger, "there are " << numOfCpuLogicalCores << " logical CPU cores");
		unsigned int numCoreToSet = numOfCpuLogicalCores + 1;
		EXPECT_EQ(false, sampleWrappedThread.SetAffinity(numCoreToSet));
		numCoreToSet = numOfCpuLogicalCores - 1;
		EXPECT_EQ(true, sampleWrappedThread.SetAffinity(numCoreToSet));
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");


	LOG4CXX_INFO(rootLogger, "thread ran its function and was joined successfully");
}
