#include <iostream>
#include <stdexcept>
#include <utility>
#include "output_adapter.h"

void OutputAdapter::Add(std::unique_ptr<ILogger> logger)
{
    if (!logger)
    {
        throw std::invalid_argument("Logger cannot be null");
    }

    loggers_.push_back(std::move(logger));
}

void OutputAdapter::RemoveAll()
{
    loggers_.clear();
}

void OutputAdapter::LogInfo(const std::string& message)
{
    std::cout << "\nOutputAdapter: Fan-out to "
              << loggers_.size()
              << " backend(s)\n";

    // Composite Pattern:
    // Delegate the same operation to every registered child.
    for (auto& logger : loggers_)
    {
        logger->LogInfo(message);
    }
}