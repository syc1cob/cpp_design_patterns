////////////////////////////////////////////////////////////////////////////////
//
// Leaf 2
//
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "ilogger.h"

class FileLogger : public ILogger
{
public:

    explicit FileLogger(std::string filename)
        : filename_(std::move(filename))
    {
    }

    void LogInfo(const std::string& message) override
    {
        // Normally writes to a file.
        // Simulated here using stdout.

        std::cout
            << "[File : "
            << filename_
            << "] "
            << message
            << '\n';
    }

private:

    std::string filename_;
};

