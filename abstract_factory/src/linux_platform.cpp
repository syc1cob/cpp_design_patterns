#include "linux_platform.h"

#include <iostream>
#include <memory>

void LinuxThread::start()
{
    std::cout << "[Linux] Thread started (simulated)\n";
}

void LinuxMutex::lock()
{
    std::cout << "[Linux] Mutex locked (simulated)\n";
}

void LinuxMutex::unlock()
{
    std::cout << "[Linux] Mutex unlocked (simulated)\n";
}

std::unique_ptr<IThread> LinuxFactory::createThread()
{
    return std::make_unique<LinuxThread>();
}

std::unique_ptr<IMutex> LinuxFactory::createMutex()
{
    return std::make_unique<LinuxMutex>();
}