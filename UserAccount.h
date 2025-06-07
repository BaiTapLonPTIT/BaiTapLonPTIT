#pragma once  // Chỉ định rằng file này chỉ nên được include một lần trong quá trình biên dịch

#include <string>

using namespace std;

// Lớp UserAccount đại diện cho tài khoản người dùng
class UserAccount {
public:
    string username;  // Tên đăng nhập
    string password;  // Mật khẩu

    // Constructor: khởi tạo đối tượng UserAccount với tên và mật khẩu
    UserAccount(const string& uname, const string& pwd)
        : username(uname), password(pwd) {}
};
