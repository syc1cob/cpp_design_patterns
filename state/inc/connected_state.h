#pragma once
#include <iostream>
#include "iconnection_state.h"

class ConnectedState final : public ConnectionState {
public:
    void sendRequest() const override {
        std::cout << "Sending diagnostic request\n";
    }
};
