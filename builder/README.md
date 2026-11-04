# Builder Design Pattern – C++17

## Overview

The **Builder Pattern** is a creational design pattern that allows complex objects to be constructed step by step.

It separates the construction process from the final object, making object creation more readable, flexible, and maintainable.

This project demonstrates the Builder Pattern using an automotive **SOME/IP service configuration** example implemented in C++17.

The example builds a `SomeIpConfig` object containing service identification, network settings, service discovery configuration, timeout, and retry parameters.

## 1. Problem Statement

Consider configuring a SOME/IP service using a constructor with many parameters:

```cpp
SomeIpConfig config(
    0x103,
    "BodyHvacService",
    "192.168.1.10",
    30500,
    30490,
    true,
    1000,
    3
);
```

This approach has several disadvantages:

- It is difficult to identify what each argument represents.
- Optional parameters make constructors increasingly complex.
- Multiple arguments of the same type can accidentally be swapped.
- Adding new configuration parameters may require changing constructor signatures.
- Configuration validation can become difficult to organize.

For example, it is not immediately clear whether `1000` represents a timeout, retry interval, or another configuration parameter.

## 2. Solution: Builder Pattern

The Builder Pattern allows configuration parameters to be set individually using descriptive methods.

```cpp
auto config = SomeIpConfig::Builder{}
    .setServiceId(0x103)
    .setServiceName("BodyHvacService")
    .setIpAddress("192.168.1.10")
    .setTcpPort(30500)
    .setUdpPort(30490)
    .enableServiceDiscovery(true)
    .setTimeoutMs(1000)
    .setRetryCount(3)
    .build();
```

Benefits of this approach include:

- Improved readability.
- Clear identification of configuration parameters.
- Support for optional parameters and defaults.
- Centralized validation.
- Separation of construction logic from application logic.

The values used in this example are illustrative and are not standardized AUTOSAR defaults.

## 3. Architecture

```text
                  +----------------------+
                  |        Client        |
                  |       main()         |
                  +----------------------+
                             |
                             | Creates and configures
                             v
                  +----------------------+
                  | SomeIpConfig::Builder|
                  +----------------------+
                  | setServiceId()       |
                  | setServiceName()     |
                  | setIpAddress()       |
                  | setTcpPort()         |
                  | setUdpPort()         |
                  | enableServiceDiscovery() |
                  | setTimeoutMs()       |
                  | setRetryCount()      |
                  | build()              |
                  +----------------------+
                             |
                             | Validates and constructs
                             v
                  +----------------------+
                  |     SomeIpConfig     |
                  +----------------------+
                  | serviceId_           |
                  | serviceName_         |
                  | ipAddress_           |
                  | tcpPort_             |
                  | udpPort_             |
                  | serviceDiscovery_    |
                  | timeoutMs_           |
                  | retryCount_          |
                  +----------------------+
```

The client configures the Builder, and the Builder creates the final `SomeIpConfig` object after validation.

## 4. Project Structure

```text
builder/
├── inc/
│   └── someip_config.h
├── src/
│   ├── someip_config.cpp
│   └── main.cpp
├── CMakeLists.txt
└── README.md
```

## 5. Design Pattern Components

| Component | Implementation | Responsibility |
|---|---|---|
| Product | `SomeIpConfig` | Represents the completed SOME/IP configuration |
| Builder | `SomeIpConfig::Builder` | Collects configuration parameters and constructs the Product |
| Client | `main()` | Configures the Builder and obtains the final Product |
| Director | Not used | Optional component that defines predefined construction sequences |

This implementation uses a **fluent Builder**, where setter methods return a reference to the Builder to support method chaining.

## 6. Implementation

### 6.1 Product – `SomeIpConfig`

The Product represents the completed configuration.

```cpp
class SomeIpConfig
{
public:
    class Builder;

    std::uint16_t serviceId() const noexcept;
    const std::string& serviceName() const noexcept;
    const std::string& ipAddress() const noexcept;
    std::uint16_t tcpPort() const noexcept;
    std::uint16_t udpPort() const noexcept;
    bool serviceDiscoveryEnabled() const noexcept;
    int timeoutMs() const noexcept;
    int retryCount() const noexcept;

private:
    explicit SomeIpConfig(const Builder& builder);

    std::uint16_t serviceId_;
    std::string serviceName_;
    std::string ipAddress_;
    std::uint16_t tcpPort_;
    std::uint16_t udpPort_;
    bool serviceDiscovery_;
    int timeoutMs_;
    int retryCount_;
};
```

The constructor is private, so external application code cannot directly construct a `SomeIpConfig` using that constructor.

The Builder is responsible for creating a validated configuration.

### 6.2 Builder – `SomeIpConfig::Builder`

```cpp
class SomeIpConfig::Builder
{
public:
    Builder& setServiceId(std::uint16_t id);
    Builder& setServiceName(std::string name);
    Builder& setIpAddress(std::string address);
    Builder& setTcpPort(std::uint16_t port);
    Builder& setUdpPort(std::uint16_t port);
    Builder& enableServiceDiscovery(bool enabled);
    Builder& setTimeoutMs(int timeout);
    Builder& setRetryCount(int count);

    SomeIpConfig build() const;

private:
    friend class SomeIpConfig;

    std::uint16_t serviceId_{0};
    std::string serviceName_;
    std::string ipAddress_;
    std::uint16_t tcpPort_{0};
    std::uint16_t udpPort_{0};
    bool serviceDiscovery_{false};
    int timeoutMs_{1000};
    int retryCount_{3};
};
```

The Builder stores intermediate configuration values until `build()` is called.

Default values are provided for optional parameters.

### 6.3 Fluent Interface and Method Chaining

Each setter returns `Builder&`.

```cpp
SomeIpConfig::Builder&
SomeIpConfig::Builder::setTimeoutMs(int timeout)
{
    timeoutMs_ = timeout;
    return *this;
}
```

`return *this` returns a reference to the same Builder object.

This enables method chaining:

```cpp
builder.setServiceId(0x103)
       .setTimeoutMs(1000)
       .setRetryCount(3);
```

All setter calls operate on the same Builder instance.

### 6.4 Validation During Construction

The `build()` method validates the configuration before creating the Product.

```cpp
SomeIpConfig SomeIpConfig::Builder::build() const
{
    if (serviceId_ == 0) {
        throw std::invalid_argument("Service ID is required");
    }

    if (serviceName_.empty()) {
        throw std::invalid_argument("Service name is required");
    }

    if (ipAddress_.empty()) {
        throw std::invalid_argument("IP address is required");
    }

    if (tcpPort_ == 0 && udpPort_ == 0) {
        throw std::invalid_argument(
            "At least one transport port is required");
    }

    if (timeoutMs_ <= 0 || retryCount_ < 0) {
        throw std::invalid_argument(
            "Invalid timeout or retry count");
    }

    return SomeIpConfig(*this);
}
```

This ensures that the Builder does not produce a configuration that violates these application-level validation rules.

Additional validation may be required in a production system, such as verifying IP address syntax and protocol-specific constraints.

### 6.5 Client Code

```cpp
int main()
{
    auto config = SomeIpConfig::Builder{}
        .setServiceId(0x103)
        .setServiceName("BodyHvacService")
        .setIpAddress("192.168.1.10")
        .setTcpPort(30500)
        .setUdpPort(30490)
        .enableServiceDiscovery(true)
        .setTimeoutMs(1000)
        .setRetryCount(3)
        .build();

    std::cout << "Service: "
              << config.serviceName() << '\n';

    return 0;
}
```

The client does not need to know the internal construction details of `SomeIpConfig`.

## 7. Execution Flow

1. The client creates a `SomeIpConfig::Builder`.
2. Setter methods populate the Builder's internal fields.
3. Optional parameters retain their default values if not explicitly set.
4. The client calls `build()`.
5. The Builder validates the accumulated configuration.
6. If validation fails, `std::invalid_argument` is thrown.
7. If validation succeeds, the Builder constructs a `SomeIpConfig` object.
8. The client receives the completed configuration.

## 8. Build and Run

### Prerequisites

- C++17-compatible compiler.
- CMake 3.16 or later.

### Build

From the `builder/` directory:

```bash
cmake -S . -B build
cmake --build build
```

### Run on Linux

```bash
./build/builder
```

### Run on Windows (Visual Studio generator)

```powershell
.\build\Debug\builder.exe
```

### Expected Output

```text
Service: BodyHvacService
Service ID: 259
IP address: 192.168.1.10
TCP port: 30500
UDP port: 30490
Timeout: 1000 ms
Retries: 3
```

## 9. Builder vs Factory Method vs Abstract Factory

| Pattern | Purpose | Example |
|---|---|---|
| Builder | Constructs a complex object step by step | SOME/IP configuration with optional parameters |
| Factory Method | Delegates object creation through a factory method | Creating different transport implementations |
| Abstract Factory | Creates families of related objects | Linux or QNX thread and mutex implementations |

**Key difference:**

Builder focuses on **how an object is configured and assembled**.

Factory patterns focus on **encapsulating or selecting object creation**.

## 10. Advantages

- Improves readability when constructors have many parameters.
- Supports optional parameters and default values.
- Centralizes construction and validation logic.
- Reduces the need for multiple overloaded constructors.
- Separates object construction from object usage.
- Supports creating different configurations using the same Builder.
- Can produce objects that expose only read-only operations.

## 11. Drawbacks

### 11.1 Additional Boilerplate

The Builder may require separate setter methods and storage for each configuration parameter.

### 11.2 Duplicated State

The Builder and the final Product may temporarily hold copies of the same configuration data.

### 11.3 Runtime Validation

A simple Builder may allow incomplete configurations until `build()` is called.

### 11.4 Thread Safety

A mutable Builder is not automatically thread-safe.

Concurrent calls to setter methods on the same Builder require synchronization.

### 11.5 Overengineering

For objects with only a few parameters, constructors or aggregate initialization may be simpler.

### 11.6 Embedded System Considerations

Dynamic strings, exceptions, memory allocation, and object copying may require special consideration in resource-constrained or safety-critical systems.

The Builder Pattern itself does not require dynamic allocation or exceptions.

## 12. SOLID Principles

### Single Responsibility Principle (SRP)

The Builder manages configuration assembly and validation, while the Product represents the completed configuration.

### Open/Closed Principle (OCP)

New optional configuration parameters can often be added to the Builder without changing existing client call sites.

### Dependency Inversion Principle (DIP)

Builder does not inherently require interfaces or dependency inversion. This principle becomes relevant when builders construct objects that depend on abstractions rather than concrete implementations.

## 13. Automotive and Adaptive AUTOSAR Applications

The Builder Pattern can be useful for constructing:

- SOME/IP service configuration objects.
- Diagnostic request objects.
- Communication and transport settings.
- Test fixtures for Adaptive AUTOSAR components.
- Logging configuration objects.
- Application-specific startup configuration.
- Complex messages with optional fields.

For example, a diagnostic request may contain an ECU identifier, request payload, timeout, retry count, and optional metadata.

Builder provides a readable way to assemble and validate such requests.

In Adaptive AUTOSAR, a Builder can complement application-level configuration handling, but it does not replace standardized ARXML manifests, configuration generators, or platform-specific validation.

## 14. Questions and Answers

### Q1. What problem does the Builder Pattern solve?

Builder simplifies the construction of complex objects with many parameters, especially when some parameters are optional.

It improves readability and separates object construction from application logic.

### Q2. What is the difference between Builder and Factory?

Factory encapsulates object creation, often selecting a concrete implementation.

Builder constructs an object step by step, allowing individual configuration parameters to be supplied before the final object is created.

### Q3. Why do Builder setter methods return `Builder&`?

Returning `Builder&` allows method chaining.

```cpp
Builder& setRetryCount(int count)
{
    retryCount_ = count;
    return *this;
}
```

Each setter modifies the same Builder instance and returns a reference to it.

### Q4. Is the Builder Pattern thread-safe?

Not automatically.

If multiple threads modify the same Builder simultaneously without synchronization, data races may occur.

A common approach is to use a separate Builder instance per thread.

### Q5. Does Builder require inheritance or virtual functions?

No.

This example uses a nested Builder class without inheritance or virtual functions.

The classic GoF Builder can use an abstract Builder interface and concrete builders, but that structure is not mandatory for modern fluent builders.

### Q6. Can Builder construct immutable objects?

Yes.

The Builder collects mutable configuration values and constructs a final object that exposes only read-only operations.

This can help prevent accidental modification after construction.

### Q7. What is the Director in the classic Builder Pattern?

The Director defines a sequence of construction steps.

For example, a Director might configure a Builder to produce a predefined diagnostic request or service configuration.

A Director is optional in modern fluent Builder implementations.

### Q8. How would you handle mandatory parameters?

Several approaches are possible:

- Validate mandatory fields in `build()`.
- Require mandatory fields in the Builder constructor.
- Use a staged Builder that enforces construction order at compile time.

The current example validates mandatory parameters in `build()`.

### Q9. Where would Builder be useful in Adaptive AUTOSAR?

Builder can be useful when constructing application-level service configurations, diagnostic requests, communication settings, and test objects.

It is particularly useful when objects contain many optional parameters or require validation.

### Q10. When would you avoid using Builder?

Avoid Builder when object construction is simple and a constructor or aggregate initialization is already clear.

Introducing a Builder for an object with only two or three straightforward parameters may add unnecessary complexity.

### Q11. What happens if `build()` fails validation?

The method throws `std::invalid_argument`.

The Product is not constructed successfully, and the caller can handle the exception.

In environments where exceptions are disabled, validation can instead return a status or result type.

### Q12. Can the same Builder create multiple objects?

Yes.

Because `build()` is declared `const` in this implementation, it does not modify the Builder.

The same Builder can be used to create multiple configurations.

```cpp
SomeIpConfig::Builder builder;

builder.setServiceId(0x103)
       .setServiceName("BodyHvacService")
       .setIpAddress("192.168.1.10")
       .setTcpPort(30500);

auto config1 = builder.build();

builder.setTimeoutMs(2000);

auto config2 = builder.build();
```

`config1` retains its original timeout, while `config2` uses the updated timeout.

### Q13. What is the difference between a fluent interface and the Builder Pattern?

A fluent interface is an API style that supports chaining method calls.

The Builder Pattern is a design pattern for constructing objects step by step.

Builder implementations frequently use fluent interfaces, but fluent interfaces can also be used outside the Builder Pattern.

### Q14. Does the Builder Pattern improve performance?

Not necessarily.

Its primary benefits are readability, maintainability, and construction flexibility.

Depending on the implementation, Builder may introduce additional copies or allocations.

Move semantics and careful ownership design can reduce these costs.

### Q15. Can Builder be used without dynamic memory allocation?

Yes.

A Builder can store values directly and return a Product by value.

The Builder Pattern does not inherently require heap allocation.

However, individual member types such as `std::string` may still allocate dynamically.

## 15. Key Takeaway

> **The Builder Pattern separates the construction of a complex object from its representation, allowing objects to be configured step by step.**

In this project, `SomeIpConfig::Builder` provides a readable and validated way to create SOME/IP service configurations.

Builder is especially useful when dealing with complex configurations, optional parameters, and construction-time validation in modern C++ and automotive software.