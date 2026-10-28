#pragma once

#include <mutex>
#include <memory>

#include "imutex.h"
#include "ithread.h"
class PlatformFactory {
public:
    virtual ~PlatformFactory() = default;

    virtual std::unique_ptr<IThread> createThread() = 0;
    virtual std::unique_ptr<IMutex> createMutex() = 0;
};