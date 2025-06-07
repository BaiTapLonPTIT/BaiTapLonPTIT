// TransactionReport.cpp
#include "TransactionReport.h"
#include <iostream>
#include <map>

TransactionReport::TransactionReport(const std::vector<Transaction>& transactions)
    : transactions(transactions) {}

void TransactionReport::printSummaryReport() const {
    std::cout << "===== Báo cáo giao d?ch =====" << std::endl;
    std::cout << "T?ng s? giao d?ch: " << transactions.size() << std::endl;
    std::cout << "T?ng s? ti?n: " << getTotalAmount() << " VND" << std::endl;

    std::map<TransactionType, int> counts;
    for (const auto& tx : transactions) {
        counts[tx.getType()]++;
    }

    for (const auto& pair : counts) {
        std::string typeStr;
        switch (pair.first) {
            case TransactionType::TRANSFER: typeStr = "Chuy?n kho?n"; break;
            case TransactionType::DEPOSIT: typeStr = "N?p ti?n"; break;
            case TransactionType::WITHDRAW: typeStr = "Rút ti?n"; break;
        }
        std::cout << "- " << typeStr << ": " << pair.second << " giao d?ch" << std::endl;
    }
}

double TransactionReport::getTotalAmount() const {
    double total = 0;
    for (const auto& tx : transactions) {
        total += tx.getAmount();
    }
    return total;
}

int TransactionReport::getTransactionCountByType(TransactionType type) const {
    int count = 0;
    for (const auto& tx : transactions) {
        if (tx.getType() == type)
            count++;
    }
    return count;
}


