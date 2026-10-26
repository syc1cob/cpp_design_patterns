////////////////////////////////////////////////////////////////////////////////
//
// Leaf 3
//
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "ilogger.h"

class RemoteLogger : public ILogger
{
public:

    explicit RemoteLogger(std::string endpoint)
        : endpoint_(std::move(endpoint))
    {
    }

    void LogInfo(const std::string& message) override
    {
        // Normally sends via TCP / Shared Memory / SOME/IP etc.

        std::cout
            << "[Remote : "
            << endpoint_
            << "] "
            << message
            << '\n';
    }

private:

    std::string endpoint_;
};

