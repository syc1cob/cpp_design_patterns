#include "console_logger.h"

#include <iostream>

void ConsoleLogger::log(const std::string& message)
{
    std::cout << "[Console] " << message << '\n';
}