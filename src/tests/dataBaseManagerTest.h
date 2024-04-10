#include <thread> 						// applicble since C++11
#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking

#include "../dataBaseManager/include/lib1.h"

TEST(dataBaseManagerTest, dataBaseManagerBasicest)
{ 
	std::cout << "dataBaseManagerTest::dataBaseManagerBasicest - start" << std::endl;
	ObjectLib1 testedObj;
	HeapLeakChecker heap_checker("dataBaseManagerBasicest");
    {
		std::cout << "dataBaseManagerTest::dataBaseManagerBasicest - calling func1()" << std::endl;
		testedObj.func1();
    }

    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	std::cout << "dataBaseManagerTest::dataBaseManagerBasicest - end" << std::endl;
}
