#include <iostream>

#include "infra/include/cpp11ThreadWrapper.h"
#include "infra/include/logger.h"
#include "playground/include/playground.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "main - started" << endl;

	// The first paramter is the path to the logger configuration file
	const string appLoggingConfigurationFileName = string(argv[1]);
	cout << "main - the logger configuration file is:" << appLoggingConfigurationFileName << endl;

	// This line will configuer the root logger for the entire
	// application and/or playground flow
	log4cxx::PropertyConfigurator::configure(appLoggingConfigurationFileName.c_str());
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "===started the logger===");

#ifdef ENABLE_TESTING
	if (string(argv[2]) == "-p")
	{
		runPlaygroundFunc(argc, argv);
		return 0;
	}
#endif

	LOG4CXX_INFO(rootLogger, "===end of main program, return 0===");
	return 0;
}
