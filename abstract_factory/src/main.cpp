#include "linux_platform.h"
#include "qnx_platform.h"

#include <iostream>

// Client code: Depends only on the abstract factory.
void Application(PlatformFactory& factory)
{
    auto thread = factory.createThread();
    auto mutex = factory.createMutex();

    thread->start();

    mutex->lock();
    std::cout << "[Application] Performing protected operation\n";
    mutex->unlock();
}

int main()
{
    LinuxFactory linuxFactory;
    QnxFactory qnxFactory;

    std::cout << "=== Linux Platform ===\n";
    Application(linuxFactory);

    std::cout << "\n=== QNX Platform ===\n";
    Application(qnxFactory);

    return 0;
}