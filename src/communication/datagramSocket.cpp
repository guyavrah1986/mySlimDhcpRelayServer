#include <log4cxx/logger.h>
#include <sys/socket.h> // for SOCK_DGRAM

#include "include/datagramSocket.h"

using namespace std;

DatagramSocket::DatagramSocket(int protocol) 
    : SocketBase(protocol)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "created objec with protocol:" << m_protocol);
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
