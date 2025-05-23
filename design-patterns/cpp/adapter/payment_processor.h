#pragma once
#include <string>

class PaymentProcessor {
public:
    virtual ~PaymentProcessor() = default;
    virtual void processPayment(double amount, const std::string& currency) = 0;
    virtual bool isPaymentSuccessful() = 0;
    virtual std::string getTransactionId() = 0;
}; 