#include <iostream>
#include <unordered_map>
#include <thread>

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

    // create a new thread and assgin it some work to do
    int num = 15;
    cout << funcName + "initially, num is:" << num << endl;
    thread t1(&workerThreadFunc1, ref(num));

    // wait for the worker thread to finish
    cout << funcName + "waiting for worker thread to terminate" << endl;
    t1.join();
    cout << funcName + "after worker thread is done waiting, num is:" << num << endl;
    cout << funcName + "END" << endl;
}

void workerThreadFunc1(int& num)
{
    string funcName = "workerThreadFunc1 - ";
    cout << funcName + "start, got num:" << num << endl;
    num += 1;
    cout << funcName + "end" << endl;
}