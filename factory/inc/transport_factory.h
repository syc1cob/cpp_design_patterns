#pragma once

#include <memory>
#include "itransport.h"

enum class Protocol
{
    TCP,
    UDP
};

class TransportFactory
{
public:
    static std::unique_ptr<ITransport> Create(Protocol protocol);
};