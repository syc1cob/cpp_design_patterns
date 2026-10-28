#pragma once
#include "ispeed_sensor.h"
#include "legacy_speed_sensor.h"
// The Adapter implements the expected interface
//  and wraps the legacy sensor.
 class SpeedSensorAdapter : public ISpeedSensor{
    public:
        explicit SpeedSensorAdapter(const LegacySpeedSensor& sensor);
        double getSpeedKmph() const override;
    private:
        const LegacySpeedSensor& m_sensor;

 };