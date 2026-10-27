#pragma once

#include "itransport.h"

#include <iostream>

class TcpTransport : public ITransport
{
public:
    void Send(const std::string& message) override
    {
        std::cout << "[TCP] Sending: " << message << '\n';
    }
};