#include <thread> 						// applicble since C++11
#include <gperftools/heap-checker.h> 	// for tcmalloc heap checking

#include "../dataBaseManager/include/lib1.h"

TEST(dataBaseManagerTest, dataBaseManagerBasicest)
{ 
	std::cout << "dataBaseManagerTest::dataBaseManagerBasicest - start" << std::endl;
	HeapLeakChecker heap_checker("dataBaseManagerBasicest");
    {
		std::cout << "some stuff" << std::endl;
    }

    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
	std::cout << "dataBaseManagerTest::dataBaseManagerBasicest - end" << std::endl;
}
