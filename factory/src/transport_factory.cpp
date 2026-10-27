#include <stdexcept>
#include "transport_factory.h"
#include "tcp_transport.h"
#include "udp_transport.h"

std::unique_ptr<ITransport> TransportFactory::Create(Protocol protocol)
{
    switch (protocol)
    {
        case Protocol::TCP:
            return std::make_unique<TcpTransport>();

        case Protocol::UDP:
            return std::make_unique<UdpTransport>();

        default:
            throw std::invalid_argument("Unsupported protocol");
    }
}