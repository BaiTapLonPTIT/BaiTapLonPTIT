// TransactionProcessor.cpp
#include "TransactionProcessor.h"
#include <iostream>

TransactionProcessor::TransactionProcessor(TransactionManager& manager)
    : transactionManager(manager) {}

bool TransactionProcessor::validateTransaction(const Transaction& transaction) {
    // Ki?m tra s? ti?n h?p l?
    if (transaction.getAmount() <= 0) return false;

    // Các di?u ki?n b? sung
    if (transaction.getFromWalletId().empty() || transaction.getToWalletId().empty())
        return false;

    return true;
}

void TransactionProcessor::applyTransaction(const Transaction& transaction) {
    // Th?c thi giao d?ch
    transactionManager.addTransaction(transaction);
}

bool TransactionProcessor::processTransaction(const Transaction& transaction) {
    if (!validateTransaction(transaction)) {
        std::cerr << "Giao d?ch không h?p l?!" << std::endl;
        return false;
    }

    applyTransaction(transaction);
    return true;
}

bool TransactionProcessor::rollbackTransaction(const std::string& transactionId) {
    return transactionManager.removeTransaction(transactionId);
}


