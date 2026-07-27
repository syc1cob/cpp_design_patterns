#pragma once

#include <iostream>
#include "payment_strategy.h"

class CreditCardPayment : public PaymentStrategy
{
public:
    void Pay(double amount) const override
    {
        std::cout
            << "[Credit Card] Payment successful. Amount = ₹"
            << amount
            << '\n';
    }
};
