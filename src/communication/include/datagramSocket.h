#pragma once

#include "socketBase.h"

class DatagramSocket : public SocketBase
{
public:
    DatagramSocket(int protocol, unsigned int port, const std::string& ipAddressToBind);
    virtual ~DatagramSocket();

    // Copy semantics - disabled:
    // =========================
    DatagramSocket(const DatagramSocket& other) = delete;
    DatagramSocket& operator=(const DatagramSocket& rhs) = delete;

    // Abstract interface:
    // ==================
    virtual int GetSocketType() const override;
};