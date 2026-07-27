#include "payment_processor.h"

#include <iostream>
#include <stdexcept>

PaymentProcessor::PaymentProcessor(
    std::unique_ptr<PaymentStrategy> strategy)
    : m_strategy(std::move(strategy))
{
}

void PaymentProcessor::SetStrategy(
    std::unique_ptr<PaymentStrategy> strategy)
{
    m_strategy = std::move(strategy);
}

void PaymentProcessor::MakePayment(double amount) const
{
    if (nullptr == m_strategy)
    {
        throw std::runtime_error("Payment strategy is not set.");
    }

    std::cout << "Processing payment...\n";

    m_strategy->Pay(amount);

    std::cout << "Payment completed.\n\n";
}
