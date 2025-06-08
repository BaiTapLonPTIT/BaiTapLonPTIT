#include "Transaction.h"
#include <sstream>
#include <vector>

// Ham khoi tao mac dinh cua Transaction
Transaction::Transaction() : amount(0), timestamp(0), status("pending") {}

// Ham khoi tao co tham so day du
Transaction::Transaction(
    const std::string& transactionId,     // Ma giao dich
    const std::string& fromWalletId,      // Vi nguon
    const std::string& toWalletId,        // Vi dich
    int amount,                           // So tien giao dich
    time_t timestamp,                     // Thoi diem giao dich (UNIX timestamp)
    const std::string& status             // Trang thai giao dich
)
    : transactionId(transactionId),
      fromWalletId(fromWalletId),
      toWalletId(toWalletId),
      amount(amount),
      timestamp(timestamp),
      status(status) {}

// Ham chuyen doi doi tuong Transaction thanh chuoi CSV de luu file
std::string Transaction::serialize() const {
    std::ostringstream oss; // Tao stream de ghi chuoi
    oss << transactionId << ','           // Ma giao dich
        << fromWalletId << ','            // Vi nguon
        << toWalletId << ','              // Vi dich
        << amount << ','                  // So tien
        << timestamp << ','               // Thoi gian
        << status;                        // Trang thai
    return oss.str(); // Tra ve chuoi da ghep
}

// Ham chuyen chuoi CSV thanh doi tuong Transaction
Transaction Transaction::deserialize(const std::string& data) {
    std::istringstream iss(data); // Tao stream de doc chuoi
    std::string token;            // Bien tam de luu tru truong
    std::vector<std::string> tokens; // Luu tat ca cac truong tach duoc

    // Tach chuoi theo dau ',' va luu vao vector tokens
    while (std::getline(iss, token, ',')) 
        tokens.push_back(token);

    // Neu so truong < 6 thi tra ve doi tuong mac dinh
    if (tokens.size() < 6) return Transaction();

    // Tao doi tuong Transaction tu vector tokens
    return Transaction(
        tokens[0],                          // transactionId
        tokens[1],                          // fromWalletId
        tokens[2],                          // toWalletId
        std::stoi(tokens[3]),               // amount (chuyen tu chuoi sang int)
        std::stol(tokens[4]),               // timestamp (chuyen tu chuoi sang long)
        tokens[5]                           // status
    );
}
