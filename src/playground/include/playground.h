#pragma once


// Public functions
// ================
int runPlaygroundFunc(int argc, char** argv);

int cpp11StdThreadExample(int argc, char** argv);

int simpleSocketListeningThreadFunc(int argc, char** argv);

int simpleDatagramSocketExampleFunc(int argc, char** argv);

int posixCpp11StdThreadWrapperSetThreadPriority(int argc, char** argv);

int setThreadPriorityExample(int argc, char** argv);

int setThreadCpuAffinityExample(int argc, char** argv);

int threadPoolUsageExample(int argc, char** argv);

// Utilities functions
// ===================
void workerThreadFunc1(int socketNum);

int cpp11StdThreadWrapperSampleFunc(int num);

void runLoopFunc();

void f(int num);

void dummyLoopFunc(size_t desiredCpuNum);
