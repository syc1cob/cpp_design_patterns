#pragma once

#include "ilogger.h"

class ConsoleLogger : public ILogger {
public:
    void log(const std::string& message) override;
};