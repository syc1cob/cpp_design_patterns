# Factory Pattern – Automotive Transport Creation (C++17)

## Overview

This project demonstrates the **Simple Factory Pattern** using an automotive communication example.

The factory creates TCP or UDP transport objects based on a requested protocol. The application interacts with them through a common `ITransport` interface.

## Problem

Without a factory, client code must know which concrete transport class to instantiate.

This introduces dependencies between application code and concrete implementations.

## Solution

Centralize object creation in `TransportFactory`.

```cpp
auto transport = TransportFactory::Create(Protocol::TCP);
transport->Send("Vehicle speed = 120 km/h");
```

## Project Structure

```text
factory/
├── inc/
│   ├── itransport.h
│   ├── tcp_transport.h
│   ├── udp_transport.h
│   └── transport_factory.h
├── src/
│   ├── transport_factory.cpp
│   └── main.cpp
├── CMakeLists.txt
└── README.md
```

## Pattern Components

| Component | Class |
|---|---|
| Product interface | `ITransport` |
| Concrete products | `TcpTransport`, `UdpTransport` |
| Factory | `TransportFactory` |
| Client | `Application()` |

## Build and Run

```bash
cmake -S . -B build
cmake --build build
./build/factory
```

## Advantages

- Centralizes object creation
- Reduces client dependency on concrete classes
- Simplifies object lifetime management using `std::unique_ptr`
- Allows creation logic to be extended independently of the client

## Limitations

- Adding a new protocol requires modifying the factory.
- A large factory can accumulate many creation branches.
- This example simulates sending; it does not implement real network sockets.

## Factory vs Strategy

Factory determines **which object to create**.

Strategy determines **which interchangeable behavior to execute**.

They can work together: a factory can create the appropriate strategy object based on configuration.

## Q&A

**Q1. Why use a factory instead of calling `new` or `std::make_unique` directly?**

To centralize object creation and reduce coupling between client code and concrete classes.

**Q2. Why does the factory return `std::unique_ptr<ITransport>`?**

It transfers ownership of the newly created object to the caller and provides automatic cleanup.

**Q3. Is a static factory method the same as the GoF Factory Method Pattern?**

No. A static factory centralizes creation using a function, while GoF Factory Method uses a polymorphic creator hierarchy.

**Q4. What happens when a new transport protocol is introduced?**

A new implementation of `ITransport` is added, and the simple factory's creation logic must be extended.

**Q5. Can Factory and Strategy be used together?**

Yes. A factory can construct a concrete strategy while the client uses it through a common interface.

## Key Takeaway

> A factory separates object creation from object usage, helping client code depend on abstractions instead of concrete implementations.