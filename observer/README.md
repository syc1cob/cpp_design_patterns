# Observer Design Pattern – Vehicle Speed Monitoring

## Overview

The **Observer Pattern** is a behavioral design pattern that defines a one-to-many dependency between objects.

When one object (the Subject) changes its state, all registered observers are automatically notified.

This project demonstrates the Observer Pattern using a vehicle speed monitoring system written in C++17.

## Problem Statement

Consider a vehicle speed sensor that provides speed updates to multiple components:

- Dashboard display
- Overspeed warning system
- Speed logger

Without the Observer Pattern, the speed sensor might directly call each component:

```cpp
dashboard.update(speed);
warning.check(speed);
logger.log(speed);
```

This tightly couples the sensor to its consumers. Adding another consumer would require modifying the sensor implementation.

## Solution

The Observer Pattern introduces a common `SpeedObserver` interface.

Each interested component subscribes to `SpeedSource` and receives notifications through `onSpeedChanged()`.

## Architecture

```text
                  SpeedSource
                    (Subject)
                        |
                 updateSpeed()
                        |
                   notify all
                        |
           +------------+------------+
           |            |            |
           v            v            v
       Dashboard    SpeedWarning   SpeedLogger
       (Observer)    (Observer)    (Observer)
           |            |            |
           v            v            v
      Show Speed    Check Limit    Log Speed
```

## Pattern Components

| Component | Implementation |
|---|---|
| Subject | `SpeedSource` |
| Observer interface | `SpeedObserver` |
| Concrete observer | `DashboardDisplay` |
| Concrete observer | `SpeedWarning` |
| Concrete observer | `SpeedLogger` |
| Client | `main()` |

## How It Works

1. Observers register using `subscribe()`.
2. The Subject stores non-owning references to observers.
3. `updateSpeed()` triggers notifications to registered observers.
4. Each observer independently handles the speed update.
5. Observers can unregister using `unsubscribe()`.

## Build and Run

```bash
cmake -S . -B build
cmake --build build
./build/observer
```

## Important C++ Concepts

### Non-owning references

```cpp
std::vector<std::reference_wrapper<SpeedObserver>> observers_;
```

`SpeedSource` does not own the observers. The caller must ensure that registered observers remain alive until they unsubscribe or the subject is destroyed.

### Duplicate registration prevention

`subscribe()` uses `std::find_if()` to prevent the same observer from being registered twice.

### Unsubscription

`unsubscribe()` uses the erase-remove idiom to remove an observer.

### Polymorphism

Each concrete observer implements the same virtual callback:

```cpp
void onSpeedChanged(int speed) override;
```

## Observer vs Composite

| Observer | Composite |
|---|---|
| Behavioral pattern | Structural pattern |
| One-to-many notifications | Part-whole hierarchy |
| Subscribers react to events | Composite delegates operations to children |
| Observers can subscribe/unsubscribe | Composites own or reference child components |

Both can involve fan-out, but they solve different design problems.

## Automotive Applications

Observer-style architectures are useful for:

- Vehicle speed notifications
- Sensor data monitoring
- Diagnostic status changes
- ECU state notifications
- Event-driven middleware
- Application state updates

For example, a vehicle speed provider may notify a dashboard, safety monitoring component, and logging service without depending directly on their implementations.

## Advantages

- Loose coupling between Subject and observers
- Easy to add new subscribers
- Dynamic subscription and unsubscription
- Supports event-driven designs
- Follows the Open/Closed Principle

## Limitations

This example intentionally uses a simple synchronous notification mechanism.

- Observers must outlive their registrations.
- Subscription changes during notification are not supported.
- The implementation is not thread-safe.
- Slow observers delay later notifications.
- Exceptions thrown by an observer can interrupt notification.

Production systems may require synchronization, subscription tokens, automatic disconnection, or asynchronous event dispatch.

## QA

**Q1. What problem does the Observer Pattern solve?**

It decouples an event producer from its consumers and allows multiple objects to receive notifications without the producer knowing their concrete types.

**Q2. What is the difference between Subject and Observer?**

The Subject manages subscriptions and publishes updates. Observers implement the callback that handles those updates.

**Q3. Why use `std::reference_wrapper`?**

Because standard containers cannot store references directly. `std::reference_wrapper` provides reference-like behavior while allowing storage in a `std::vector`.

**Q4. What happens if an observer is destroyed without unsubscribing?**

The Subject retains a dangling reference. Calling that observer results in undefined behavior.

**Q5. Is Observer the same as publish-subscribe?**

They are closely related. Classic Observer typically maintains direct in-process subscriptions, while publish-subscribe systems may use an event broker or messaging infrastructure to further decouple publishers and subscribers.

## Key Takeaway

> The Observer Pattern allows one object to notify multiple interested objects about changes without depending on their concrete implementations.

This is especially useful for event-driven C++ applications and automotive middleware.