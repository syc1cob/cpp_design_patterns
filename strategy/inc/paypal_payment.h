#pragma once

#include <iostream>
#include "payment_strategy.h"

class PayPalPayment : public PaymentStrategy
{
public:
    void Pay(double amount) const override
    {
        std::cout
            << "[PayPal] Payment successful. Amount = ₹"
            << amount
            << '\n';
    }
};
