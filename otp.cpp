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
    static std::map<std::string, std::pair<int, std::chrono::system_clock::time_point>> otpStore;
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
        otpStore[transactionId] = std::make_pair(otp, std::chrono::system_clock::now());
        
        return otp;
    }

    // Xác thực OTP cho một giao dịch
    static bool verifyOTP(const std::string& transactionId, int inputOTP) {
        auto it = otpStore.find(transactionId);
        if (it == otpStore.end()) {
            return false; // Không tìm thấy OTP
        }

        auto& [storedOTP, timestamp] = it->second;
        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - timestamp).count();

        // Kiểm tra OTP hết hạn chưa
        if (elapsed > OTP_VALIDITY_SECONDS) {
            otpStore.erase(it);
            return false;
        }

        // Kiểm tra đúng OTP, nếu đúng thì xóa khỏi map
        if (storedOTP == inputOTP) {
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
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - it->second.second).count();
        return std::max(0, OTP_VALIDITY_SECONDS - static_cast<int>(elapsed));
    }

    // Xóa các OTP đã hết hạn khỏi map
    static void clearExpiredOTPs() {
        auto now = std::chrono::system_clock::now();
        for (auto it = otpStore.begin(); it != otpStore.end();) {
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - it->second.second).count();
            if (elapsed > OTP_VALIDITY_SECONDS) {
                it = otpStore.erase(it);
            } else {
                ++it;
            }
        }
    }
};

// Khởi tạo biến static lưu trữ OTP
std::map<std::string, std::pair<int, std::chrono::system_clock::time_point>> TransactionOTP::otpStore;

// Ví dụ sử dụng lớp TransactionOTP
int main() {
    std::string transactionId = "TX123456";
    
    // Sinh OTP cho giao dịch
    int otp = TransactionOTP::generateOTP(transactionId);
    std::cout << "Generated OTP for transaction " << transactionId << ": " << otp << std::endl;
    
    // Mô phỏng nhập OTP để xác thực
    std::cout << "Enter OTP to verify: ";
    int inputOTP;
    std::cin >> inputOTP;
    
    if (TransactionOTP::verifyOTP(transactionId, inputOTP)) {
        std::cout << "OTP verified successfully!" << std::endl;
    } else {
        std::cout << "Invalid or expired OTP!" << std::endl;
    }
    
    return 0;
}