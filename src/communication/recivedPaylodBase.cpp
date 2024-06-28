#include <log4cxx/logger.h>

#include "include/recivedPaylodBase.h"

using namespace std;

RecivedPaylodBase::RecivedPaylodBase(void* buff, unsigned int buffMaxLen, int flags)
    : m_buff(buff)
    , m_buffMaxLen(buffMaxLen)
    , m_flags(flags)
    , m_numBytesRead(-1)
{

}

RecivedPaylodBase::~RecivedPaylodBase()
{

}

DgramOrigAddressIpv4::DgramOrigAddressIpv4()
    : m_origSenderAddrlen(sizeof(m_origSenderAddr))
{
    auto rootLogger = log4cxx::Logger::getRootLogger();
    LOG4CXX_DEBUG(rootLogger, "m_origSenderAddrlen was set to:" << m_origSenderAddrlen);
}

DgramOrigAddressIpv4::~DgramOrigAddressIpv4()
{

}