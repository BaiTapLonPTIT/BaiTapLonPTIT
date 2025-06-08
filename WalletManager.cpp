#include <iostream>  // Thư viện nhập xuất chuẩn
#include "WalletManager.h"  // Include định nghĩa lớp WalletManager
#include <fstream>   // Thư viện xử lý file
#include <sstream>   // Thư viện xử lý chuỗi
using namespace std;

// Tạo ví mới cho người dùng
void WalletManager::createWallet(const string& username) {
    // Tạo ID ví bằng cách thêm "W" vào số thứ tự
    string walletId = "W" + to_string(wallets.size() + 1);
    // Thêm ví mới vào danh sách với số dư ban đầu là 0
    wallets.push_back(Wallet(walletId, username, 0));
    cout << "Tao vi thanh cong! ID vi: " << walletId << endl;
}

// Đọc dữ liệu ví từ file
bool WalletManager::loadFromFile(const string& filename) {
    wallets.clear();  // Xóa danh sách ví hiện tại
    ifstream fin(filename);  // Mở file để đọc
    if (!fin) return false;  // Kiểm tra file có mở thành công không
    string line;
    // Đọc từng dòng trong file
    while (getline(fin, line)) {
        if (!line.empty()) wallets.push_back(Wallet::deserialize(line));  // Chuyển đổi dữ liệu thành ví và thêm vào danh sách
    }
    return true;
}

// Lưu dữ liệu ví vào file
bool WalletManager::saveToFile(const string& filename) {
    ofstream fout(filename);  // Mở file để ghi
    if (!fout) return false;  // Kiểm tra file có mở thành công không
    // Ghi thông tin từng ví vào file
    for (const auto& wallet : wallets) {
        fout << wallet.serialize() << "\n";
    }
    return true;
}

// Tạo bản sao lưu dữ liệu ví
bool WalletManager::backup(const string& backupFile) {
    return saveToFile(backupFile);  // Sử dụng hàm saveToFile để tạo bản sao lưu
}

// Tìm ví theo ID
Wallet* WalletManager::findWallet(const string& walletId) {
    // Duyệt qua danh sách ví để tìm ví có ID trùng khớp
    for (auto& wallet : wallets) {
        if (wallet.walletId == walletId) return &wallet;
    }
    return nullptr;  // Không tìm thấy ví
}

// Tìm ví theo tên đăng nhập của chủ ví
Wallet* WalletManager::findWalletByUser(const string& username) {
    // Duyệt qua danh sách ví để tìm ví của người dùng
    for (auto& wallet : wallets) {
        if (wallet.ownerUsername == username) return &wallet;
    }
    return nullptr;  // Không tìm thấy ví
} 