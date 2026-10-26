# Composite Design Pattern in C++17

## Overview

The **Composite Pattern** is a structural design pattern that allows clients to treat individual objects and collections of objects uniformly through a common interface.

This project demonstrates the Composite Pattern using a **logging fan-out architecture**, inspired by logging middleware such as Adaptive AUTOSAR DLT.

A single logging API call is forwarded to multiple configured logging backends without the application knowing how many backends exist.

## 1. Problem Statement

Consider an application that supports multiple logging destinations:

- Console
- File
- Remote logging server

Without the Composite Pattern, the application might explicitly invoke each backend:

```cpp
console.LogInfo("Vehicle started");
file.LogInfo("Vehicle started");
remote.LogInfo("Vehicle started");
```

This introduces several problems:

- Application code depends on concrete logging implementations.
- Adding a new logging destination requires modifying the application.
- Logging logic is duplicated.
- Managing multiple outputs becomes difficult.

## 2. Solution: Composite Pattern

Introduce an `OutputAdapter` that implements the same `ILogger` interface as the individual logging backends.

The application simply calls:

```cpp
logger.LogInfo("Vehicle Speed = 120 km/h");
```

Internally, `OutputAdapter` forwards the request to every registered backend.

### Architecture

```text
                     Application
                          |
                          | LogInfo()
                          v
                   +---------------+
                   | OutputAdapter |
                   |  (Composite)  |
                   +---------------+
                          |
             +------------+------------+
             |            |            |
             v            v            v
        ConsoleLogger  FileLogger  RemoteLogger
           (Leaf)       (Leaf)       (Leaf)
             |            |            |
             v            v            v
           stdout      Log File     Network
```

The application is unaware of the number and type of configured backends.

## 3. Project Structure

```text
composite/
├── inc/
│   ├── ilogger.h
│   ├── console_logger.h
│   ├── file_logger.h
│   ├── remote_logger.h
│   └── output_adapter.h
│
├── src/
│   ├── output_adapter.cpp
│   └── main.cpp
│
├── CMakeLists.txt
└── README.md
```

## 4. Composite Pattern Components

| Pattern Component | Implementation | Responsibility |
|---|---|---|
| Component | `ILogger` | Common logging interface |
| Leaf | `ConsoleLogger` | Logs to console |
| Leaf | `FileLogger` | Simulates file logging |
| Leaf | `RemoteLogger` | Simulates network logging |
| Composite | `OutputAdapter` | Holds and delegates to multiple loggers |
| Client | `Application()` | Uses the `ILogger` interface |

### Component Interface

```cpp
class ILogger
{
public:
    virtual ~ILogger() = default;

    virtual void LogInfo(const std::string& message) = 0;
};
```

Both the individual loggers and `OutputAdapter` implement this interface.

### Leaf Example

```cpp
class ConsoleLogger : public ILogger
{
public:
    void LogInfo(const std::string& message) override
    {
        std::cout << "[Console] " << message << '\n';
    }
};
```

### Composite Implementation

```cpp
class OutputAdapter : public ILogger
{
public:
    void Add(std::unique_ptr<ILogger> logger);

    void RemoveAll();

    void LogInfo(const std::string& message) override;

private:
    std::vector<std::unique_ptr<ILogger>> loggers_;
};
```

The key Composite operation is:

```cpp
void OutputAdapter::LogInfo(const std::string& message)
{
    for (auto& logger : loggers_)
    {
        logger->LogInfo(message);
    }
}
```

**One client call is delegated to all registered child objects.**

## 5. Client Code

```cpp
void Application(ILogger& logger)
{
    logger.LogInfo("Vehicle Speed = 120 km/h");
}
```

The application depends only on the abstraction `ILogger`.

It can work with a single logger:

```cpp
ConsoleLogger console;
Application(console);
```

Or a composite logger:

```cpp
OutputAdapter logger;

logger.Add(std::make_unique<ConsoleLogger>());
logger.Add(std::make_unique<FileLogger>("vehicle.log"));
logger.Add(std::make_unique<RemoteLogger>(
    "tcp://192.168.0.10:3490"));

Application(logger);
```

No changes to `Application()` are required.

## 6. Example Output

```text
=== All outputs enabled ===

OutputAdapter: Fan-out to 3 backend(s)
[Console] Vehicle Speed = 120 km/h
[File : vehicle.log] Vehicle Speed = 120 km/h
[Remote : tcp://192.168.0.10:3490] Vehicle Speed = 120 km/h

=== Console only ===

OutputAdapter: Fan-out to 1 backend(s)
[Console] Vehicle Speed = 120 km/h
```

**Note:** The file and remote backends are simulated using console output. This project focuses on demonstrating the Composite Pattern rather than implementing actual file I/O or network communication.

## 7. Runtime Configuration

The active logging backends can be changed at runtime.

```cpp
logger.RemoveAll();

logger.Add(std::make_unique<ConsoleLogger>());

Application(logger);
```

The application code remains unchanged.

The `OutputAdapter` owns its child loggers through `std::unique_ptr`, providing automatic resource management.

## 8. Real-World Mapping: Adaptive AUTOSAR DLT

This example is conceptually inspired by the fan-out architecture used in logging middleware.

| This Example | DLT-style Architecture |
|---|---|
| `ILogger` | Common output interface |
| `ConsoleLogger` | Console output backend |
| `FileLogger` | File output backend |
| `RemoteLogger` | Remote/DLT proxy backend |
| `OutputAdapter` | Output adapter |
| `LogInfo()` | Logging operation |
| `loggers_` | Collection of configured outputs |

A DLT-style adapter may forward an operation conditionally:

```cpp
for (auto& output : outputs)
{
    if (output->is_logstream_enabled(streamHandler))
    {
        output->log_uint32(streamHandler, value);
    }
}
```

Our simplified example forwards the operation to every registered backend:

```cpp
for (auto& logger : loggers_)
{
    logger->LogInfo(message);
}
```

Both demonstrate the same fundamental idea: **the caller interacts with one object while the adapter delegates operations to multiple child objects.**

For a strict Composite Pattern implementation, the composite and its children must expose the same component interface. This is explicitly demonstrated in this project through `ILogger`.

## 9. Composite vs Strategy Pattern

| Composite Pattern | Strategy Pattern |
|---|---|
| Structural design pattern | Behavioral design pattern |
| Represents individual objects and groups uniformly | Encapsulates interchangeable algorithms |
| Composite typically delegates to multiple children | Context typically uses one selected strategy |
| Supports nested object hierarchies | Supports runtime algorithm replacement |

Composite focuses on **part-whole relationships**, whereas Strategy focuses on **interchangeable behavior**.

## 10. Advantages

- Uniform interface for single and multiple objects
- Hides logging fan-out from application code
- Easy to add new backend implementations
- Supports runtime configuration
- Automatic ownership management using `std::unique_ptr`
- Supports nested composites
- Promotes loose coupling and extensibility

## 11. Limitations

- More abstraction than a simple direct logging call
- Failure handling across multiple backends requires additional design
- Concurrent logging requires synchronization
- A slow backend can delay other backends in this synchronous implementation
- Duplicate backend registration can produce duplicate log messages

These concerns are intentionally outside the scope of this learning example.

## 12. SOLID Principles

**Single Responsibility Principle (SRP)**

Each leaf handles its own logging behavior, while `OutputAdapter` manages delegation.

**Open/Closed Principle (OCP)**

New logging backends can be introduced without modifying the `OutputAdapter`.

**Liskov Substitution Principle (LSP)**

Any implementation of `ILogger`, including `OutputAdapter`, can be passed to `Application()`.

**Dependency Inversion Principle (DIP)**

The application depends on the `ILogger` abstraction rather than concrete backend classes.

## 13. Build and Run

### Prerequisites

- C++17-compatible compiler
- CMake 3.16 or later

### Build

From the `composite/` directory:

```bash
cmake -S . -B build
cmake --build build
```

### Run on Linux

```bash
./build/composite
```

### Run on Windows

For a Visual Studio multi-configuration build:

```powershell
.\build\Debug\composite.exe
```

## 14. Interview Questions

### Q1. What problem does the Composite Pattern solve?

It allows a client to treat an individual object and a collection of objects uniformly using the same interface.

### Q2. Why is `OutputAdapter` a Composite?

Because it implements `ILogger` while containing multiple child objects that also implement `ILogger`. It delegates logging operations to those children.

### Q3. Why use `std::unique_ptr`?

It expresses exclusive ownership and automatically destroys registered logging backends when they are removed or when the composite is destroyed.

### Q4. Can a Composite contain another Composite?

Yes.

```cpp
auto localOutputs = std::make_unique<OutputAdapter>();

localOutputs->Add(std::make_unique<ConsoleLogger>());
localOutputs->Add(std::make_unique<FileLogger>("app.log"));

OutputAdapter root;

root.Add(std::move(localOutputs));
root.Add(std::make_unique<RemoteLogger>("tcp://localhost:3490"));

Application(root);
```

This forms a recursive hierarchy where a composite can contain both leaves and other composites.

### Q5. Is the Composite Pattern the same as Observer?

No.

Composite represents a part-whole object hierarchy with a shared interface. Observer represents a one-to-many notification relationship between a subject and its subscribers.

Both can involve fan-out, but their intent and object relationships are different.

## 15. Key Takeaway

> **The Composite Pattern allows individual objects and collections of objects to be treated uniformly through a common interface.**

In this example, `OutputAdapter` behaves like a single logger while internally managing multiple logging backends.

This pattern is useful in logging middleware, GUI hierarchies, file systems, scene graphs, and other systems that operate on individual objects and groups of objects.