#include "console_logger.h"
#include "diagnostic_manager.h"
#include "mock_logger.h"

#include <cassert>
#include <iostream>

int main()
{
    // Production usage
    ConsoleLogger consoleLogger;

    DiagnosticManager manager(consoleLogger);
    manager.reportError();

    // Unit test using a mock dependency
    MockLogger mockLogger;

    DiagnosticManager testManager(mockLogger);
    testManager.reportError();

    assert(mockLogger.messages().size() == 1);
    assert(mockLogger.messages()[0] ==
           "ECU communication failure");

    std::cout << "Dependency Injection test passed\n";

    return 0;
}