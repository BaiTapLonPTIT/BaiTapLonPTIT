#include "utils.h"
#include <random>
#include <ctime>
#include <sstream>
#include <algorithm>  

// Ham tao mat khau ngau nhien voi do dai do nguoi dung chi dinh
std::string generateRandomPassword(int length) {    
    // Tap ky tu su dung trong mat khau (chu thuong, chu hoa, so va ky tu dac biet)
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string numbers = "0123456789";
    const std::string special = "!@#$%^&*()";
    const std::string all_chars = lowercase + uppercase + numbers + special;

    // Khoi tao bo sinh so ngau nhien voi seed tu thiet bi ngau nhien va thoi gian
    std::random_device rd;
    std::mt19937 gen(rd() ^ static_cast<unsigned int>(std::time(nullptr)));
    
    // Tao mat khau voi it nhat 1 ky tu tu moi tap
    std::string pw;
    std::uniform_int_distribution<> dis(0, all_chars.size() - 1);
    
    // Them it nhat 1 ky tu tu moi tap
    pw += lowercase[gen() % lowercase.size()];
    pw += uppercase[gen() % uppercase.size()];
    pw += numbers[gen() % numbers.size()];
    pw += special[gen() % special.size()];
    
    // Them cac ky tu con lai
    for (int i = 4; i < length; ++i) {
        pw += all_chars[dis(gen)];
    }
    
    // Xao tron mat khau
    std::shuffle(pw.begin(), pw.end(), gen);
    
    return pw;
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