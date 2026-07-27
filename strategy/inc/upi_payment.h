#pragma once

#include <iostream>
#include "payment_strategy.h"

class UPIPayment : public PaymentStrategy
{
public:
    void Pay(double amount) const override
    {
        std::cout
            << "[UPI] Payment successful. Amount = ₹"
            << amount
            << '\n';
    }
};
