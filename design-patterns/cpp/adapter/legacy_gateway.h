#pragma once
#include <string>

class LegacyGateway {
public:
    void executeTransaction(double totalAmount, const std::string& currency);
    bool checkStatus(long transactionReference);
    long getReferenceNumber();

private:
    long transactionReference;
    bool isPaymentSuccessful = false;
}; 