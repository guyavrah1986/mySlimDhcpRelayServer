#include <log4cxx/logger.h>
#include <sys/socket.h>
#include <unistd.h>

#include "include/socketBase.h"

using namespace std;

SocketBase::SocketBase(int protocol)
    : m_protocol(protocol)
    , m_socketDescriptor(-1)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "created objec with protocol:" << m_protocol);
}
    
SocketBase::~SocketBase()
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    if (m_socketDescriptor > 0)
    {
        LOG4CXX_INFO(rootLogger, "socket descritor has a valid value, trying to close it");

        if (0 > close(m_socketDescriptor))
        {
            LOG4CXX_ERROR(rootLogger, "was unable to close socket descriptor:" << m_socketDescriptor);
        }

    }

    LOG4CXX_WARN(rootLogger, "socket descritor does NOT have a valid value (did not try to close it)");
}

bool SocketBase::CreateSocket()
{
    int m_socketDescriptor = socket(AF_INET, this->GetSocketType(), 0);
    if (0 > m_socketDescriptor)
    {
        return false;
    }

    return true;
}