#pragma once

class SpeedObserver
{
public:
    virtual ~SpeedObserver() = default;

    virtual void onSpeedChanged(int speed) = 0;
};
