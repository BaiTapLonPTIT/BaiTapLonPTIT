// TransactionReport.h
#ifndef TRANSACTION_REPORT_H
#define TRANSACTION_REPORT_H

#include "../Transaction.h"
#include <vector>
#include <string>

class TransactionReport {
public:
    TransactionReport(const std::vector<Transaction>& transactions);

    void printSummaryReport() const;
    double getTotalAmount() const;
    int getTransactionCountByType(TransactionType type) const;

private:
    std::vector<Transaction> transactions;
};

#endif

