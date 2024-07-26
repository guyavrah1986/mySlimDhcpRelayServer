/*
import my_module;
import PublicFunc;
*/
#include <iostream>

using namespace std;


void testFunc()
{
    string funcName = "testFunc - ";
    cout << funcName + "start" << endl;
    cout << funcName + "end" << endl;
}

int main(int argc, char** argv)
{
    cout << "main - start" << endl;
    testFunc();
    //PublicFunc(1.2);
    cout << "main - end" << endl;
    return 0;
}