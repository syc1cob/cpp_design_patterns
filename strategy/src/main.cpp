#include <memory>

#include "credit_card_payment.h"
#include "payment_processor.h"
#include "paypal_payment.h"
#include "upi_payment.h"

int main()
{
    PaymentProcessor processor(
        std::make_unique<CreditCardPayment>());

    processor.MakePayment(1500);

    processor.SetStrategy(
        std::make_unique<UPIPayment>());

    processor.MakePayment(750);

    processor.SetStrategy(
        std::make_unique<PayPalPayment>());

    processor.MakePayment(2500);

    return 0;
}
