#include "legacy_speed_sensor.h"

LegacySpeedSensor::LegacySpeedSensor(double speedMph):m_speedMph{speedMph}{

}
double LegacySpeedSensor::readSpeedMph() const{
    return m_speedMph;
}