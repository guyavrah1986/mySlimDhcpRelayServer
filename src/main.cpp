#include <iostream>

#include "infra/include/cpp11ThreadWrapper.h"
#include "dataBaseManager/include/lib1.h"
#include "playground/include/playground.h"

using namespace std;


void runPlaygroundFunc()
{
	sampleFuncToTestBoostLogger();
}

int main(int argc, char** argv)
{
	cout << "main - started" << endl;
	runPlaygroundFunc();
	cout << "main - end" << endl;
	return 0;
}
