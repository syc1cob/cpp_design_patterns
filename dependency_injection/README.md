# Dependency Injection in C++17

## Overview

**Dependency Injection (DI)** is a software design technique in which a class receives its dependencies from outside rather than creating them internally.

Dependency Injection helps achieve:

- Loose coupling between components.
- Better unit testability.
- Flexibility to replace implementations.
- Clear separation of responsibilities.
- Explicit dependency and lifetime management.

This project demonstrates Dependency Injection using an automotive **Diagnostic Manager** that depends on a logging interface.

The same `DiagnosticManager` can work with a production `ConsoleLogger` or a test `MockLogger` without modifying its implementation.

## 1. Problem Statement

Consider a `DiagnosticManager` that directly creates a concrete logger.

```cpp
class DiagnosticManager {
public:
    void reportError() {
        FileLogger logger;
        logger.log("ECU communication failure");
    }
};
```

This approach introduces several problems.

### Tight Coupling

`DiagnosticManager` directly depends on `FileLogger`.

Replacing the logger with another implementation requires modifying the diagnostic manager.

### Difficult Unit Testing

The diagnostic manager cannot easily use a mock logger to verify interactions.

Tests may depend on actual console, filesystem, or network operations.

### Violation of Separation of Responsibilities

The diagnostic manager is responsible for both diagnostic processing and constructing its logging dependency.

### Limited Flexibility

Different environments may require different logging implementations:

- Console logging during development.
- File or network logging in production.
- Mock logging during unit testing.

The diagnostic manager should not need modification for each environment.

## 2. Solution: Dependency Injection

Instead of constructing the logger internally, inject it through the constructor.

```cpp
class DiagnosticManager {
public:
    explicit DiagnosticManager(ILogger& logger)
        : logger_(logger)
    {
    }

private:
    ILogger& logger_;
};
```

The application creates the concrete logger and supplies it to `DiagnosticManager`.

```cpp
ConsoleLogger logger;
DiagnosticManager manager(logger);
```

The diagnostic manager depends only on the `ILogger` abstraction.

## 3. Architecture

```text
                 +----------------------+
                 |        main()        |
                 |   Composition Root   |
                 +----------------------+
                           |
                 Creates dependencies
                           |
             +-------------+-------------+
             |                           |
             v                           v
    +------------------+       +------------------+
    | DiagnosticManager|       |  ConsoleLogger   |
    +------------------+       +------------------+
    | ILogger& logger_ |       | log(message)     |
    +------------------+       +------------------+
             |                           |
             | depends on                | implements
             v                           v
                 +------------------+
                 |     ILogger      |
                 +------------------+
                 | log(message) = 0 |
                 +------------------+
                           ^
                           |
                     implements
                           |
                 +------------------+
                 |    MockLogger    |
                 +------------------+
                 | log(message)     |
                 | messages()       |
                 +------------------+
```

The composition root, `main()`, decides which concrete implementation to inject.

The diagnostic manager remains independent of that decision.

## 4. Project Structure

```text
dependency_injection/
├── inc/
│   ├── ilogger.h
│   ├── console_logger.h
│   ├── mock_logger.h
│   └── diagnostic_manager.h
├── src/
│   ├── console_logger.cpp
│   ├── diagnostic_manager.cpp
│   └── main.cpp
├── CMakeLists.txt
└── README.md
```

## 5. Components

| Component | Implementation | Responsibility |
|---|---|---|
| Abstraction | `ILogger` | Defines the logging interface |
| Concrete dependency | `ConsoleLogger` | Performs console logging |
| Test double | `MockLogger` | Records messages for verification |
| Consumer | `DiagnosticManager` | Performs diagnostic operations |
| Composition root | `main()` | Creates and injects dependencies |

## 6. Implementation

### 6.1 ILogger – Abstract Interface

**File:** `inc/ilogger.h`

```cpp
#pragma once

#include <string>

class ILogger {
public:
    virtual ~ILogger() = default;

    virtual void log(const std::string& message) = 0;
};
```

`ILogger` defines the behavior expected by `DiagnosticManager`.

It does not specify how messages are stored or transmitted.

### 6.2 ConsoleLogger – Concrete Implementation

**File:** `inc/console_logger.h`

```cpp
#pragma once

#include "ilogger.h"

class ConsoleLogger : public ILogger {
public:
    void log(const std::string& message) override;
};
```

**File:** `src/console_logger.cpp`

```cpp
#include "console_logger.h"

#include <iostream>

void ConsoleLogger::log(const std::string& message)
{
    std::cout << "[Console] " << message << '\n';
}
```

`ConsoleLogger` implements the logging interface using standard output.

### 6.3 DiagnosticManager – Dependency Consumer

**File:** `inc/diagnostic_manager.h`

```cpp
#pragma once

#include "ilogger.h"

class DiagnosticManager {
public:
    explicit DiagnosticManager(ILogger& logger);

    void reportError();

private:
    ILogger& logger_;
};
```

**File:** `src/diagnostic_manager.cpp`

```cpp
#include "diagnostic_manager.h"

DiagnosticManager::DiagnosticManager(ILogger& logger)
    : logger_(logger)
{
}

void DiagnosticManager::reportError()
{
    logger_.log("ECU communication failure");
}
```

The important point is:

```cpp
explicit DiagnosticManager(ILogger& logger);
```

The dependency is provided externally.

`DiagnosticManager` does not create or own the logger.

### 6.4 MockLogger – Test Implementation

**File:** `inc/mock_logger.h`

```cpp
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
```

`MockLogger` stores messages in memory instead of writing them to an external destination.

This allows tests to verify diagnostic behavior without relying on external resources.

Technically, this simple implementation is also commonly described as a *fake* or *spy*, because it records calls rather than using a mocking framework.

### 6.5 Client Code

**File:** `src/main.cpp`

```cpp
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

    // Test usage
    MockLogger mockLogger;

    DiagnosticManager testManager(mockLogger);
    testManager.reportError();

    assert(mockLogger.messages().size() == 1);
    assert(mockLogger.messages()[0] ==
           "