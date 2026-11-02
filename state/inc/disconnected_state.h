#pragma once

#include <iostream>
#include "iconnection_state.h"

class DisconnectedState final : public ConnectionState {
public:
    void sendRequest() const override {
        std::cout << "Rejected: connection unavailable\n";
    }
};