#include "speed_sensor_adapter.h"

SpeedSensorAdapter::SpeedSensorAdapter(const LegacySpeedSensor& sensor):m_sensor{sensor}{

}

double SpeedSensorAdapter::getSpeedKmph() const
{
    constexpr double mphToKmph = 1.609344;
    return (m_sensor.readSpeedMph() * mphToKmph);
}