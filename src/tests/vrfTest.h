#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking
#include <log4cxx/logger.h>

#include "../managedObjects/include/vrf.h"

TEST(vrfTest, createSingleVrfOnTheStack)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to create single Vrf on the stack");
	HeapLeakChecker heap_checker("test_createSingleVrfOnTheStack");
    {
		std::vector<std::string> interfacesList;
		std::string interfaceAddr("192.168.1.2");
		interfacesList.push_back(interfaceAddr);
		Vrf vrf(interfacesList);
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
}

TEST(vrfTest, setInterfacesOfVrfWithNoInterfaces)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to create single Vrf on the stack");
	HeapLeakChecker heap_checker("test_createSingleVrfOnTheStack");
    {
		std::vector<std::string> interfacesList;
		Vrf vrf(interfacesList);
		Result res = vrf.SetInterfaces();
		EXPECT_EQ(ErrorCode::UTILS_ERROR_CODE_NO_INTERFACE, res.GetErrorCode());
	    LOG4CXX_INFO(rootLogger, "error reason is:" << res.GetErrorCodeMessage());
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
}
