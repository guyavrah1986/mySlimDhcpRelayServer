#pragma once

#include "recivedPaylodBase.h"

class SocketBase
{
public:
    SocketBase(unsigned int port, const std::string& ipAddressToBind);
    virtual ~SocketBase();

    // Copy semantics - disabled:
    // =========================
    SocketBase(const SocketBase& other) = delete;
    SocketBase& operator=(const SocketBase& rhs) = delete;
    
    // Abstract interface:
    // ==================
    virtual int GetSocketType() const = 0;
    virtual bool ReciveData(RecivedPaylodBase& payload) = 0;
    //virtual bool SendData(const void *msg, int len, unsigned int flags) = 0;

    // Common capabilities:
    // ====================
    bool CreateSocket();  
    bool BindSocket();

    // Getters & setters:
    // ==================
    int GetSocketDescriptor() const;
    int GetSocketDomain() const;

protected:
    int m_socketDescriptor;
    unsigned int m_port;

    // TODO: make sure if needed
    uint32_t m_interfaceId;
    std::string m_ipAddrToBind;
};