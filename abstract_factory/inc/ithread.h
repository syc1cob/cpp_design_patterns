#pragma once

// Abstract Product 1
class IThread {
public:
    virtual ~IThread() = default;
    virtual void start() = 0;
};