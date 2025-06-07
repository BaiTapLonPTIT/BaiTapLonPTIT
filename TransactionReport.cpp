#include "TransactionReport.h"
#include <iostream>

void TransactionReport::generateReport(const TransactionManager& manager) {
    auto txns = manager.getAllTransactions();
    std::cout << "---- Báo cáo Giao dịch ----\n";
    for (const auto& txn : txns) {
        std::cout << "ID: " << txn->getId()
                  << ", Loại: " << static_cast<int>(txn->getType())
                  << ", Số tiền: " << txn->getAmount()
                  << ", Trạng thái: " << static_cast<int>(txn->getStatus())
                  << "\n";
    }
}
