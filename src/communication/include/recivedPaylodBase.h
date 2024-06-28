// ============================================================================
// DatagramSocket:
// This class represents (holds) the common part that will be recived
// by both STREAM and DGRAM socket types. 
// It is the role of this class derived classes to extend it accordsing
// to their needs. 
// In short, what it holds, is the actual payload (data) that was recived
//on some socket when a "message" (or just stream of bytes) arrived.
// Its implementation and desgin are derived from the following APIs:
// 1. int recv(int sockfd, void *buf, int len, int flags);                   --> SOCK_STREAS
// 2. int recvfrom(int sockfd, void *buf, int len,
//                  unsigned int flags, struct sockaddr *from, int *fromlen); --> SOCK_DGRAM
// ============================================================================
#pragma once

#include <arpa/inet.h>

class RecivedPaylodBase
{
public:
    RecivedPaylodBase(void* buff, unsigned int buffMaxLen, int flags);
    virtual ~RecivedPaylodBase();

    // Disable copy semantics
    RecivedPaylodBase(const RecivedPaylodBase& other) = delete;
    RecivedPaylodBase& operator=(const RecivedPaylodBase& rhs) = delete;

    void* m_buff;
    unsigned int m_buffMaxLen;
    int m_flags;
    int m_numBytesRead;
};

class DgramOrigAddressIpv4
{
public:
    DgramOrigAddressIpv4();
    virtual ~DgramOrigAddressIpv4();

    // Disable copy semantics
    DgramOrigAddressIpv4(const DgramOrigAddressIpv4& other) = delete;
    DgramOrigAddressIpv4& operator=(const DgramOrigAddressIpv4& rhs) = delete;

    struct sockaddr_storage m_origSenderAddr;
    int                m_origSenderAddrlen;
};