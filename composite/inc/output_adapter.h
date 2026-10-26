#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ilogger.h"

// Composite: Implements the same interface as individual loggers.
// Owns multiple ILogger objects and delegates logging to all of them.

class OutputAdapter : public ILogger
{
public:
    OutputAdapter() = default;
    ~OutputAdapter() override = default;

    OutputAdapter(const OutputAdapter&) = delete;
    OutputAdapter& operator=(const OutputAdapter&) = delete;

    OutputAdapter(OutputAdapter&&) = default;
    OutputAdapter& operator=(OutputAdapter&&) = default;

    // Add a new logging backend.
    void Add(std::unique_ptr<ILogger> logger);

    // Remove all registered backends.
    void RemoveAll();

    // Composite operation: fan-out to all registered backends.
    void LogInfo(const std::string& message) override;

private:
    std::vector<std::unique_ptr<ILogger>> loggers_;
};