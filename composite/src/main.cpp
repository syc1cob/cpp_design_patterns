// composite_pattern_example.cpp
//
// Composite Pattern
//
// Real-world example:
// One logger fans out log requests to multiple logging backends,
// similar to ara::log / DLT OutputAdapter.
//
// Compile:
// g++ -std=c++17 main.cpp -o composite
//

#include <iostream>
#include "console_logger.h"
#include "file_logger.h"
#include "remote_logger.h"
#include "output_adapter.h"

// Client code
// Depends only on ILogger, not concrete implementations.
void Application(ILogger& logger)
{
    logger.LogInfo("Vehicle Speed = 120 km/h");
}


////////////////////////////////////////////////////////////////////////////////
//
// Main
//
////////////////////////////////////////////////////////////////////////////////

int main()
{
    OutputAdapter logger;

    logger.Add(
        std::make_unique<ConsoleLogger>());

    logger.Add(
        std::make_unique<FileLogger>("vehicle.log"));

    logger.Add(
        std::make_unique<RemoteLogger>(
            "tcp://192.168.0.10:3490"));

    std::cout
        << "========== All Outputs Enabled ==========\n";

    Application(logger);

    logger.RemoveAll();

    logger.Add(
        std::make_unique<ConsoleLogger>());

    std::cout
        << "\n========== Console Only ==========\n";

    Application(logger);

    return 0;
}
