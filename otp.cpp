#include <iostream>      // Thư viện nhập xuất chuẩn
#include <cstdlib>       // Thư viện cho hàm rand, srand
#include <ctime>         // Thư viện thời gian C
#include <string>        // Thư viện xử lý chuỗi
#include <map>           // Thư viện map
#include <chrono>        // Thư viện thời gian hiện đại

// Lớp quản lý OTP cho giao dịch
class TransactionOTP {
private:
    // Lưu trữ OTP theo transactionId, kèm thời điểm tạo
    struct OTPData {
        int otp;
        std::chrono::system_clock::time_point timestamp;
    };
    static std::map<std::string, OTPData> otpStore;
    static const int OTP_VALIDITY_SECONDS = 300; // Thời gian hiệu lực OTP (5 phút)

public:
    // Sinh OTP cho một giao dịch, lưu lại thời điểm tạo
    static int generateOTP(const std::string& transactionId) {
        // Khởi tạo seed cho random nếu chưa có
        static bool seeded = false;
        if (!seeded) {
            srand(time(0));
            seeded = true;
        }

        // Sinh OTP 6 chữ số
        int otp = 100000 + rand() % 900000;
        
        // Lưu OTP cùng thời điểm tạo vào map
        OTPData data;
        data.otp = otp;
        data.timestamp = std::chrono::system_clock::now();
        otpStore[transactionId] = data;
        
        return otp;
    }

    // Xác thực OTP cho một giao dịch
    static bool verifyOTP(const std::string& transactionId, int inputOTP) {
        auto it = otpStore.find(transactionId);
        if (it == otpStore.end()) {
            return false; // Không tìm thấy OTP
        }

        const OTPData& data = it->second;
        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            now - data.timestamp).count();

        // Kiểm tra OTP hết hạn chưa
        if (elapsed > OTP_VALIDITY_SECONDS) {
            otpStore.erase(it);
            return false;
        }

        // Kiểm tra đúng OTP, nếu đúng thì xóa khỏi map
        if (data.otp == inputOTP) {
            otpStore.erase(it);
            return true;
        }
        return false;
    }

    // Lấy thời gian còn lại của OTP
    static int getRemainingTime(const std::string& transactionId) {
        auto it = otpStore.find(transactionId);
        if (it == otpStore.end()) {
            return 0;
        }

        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - it->second.timestamp).count();
        return std::max(0, OTP_VALIDITY_SECONDS - static_cast<int>(elapsed));
    }

    // Xóa các OTP đã hết hạn khỏi map
    static void clearExpiredOTPs() {
        auto now = std::chrono::system_clock::now();
        for (auto it = otpStore.begin(); it != otpStore.end();) {
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - it->second.timestamp).count();
            if (elapsed > OTP_VALIDITY_SECONDS) {
                it = otpStore.erase(it);
            } else {
                ++it;
            }
        }
    }
};

// Khởi tạo static member
std::map<std::string, TransactionOTP::OTPData> TransactionOTP::otpStore;