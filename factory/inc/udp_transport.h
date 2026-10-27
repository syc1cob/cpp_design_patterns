#pragma once

#include "itransport.h"

#include <iostream>

class UdpTransport : public ITransport
{
public:
    void Send(const std::string& message) override
    {
        std::cout << "[UDP] Sending: " << message << '\n';
    }
};