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
    DgramOrigAddressIpv4 dgramIpv4AddressInfo;
    int readBytes = recvfrom(this->m_socketDescriptor, payload.m_buff, payload.m_buffMaxLen,
                             payload.m_flags, (struct sockaddr *)&dgramIpv4AddressInfo.m_origSenderAddr, (socklen_t*)&dgramIpv4AddressInfo.m_origSenderAddrlen);

    bool readSuccessfully = false;
    if (readBytes < 0)
    {
        // Error has occured, retirve more info from perror
    }
    else if (0 == readBytes)
    {
        // No bytes were read: 
        // TODO: decide how to treat this case
    }
    else
    {
        readSuccessfully = true;
    }
    
    return readSuccessfully;
}

