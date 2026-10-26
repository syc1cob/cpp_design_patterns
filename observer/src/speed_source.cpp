/*This implements registration, unregistration, and notification.*/
#include "speed_source.h"

#include <algorithm>
#include <functional>

void SpeedSource::subscribe(SpeedObserver& observer)
{
    const auto it = std::find_if(
        observers_.begin(),
        observers_.end(),
        [&observer](const auto& entry)
        {
            return &entry.get() == &observer;
        });

    // Prevent duplicate subscriptions.
    if (it == observers_.end())
    {
        observers_.push_back(std::ref(observer));
    }
}

void SpeedSource::unsubscribe(SpeedObserver& observer)
{
    observers_.erase(
        std::remove_if(
            observers_.begin(),
            observers_.end(),
            [&observer](const auto& entry)
            {
                return &entry.get() == &observer;
            }),
        observers_.end());
}

void SpeedSource::updateSpeed(int speed)
{
    // Notify all registered observers.
    for (auto& observer : observers_)
    {
        observer.get().onSpeedChanged(speed);
    }
}