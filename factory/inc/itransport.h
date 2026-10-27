#pragma once

#include <string>

class ITransport
{
public:
    virtual ~ITransport() = default;

    virtual void Send(const std::string& message) = 0;
};