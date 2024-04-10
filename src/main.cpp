#include <iostream>

#include "infra/include/cpp11ThreadWrapper.h"
#include "dataBaseManager/include/lib1.h"

using namespace std;

void useLib1()
{
	ObjectLib1 lib1Obj;
	cout << "useLib1 - created an ObjectLib1 on the stack" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - started" << endl;
	thread sampleThread;
	cpp11ThreadWrapper::RAIIAction action;
	cpp11ThreadWrapper sampleWrappedThread(move(sampleThread), action);
	useLib1();
	cout << "main - end" << endl;
	return 0;
}
