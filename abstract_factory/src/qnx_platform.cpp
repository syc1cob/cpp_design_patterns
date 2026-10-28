#include "qnx_platform.h"

#include <iostream>
#include <memory>

void QnxThread::start()
{
    std::cout << "[QNX] Thread started (simulated)\n";
}

void QnxMutex::lock()
{
    std::cout << "[QNX] Mutex locked (simulated)\n";
}

void QnxMutex::unlock()
{
    std::cout << "[QNX] Mutex unlocked (simulated)\n";
}

std::unique_ptr<IThread> QnxFactory::createThread()
{
    return std::make_unique<QnxThread>();
}

std::unique_ptr<IMutex> QnxFactory::createMutex()
{
    return std::make_unique<QnxMutex>();
}