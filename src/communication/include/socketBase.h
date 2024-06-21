#pragma once

class SocketBase
{
public:
    SocketBase(int protocol, unsigned int port, const std::string& ipAddressToBind);
    virtual ~SocketBase();

    // Copy semantics - disabled:
    // =========================
    SocketBase(const SocketBase& other) = delete;
    SocketBase& operator=(const SocketBase& rhs) = delete;
    
    // Abstract interface:
    // ==================
    virtual int GetSocketType() const = 0;

    // Common capabilities:
    // ====================
    bool CreateSocket();  
    bool BindSocket();

    // Getters & setters:
    // ==================
    int GetSocketDescriptor() const;

protected:
    int m_protocol;
    int m_socketDescriptor;
    unsigned int m_port;
    uint32_t m_interfaceId;
    std::string m_ipAddrToBind;
};