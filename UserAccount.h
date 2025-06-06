#pragma once  // Chỉ định rằng file này chỉ nên được include một lần trong quá trình biên dịch

#include <string>  // Dùng để sử dụng kiểu std::string

// Lớp UserAccount đại diện cho tài khoản người dùng
class UserAccount {
public:
    std::string username;  // Tên đăng nhập
    std::string password;  // Mật khẩu

    // Constructor: khởi tạo đối tượng UserAccount với tên và mật khẩu
    UserAccount(const std::string& uname, const std::string& pwd)
        : username(uname), password(pwd) {}
};
