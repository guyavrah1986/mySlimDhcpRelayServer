#include <iostream>

#include "dataBaseManager/include/lib1.h"
#include "infra/include/cpp11ThreadWrapper.h"
#include "infra/include/logger.h"
#include "playground/include/playground.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "main - started" << endl;
	log4cxx::BasicConfigurator::configure();
	auto mainFuncLogger = log4cxx::Logger::getLogger("GlobalLogger.main");
    LOG4CXX_INFO(mainFuncLogger, "===started the logger===");

#ifdef ENABLE_TESTING
	if (string(argv[1]) == "-p")
	{
		runPlaygroundFunc(argc, argv);
		return 0;
	}
#endif

	LOG4CXX_INFO(mainFuncLogger, "main - running production code");
	cout << "main - end" << endl;
	return 0;
}
