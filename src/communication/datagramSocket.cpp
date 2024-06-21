#include <log4cxx/logger.h>
#include <sys/socket.h>     // for SOCK_DGRAM

#include "include/datagramSocket.h"

using namespace std;

DatagramSocket::DatagramSocket(int protocol, unsigned int port) 
    : SocketBase(protocol, port)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "created object with protocol:" << m_protocol
        << " and port:" << m_port);
}
    
DatagramSocket::~DatagramSocket()
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "deleting object");
}

int DatagramSocket::GetSocketType() const
{
    return SOCK_DGRAM;
}
