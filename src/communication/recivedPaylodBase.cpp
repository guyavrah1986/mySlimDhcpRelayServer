#include "include/recivedPaylodBase.h"

using namespace std;

RecivedPaylodBase::RecivedPaylodBase(void* buff, unsigned int buffMaxLen, int flags)
    : m_buff(buff)
    , m_buffMaxLen(buffMaxLen)
    , m_flags(flags)
{

}

RecivedPaylodBase::~RecivedPaylodBase()
{

}

DgramOrigAddressIpv4::DgramOrigAddressIpv4()
{
    
}

DgramOrigAddressIpv4::~DgramOrigAddressIpv4()
{

}