#pragma once

#include "speed_observer.h"

#include <iostream>

class DashboardDisplay : public SpeedObserver
{
public:
    void onSpeedChanged(int speed) override
    {
        std::cout << "[Dashboard] Current speed: "
                  << speed << " km/h\n";
    }
};
