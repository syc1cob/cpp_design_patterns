#include "someip_config.h"

#include <stdexcept>
#include <utility>

SomeIpConfig::SomeIpConfig(const Builder& builder)
    : serviceId_(builder.serviceId_),
      serviceName_(builder.serviceName_),
      ipAddress_(builder.ipAddress_),
      tcpPort_(builder.tcpPort_),
      udpPort_(builder.udpPort_),
      serviceDiscovery_(builder.serviceDiscovery_),
      timeoutMs_(builder.timeoutMs_),
      retryCount_(builder.retryCount_)
{
}

SomeIpConfig::Builder&
SomeIpConfig::Builder::setServiceId(std::uint16_t id)
{
    serviceId_ = id;
    return *this;
}

SomeIpConfig::Builder&
SomeIpConfig::Builder::setServiceName(std::string name)
{
    serviceName_ = std::move(name);
    return *this;
}

SomeIpConfig::Builder&
SomeIpConfig::Builder::setIpAddress(std::string address)
{
    ipAddress_ = std::move(address);
    return *this;
}

SomeIpConfig::Builder&
SomeIpConfig::Builder::setTcpPort(std::uint16_t port)
{
    tcpPort_ = port;
    return *this;
}

SomeIpConfig::Builder&
SomeIpConfig::Builder::setUdpPort(std::uint16_t port)
{
    udpPort_ = port;
    return *this;
}

SomeIpConfig::Builder&
SomeIpConfig::Builder::enableServiceDiscovery(bool enabled)
{
    serviceDiscovery_ = enabled;
    return *this;
}

SomeIpConfig::Builder&
SomeIpConfig::Builder::setTimeoutMs(int timeout)
{
    timeoutMs_ = timeout;
    return *this;
}

SomeIpConfig::Builder&
SomeIpConfig::Builder::setRetryCount(int count)
{
    retryCount_ = count;
    return *this;
}

SomeIpConfig SomeIpConfig::Builder::build() const
{
    if (serviceId_ == 0) {
        throw std::invalid_argument("Service ID is required");
    }

    if (serviceName_.empty()) {
        throw std::invalid_argument("Service name is required");
    }

    if (ipAddress_.empty()) {
        throw std::invalid_argument("IP address is required");
    }

    if (tcpPort_ == 0 && udpPort_ == 0) {
        throw std::invalid_argument(
            "At least one transport port is required");
    }

    if (timeoutMs_ <= 0 || retryCount_ < 0) {
        throw std::invalid_argument(
            "Invalid timeout or retry count");
    }

    return SomeIpConfig(*this);
}

std::uint16_t SomeIpConfig::serviceId() const noexcept
{
    return serviceId_;
}

const std::string& SomeIpConfig::serviceName() const noexcept
{
    return serviceName_;
}

const std::string& SomeIpConfig::ipAddress() const noexcept
{
    return ipAddress_;
}

std::uint16_t SomeIpConfig::tcpPort() const noexcept
{
    return tcpPort_;
}

std::uint16_t SomeIpConfig::udpPort() const noexcept
{
    return udpPort_;
}

bool SomeIpConfig::serviceDiscoveryEnabled() const noexcept
{
    return serviceDiscovery_;
}

int SomeIpConfig::timeoutMs() const noexcept
{
    return timeoutMs_;
}

int SomeIpConfig::retryCount() const noexcept
{
    return retryCount_;
}