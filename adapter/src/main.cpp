#include "ispeed_sensor.h"
#include "legacy_speed_sensor.h"
#include "speed_sensor_adapter.h"

#include <iomanip>
#include <iostream>

// Client code
void Application(const ISpeedSensor& sensor)
{
    std::cout << std::fixed << std::setprecision(2)
              << "Vehicle speed: "
              << sensor.getSpeedKmph()
              << " km/h\n";
}

int main()
{
    // Existing legacy library object
    LegacySpeedSensor legacySensor(60.0);

    // Wrap legacy API with an adapter
    SpeedSensorAdapter adapter(legacySensor);

    // Application uses the modern interface
    Application(adapter);

    return 0;
}