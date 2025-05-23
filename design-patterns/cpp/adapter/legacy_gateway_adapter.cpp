#include "legacy_gateway_adapter.h"
#include <iostream>

LegacyGatewayAdapter::LegacyGatewayAdapter(LegacyGateway* legacyGateway) 
    : legacyGateway(legacyGateway) {}

void LegacyGatewayAdapter::processPayment(double amount, const std::string& currency) {
    std::cout << "LegacyGatewayAdapter: Processing payment of " << amount << " " << currency << std::endl;
    legacyGateway->executeTransaction(amount, currency);
    std::cout << "LegacyGatewayAdapter: Payment processed successfully. Txn ID: " 
              << legacyGateway->getReferenceNumber() << std::endl;
}

bool LegacyGatewayAdapter::isPaymentSuccessful() {
    return legacyGateway->checkStatus(legacyGateway->getReferenceNumber());
}

std::string LegacyGatewayAdapter::getTransactionId() {
    return std::to_string(legacyGateway->getReferenceNumber());
} 