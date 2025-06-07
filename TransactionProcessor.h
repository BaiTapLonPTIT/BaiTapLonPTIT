// TransactionProcessor.h
#ifndef TRANSACTION_PROCESSOR_H
#define TRANSACTION_PROCESSOR_H

#include "../Transaction.h"
#include "../TransactionManager.h"
#include <string>

class TransactionProcessor {
public:
    TransactionProcessor(TransactionManager& manager);
    
    bool processTransaction(const Transaction& transaction);
    bool rollbackTransaction(const std::string& transactionId);

private:
    TransactionManager& transactionManager;

    bool validateTransaction(const Transaction& transaction);
    void applyTransaction(const Transaction& transaction);
};

#endif

