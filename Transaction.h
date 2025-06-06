#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    std::string id;
    std::string walletFrom;
    std::string walletTo;
    int points;
    std::string timestamp;
    std::string status;

public:
    Transaction() = default;
    Transaction(const std::string& id,
                const std::string& walletFrom,
                const std::string& walletTo,
                int points,
                const std::string& timestamp,
                const std::string& status);

    // Getters
    const std::string& getId() const;
    const std::string& getWalletFrom() const;
    const std::string& getWalletTo() const;
    int getPoints() const;
    const std::string& getTimestamp() const;
    const std::string& getStatus() const;

    // Serialize & Deserialize
    std::string serialize() const;
    static Transaction deserialize(const std::string& data);
};

#endif // TRANSACTION_H

