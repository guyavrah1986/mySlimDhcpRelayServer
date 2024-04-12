#include <thread> 						// applicble since C++11
#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking

#include "../infra/include/logger.h"
#include "../dataBaseManager/include/lib1.h"

TEST(dataBaseManagerTest, dataBaseManagerBasicest)
{ 
	auto dataBaseManagerTestLogger = log4cxx::Logger::getLogger("GlobalLogger.main");
	LOG4CXX_INFO(dataBaseManagerTestLogger, "===dataBaseManagerTest::dataBaseManagerBasicest - start===");
	ObjectLib1 testedObj;
	HeapLeakChecker heap_checker("dataBaseManagerBasicest");
    {
		LOG4CXX_INFO(dataBaseManagerTestLogger,"calling func1()");
		testedObj.func1();

		//LOG4CXX_INFO(dataBaseManagerTestLogger,"pi point to value of:" << *pi);
    }

    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	LOG4CXX_INFO(dataBaseManagerTestLogger,"dataBaseManagerTest::dataBaseManagerBasicest - end");
}
