#include <iostream>
#include <gtest/gtest.h>

// Local include files for the different objects we wish to test
// Each header file listed here contains GTest unit tests for some objects
#include "../infra/include/logger.h"
#include "cpp11ThreadWrapperTest.h"
#include "dataBaseManagerTest.h"

using namespace std;

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	cout << "main - START of unit tests" << endl;
	log4cxx::BasicConfigurator::configure();
	auto unitTestLogger = log4cxx::Logger::getLogger("GlobalLogger.main");
	LOG4CXX_INFO(unitTestLogger, "===started the logger for the unit tests===");
	int unitTestRetCode = RUN_ALL_TESTS();
	cout << "main - END of unit tests" << endl;
	return unitTestRetCode;
}
