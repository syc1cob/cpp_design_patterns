#include "transport_factory.h"

#include <iostream>
#include <memory>
#include <string>

// Client code depends only on the abstraction.
void Application(ITransport& transport)
{
    transport.Send("Vehicle speed = 120 km/h");
}

int main()
{
    auto tcp = TransportFactory::Create(Protocol::TCP);
    auto udp = TransportFactory::Create(Protocol::UDP);

    std::cout << "=== TCP Communication ===\n";
    Application(*tcp);

    std::cout << "\n=== UDP Communication ===\n";
    Application(*udp);

    return 0;
}