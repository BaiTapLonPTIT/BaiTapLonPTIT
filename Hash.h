#pragma once // Đảm bảo file chỉ được include một lần
#include <string>      // Thư viện xử lý chuỗi
#include <functional>  // Thư viện cho std::function
#include <sstream>     // Thư viện xử lý stringstream
#include <iomanip>     // Thư viện định dạng xuất nhập

// Khai báo hàm băm SHA-256, định nghĩa ở file .cpp
std::string sha256(const std::string& str); // Trả về chuỗi băm SHA-256 của chuỗi đầu vào 