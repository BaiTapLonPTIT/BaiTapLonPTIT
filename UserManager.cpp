#include "UserManager.h"
#include <iostream>

using namespace std;

// Hàm thực hiện việc đăng ký người dùng mới
UserAccount* UserManager::login() {
    string username, password;

    cout << "Nhap ten dang nhap: ";
    cin >> username;  // Nhập tên đăng nhập

    cout << "Nhap mat khau: ";
    cin >> password;  // Nhập mật khẩu

    // Duyệt qua danh sách người dùng để kiểm tra thông tin
    for (auto& user : users) {
        if (user.username == username && user.password == password) {
            cout << "Dang nhap thanh cong!\n";
            return &user;  // Trả về con trỏ đến tài khoản nếu đúng
        }
    }

    cout << "Dang nhap that bai!\n";
    return nullptr;  // Trả về nullptr nếu đăng nhập thất bại
}
