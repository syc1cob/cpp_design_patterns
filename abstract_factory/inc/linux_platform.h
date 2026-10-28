#pragma once

#include "platform_factory.h"

// Concrete Product 1
class LinuxThread : public IThread
{
public:
    void start() override;
};

// Concrete Product 2
class LinuxMutex : public IMutex
{
public:
    void lock() override;
    void unlock() override;
};

// Concrete Factory: Creates Linux products.
class LinuxFactory : public PlatformFactory
{
public:
    std::unique_ptr<IThread> createThread() override;
    std::unique_ptr<IMutex> createMutex() override;
};