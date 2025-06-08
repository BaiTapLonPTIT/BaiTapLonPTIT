#pragma once  // Ngăn chặn việc include file nhiều lần
#include "Wallet.h"  // Include định nghĩa lớp Wallet
#include <vector>    // Thư viện vector để lưu danh sách ví
#include <string>    // Thư viện xử lý chuỗi
using namespace std; // Sử dụng namespace std

class WalletManager {
public:
    vector<Wallet> wallets;  // Danh sách các ví được quản lý

    // Đọc dữ liệu ví từ file
    bool loadFromFile(const string& filename);

    // Lưu dữ liệu ví vào file
    bool saveToFile(const string& filename);

    // Tạo bản sao lưu dữ liệu ví
    bool backup(const string& backupFile);

    // Tìm ví theo ID
    Wallet* findWallet(const string& walletId);

    // Tìm ví theo tên đăng nhập của chủ ví
    Wallet* findWalletByUser(const string& username);

    // Tạo ví mới cho người dùng
    void createWallet(const string& username);
};