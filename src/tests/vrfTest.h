#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking
#include <log4cxx/logger.h>

#include "../managedObjects/include/vrf.h"

TEST(vrfTest, createSingleVrfOnTheStack)
{ 
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to create single Vrf on the stack");
	HeapLeakChecker heap_checker("test_createSingleVrfOnTheStack");
    {
		Vrf("2eedfd");
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
}
