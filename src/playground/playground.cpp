#include <iostream>
#include <unordered_map>

#include "include/playground.h"

using namespace std;

void runPlaygroundFunc(int argc, char** argv)
{
	string funcName = "runPlaygroundFunc - ";
    cout << funcName + "start" << endl;

    // initialize the dictionary of functions:
    typedef void (*funcPointer)(int, char**);
    unordered_map<string, funcPointer> funcDict;
      
    // Add functions to the dictionary
    funcDict["cpp11ThreadExample"] = &cpp11ThreadExample;

    // extract the 2nd argument which indicates the function to run:
    string funcToRunName = string(argv[2]);
    auto it = funcDict.find(funcToRunName);
    if (nullptr == it)
    {
        cout << funcName + "got an invalid name of playground function to run" << endl;
        return;
    }

    cout << funcName + "about to run function:" << funcToRunName << endl;
    (*it->second)(argc, argv);
    cout << funcName + "back from function:" << funcToRunName << endl;
    cout << funcName + "end" << endl;
}

void cpp11ThreadExample(int argc, char** argv)
{
    string funcName = "cpp11ThreadExample - ";
    cout << funcName + "START" << endl;

    cout << funcName + "END" << endl;
}