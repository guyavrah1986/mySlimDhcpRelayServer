#pragma once

class SocketBase
{
public:
    SocketBase();
    virtual ~SocketBase();

    enum Family
    {
        TCP = 0,
        UDP,
        RAW
    };

    // Abstract interface:
    // ==================
    virtual bool CreateSocket() = 0;    
};