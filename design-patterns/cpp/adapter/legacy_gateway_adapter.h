#pragma once
#include "payment_processor.h"
#include "legacy_gateway.h"

class LegacyGatewayAdapter : public PaymentProcessor {
public:
    explicit LegacyGatewayAdapter(LegacyGateway* legacyGateway);
    void processPayment(double amount, const std::string& currency) override;
    bool isPaymentSuccessful() override;
    std::string getTransactionId() override;

private:
    LegacyGateway* legacyGateway;
}; 