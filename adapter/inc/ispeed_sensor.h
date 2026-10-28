#pragma once
// Target interface expected by the application.
class ISpeedSensor {
public:
    virtual ~ISpeedSensor() = default;

    virtual double getSpeedKmph() const = 0;
};