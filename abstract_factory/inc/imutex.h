#pragma once
// Abstract Product 2
class IMutex {
public:
    virtual ~IMutex() = default;
    virtual void lock() = 0;
    virtual void unlock() = 0;
};