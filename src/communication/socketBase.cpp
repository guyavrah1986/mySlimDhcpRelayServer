#include <arpa/inet.h>
#include <log4cxx/logger.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "include/socketBase.h"

using namespace std;

SocketBase::SocketBase(int protocol, unsigned int port)
    : m_protocol(protocol)
    , m_socketDescriptor(-1)
    , m_port(port)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "created objec with protocol:" << m_protocol);
}
    
SocketBase::~SocketBase()
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    if (m_socketDescriptor > 0)
    {
        LOG4CXX_DEBUG(rootLogger, "socket descriptor has a valid value, trying to close it");
        if (0 > close(m_socketDescriptor))
        {
            LOG4CXX_ERROR(rootLogger, "was unable to close socket descriptor:" << m_socketDescriptor);
        }

        LOG4CXX_INFO(rootLogger, "socket descriptor:" << m_socketDescriptor << " was closed successfully");
    }
    else
    {
        LOG4CXX_WARN(rootLogger, "socket descritor does NOT have a valid value (did not try to close it)");
    }
}

bool SocketBase::CreateSocket()
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    m_socketDescriptor = socket(AF_INET, this->GetSocketType(), 0);
    LOG4CXX_DEBUG(rootLogger, "socket descriptor is:" << m_socketDescriptor);
    if (0 > m_socketDescriptor)
    {
        return false;
    }

    return true;
}

bool SocketBase::BindSocket()
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    struct sockaddr_in serveraddr = {};
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(m_port);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(m_socketDescriptor, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        LOG4CXX_ERROR(rootLogger, "trying to bind socket:" << m_socketDescriptor 
            <<  " to port number:" << m_port << " failed");
        return false;
    }

    LOG4CXX_INFO(rootLogger, "binded socket:" << m_socketDescriptor << " with port:" << m_port
        << " to interface:");
    return true;
}

int SocketBase::GetSocketDescriptor() const
{
    return this->m_socketDescriptor;
}