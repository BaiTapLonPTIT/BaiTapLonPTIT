#include "Wallet.h"  // Include định nghĩa lớp Wallet
#include <sstream>   // Thư viện xử lý chuỗi
#include <vector>    // Thư viện vector để lưu trữ dữ liệu

// Constructor mặc định: khởi tạo ví với số dư = 0
Wallet::Wallet() : balance(0) {}

// Constructor đầy đủ tham số: khởi tạo ví với thông tin đầy đủ
Wallet::Wallet(const std::string& walletId, const std::string& ownerUsername, int balance)
    : walletId(walletId), ownerUsername(ownerUsername), balance(balance) {}

// Chuyển đổi thông tin ví thành chuỗi để lưu vào file
std::string Wallet::serialize() const {
    std::ostringstream oss;  // Tạo đối tượng stringstream để ghi dữ liệu
    // Ghi các thông tin của ví, phân cách bằng dấu phẩy
    oss << walletId << ',' << ownerUsername << ',' << balance;
    return oss.str();  // Trả về chuỗi đã tạo
}

// Tạo đối tượng ví từ chuỗi dữ liệu đọc từ file
Wallet Wallet::deserialize(const std::string& data) {
    std::istringstream iss(data);  // Tạo đối tượng stringstream để đọc dữ liệu
    std::string token;             // Biến tạm để lưu từng phần dữ liệu
    std::vector<std::string> tokens;  // Vector lưu các phần dữ liệu sau khi tách
    
    // Tách chuỗi dữ liệu theo dấu phẩy
    while (std::getline(iss, token, ',')) tokens.push_back(token);
    
    // Kiểm tra dữ liệu có đủ 3 trường không (ID, username, balance)
    if (tokens.size() < 3) return Wallet();  // Nếu không đủ, trả về ví rỗng
    
    // Tạo và trả về ví mới với dữ liệu đã đọc
    return Wallet(tokens[0], tokens[1], std::stoi(tokens[2]));
} 