#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking
#include <sys/socket.h> 				// for SOCK_DGRAM

#include "../infra/include/logger.h"
#include "../communication/include/datagramSocket.h"

TEST(datagrameSocketTest, createSingleDatagramSocketObject)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
	HeapLeakChecker heap_checker("createSingleDatagramSocketObject");
    {
		int protocol = 1;
		DatagramSocket testSocket(protocol);
		EXPECT_EQ(SOCK_DGRAM, testSocket.GetSocketType());

		// Try to copy/assgin operator the object - should not compile
		//DatagramSocket testSocket2(testSocket);
		//DatagramSocket testSocket2(protocol);
		//testSocket = testSocket2;

		LOG4CXX_INFO(rootLogger,"created DatagramSocket on the stack");
    }

    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	LOG4CXX_INFO(rootLogger,"socketTest::createSingleDatagramSocketObject - end");
}
