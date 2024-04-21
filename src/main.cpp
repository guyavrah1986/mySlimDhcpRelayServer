#include <iostream>

#include "dataBaseManager/include/lib1.h"
#include "infra/include/cpp11ThreadWrapper.h"
#include "infra/include/logger.h"
#include "playground/include/playground.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "main - started" << endl;

	// This line will configuer the root logger for the entire
	// application and/or playground flow
	log4cxx::BasicConfigurator::configure();
	auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "===started the logger===");

#ifdef ENABLE_TESTING
	if (string(argv[1]) == "-p")
	{
		runPlaygroundFunc(argc, argv);
		return 0;
	}
#endif

	//LOG4CXX_INFO(rootLogger, "main - running production code");
	cout << "main - end" << endl;
	return 0;
}
