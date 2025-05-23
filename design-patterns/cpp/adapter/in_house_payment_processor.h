#pragma once
#include "payment_processor.h"
#include <string>

class InHousePaymentProcessor : public PaymentProcessor {
public:
    void processPayment(double amount, const std::string& currency) override;
    bool isPaymentSuccessful() override;
    std::string getTransactionId() override;

private:
    std::string transactionId;
    bool isPaymentSuccessful = false;
}; 