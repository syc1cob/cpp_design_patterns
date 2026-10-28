#pragma once
// This is the Adaptee, an existing class with an incompatible API.
class LegacySpeedSensor {
public:
    explicit LegacySpeedSensor(double speedMph);

    double readSpeedMph() const;

private:
    double m_speedMph;
};