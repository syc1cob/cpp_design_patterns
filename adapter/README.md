# Adapter Design Pattern – C++17

## Overview

The **Adapter Pattern** is a structural design pattern that allows objects with incompatible interfaces to work together.

It acts as a bridge between an existing class and the interface expected by the client.

This project demonstrates the Adapter Pattern using a **legacy vehicle speed sensor** that reports speed in miles per hour (mph), while a modern vehicle application expects speed in kilometers per hour (km/h).

The adapter translates both the method interface and the data representation without modifying the legacy implementation.

## 1. Problem Statement

Consider a vehicle monitoring application that expects the following interface:

```cpp
class ISpeedSensor {
public:
    virtual ~ISpeedSensor() = default;

    virtual double getSpeedKmph() const = 0;
};
```

However, an existing sensor library provides:

```cpp
class LegacySpeedSensor {
public:
    double readSpeedMph() const;
};
```

The interfaces are incompatible because:

- The application expects `getSpeedKmph()`.
- The legacy sensor exposes `readSpeedMph()`.
- The application expects km/h, but the legacy sensor reports mph.

Modifying the legacy library may not be possible because it could be third-party software or an existing production component.

## 2. Solution: Adapter Pattern

Introduce a `SpeedSensorAdapter` that implements `ISpeedSensor` and internally delegates to `LegacySpeedSensor`.

The adapter performs two transformations:

1. **Interface adaptation:** `getSpeedKmph()` → `readSpeedMph()`.
2. **Data conversion:** mph → km/h.

The client interacts only with `ISpeedSensor`, remaining independent of the legacy implementation.

## 3. Architecture

```text
                  Vehicle Application
                          |
                          | getSpeedKmph()
                          v
                   +--------------+
                   | ISpeedSensor |
                   |   (Target)   |
                   +--------------+
                          ^
                          |
                   implements
                          |
                   +--------------------+
                   | SpeedSensorAdapter |
                   |     (Adapter)      |
                   +--------------------+
                          |
                          | readSpeedMph()
                          v
                   +--------------------+
                   | LegacySpeedSensor  |
                   |     (Adaptee)      |
                   +--------------------+
                          |
                          v
                     Speed in mph

                 Adapter converts mph
                        to km/h
```

## 4. Project Structure

```text
adapter/
├── inc/
│   ├── ispeed_sensor.h
│   ├── legacy_speed_sensor.h
│   └── speed_sensor_adapter.h
├── src/
│   ├── legacy_speed_sensor.cpp
│   ├── speed_sensor_adapter.cpp
│   └── main.cpp
├── CMakeLists.txt
└── README.md
```

## 5. Design Pattern Components

| Component | Implementation | Responsibility |
|---|---|---|
| Target | `ISpeedSensor` | Defines the interface expected by the application |
| Adaptee | `LegacySpeedSensor` | Existing class with an incompatible interface |
| Adapter | `SpeedSensorAdapter` | Translates the interface and converts units |
| Client | `Application()` | Uses the Target interface |

## 6. Implementation

### Target Interface

```cpp
class ISpeedSensor {
public:
    virtual ~ISpeedSensor() = default;

    virtual double getSpeedKmph() const = 0;
};
```

The application depends on this interface.

### Adaptee

```cpp
class LegacySpeedSensor {
public:
    explicit LegacySpeedSensor(double speedMph);

    double readSpeedMph() const;

private:
    double m_speedMph;
};
```

This class represents the existing sensor API.

### Adapter

```cpp
class SpeedSensorAdapter : public ISpeedSensor {
public:
    explicit SpeedSensorAdapter(const LegacySpeedSensor& sensor);

    double getSpeedKmph() const override;

private:
    const LegacySpeedSensor& sensor_;
};
```

The adapter implements the expected interface while holding a reference to the legacy sensor.

### Adapter Implementation

```cpp
double SpeedSensorAdapter::getSpeedKmph() const
{
    constexpr double mphToKmph = 1.609344;

    return sensor_.readSpeedMph() * mphToKmph;
}
```

The adapter calls the legacy API, retrieves the speed in mph, converts it into km/h, and returns the result.


## 15.  Questions and Answers

### Q1. What problem does the Adapter Design Pattern solve?

The Adapter Pattern allows classes with incompatible interfaces to work together without modifying their existing implementations.

For example, an application expects `getSpeedKmph()`, but a legacy sensor provides `readSpeedMph()`. An adapter translates the interface and converts the returned value.

### Q2. What are the main components of the Adapter Pattern?

There are four components:

1. **Target:** The interface expected by the client (`ISpeedSensor`).
2. **Adaptee:** The existing class with an incompatible interface (`LegacySpeedSensor`).
3. **Adapter:** The class that translates calls between the Target and Adaptee (`SpeedSensorAdapter`).
4. **Client:** The application that uses the Target interface (`Application()`).

### Q3. Why does `SpeedSensorAdapter` inherit from `ISpeedSensor`?

Because the adapter must implement the interface expected by the client.

```cpp
class SpeedSensorAdapter : public ISpeedSensor {
public:
    double getSpeedKmph() const override;
};
```

This allows the adapter to be used polymorphically wherever `ISpeedSensor` is expected.

### Q4. Why does the adapter contain a `LegacySpeedSensor` reference?

The adapter delegates operations to the existing implementation.

```cpp
class SpeedSensorAdapter : public ISpeedSensor {
private:
    const LegacySpeedSensor& sensor_;
};
```

This is an **Object Adapter**, where composition is used to access the Adaptee.

The reference is non-owning, so the legacy sensor must outlive the adapter's use of it.

### Q5. What is the difference between Adapter and Strategy?

**Adapter** converts an incompatible interface into one the

