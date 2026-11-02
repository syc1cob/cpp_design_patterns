#pragma once

#include <cstdint>
#include <string>

class SomeIpConfig
{
public:
    class Builder;

    std::uint16_t serviceId() const noexcept;
    const std::string& serviceName() const noexcept;
    const std::string& ipAddress() const noexcept;
    std::uint16_t tcpPort() const noexcept;
    std::uint16_t udpPort() const noexcept;
    bool serviceDiscoveryEnabled() const noexcept;
    int timeoutMs() const noexcept;
    int retryCount() const noexcept;

private:
    explicit SomeIpConfig(const Builder& builder);

    std::uint16_t serviceId_;
    std::string serviceName_;
    std::string ipAddress_;
    std::uint16_t tcpPort_;
    std::uint16_t udpPort_;
    bool serviceDiscovery_;
    int timeoutMs_;
    int retryCount_;
};

class SomeIpConfig::Builder
{
public:
    Builder& setServiceId(std::uint16_t id);
    Builder& setServiceName(std::string name);
    Builder& setIpAddress(std::string address);
    Builder& setTcpPort(std::uint16_t port);
    Builder& setUdpPort(std::uint16_t port);
    Builder& enableServiceDiscovery(bool enabled);
    Builder& setTimeoutMs(int timeout);
    Builder& setRetryCount(int count);

    SomeIpConfig build() const;

private:
    friend class SomeIpConfig;

    std::uint16_t serviceId_{0};
    std::string serviceName_;
    std::string ipAddress_;
    std::uint16_t tcpPort_{0};
    std::uint16_t udpPort_{0};
    bool serviceDiscovery_{false};
    int timeoutMs_{1000};
    int retryCount_{3};
};