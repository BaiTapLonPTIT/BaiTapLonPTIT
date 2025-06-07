#include "Transaction.h"
#include <sstream>
#include <stdexcept>

Transaction::Transaction(const std::string& id,
                         const std::string& walletFrom,
                         const std::string& walletTo,
                         int points,
                         const std::string& timestamp,
                         const std::string& status)
    : id(id), walletFrom(walletFrom), walletTo(walletTo),
      points(points), timestamp(timestamp), status(status) {}

const std::string& Transaction::getId() const { return id; }
const std::string& Transaction::getWalletFrom() const { return walletFrom; }
const std::string& Transaction::getWalletTo() const { return walletTo; }
int Transaction::getPoints() const { return points; }
const std::string& Transaction::getTimestamp() const { return timestamp; }
const std::string& Transaction::getStatus() const { return status; }

std::string Transaction::serialize() const {
    std::ostringstream oss;
    oss << id << "," << walletFrom << "," << walletTo << ","
        << points << "," << timestamp << "," << status;
    return oss.str();
}

Transaction Transaction::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string id, walletFrom, walletTo, timestamp, status;
    int points;

    if (!std::getline(iss, id, ',')) throw std::runtime_error("Invalid data");
    if (!std::getline(iss, walletFrom, ',')) throw std::runtime_error("Invalid data");
    if (!std::getline(iss, walletTo, ',')) throw std::runtime_error("Invalid data");

    std::string pointsStr;
    if (!std::getline(iss, pointsStr, ',')) throw std::runtime_error("Invalid data");
    points = std::stoi(pointsStr);

    if (!std::getline(iss, timestamp, ',')) throw std::runtime_error("Invalid data");
    if (!std::getline(iss, status, ',')) throw std::runtime_error("Invalid data");

    return Transaction(id, walletFrom, walletTo, points, timestamp, status);
}

