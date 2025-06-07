#include "utils.h"
#include <random>
#include <ctime>
#include <sstream>

// Ham tao mat khau ngau nhien voi do dai do nguoi dung chi dinh
std::string generateRandomPassword(int length) {    
     // Tap ky tu su dung trong mat khau (chu thuong, chu hoa, so va ky tu dac biet)
    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
    std::random_device rd; // Thiet bi sinh ngau nhien
    std::mt19937 gen(rd()); // Bo sinh so ngau nhien theo thuat toan Mersenne Twister
    std::uniform_int_distribution<> dis(0, chars.size() - 1);// Phan bo ngau nhien tu 0 den kich thuoc tap ky tu - 1
    std::string pw; // Bien chua mat khau duoc tao ra

    // Lap de tao mat khau co do dai nhu yeu cau
    for (int i = 0; i < length; ++i) 
    pw += chars[dis(gen)]; // Lay ngau nhien 1 ky tu tu tap va noi vao chuoi
    return pw; // Tra ve mat khau ngau nhien
}

// Ham tao ma OTP ngau nhien 6 chu so
std::string generateRandomOTP() {
    std::random_device rd; // Thiet bi sinh ngau nhien
    std::mt19937 gen(rd()); // Bo sinh so ngau nhien
    std::uniform_int_distribution<> dis(100000, 999999); // Phan bo ngau nhien tu 100000 den 999999
    
    return std::to_string(dis(gen)); // Tra ve OTP duoi dang chuoi
}

// Ham lay thoi gian hien tai duoi dang chuoi (vi du: 2025-06-07 14:30:15)
std::string getCurrentTimeString() {
    std::time_t now = std::time(nullptr); // Lay thoi gian he thong
    char buf[32]; // Bo dem de luu chuoi thoi gian
    // Dinh dang thoi gian thanh chuoi co dang nam-thang-ngay gio:phut:giay
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return buf; // Tra ve chuoi thoi gian
} 