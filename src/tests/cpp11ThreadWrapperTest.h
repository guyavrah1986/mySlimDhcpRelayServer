#include <thread> 						// applicble since C++11
#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking

#include "../infra/include/cpp11ThreadWrapper.h"

TEST(cpp11ThreadWrapperTest, createSingleThreadAndRunTillCompletion)
{ 
	std::cout << "cpp11ThreadWrapperTest::createSingleThreadAndRunTillCompletion - start" << std::endl;
	HeapLeakChecker heap_checker("test_singleCpp11ThreadWrapperTest");
    {
	    std::thread sampleThread;
		cpp11ThreadWrapper::RAIIAction action;
		cpp11ThreadWrapper sampleWrappedThread(std::move(sampleThread), action);
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	std::cout << "cpp11ThreadWrapperTest::createSingleThreadAndRunTillCompletion - end" << std::endl;
}
