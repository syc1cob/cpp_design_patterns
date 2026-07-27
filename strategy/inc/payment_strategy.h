#pragma once

class PaymentStrategy
{
public:
    virtual ~PaymentStrategy() = default;

    virtual void Pay(double amount) const = 0;
};
