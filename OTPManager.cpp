#include "OTPManager.h"
#include <random>
#include <ctime>

// Ham khoi tao, dat thoi gian tao OTP la 0 va danh dau OTP da su dung
OTPManager::OTPManager() : generatedAt(0), isUsed(true) {}

// Ham tao ma OTP moi cho nguoi dung
void OTPManager::generateOTP(const std::string& username) {
    this->username = username; // Luu ten nguoi dung
    std::random_device rd; // Thiet bi sinh ngau nhien
    std::mt19937 gen(rd()); // Bo sinh so ngau nhien theo thuat toan Mersenne Twister
    std::uniform_int_distribution<> dis(100000, 999999); // Khoang so ngau nhien tu 100000 den 999999
    currentOTP = std::to_string(dis(gen)); // Tao ma OTP gom 6 chu so
    generatedAt = std::time(nullptr); // Luu thoi gian tao OTP
    isUsed = false; // Danh dau OTP chua su dung
}
// Ham kiem tra ma OTP co hop le khong
bool OTPManager::verifyOTP(const std::string& username, const std::string& otp) {
    time_t now = std::time(nullptr);// Lay thoi gian hien tai
    if (isUsed) return false;// Neu OTP da su dung thi tu choi
    if (this->username != username) return false;// Kiem tra ten nguoi dung co khop khong
    if (currentOTP != otp) return false;// Kiem tra OTP co dung khong
    if (now - generatedAt > 300) return false; // // Kiem tra OTP con hieu luc trong 5 phut (300 giay)
    isUsed = true;// Danh dau OTP da su dung
    return true;// OTP hop le
} 