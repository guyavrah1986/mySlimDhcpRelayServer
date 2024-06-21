#include <fcntl.h>						// for fcntl
#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking
#include <sys/socket.h> 				// for SOCK_DGRAM

#include "../communication/include/datagramSocket.h"
#include "../infra/include/logger.h"

TEST(datagrameSocketTest, createSingleDatagramSocketObject)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
	HeapLeakChecker heap_checker("createSingleDatagramSocketObject");
    {
		int protocol = 1;
		unsigned int port = 5001;
		DatagramSocket testSocket(protocol, port);
		EXPECT_EQ(SOCK_DGRAM, testSocket.GetSocketType());
		LOG4CXX_INFO(rootLogger,"created DatagramSocket on the stack");

		// Try to copy/assgin operator the object - should not compile
		//DatagramSocket testSocket2(testSocket);
		//DatagramSocket testSocket2(protocol);
		//testSocket = testSocket2;
    }

    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	LOG4CXX_INFO(rootLogger,"socketTest::createSingleDatagramSocketObject - end");
}

TEST(datagrameSocketTest, createSocketOnDatagramSocketObjectAndThenCloseIt)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
	int socketDescriptor;
	HeapLeakChecker heap_checker("createSocketOnDatagramSocketObjectAndThenCloseIt");
    {
		int protocol = 1;
		unsigned int port = 5000;
		DatagramSocket testSocket(protocol, port);
		EXPECT_EQ(SOCK_DGRAM, testSocket.GetSocketType());

		// Create the socket:
		bool ret = testSocket.CreateSocket();
		EXPECT_EQ(true, ret);

		// Keep for later verification
		socketDescriptor = testSocket.GetSocketDescriptor();
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");

	// Make sure that the dtor of the tested object indeed "released"
	// the socket from the OS: Note that in real production environment
	// this check is NOT relevant, because when a socket descriptor with
	// some value is deleted (removed), it can be the case that another
	// socket that is created just afterwards, will get the same socket
	// descriptor, thus causing this check to be invalid!
	int ret = fcntl(socketDescriptor, F_GETFD) != -1 || errno != EBADF;
	EXPECT_EQ(0, ret);

	LOG4CXX_INFO(rootLogger,"socketTest::createSockeOnDatagramSocketObjectAndThenCloseIt - end");
}

TEST(datagrameSocketTest, createSocketThenBindItAndFinallyCloseIt)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
	int socketDescriptor;
	HeapLeakChecker heap_checker("createSocketThenBindItAndFinallyCloseIt");
    {
		int protocol = 1;
		unsigned int port = 5000;
		DatagramSocket testSocket(protocol, port);
		EXPECT_EQ(SOCK_DGRAM, testSocket.GetSocketType());

		// Create the socket:
		bool ret = testSocket.CreateSocket();
		EXPECT_EQ(true, ret);

		// Bind the socket. 
		// NOTE: In unit test environment, it is only relevant to check
		// this test when the socket is either "binded" to any interface
		// on the system OR to the loopback interface!
		ret = testSocket.BindSocket();
		EXPECT_EQ(true, ret);

		// Keep for later verification
		socketDescriptor = testSocket.GetSocketDescriptor();
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");

	// Make sure that the dtor of the tested object indeed "released"
	// the socket from the OS: Note that in real production environment
	// this check is NOT relevant, because when a socket descriptor with
	// some value is deleted (removed), it can be the case that another
	// socket that is created just afterwards, will get the same socket
	// descriptor, thus causing this check to be invalid!
	int ret = fcntl(socketDescriptor, F_GETFD) != -1 || errno != EBADF;
	EXPECT_EQ(0, ret);

	LOG4CXX_INFO(rootLogger,"socketTest::createSockeOnDatagramSocketObjectAndThenCloseIt - end");
}

