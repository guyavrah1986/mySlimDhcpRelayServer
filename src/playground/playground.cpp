#include <arpa/inet.h>
#include <iostream>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/logger.h>
#include <stdint.h>
#include <sys/socket.h>
#include <thread>
#include <unordered_map>
#include <unistd.h>

#include "include/playground.h"
#include "../infra/include/posixCpp11ThreadWrapper.h"

using namespace std;

void runPlaygroundFunc(int argc, char** argv)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "about to run some public function");

    // initialize the dictionary of functions:
    typedef void (*funcPointer)(int, char**);
    unordered_map<string, funcPointer> funcDict;
      
    // Add functions to the dictionary
    funcDict["cpp11ThreadExample"] = &cpp11StdThreadExample;
    funcDict["cpp11StdThreadWrapperExample"] = &cpp11StdThreadWrapperExample;
    funcDict["simpleSocketListeningThreadFunc"] = &simpleSocketListeningThreadFunc;

    // extract the 3rd argument which indicates the function to run:
    string funcToRunName = string(argv[3]);
    auto it = funcDict.find(funcToRunName);
    if (nullptr == it)
    {
        LOG4CXX_ERROR(rootLogger, "got an invalid name of playground function to run:" + funcToRunName);
        return;
    }

    LOG4CXX_INFO(rootLogger, "about to run function:" + funcToRunName);
    (*it->second)(argc, argv);
    LOG4CXX_INFO(rootLogger, "back from function:" + funcToRunName);
}

void cpp11StdThreadExample(int argc, char** argv)
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

int cpp11StdThreadWrapperSampleFunc(int num)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    size_t threadId = hash<thread::id>{}(this_thread::get_id());
    LOG4CXX_INFO(rootLogger, "running thread:" << threadId << ", got num:" << num);
    return 0;
}

void cpp11StdThreadWrapperExample(int argc, char** argv)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "start of std::thread wrapper usage example");
    PosixCpp11ThreadWrapper sampleWrappedThread(std::move(thread(cpp11StdThreadWrapperSampleFunc, 1)), &thread::join);
    LOG4CXX_INFO(rootLogger, "end of std::thread wrapper usage example");
}

void workerThreadFunc1(int num)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "START of handler function, the socket got is:" << num);
    size_t threadId = hash<thread::id>{}(this_thread::get_id());
    LOG4CXX_INFO(rootLogger, "the thread ID is:" << threadId);

    // For debug, write the socket value allocated to this request
    // back to the client:
    string msgToClient = "The socket number allocated was:" + num;

    size_t msgLen = msgToClient.length();
    write(num, msgToClient.c_str(), msgLen);
    LOG4CXX_INFO(rootLogger, "END of handler function");
}

void simpleSocketListeningThreadFunc(int argc, char** argv)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "start");
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;

    // For debug - get the main thread ID
    size_t mainThreadId = hash<thread::id>{}(this_thread::get_id());

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == socket_desc)
    {
        LOG4CXX_ERROR(rootLogger, "Could not create socket, aborting");
        return;
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
        return;
    }

    LOG4CXX_INFO(rootLogger, "Socket was binded successfully");

    // Listen for incoming connection on this port
    int maxNumOfWaitingConnections = 3;
    listen(socket_desc, maxNumOfWaitingConnections);
    LOG4CXX_INFO(rootLogger, "Socket is now listening...");

    // for debug - remove afterwards
    /*
    LOG4CXX_INFO(rootLogger, "Press any key to continue");
    char cInput;
    cin >> cInput;
    */

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
        return;
    }

    LOG4CXX_INFO(rootLogger, "end");
}