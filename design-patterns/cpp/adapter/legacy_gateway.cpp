#include "legacy_gateway.h"
#include <iostream>
#include <chrono>

void LegacyGateway::executeTransaction(double totalAmount, const std::string& currency) {
    std::cout << "LegacyGateway: Executing transaction for " << currency << " " << totalAmount << std::endl;
    auto now = std::chrono::high_resolution_clock::now();
    transactionReference = now.time_since_epoch().count();
    isPaymentSuccessful = true;
    std::cout << "LegacyGateway: Transaction executed successfully. Txn ID: " << transactionReference << std::endl;
}

bool LegacyGateway::checkStatus(long transactionReference) {
    std::cout << "LegacyGateway: Checking status for ref: " << transactionReference << std::endl;
    return isPaymentSuccessful;
}

long LegacyGateway::getReferenceNumber() {
    return transactionReference;
} 