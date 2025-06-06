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

    // Có th? thêm các phuong th?c tìm ki?m, l?c ? dây
};

#endif // TRANSACTIONMANAGER_H

