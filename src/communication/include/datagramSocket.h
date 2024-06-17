#pragma once

#include "socketBase.h"

class DatagramSocket : public SocketBase
{
public:
    DatagramSocket();
    virtual ~DatagramSocket();


    // Abstract interface:
    // ==================
    virtual bool CreateSocket() override; 
};