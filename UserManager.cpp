#include "UserManager.h"
#include <iostream>  // Dùng để nhập xuất

// Hàm thực hiện việc đăng ký người dùng mới
void UserManager::registerUser() {
    std::string username, password;

    std::cout << "Nhap ten dang nhap: ";
    std::cin >> username;  // Nhập tên người dùng từ bàn phím

    std::cout << "Nhap mat khau: ";
    std::cin >> password;  // Nhập mật khẩu từ bàn phím

    // Thêm người dùng mới vào danh sách
    users.push_back(UserAccount(username, password));

    std::cout << "Dang ky thanh cong!\n";
}
