#pragma once

#include "ilogger.h"

#include <string>
#include <vector>

class MockLogger : public ILogger {
public:
    void log(const std::string& message) override
    {
        messages_.push_back(message);
    }

    const std::vector<std::string>& messages() const
    {
        return messages_;
    }

private:
    std::vector<std::string> messages_;
};