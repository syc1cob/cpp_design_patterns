# Abstract Factory Design Pattern – C++17

## Overview

The **Abstract Factory Pattern** is a creational design pattern that provides an interface for creating families of related objects without specifying their concrete classes.

This project demonstrates the Abstract Factory Pattern using **Linux and QNX platform-specific services**, inspired by cross-platform embedded and automotive software development.

The application creates threads and mutexes through a common factory interface, without depending on the platform-specific implementations.

> **Note:** This is an educational implementation. Thread and mutex operations are simulated using console output. No actual OS threads or synchronization primitives are created.

## 1. Problem Statement

Consider an embedded application that must support two operating systems:

- Linux
- QNX

Each platform requires its own implementations of:

- Thread
- Mutex

Without Abstract Factory, application code may contain platform-specific object creation logic:

```cpp
if (platform == Platform::Linux) {
    thread = std::make_unique<LinuxThread>();
    mutex = std::make_unique<LinuxMutex>();
} else {
    thread = std::make_unique<QnxThread>();
    mutex = std::make_unique<QnxMutex>();
}
```

This introduces several problems:

- Application code depends on concrete platform-specific classes.
- Platform-selection logic may be duplicated.
- Adding another platform requires changes wherever products are constructed.
- Related platform-specific objects may accidentally be mixed.

## 2. Solution: Abstract Factory

Introduce a `PlatformFactory` interface that defines methods to create related products.

```cpp
class PlatformFactory {
public:
    virtual ~PlatformFactory() = default;

    virtual std::unique_ptr<IThread> createThread() = 0;
    virtual std::unique_ptr<IMutex> createMutex() = 0;
};
```

Each platform provides a concrete factory:

- `LinuxFactory` creates `LinuxThread` and `LinuxMutex`.
- `QnxFactory` creates `QnxThread` and `QnxMutex`.

The application interacts only with the abstract interfaces.

## 3. Architecture

```text
                       Application
                            |
                            v
                    PlatformFactory
                    (Abstract Factory)
                            |
                 +----------+----------+
                 |                     |
                 v                     v
            LinuxFactory           QnxFactory
                 |                     |
          +------+------+       +------+------+
          |             |       |             |
          v             v       v             v
     LinuxThread   LinuxMutex QnxThread   QnxMutex
          |             |       |             |
          +-------------+       +-------------+
          Linux Family            QNX Family

Abstract Products:
    IThread
    IMutex
```

Both product families implement the same abstract interfaces.

## 4. Project Structure

```text
abstract_factory/
├── inc/
│   ├── ithread.h
│   ├── imutex.h
│   ├── platform_factory.h
│   ├── linux_platform.h
│   └── qnx_platform.h
├── src/
│   ├── linux_platform.cpp
│   ├── qnx_platform.cpp
│   └── main.cpp
├── CMakeLists.txt
└── README.md
```

## 5. Design Pattern Components

| Component | Implementation | Responsibility |
|---|---|---|
| Abstract Factory | `PlatformFactory` | Declares product creation methods |
| Concrete Factory | `LinuxFactory` | Creates Linux product family |
| Concrete Factory | `QnxFactory` | Creates QNX product family |
| Abstract Product 1 | `IThread` | Common thread interface |
| Abstract Product 2 | `IMutex` | Common mutex interface |
| Concrete Products | `LinuxThread`, `LinuxMutex` | Linux implementations |
| Concrete Products | `QnxThread`, `QnxMutex` | QNX implementations |
| Client | `Application()` | Uses abstract interfaces |

## 6. Implementation

### Abstract Products

```cpp
class IThread {
public:
    virtual ~IThread() = default;
    virtual void start() = 0;
};

class IMutex {
public:
    virtual ~IMutex() = default;
    virtual void lock() = 0;
    virtual void unlock() = 0;
};
```

### Abstract Factory

```cpp
class PlatformFactory {
public:
    virtual ~PlatformFactory() = default;

    virtual std::unique_ptr<IThread> createThread() = 0;
    virtual std::unique_ptr<IMutex> createMutex() = 0;
};
```

### Concrete Factory Example

```cpp
std::unique_ptr<IThread> LinuxFactory::createThread()
{
    return std::make_unique<LinuxThread>();
}

std::unique_ptr<IMutex> LinuxFactory::createMutex()
{
    return std::make_unique<LinuxMutex>();
}
```

The factory encapsulates the creation of related Linux products.

### Client Code

```cpp
void Application(PlatformFactory& factory)
{
    auto thread = factory.createThread();
    auto mutex = factory.createMutex();

    thread->start();

    mutex->lock();
    std::cout << "[Application] Performing protected operation\n";
    mutex->unlock();
}
```

The application does not depend on `LinuxThread`, `QnxThread`, `LinuxMutex`, or `QnxMutex`.

It receives a factory and creates the required products through the abstract interface.

## 7. Build and Run

### Prerequisites

- C++17-compatible compiler
- CMake 3.16 or later

### Build

From the `abstract_factory/` directory:

```bash
cmake -S . -B build
cmake --build build
```

### Run on Linux

```bash
./build/abstract_factory
```

### Run on Windows (Visual Studio generator)

```powershell
.\build\Debug\abstract_factory.exe
```

## 8. Expected Output

```text
=== Linux Platform ===
[Linux] Thread started (simulated)
[Linux] Mutex locked (simulated)
[Application] Performing protected operation
[Linux] Mutex unlocked (simulated)

=== QNX Platform ===
[QNX] Thread started (simulated)
[QNX] Mutex locked (simulated)
[Application] Performing protected operation
[QNX] Mutex unlocked (simulated)
```

## 9. Abstract Factory vs Factory Method vs Strategy

| Pattern | Type | Purpose |
|---|---|---|
| Abstract Factory | Creational | Creates families of related objects |
| Factory Method | Creational | Allows subclasses to determine which product is created |
| Strategy | Behavioral | Encapsulates interchangeable algorithms |

**Abstract Factory:** Choose a platform-specific family of thread and mutex implementations.

**Factory Method:** Delegate the creation of a product to an overridable method.

**Strategy:** Select an interchangeable behavior, such as a retry algorithm.

## 10. Advantages

- Decouples application code from concrete implementations.
- Ensures related products are created through a consistent factory.
- Centralizes platform-specific object creation.
- Makes adding new product families easier.
- Supports dependency inversion and interface-based design.
- Works naturally with polymorphism and smart pointers.

## 11. Limitations

- Introduces additional interfaces and classes.
- Adding a new product type requires updating all concrete factories.
- Product-family selection must still happen somewhere in the application.
- Platform-specific functionality may not fit a common abstraction.

### Production Considerations

This example intentionally simplifies operating-system behavior.

A production implementation should consider:

- Actual Linux/QNX threading and synchronization APIs.
- Thread creation, joining, and shutdown.
- RAII-based mutex locking.
- Error handling and resource cleanup.
- Thread-safety and exception safety.
- Platform-specific scheduling and priority requirements.

The sample demonstrates object creation and dependency management, not real threading.

## 12. SOLID Principles

**Single Responsibility Principle (SRP)**

Factories handle object creation, while product classes handle platform-specific behavior.

**Open/Closed Principle (OCP)**

A new platform family can be added by implementing the existing interfaces without modifying the abstract factory or client.

**Liskov Substitution Principle (LSP)**

Concrete factories can be used wherever `PlatformFactory` is expected, and concrete products can be used through their abstract product interfaces.

**Dependency Inversion Principle (DIP)**

The application depends on `PlatformFactory`, `IThread`, and `IMutex`, rather than concrete Linux/QNX implementations.

## 13. Automotive and Embedded Applications

Abstract Factory can be useful when supporting multiple:

- Operating systems, such as Linux and QNX.
- Hardware platforms.
- Communication middleware implementations.
- Storage backends.
- Platform abstraction layers.

For example, an embedded application may select a platform factory during initialization and use it to construct related platform-dependent services.

This reduces platform-specific dependencies in the application's core logic.

## 14. Q&A

### Q1. What problem does the Abstract Factory Pattern solve?

It provides a common interface for creating related objects while hiding their concrete implementations from client code.

### Q2. What is the difference between Abstract Factory and Factory Method?

Factory Method focuses on an overridable creation operation, typically for one product type. Abstract Factory exposes creation operations for a family of related products.

### Q3. Why does `PlatformFactory` have multiple creation methods?

Because it creates a family of related products, such as a thread and mutex for a particular platform.

### Q4. Why return `std::unique_ptr`?

It expresses exclusive ownership, supports polymorphic objects, and provides automatic resource cleanup.

### Q5. How would you add another platform?

Create new product implementations such as `NewPlatformThread` and `NewPlatformMutex`, then implement `NewPlatformFactory`.

The existing application logic can remain unchanged.

### Q6. What happens when a new product type is introduced?

If a new method such as `createTimer()` is added to `PlatformFactory`, every concrete factory must implement it.

This is a key trade-off of Abstract Factory: adding new product families is relatively easy, but extending the set of product types requires changes across the factory hierarchy.

### Q7. Does Abstract Factory guarantee that incompatible objects can never be mixed?

Not automatically. It encourages consistent product creation through one factory, but the current interfaces do not prevent clients from manually mixing products from different families.

Stronger compatibility guarantees require additional design constraints.

## 15. Key Takeaway

> **Abstract Factory creates families of related objects through common interfaces, without exposing their concrete classes to the client.**

In this example, `PlatformFactory` provides platform-specific thread and mutex objects, while `Application()` remains independent of the Linux and QNX implementations.

This pattern is particularly useful for cross-platform C++, embedded software, and automotive applications.