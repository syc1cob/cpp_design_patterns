#pragma once

#include "platform_factory.h"

// Concrete Product 1
class QnxThread : public IThread
{
public:
    void start() override;
};

// Concrete Product 2
class QnxMutex : public IMutex
{
public:
    void lock() override;
    void unlock() override;
};

// Concrete Factory: Creates QNX products.
class QnxFactory : public PlatformFactory
{
public:
    std::unique_ptr<IThread> createThread() override;
    std::unique_ptr<IMutex> createMutex() override;
};