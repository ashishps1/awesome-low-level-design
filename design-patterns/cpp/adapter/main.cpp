#include "in_house_payment_processor.h"
#include "legacy_gateway.h"
#include "legacy_gateway_adapter.h"
#include <iostream>

int main() {
    std::cout << "Adapter Pattern Demo\n" << std::endl;

    // Using the new payment processor
    std::cout << "Using InHousePaymentProcessor:" << std::endl;
    PaymentProcessor* processor = new InHousePaymentProcessor();
    processor->processPayment(100.0, "USD");
    std::cout << "Payment successful: " << (processor->isPaymentSuccessful() ? "Yes" : "No") << std::endl;
    std::cout << "Transaction ID: " << processor->getTransactionId() << std::endl;
    delete processor;

    std::cout << "\nUsing LegacyGateway through adapter:" << std::endl;
    LegacyGateway* legacyGateway = new LegacyGateway();
    PaymentProcessor* adapter = new LegacyGatewayAdapter(legacyGateway);
    adapter->processPayment(200.0, "EUR");
    std::cout << "Payment successful: " << (adapter->isPaymentSuccessful() ? "Yes" : "No") << std::endl;
    std::cout << "Transaction ID: " << adapter->getTransactionId() << std::endl;
    
    delete adapter;
    delete legacyGateway;

    return 0;
} 