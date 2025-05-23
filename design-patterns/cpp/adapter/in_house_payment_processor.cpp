#include "in_house_payment_processor.h"
#include <iostream>
#include <chrono>
#include <sstream>

void InHousePaymentProcessor::processPayment(double amount, const std::string& currency) {
    std::cout << "InHousePaymentProcessor: Processing payment of " << amount << " " << currency << std::endl;
    // Process payment logic
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    transactionId = "TXN_" + std::to_string(now_ms.count());
    isPaymentSuccessful = true;
    std::cout << "InHousePaymentProcessor: Payment successful. Txn ID: " << transactionId << std::endl;
}

bool InHousePaymentProcessor::isPaymentSuccessful() {
    return isPaymentSuccessful;
}

std::string InHousePaymentProcessor::getTransactionId() {
    return transactionId;
} 