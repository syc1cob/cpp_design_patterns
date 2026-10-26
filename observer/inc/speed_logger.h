/* A concrete observer that logs speed changes.*/
#pragma once

#include "speed_observer.h"

#include <iostream>

class SpeedLogger : public SpeedObserver
{
public:
    void onSpeedChanged(int speed) override
    {
        std::cout << "[Logger] Speed updated to "
                  << speed << " km/h\n";
    }
};