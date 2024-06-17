#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking

#include "../infra/include/logger.h"
#include "../communication/include/datagramSocket.h"

TEST(datagrameSocketTest, createSingleDatagramSocketObject)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
	HeapLeakChecker heap_checker("createSingleDatagramSocketObject");
    {
		DatagramSocket testSocket;
		LOG4CXX_INFO(rootLogger,"calling func1()");
    }

    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	LOG4CXX_INFO(rootLogger,"socketTest::createSingleSocketObject - end");
}
