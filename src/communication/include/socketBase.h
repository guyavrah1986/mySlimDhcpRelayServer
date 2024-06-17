#pragma once

class SocketBase
{
public:
    SocketBase(int protocol);
    virtual ~SocketBase();

    // Copy semantics - disabled:
    // =========================
    SocketBase(const SocketBase& other) = delete;
    SocketBase& operator=(const SocketBase& rhs) = delete;
    
    // Public API:
    // ===========
    virtual bool CreateSocket();    
    
    // Abstract interface:
    // ==================
    virtual int GetSocketType() const = 0;

protected:
    int m_protocol;
    int m_socketDescriptor;
};