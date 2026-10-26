/*A concrete observer that checks for overspeeding.*/ 
#pragma once

#include "speed_observer.h"

#include <iostream>

class SpeedWarning : public SpeedObserver
{
public:
    explicit SpeedWarning(int speedLimit)
        : speedLimit_(speedLimit)
    {
    }

    void onSpeedChanged(int speed) override
    {
        if (speed > speedLimit_)
        {
            std::cout << "[Warning] Overspeed detected! "
                      << speed << " km/h\n";
        }
    }

private:
    int speedLimit_;
};
