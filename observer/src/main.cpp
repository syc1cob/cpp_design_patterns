#include "speed_source.h"
#include "dashboard_display.h"
#include "speed_warning.h"
#include "speed_logger.h"

#include <iostream>

int main()
{
    SpeedSource speedSource;

    DashboardDisplay dashboard;
    SpeedWarning warning(100);
    SpeedLogger logger;

    // Register observers.
    speedSource.subscribe(dashboard);
    speedSource.subscribe(warning);
    speedSource.subscribe(logger);

    std::cout << "=== Vehicle Speed: 60 km/h ===\n";
    speedSource.updateSpeed(60);

    std::cout << "\n=== Vehicle Speed: 120 km/h ===\n";
    speedSource.updateSpeed(120);

    // Dashboard no longer receives updates.
    speedSource.unsubscribe(dashboard);

    std::cout << "\n=== Dashboard Unsubscribed ===\n";
    speedSource.updateSpeed(130);

    return 0;
}