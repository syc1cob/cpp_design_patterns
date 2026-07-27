#pragma once

#include <memory>

#include "payment_strategy.h"

class PaymentProcessor
{
public:
    explicit PaymentProcessor(std::unique_ptr<PaymentStrategy> strategy);

    void SetStrategy(std::unique_ptr<PaymentStrategy> strategy);

    void MakePayment(double amount) const;

private:
    std::unique_ptr<PaymentStrategy> m_strategy;
};
