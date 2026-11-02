#pragma once

class ConnectionState {
public:
    virtual ~ConnectionState() = default;
    virtual void sendRequest() const = 0;
};