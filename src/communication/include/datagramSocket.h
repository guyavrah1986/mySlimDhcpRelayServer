// ============================================================================
// DatagramSocket:
// The role of this class is to represent a DGRAM_SOCK which is used mainly
// for UDP connection-less communication.
// NOTES:
// 1. In contrast to SOCK_STREAM socket, which the source and destination of
// it are "known" in advance, here it is not the case.
// For that, once a message is recived, the source address from which the 
// message arrived, is extracted and kept in the respective class members.
// If one wishes, at any later point of time to send data "back" to this sender
// it needs to get the address before it calls again the Recive method of this
// class (which will override the respective class member with the address of
// the newly arrived message)
// ============================================================================
#pragma once

#include "socketBase.h"

class DatagramSocket : public SocketBase
{
public:
    DatagramSocket(unsigned int port, const std::string& ipAddressToBind);
    virtual ~DatagramSocket();

    // Copy semantics - disabled:
    // =========================
    DatagramSocket(const DatagramSocket& other) = delete;
    DatagramSocket& operator=(const DatagramSocket& rhs) = delete;

    // Abstract interface:
    // ==================
    virtual int GetSocketType() const override;
    virtual bool ReciveData(RecivedPaylodBase& payload) override;
    virtual bool SendData(const void* msg, int len, unsigned int flags) override;

    // Getters & setters:
    // ==================
    void SetSocketProtocol();

private:
    void* getSenderAddress(const struct sockaddr *sa);

protected:
    /* Address of the host that the last message on this
    socket arrived from. In order to be able to reply to
    this host, user of this class should call the get 
    function to retrieve this value.*/
    DgramOrigAddressIpv4 m_lastRecivedAddress;
};