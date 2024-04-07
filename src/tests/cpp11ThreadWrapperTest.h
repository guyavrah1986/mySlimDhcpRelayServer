#include <thread> // applicable since C++11

#include "../utilities/cpp11ThreadWrapper/include/cpp11ThreadWrapper.h"

void simpleWorkerFuncForThread()
{
	std::cout << "simpleWorkerFuncForThread - start" << std::endl;
}

TEST(cpp11ThreadWrapperTest, createSingleThreadAndRunTillCompletion)
{ 
	std::cout << "cpp11ThreadWrapperTest::createSingleThreadAndRunTillCompletion" << std::endl;
	std::thread sampleThread;
	cpp11ThreadWrapper::RAIIAction action;
	cpp11ThreadWrapper sampleWrappedThread(sampleThread, action);
}
