#include <iostream>

#include "infra/include/cpp11ThreadWrapper.h"
#include "dataBaseManager/include/lib1.h"
#include "playground/include/playground.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "main - started" << endl;
	if (string(argv[1]) == "-p")
	{
		runPlaygroundFunc(argc, argv);
		return 0;
	}

	cout << "main - running production code" << endl;
	cout << "main - end" << endl;
	return 0;
}
