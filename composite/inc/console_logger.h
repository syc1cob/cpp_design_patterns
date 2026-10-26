#pragma once
#include "ilogger.h"

////////////////////////////////////////////////////////////////////////////////
//
// Leaf 1
//
////////////////////////////////////////////////////////////////////////////////

class ConsoleLogger : public ILogger
{
public:

    void LogInfo(const std::string& message) override
    {
        std::cout
            << "[Console] "
            << message
            << '\n';
    }
};

