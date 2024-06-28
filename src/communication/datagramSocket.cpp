#include <log4cxx/logger.h>

#include "include/datagramSocket.h"

using namespace std;

DatagramSocket::DatagramSocket(unsigned int port, const string& ipAddressToBind) 
    : SocketBase(port, ipAddressToBind)
{
    SetSocketProtocol();
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

void DatagramSocket::SetSocketProtocol()
{
    this->m_protocol = IPPROTO_UDP;
}

bool DatagramSocket::ReciveData(RecivedPaylodBase& payload)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    int readBytes = recvfrom(this->m_socketDescriptor, payload.m_buff, payload.m_buffMaxLen,
                             payload.m_flags, (struct sockaddr *)&(m_lastRecivedAddress.m_origSenderAddr), (socklen_t*)&(m_lastRecivedAddress.m_origSenderAddrlen));

    //LOG4CXX_DEBUG(rootLogger, "the sin_family of the client is:" << m_lastRecivedAddress.m_origSenderAddr.sin_family);
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
        char senderAddress[INET_ADDRSTRLEN];
        inet_ntop(m_lastRecivedAddress.m_origSenderAddr.ss_family,
                  getSenderAddress((struct sockaddr *)&m_lastRecivedAddress.m_origSenderAddr),
                  senderAddress, sizeof(senderAddress));
        LOG4CXX_DEBUG(rootLogger, "got:" << readBytes << " bytes message from client:" << senderAddress);
        readSuccessfully = true;
    }
    
    return readSuccessfully;
}

bool DatagramSocket::SendData(const void* msg, int len, unsigned int flags)
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    if (nullptr == msg || len <= 0)
    {   
        LOG4CXX_ERROR(rootLogger, "invalid input to send");
        return false;
    }

    // const struct sockaddr *to, socklen_t tolen const_cast<void*>
    int sentBytes = sendto(this->GetSocketDescriptor(), msg, len, flags, (struct sockaddr *)(&(m_lastRecivedAddress.m_origSenderAddr)), sizeof(m_lastRecivedAddress.m_origSenderAddr)); 
    bool sentSuccessfully = false;
    if (sentBytes < 0)
    {
        // Error has occured, retirve more info from perror
    }
    else if (0 == sentBytes)
    {
        // No bytes were read, but it does not neccessarly mean
        // that an error indeed occur
        // TODO: decide how to treat this case
    }
    else
    {
        LOG4CXX_DEBUG(rootLogger, "successfully sent:" << sentBytes << " bytes");
        sentSuccessfully = true;
    }

    return sentSuccessfully;
}

void* DatagramSocket::getSenderAddress(const struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


