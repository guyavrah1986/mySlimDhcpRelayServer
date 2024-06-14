#include <arpa/inet.h>
#include <chrono>
#include <cstring>      // for stderror()
# include <iostream>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/logger.h>
#include <stdint.h>
#include <sys/socket.h>
#include <unordered_map>
#include <unistd.h>

#include "include/playground.h"
#include "../infra/include/posixCpp11ThreadWrapper.h"
#include "../infra/include/threadPool.h"

using namespace std;

int runPlaygroundFunc(int argc, char** argv)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to run some public function, got:" << argc
        << " command line arguments");

    // initialize the dictionary of functions:
    typedef int (*funcPointer)(int, char**);
    unordered_map<string, funcPointer> funcDict;
      
    // Add functions to the dictionary
    // -------------------------------
    funcDict["cpp11StdThreadExample"] = &cpp11StdThreadExample;
    funcDict["threadPoolUsageExample"] = &threadPoolUsageExample;
    funcDict["setThreadPriorityExample"] = &setThreadPriorityExample;
    funcDict["setThreadCpuAffinityExample"] = &setThreadCpuAffinityExample;
    funcDict["simpleSocketListeningThreadFunc"] = &simpleSocketListeningThreadFunc;
    funcDict["posixCpp11StdThreadWrapperSetThreadPriority"] = &posixCpp11StdThreadWrapperSetThreadPriority;
    
    // extract the 3rd argument which indicates the function to run:
    string funcToRunName = string(argv[3]);
    auto it = funcDict.find(funcToRunName);
    if (nullptr == it)
    {
        LOG4CXX_ERROR(rootLogger, "got an invalid name of playground function to run:" + funcToRunName);
        return 1;
    }

    LOG4CXX_INFO(rootLogger, "about to run function:" + funcToRunName);
    int retCode = (*it->second)(argc, argv);
    LOG4CXX_INFO(rootLogger, "back from function:" + funcToRunName);
    return retCode;
}

int cpp11StdThreadExample(int argc, char** argv)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "got:" << argc << " command line arguments");
    if (nullptr == argv)
    {
        LOG4CXX_ERROR(rootLogger, "got null pointer");
        return -1;
    }

    // create a new thread and assgin it some work to do
    int num = 15;
    LOG4CXX_INFO(rootLogger, "initially, num is:" << num);
    thread t1(&workerThreadFunc1, ref(num));

    // wait for the worker thread to finish
    LOG4CXX_INFO(rootLogger, "waiting for worker thread to terminate");
    t1.join();
    LOG4CXX_INFO(rootLogger,"after worker thread is done waiting, num is:" << num);
    return 0;
}

int posixCpp11StdThreadWrapperSetThreadPriority(int argc, char** argv)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "start of std::thread wrapper usage example");
    LOG4CXX_INFO(rootLogger, "got:" << argc << " command line arguments");
    if (nullptr == argv)
    {
        LOG4CXX_ERROR(rootLogger, "got null pointer");
        return -1;
    }

    PosixCpp11ThreadWrapper sampleWrappedThread(std::move(thread(runLoopFunc)), &thread::join);
    LOG4CXX_INFO(rootLogger, "created and started the POSIX thread wrapper");
    int priorityToSet = 5;
    bool ret = sampleWrappedThread.SetScheduling(priorityToSet, SCHED_OTHER);
    if (false == ret)
    {
        LOG4CXX_ERROR(rootLogger, "was unable to set thread's priority, aborting");
        return 1;
    }

    LOG4CXX_INFO(rootLogger, "changed its priority to:" << priorityToSet);
    pthread_t workerThreadId = sampleWrappedThread.GetThread().native_handle();
    LOG4CXX_INFO(rootLogger, "check the priority of thread:" << workerThreadId);
    return 0;
}

int simpleSocketListeningThreadFunc(int argc, char** argv)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "start");
    LOG4CXX_INFO(rootLogger, "got:" << argc << " command line arguments");
    if (nullptr == argv)
    {
        LOG4CXX_ERROR(rootLogger, "got null pointer");
        return -1;
    }
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;

    // For debug - get the main thread ID
    size_t mainThreadId = hash<thread::id>{}(this_thread::get_id());

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == socket_desc)
    {
        LOG4CXX_ERROR(rootLogger, "Could not create socket, aborting");
        return 1;
    }
    
    LOG4CXX_INFO(rootLogger, "Socket created successfully");

    // Set the port number on which the server will listen on
    uint16_t portNum = 8888;

    //Prepare the sockaddr_in structure

    server.sin_family = AF_INET;            // IPv4
    server.sin_addr.s_addr = INADDR_ANY;    // Accepts incoming connections from all IPv4 
    server.sin_port = htons(portNum);

    // Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        LOG4CXX_ERROR(rootLogger, "bind failed, aborting");
        return 1;
    }

    LOG4CXX_INFO(rootLogger, "Socket was binded successfully");

    // Listen for incoming connection on this port
    int maxNumOfWaitingConnections = 3;
    listen(socket_desc, maxNumOfWaitingConnections);
    LOG4CXX_INFO(rootLogger, "Socket is now listening...");

    // for debug - remove afterwards
    
    //LOG4CXX_INFO(rootLogger, "Press any key to continue");
    //char cInput;
    //cin >> cInput;
    

    // This is where the server accepts incoming connections
    LOG4CXX_INFO(rootLogger, "about to start and accepting connections...");
    while((client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c)))
    {
        LOG4CXX_INFO(rootLogger, "Accepted connection on the main thread which is:" << mainThreadId);
        
        // Create a thread to handle the connection
        
		//Cpp11ThreadWrapper sampleWrappedThread(std::move(thread(workerThreadFunc1, client_sock)), &thread::join);
        
        LOG4CXX_INFO(rootLogger, "kicked off a worker thread for client socket:" << client_sock);
        LOG4CXX_INFO(rootLogger, "back to wait (sleep) on accept...");
    }
     
    if (client_sock < 0)
    {
        LOG4CXX_ERROR(rootLogger, "accept failed, aborting");
        return 1;
    }

    LOG4CXX_INFO(rootLogger, "end");
    return 0;
}

int setThreadPriorityExample(int argc, char** argv)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "start");
    LOG4CXX_INFO(rootLogger, "got:" << argc << " command line arguments");
    if (nullptr == argv)
    {
        LOG4CXX_ERROR(rootLogger, "got null pointer");
        return -1;
    }

    thread t1(f, 1), t2(f, 2);
    sched_param sch;
    int policy; 
    pthread_getschedparam(t1.native_handle(), &policy, &sch);
    sch.sched_priority = 20;
    if (pthread_setschedparam(t1.native_handle(), SCHED_FIFO, &sch))
    {
        LOG4CXX_ERROR(rootLogger, "Failed to setschedparam: " << strerror(errno));
        return 1;
    }
 
    t1.join(); t2.join();
    LOG4CXX_INFO(rootLogger, "both threads were joined successfully");
    return 0;
}

int setThreadCpuAffinityExample(int argc, char** argv)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "start");
    LOG4CXX_INFO(rootLogger, "got:" << argc << " command line arguments");
    if (nullptr == argv)
    {
        LOG4CXX_ERROR(rootLogger, "got null pointer");
        return -1;
    }

    // Get number of cores on the system:
    unsigned int numCores = std::thread::hardware_concurrency();
    LOG4CXX_INFO(rootLogger, "machine has:" << numCores << " cores");

    size_t desiredCpuNum = 1;
    PosixCpp11ThreadWrapper myThread(move(thread(dummyLoopFunc, desiredCpuNum)), &thread::join);
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(desiredCpuNum, &cpuset);
    int rc = pthread_setaffinity_np(myThread.GetThread().native_handle(),
                                    sizeof(cpu_set_t), &cpuset);
    if (0 != rc)
    {
        LOG4CXX_ERROR(rootLogger, "was unable to set thread affinity, aborting");
        return -1;
    }

    LOG4CXX_INFO(rootLogger, "successfully set thread" << myThread.GetThread().native_handle() << " on CPU:" << desiredCpuNum);
    return 0;
}

int threadPoolUsageExample(int argc, char** argv)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "start");
    LOG4CXX_INFO(rootLogger, "got:" << argc << " command line arguments");
    if (nullptr == argv)
    {
        LOG4CXX_ERROR(rootLogger, "got null pointer");
        return -1;
    }

    ThreadPool<int> threadPool(2, workerThreadFunc1);
    threadPool.Start();
    int workItem = 1;
    LOG4CXX_INFO(rootLogger, "about to add work item to the thread pool's queue");
    if (false == threadPool.QueueWorkItem(workItem))
    {
        LOG4CXX_ERROR(rootLogger, "was unable to add work item:" << workItem << ", aborting");
        return -1;
    }

    LOG4CXX_INFO(rootLogger, "started the pool and added single work item");
    workItem = 0;
    while (true)
    {
        LOG4CXX_INFO(rootLogger, "please enter your choice: 1 - add work item, 2 - terminate program");
        int input;
        cin >> input;
        switch (input)
        {
            case 1:
            {
                if (false == threadPool.QueueWorkItem(++workItem))
                {
                    threadPool.Stop();
                    LOG4CXX_ERROR(rootLogger, "was unable to add work item:" << workItem << ", aborting");
                    return -1;  
                }
                else
                {
                    LOG4CXX_INFO(rootLogger, "added work item:" << workItem);
                }
                break;
            }
            case 2:
            {
                LOG4CXX_INFO(rootLogger, "terminating program");
                threadPool.Stop();
                return 0;  
            }
            default:
            {
                LOG4CXX_INFO(rootLogger, "please insert 1 or 2");
                break;
            }
        }
    }

    return 0;
}

// ===================
// Utilities functions:
// ===================
void workerThreadFunc1(int num)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "START of handler function, the socket got is:" << num);
    size_t threadId = hash<thread::id>{}(this_thread::get_id());
    LOG4CXX_INFO(rootLogger, "thread ID is:" << threadId << " got num:" << num);

    // For debug, write the socket value allocated to this request
    // back to the client:
    //string msgToClient = "The socket number allocated was:" + num;

    //size_t msgLen = msgToClient.length();
    //write(num, msgToClient.c_str(), msgLen);
    LOG4CXX_INFO(rootLogger, "END of handler function");
}

void runLoopFunc()
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    unsigned int iteration = 0;
    while (true)
    {
        ++iteration;
        LOG4CXX_INFO(rootLogger, "within worker thread in iteration:" << ++iteration);
        sleep(5);
    }
}

int cpp11StdThreadWrapperSampleFunc(int num)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    size_t threadId = hash<thread::id>{}(this_thread::get_id());
    LOG4CXX_INFO(rootLogger, "running thread:" << threadId << ", got num:" << num);
    return 0;
}

mutex iomutex;
void f(int num)
{
    this_thread::sleep_for(chrono::seconds(1));
 
    sched_param sch;
    int policy; 
    pthread_getschedparam(pthread_self(), &policy, &sch);
    lock_guard<mutex> lk(iomutex);
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "Thread " << num << " is executing at priority:" 
                << sch.sched_priority);

}

void dummyLoopFunc(size_t desiredCpuNum)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    pthread_t threadId = hash<thread::id>{}(this_thread::get_id());
    LOG4CXX_INFO(rootLogger, "thread:" << threadId << " is desired to be ran on CPU:" << desiredCpuNum);
    LOG4CXX_INFO(rootLogger, "entering infine loop");
    while (true)
    {
        unsigned int numSecToSleep = 3;
        this_thread::sleep_for(chrono::seconds(numSecToSleep));
        LOG4CXX_INFO(rootLogger, "thread ID:" << threadId << " done sleeping for " << numSecToSleep << " seconds");
        int usedCpuNum = sched_getcpu();
        LOG4CXX_INFO(rootLogger, "thread ID:" << threadId << " is running on CPU:" << usedCpuNum);
    }
}
