#pragma once  // Đảm bảo file header chỉ include một lần

#include "UserAccount.h"  // Sử dụng lớp UserAccount
#include <vector>         // Dùng để lưu danh sách người dùng
#include <string>

// Lớp UserManager quản lý đăng ký và đăng nhập
class UserManager {
private:
    std::vector<UserAccount> users;  // Danh sách các người dùng đã đăng ký

public:
    void registerUser();     // Hàm xử lý đăng ký
    UserAccount* login();    // Hàm xử lý đăng nhập, trả về con trỏ đến UserAccount nếu thành công
};
