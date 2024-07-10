#include <iostream>
#include <gtest/gtest.h>

// Local include files for the different objects we wish to test
// Each header file listed here contains GTest unit tests for some objects
#include "../infra/include/logger.h"
#include "cpp11ThreadWrapperTest.h"
#include "testSocket.h"
#include "threadPoolTest.h"
#include "vrfTest.h"

using namespace std;

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);

	// The first paramter is the path to the logger configuration file
	const string unitTestLoggingConfigurationFileName = string(argv[1]);
	cout << "main - the logger configuration file is:" << unitTestLoggingConfigurationFileName << endl;

	// This line will configuer the root logger for the entire
	// application and/or playground flow
	log4cxx::PropertyConfigurator::configure(unitTestLoggingConfigurationFileName.c_str());
	auto unitTestLogger = log4cxx::Logger::getRootLogger();
	LOG4CXX_INFO(unitTestLogger, "main - about to start to run unit tests");
	int unitTestRetCode = RUN_ALL_TESTS();
	LOG4CXX_INFO(unitTestLogger, "main - END of unit tests");
	return unitTestRetCode;
}
