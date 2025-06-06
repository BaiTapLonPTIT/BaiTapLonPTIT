#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include "Transaction.h"
#include <vector>
#include <string>

class TransactionManager {
private:
    std::vector<Transaction> transactions;

public:
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename);
    bool backup(const std::string& backupFile);
    void logTransaction(const Transaction& tx);

    // C� th? th�m c�c phuong th?c t�m ki?m, l?c ? d�y
};

#endif // TRANSACTIONMANAGER_H

