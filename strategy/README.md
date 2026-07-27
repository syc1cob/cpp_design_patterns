# Strategy Pattern in Modern C++

This project demonstrates the **Strategy Design Pattern** using a simple payment processing example.

---

## What is the Strategy Pattern?

The Strategy Pattern is a **Behavioral Design Pattern** that defines a family of algorithms, encapsulates each one in its own class, and makes them interchangeable at runtime.

Instead of writing long `if-else` or `switch` statements, each algorithm is implemented as a separate strategy class.

---

## Problem

Suppose an application supports multiple payment methods:

- Credit Card
- UPI
- PayPal

A straightforward implementation may look like this:

```cpp
if (paymentType == CreditCard)
{
    ...
}
else if (paymentType == UPI)
{
    ...
}
else if (paymentType == PayPal)
{
    ...
}

                +----------------------+
                |  PaymentStrategy     |
                +----------------------+
                | +Pay()               |
                +----------------------+
                         ▲
         --------------------------------------
         |                |                    |
         |                |                    |
+----------------+ +----------------+ +----------------+
| CreditCard     | | UPI            | | PayPal         |
+----------------+ +----------------+ +----------------+
| Pay()          | | Pay()          | | Pay()          |
+----------------+ +----------------+ +----------------+

                         ▲
                         |
                +----------------------+
                | PaymentProcessor     |
                +----------------------+
                | SetStrategy()        |
                | MakePayment()        |
                +----------------------+


```
Strategy Pattern in Embedded/Automotive

Suppose you're developing an Adaptive AUTOSAR logging framework.

Different output destinations:

Logger
   |
   +--> Console
   |
   +--> DLT
   |
   +--> File
   |
   +--> Network

Each output mechanism is a strategy.

The logger simply calls:

strategy->Log(message);

It doesn't care where the message goes.

This is a common design in middleware such as logging frameworks.

When should you use it?

Use the Strategy Pattern when:

Multiple ways exist to perform the same task.
You want to choose the behavior at runtime.
You want to avoid many if-else or switch statements.
New algorithms should be added without modifying existing code.

Avoid it when there is only one algorithm or when the behavior is unlikely to change.
