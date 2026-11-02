#include "someip_config.h"

#include <iostream>
#include <stdexcept>

int main()
{
    try {
        auto config = SomeIpConfig::Builder{}
            .setServiceId(0x103)
            .setServiceName("BodyHvacService")
            .setIpAddress("192.168.1.10")
            .setTcpPort(30500)
            .setUdpPort(30490)
            .enableServiceDiscovery(true)
            .setTimeoutMs(1000)
            .setRetryCount(3)
            .build();

        std::cout << "Service: "
                  << config.serviceName() << '\n';

        std::cout << "Service ID: "
                  << config.serviceId() << '\n';

        std::cout << "IP address: "
                  << config.ipAddress() << '\n';

        std::cout << "TCP port: "
                  << config.tcpPort() << '\n';

        std::cout << "UDP port: "
                  << config.udpPort() << '\n';

        std::cout << "Timeout: "
                  << config.timeoutMs() << " ms\n";

        std::cout << "Retries: "
                  << config.retryCount() << '\n';

    } catch (const std::exception& e) {
        std::cerr << "Configuration error: "
                  << e.what() << '\n';
        return 1;
    }

    return 0;
}