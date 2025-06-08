#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
#include "UserManager.h"
#include "WalletManager.h"
#include "TransactionManager.h"
#include "OTPManager.h"
#include "utils.h"
#include "Hash.h"

// Hàm cấu hình console để hiển thị tiếng Việt
void setupConsole() {
    SetConsoleOutputCP(65001);  // Đặt code page UTF-8 cho output
    SetConsoleCP(65001);        // Đặt code page UTF-8 cho input
}

// Định nghĩa các đường dẫn file
const std::string USER_FILE = "data/users.dat";           // File lưu thông tin người dùng
const std::string WALLET_FILE = "data/wallets.dat";       // File lưu thông tin ví
const std::string TX_FILE = "data/transactions.dat";      // File lưu thông tin giao dịch
const std::string USER_BK = "data/backup/users_backup.dat";    // File backup người dùng
const std::string WALLET_BK = "data/backup/wallets_backup.dat"; // File backup ví
const std::string TX_BK = "data/backup/transactions_backup.dat"; // File backup giao dịch
const std::string ADMIN_FILE = "data/admin.dat";          // File lưu thông tin admin

// Hàm tạo thư mục dữ liệu nếu chưa tồn tại
void ensureDataDirs() {
    CreateDirectoryA("data", NULL);           // Tạo thư mục data
    CreateDirectoryA("data/backup", NULL);    // Tạo thư mục backup
}

// Hàm hiển thị menu chính
void showMenu() {
    std::cout << "\n===== HỆ THỐNG QUẢN LÝ ĐĂNG NHẬP & VÍ ĐIỂM =====\n";
    std::cout << "1. Đăng ký tài khoản\n";
    std::cout << "2. Đăng nhập\n";
    std::cout << "3. Đăng nhập Admin\n";
    std::cout << "4. Backup dữ liệu\n";
    std::cout << "5. Phục hồi dữ liệu\n";
    std::cout << "0. Thoát\n";
    std::cout << "Chọn: ";
}

// Hàm hiển thị menu admin
void showAdminMenu() {
    std::cout << "\n===== MENU QUẢN TRỊ VIÊN =====\n";
    std::cout << "1. Xem danh sách người dùng\n";
    std::cout << "2. Xem thông tin ví\n";
    std::cout << "3. Tạo tài khoản mới\n";
    std::cout << "4. Điều chỉnh thông tin tài khoản\n";
    std::cout << "0. Đăng xuất\n";
    std::cout << "Chọn: ";
}

// Hàm tách chuỗi theo delimiter
std::vector<std::string> split(const std::string& str, char delim) {
    std::vector<std::string> tokens;          // Vector lưu các token
    std::stringstream ss(str);                // Tạo stringstream từ chuỗi đầu vào
    std::string token;                        // Biến lưu token tạm thời
    while (std::getline(ss, token, delim)) {  // Đọc từng token cho đến khi hết
        tokens.push_back(token);              // Thêm token vào vector
    }
    return tokens;                            // Trả về vector chứa các token
}

int main() {
    setupConsole();      // Cấu hình console để hiển thị tiếng Việt
    ensureDataDirs();    // Tạo các thư mục cần thiết
    
    // Khởi tạo các đối tượng quản lý
    UserManager userMgr;         // Quản lý người dùng
    WalletManager walletMgr;     // Quản lý ví
    TransactionManager txMgr;    // Quản lý giao dịch
    
    // Tải dữ liệu từ file
    userMgr.loadFromFile(USER_FILE);     // Tải thông tin người dùng
    walletMgr.loadFromFile(WALLET_FILE); // Tải thông tin ví
    txMgr.loadFromFile(TX_FILE);         // Tải thông tin giao dịch
    
    OTPManager otpMgr;    // Khởi tạo quản lý OTP
    int choice;           // Biến lưu lựa chọn menu
    
    while (true) {
        showMenu();       // Hiển thị menu chính
        std::cin >> choice;   // Nhập lựa chọn
        std::cin.ignore();    // Xóa buffer
        
        if (choice == 1) {
            // Xử lý đăng ký tài khoản
            std::string username, password, fullName, email, phone;
            std::cout << "Tên đăng nhập: "; std::getline(std::cin, username);
            std::cout << "Họ tên: "; std::getline(std::cin, fullName);
            std::cout << "Email: "; std::getline(std::cin, email);
            std::cout << "Số điện thoại: "; std::getline(std::cin, phone);
            std::cout << "Mật khẩu (bỏ trống để tự sinh): "; std::getline(std::cin, password);
            
            bool autoPw = false;    // Biến kiểm tra mật khẩu tự sinh
            if (password.empty()) {
                password = generateRandomPassword();    // Tự sinh mật khẩu
                autoPw = true;
                std::cout << "Mật khẩu tự sinh: " << password << "\n";
            }
            
            std::string walletId = "WALLET_" + username;    // Tạo ID ví từ username
            // Tạo tài khoản mới với thông tin đã nhập
            UserAccount acc(username, sha256(password), fullName, email, phone, UserRole::USER, autoPw, std::time(nullptr), 0, walletId);
            
            // Kiểm tra username đã tồn tại
            if (userMgr.findUser(username)) {
                std::cout << "Tên đăng nhập đã tồn tại!\n";
                continue;
            }

            // Thêm user và ví mới vào bộ nhớ
            userMgr.users.push_back(acc);
            walletMgr.wallets.push_back(Wallet(walletId, username, 0));

            // Lưu thông tin vào file users.dat
            std::ofstream userFile(USER_FILE, std::ios::app);
            if (userFile.is_open()) {
                userFile << username << "," << sha256(password) << "," << fullName << "," 
                        << email << "," << phone << "," << "0" << "," << (autoPw ? "1" : "0") 
                        << "," << std::time(nullptr) << "," << "0" << "," << walletId << "\n";
                userFile.close();
            } else {
                std::cout << "Lỗi khi lưu thông tin người dùng!\n";
                continue;
            }

            // Lưu thông tin vào file wallets.dat
            std::ofstream walletFile(WALLET_FILE, std::ios::app);
            if (walletFile.is_open()) {
                walletFile << walletId << "," << username << ",0\n";
                walletFile.close();
            } else {
                std::cout << "Lỗi khi lưu thông tin ví!\n";
                continue;
            }

            // Cập nhật lại dữ liệu trong bộ nhớ
            userMgr.loadFromFile(USER_FILE);
            walletMgr.loadFromFile(WALLET_FILE);

            std::cout << "Đăng ký thành công!\n";
            
            // Hiển thị thông tin đã lưu để kiểm tra
            std::cout << "\nThông tin đã lưu:\n";
            std::cout << "File users.dat:\n";
            std::ifstream checkUser(USER_FILE);
            std::string line;
            while (std::getline(checkUser, line)) {
                std::cout << line << "\n";
            }
            checkUser.close();

            std::cout << "\nFile wallets.dat:\n";
            std::ifstream checkWallet(WALLET_FILE);
            while (std::getline(checkWallet, line)) {
                std::cout << line << "\n";
            }
            checkWallet.close();
        } else if (choice == 2) {
            // Xử lý đăng nhập người dùng
            std::string username, password;
            std::cout << "Tên đăng nhập: "; std::getline(std::cin, username);
            std::cout << "Mật khẩu: "; std::getline(std::cin, password);
            
            UserAccount* user = nullptr;    // Con trỏ lưu thông tin người dùng đăng nhập
            if (userMgr.login(username, password, user)) {
                std::cout << "Đăng nhập thành công!\n";
                // Menu người dùng
                while (true) {
                    std::cout << "\n--- Xin chào, " << user->fullName << " ---\n";
                    std::cout << "1. Xem số dư ví\n";
                    std::cout << "2. Chuyển điểm\n";
                    std::cout << "3. Xem lịch sử giao dịch\n";
                    std::cout << "4. Đổi mật khẩu\n";
                    std::cout << "0. Đăng xuất\n";
                    std::cout << "Chọn: ";
                    int sub;
                    std::cin >> sub; std::cin.ignore();
                    
                    if (sub == 1) {
                        // Xem số dư ví
                        Wallet* w = walletMgr.findWalletByUser(user->username);
                        if (w) std::cout << "Số dư: " << w->balance << " điểm\n";
                        else std::cout << "Không tìm thấy ví!\n";
                    } else if (sub == 2) {
                        // Xử lý chuyển điểm
                        std::string toUser; int amount;
                        std::cout << "Chuyển tới (username): "; std::getline(std::cin, toUser);
                        std::cout << "Số điểm: "; std::cin >> amount; std::cin.ignore();
                        
                        // Kiểm tra ví nguồn và đích
                        Wallet* fromW = walletMgr.findWalletByUser(user->username);
                        Wallet* toW = walletMgr.findWalletByUser(toUser);
                        if (!fromW || !toW) { std::cout << "Ví không tồn tại!\n"; continue; }
                        if (fromW->balance < amount) { std::cout << "Không đủ số dư!\n"; continue; }
                        
                        // Xác thực OTP
                        otpMgr.generateOTP(user->username);
                        std::cout << "Mã OTP gửi tới bạn (demo): " << otpMgr.currentOTP << "\n";
                        std::string otp;
                        std::cout << "Nhập OTP: "; std::getline(std::cin, otp);
                        if (!otpMgr.verifyOTP(user->username, otp)) {
                            std::cout << "OTP không hợp lệ!\n"; continue;
                        }
                        
                        // Thực hiện chuyển điểm
                        fromW->balance -= amount;
                        toW->balance += amount;
                        Transaction tx("TX" + std::to_string(txMgr.transactions.size()+1), 
                                     fromW->walletId, toW->walletId, amount, 
                                     std::time(nullptr), "success");
                        txMgr.logTransaction(tx);
                        
                        // Lưu thay đổi vào file
                        walletMgr.saveToFile(WALLET_FILE);
                        txMgr.saveToFile(TX_FILE);
                        std::cout << "Chuyển điểm thành công!\n";
                    } else if (sub == 3) {
                        // Hiển thị lịch sử giao dịch
                        std::cout << "Lịch sử giao dịch:\n";
                        for (const auto& tx : txMgr.transactions) {
                            if (tx.fromWalletId == user->walletId || tx.toWalletId == user->walletId) {
                                std::cout << "ID: " << tx.transactionId << ", Từ: " << tx.fromWalletId 
                                         << ", Đến: " << tx.toWalletId << ", Số điểm: " << tx.amount 
                                         << ", Thời gian: " << getCurrentTimeString() 
                                         << ", Trạng thái: " << tx.status << "\n";
                            }
                        }
                    } else if (sub == 4) {
                        // Xử lý đổi mật khẩu
                        std::string oldPw, newPw;
                        std::cout << "Mật khẩu cũ: "; std::getline(std::cin, oldPw);
                        if (!userMgr.login(user->username, oldPw, user)) {
                            std::cout << "Sai mật khẩu!\n"; continue;
                        }
                        std::cout << "Mật khẩu mới: "; std::getline(std::cin, newPw);
                        userMgr.changePassword(*user, newPw);
                        userMgr.saveToFile(USER_FILE);
                        std::cout << "Đổi mật khẩu thành công!\n";
                    } else if (sub == 0) {
                        break;    // Thoát menu người dùng
                    }
                }
            } else {
                std::cout << "Đăng nhập thất bại!\n";
            }
        } else if (choice == 3) {
            // Xử lý đăng nhập admin
            std::string username, password;
            std::cout << "Tên đăng nhập Admin: "; std::getline(std::cin, username);
            std::cout << "Mật khẩu: "; std::getline(std::cin, password);
            
            // Kiểm tra thông tin admin từ file
            std::ifstream adminFile(ADMIN_FILE);
            std::string adminLine;
            bool adminFound = false;
            
            if (adminFile.is_open()) {
                while (std::getline(adminFile, adminLine)) {
                    std::vector<std::string> adminData = split(adminLine, ',');
                    if (adminData.size() >= 2 && adminData[0] == username && adminData[1] == sha256(password)) {
                        adminFound = true;
                        break;
                    }
                }
                adminFile.close();
            }
            
            if (adminFound) {
                std::cout << "Đăng nhập Admin thành công!\n";
                while (true) {
                    showAdminMenu();
                    int adminChoice;
                    std::cin >> adminChoice;
                    std::cin.ignore();
                    
                    if (adminChoice == 1) {
                        // Hiển thị danh sách người dùng
                        std::cout << "\nDanh sách người dùng:\n";
                        std::ifstream userFile(USER_FILE);
                        std::string userLine;
                        while (std::getline(userFile, userLine)) {
                            std::vector<std::string> userData = split(userLine, ',');
                            if (userData.size() >= 5) {
                                std::cout << "Username: " << userData[0] << "\n";
                                std::cout << "Họ tên: " << userData[2] << "\n";
                                std::cout << "Email: " << userData[3] << "\n";
                                std::cout << "Số điện thoại: " << userData[4] << "\n";
                                std::cout << "------------------------\n";
                            }
                        }
                        userFile.close();
                    } else if (adminChoice == 2) {
                        // Hiển thị thông tin ví
                        std::cout << "\nThông tin ví:\n";
                        std::ifstream walletFile(WALLET_FILE);
                        std::string walletLine;
                        while (std::getline(walletFile, walletLine)) {
                            std::vector<std::string> walletData = split(walletLine, ',');
                            if (walletData.size() >= 3) {
                                std::cout << "ID Ví: " << walletData[0] << "\n";
                                std::cout << "Username: " << walletData[1] << "\n";
                                std::cout << "Số dư: " << walletData[2] << " điểm\n";
                                std::cout << "------------------------\n";
                            }
                        }
                        walletFile.close();
                    } else if (adminChoice == 3) {
                        // Tạo tài khoản mới
                        std::string username, password, fullName, email, phone;
                        std::cout << "Tên đăng nhập: "; std::getline(std::cin, username);
                        std::cout << "Họ tên: "; std::getline(std::cin, fullName);
                        std::cout << "Email: "; std::getline(std::cin, email);
                        std::cout << "Số điện thoại: "; std::getline(std::cin, phone);
                        std::cout << "Mật khẩu: "; std::getline(std::cin, password);
                        
                        std::string walletId = "WALLET_" + username;
                        UserAccount acc(username, sha256(password), fullName, email, phone, 
                                      UserRole::USER, false, std::time(nullptr), 0, walletId);
                        if (userMgr.registerUser(acc)) {
                            walletMgr.wallets.push_back(Wallet(walletId, username, 0));
                            userMgr.saveToFile(USER_FILE);
                            walletMgr.saveToFile(WALLET_FILE);
                            std::cout << "Tạo tài khoản thành công!\n";
                        } else {
                            std::cout << "Tên đăng nhập đã tồn tại!\n";
                        }
                    } else if (adminChoice == 4) {
                        // Điều chỉnh thông tin tài khoản
                        std::string username;
                        std::cout << "Nhập username cần điều chỉnh: "; std::getline(std::cin, username);
                        UserAccount* user = userMgr.findUser(username);
                        if (user && user->role != UserRole::ADMIN) {
                            // Hiển thị thông tin hiện tại
                            std::cout << "Thông tin hiện tại:\n";
                            std::cout << "Họ tên: " << user->fullName << "\n";
                            std::cout << "Email: " << user->email << "\n";
                            std::cout << "Số điện thoại: " << user->phone << "\n";
                            
                            // Nhập thông tin mới
                            std::string newFullName, newEmail, newPhone;
                            std::cout << "Họ tên mới (Enter để giữ nguyên): "; std::getline(std::cin, newFullName);
                            std::cout << "Email mới (Enter để giữ nguyên): "; std::getline(std::cin, newEmail);
                            std::cout << "Số điện thoại mới (Enter để giữ nguyên): "; std::getline(std::cin, newPhone);
                            
                            // Cập nhật thông tin
                            if (!newFullName.empty()) user->fullName = newFullName;
                            if (!newEmail.empty()) user->email = newEmail;
                            if (!newPhone.empty()) user->phone = newPhone;
                            
                            userMgr.saveToFile(USER_FILE);
                            std::cout << "Cập nhật thông tin thành công!\n";
                        } else {
                            std::cout << "Không tìm thấy tài khoản!\n";
                        }
                    } else if (adminChoice == 0) {
                        break;    // Thoát menu admin
                    }
                }
            } else {
                std::cout << "Đăng nhập Admin thất bại!\n";
            }
        } else if (choice == 4) {
            // Xử lý backup dữ liệu
            std::cout << "Đang backup dữ liệu...\n";
            
            // Lưu dữ liệu hiện tại vào file chính trước
            userMgr.saveToFile(USER_FILE);     // Lưu thông tin người dùng
            walletMgr.saveToFile(WALLET_FILE); // Lưu thông tin ví
            txMgr.saveToFile(TX_FILE);         // Lưu thông tin giao dịch

            // Tạo bản sao lưu cho file users.dat
            std::ifstream srcUser(USER_FILE, std::ios::binary);
            std::ofstream dstUser(USER_BK, std::ios::binary);
            dstUser << srcUser.rdbuf();
            srcUser.close();
            dstUser.close();

            // Tạo bản sao lưu cho file wallets.dat
            std::ifstream srcWallet(WALLET_FILE, std::ios::binary);
            std::ofstream dstWallet(WALLET_BK, std::ios::binary);
            dstWallet << srcWallet.rdbuf();
            srcWallet.close();
            dstWallet.close();

            // Tạo bản sao lưu cho file transactions.dat
            std::ifstream srcTx(TX_FILE, std::ios::binary);
            std::ofstream dstTx(TX_BK, std::ios::binary);
            dstTx << srcTx.rdbuf();
            srcTx.close();
            dstTx.close();

            std::cout << "Đã backup dữ liệu thành công!\n";
        } else if (choice == 5) {
            // Xử lý phục hồi dữ liệu
            std::cout << "Đang phục hồi dữ liệu...\n";
            
            // Kiểm tra file backup có tồn tại không
            std::ifstream checkUser(USER_BK);
            std::ifstream checkWallet(WALLET_BK);
            if (!checkUser.good() || !checkWallet.good()) {
                std::cout << "Không tìm thấy file backup!\n";
                continue;
            }
            checkUser.close();
            checkWallet.close();

            // Phục hồi file users.dat từ backup
            std::ifstream srcUser(USER_BK, std::ios::binary);
            std::ofstream dstUser(USER_FILE, std::ios::binary);
            dstUser << srcUser.rdbuf();
            srcUser.close();
            dstUser.close();

            // Phục hồi file wallets.dat từ backup
            std::ifstream srcWallet(WALLET_BK, std::ios::binary);
            std::ofstream dstWallet(WALLET_FILE, std::ios::binary);
            dstWallet << srcWallet.rdbuf();
            srcWallet.close();
            dstWallet.close();

            // Phục hồi file transactions.dat từ backup
            std::ifstream srcTx(TX_BK, std::ios::binary);
            std::ofstream dstTx(TX_FILE, std::ios::binary);
            dstTx << srcTx.rdbuf();
            srcTx.close();
            dstTx.close();

            // Xóa dữ liệu cũ trong bộ nhớ
            userMgr.users.clear();         // Xóa danh sách người dùng
            walletMgr.wallets.clear();     // Xóa danh sách ví
            txMgr.transactions.clear();    // Xóa danh sách giao dịch

            // Tải lại dữ liệu từ file chính
            if (!userMgr.loadFromFile(USER_FILE)) {
                std::cout << "Lỗi khi tải dữ liệu người dùng!\n";
            }
            if (!walletMgr.loadFromFile(WALLET_FILE)) {
                std::cout << "Lỗi khi tải dữ liệu ví!\n";
            }
            if (!txMgr.loadFromFile(TX_FILE)) {
                std::cout << "Lỗi khi tải dữ liệu giao dịch!\n";
            }

            // Lưu lại để đảm bảo dữ liệu được cập nhật
            userMgr.saveToFile(USER_FILE);
            walletMgr.saveToFile(WALLET_FILE);
            txMgr.saveToFile(TX_FILE);

            std::cout << "Đã phục hồi dữ liệu thành công!\n";
            std::cout << "Số lượng người dùng: " << userMgr.users.size() << "\n";
            std::cout << "Số lượng ví: " << walletMgr.wallets.size() << "\n";
            std::cout << "Số lượng giao dịch: " << txMgr.transactions.size() << "\n";

            // Hiển thị nội dung file để kiểm tra
            std::cout << "\nNội dung file users.dat:\n";
            std::ifstream checkUserFile(USER_FILE);
            std::string line;
            while (std::getline(checkUserFile, line)) {
                std::cout << line << "\n";
            }
            checkUserFile.close();

            std::cout << "\nNội dung file wallets.dat:\n";
            std::ifstream checkWalletFile(WALLET_FILE);
            while (std::getline(checkWalletFile, line)) {
                std::cout << line << "\n";
            }
            checkWalletFile.close();
        } else if (choice == 0) {
            break;    // Thoát chương trình
        }
    }
    return 0;
} 