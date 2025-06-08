#pragma once  // Ngăn chặn việc include file nhiều lần
#include <string>  // Thư viện xử lý chuỗi

class Wallet {
public:
    std::string walletId;        // ID duy nhất của ví
    std::string ownerUsername;   // Tên đăng nhập của chủ ví
    int balance;                 // Số dư trong ví

    // Constructor mặc định
    Wallet();

    // Constructor với đầy đủ thông tin
    Wallet(const std::string& walletId, const std::string& ownerUsername, int balance);

    // Chuyển đổi thông tin ví thành chuỗi để lưu file
    std::string serialize() const;

    // Tạo đối tượng ví từ chuỗi dữ liệu đọc từ file
    static Wallet deserialize(const std::string& data);
}; 