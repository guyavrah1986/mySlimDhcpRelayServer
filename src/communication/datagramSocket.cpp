#include <cstring>          // for memset
#include <log4cxx/logger.h>
#include <sys/socket.h>     // for SOCK_DGRAM

#include "include/datagramSocket.h"

using namespace std;

DatagramSocket::DatagramSocket( unsigned int port, const string& ipAddressToBind) 
    : SocketBase(port, ipAddressToBind)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_INFO(rootLogger, "created object with protocol:" << this->GetSocketDomain()
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

bool DatagramSocket::ReciveData(RecivedPaylodBase& payload)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    memset(reinterpret_cast<void*>(&m_lastRecivedAddress), 0, sizeof(m_lastRecivedAddress));
    int readBytes = recvfrom(this->m_socketDescriptor, payload.m_buff, payload.m_buffMaxLen,
                             payload.m_flags, (struct sockaddr *)&m_lastRecivedAddress.m_origSenderAddr, (socklen_t*)&m_lastRecivedAddress.m_origSenderAddrlen);

    payload.m_numBytesRead = readBytes;
    bool readSuccessfully = false;
    if (readBytes < 0)
    {
        // Error has occured, retirve more info from perror
    }
    else if (0 == readBytes)
    {
        // No bytes were read, but it does not neccessarly mean
        // that an error indeed occur
        // TODO: decide how to treat this case
    }
    else
    {
        LOG4CXX_DEBUG(rootLogger, "successfully read:" << readBytes << " bytes");
        readSuccessfully = true;
    }
    
    return readSuccessfully;
}

