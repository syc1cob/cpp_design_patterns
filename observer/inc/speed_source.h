#pragma once

#include "speed_observer.h"

#include <functional>
#include <vector>

class SpeedSource
{
public:
    void subscribe(SpeedObserver& observer);
    void unsubscribe(SpeedObserver& observer);

    void updateSpeed(int speed);

private:
    std::vector<std::reference_wrapper<SpeedObserver>> observers_;
};
