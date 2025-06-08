#include <iostream>                    // Thu vien cho viec nhap xuat du lieu
#include <windows.h>                   // Thu vien cho ham SetConsoleOutputCP va SetConsoleCP
#include "UserManager.h"               // Thu vien quan ly nguoi dung
#include "WalletManager.h"             // Thu vien quan ly vi
#include "TransactionManager.h"        // Thu vien quan ly giao dich
#include "OTPManager.h"                // Thu vien quan ly OTP
#include "utils.h"                     // Thu vien cac tien ich chung
#include "Hash.h"                      // Thu vien ma hoa mat khau bang SHA256

// Ham cau hinh console de hien thi duoc tieng Viet
void setupConsole() {
    SetConsoleOutputCP(65001);         // Dat code page dau ra la UTF-8
    SetConsoleCP(65001);               // Dat code page dau vao la UTF-8
}

// Cac bien luu duong dan den cac file du lieu
const std::string USER_FILE = "data/users.dat";            // File luu danh sach nguoi dung
const std::string WALLET_FILE = "data/wallets.dat";        // File luu thong tin vi
const std::string TX_FILE = "data/transactions.dat";       // File luu giao dich

// Cac file backup
const std::string USER_BK = "data/backup/users_backup.dat";
const std::string WALLET_BK = "data/backup/wallets_backup.dat";
const std::string TX_BK = "data/backup/transactions_backup.dat";

// Ham tao thu muc neu chua co
void ensureDataDirs() {
    CreateDirectoryA("data", NULL);         // Tao thu muc "data" neu chua ton tai
    CreateDirectoryA("data/backup", NULL);  // Tao thu muc "data/backup" neu chua ton tai
}

// Ham hien thi menu chinh
void showMenu() {
    std::cout << "\n===== HE THONG QUAN LY DANG NHAP & VI DIEM =====\n";
    std::cout << "1. Dang ky tai khoan\n";
    std::cout << "2. Dang nhap\n";
    std::cout << "3. Backup du lieu\n";
    std::cout << "4. Phuc hoi du lieu\n";
    std::cout << "0. Thoat\n";
    std::cout << "Chon: ";
}

int main() {
    setupConsole();                // Goi ham cau hinh console
    ensureDataDirs();             // Tao cac thu muc du lieu neu chua co

    UserManager userMgr;          // Khoi tao doi tuong quan ly nguoi dung
    WalletManager walletMgr;      // Khoi tao doi tuong quan ly vi
    TransactionManager txMgr;     // Khoi tao doi tuong quan ly giao dich

    // Tai du lieu tu cac file
    userMgr.loadFromFile(USER_FILE);
    walletMgr.loadFromFile(WALLET_FILE);
    txMgr.loadFromFile(TX_FILE);
    OTPManager otpMgr;            // Khoi tao doi tuong quan ly OTP
    int choice;
    while (true) {
        showMenu();               // Hien thi menu chinh
        std::cin >> choice;       // Nhan lua chon tu nguoi dung
        std::cin.ignore();        // Bo qua ky tu '\n' con lai

        if (choice == 1) {
            // Chuc nang dang ky tai khoan moi
            std::string username, password, fullName, email, phone;
            std::cout << "Ten dang nhap: "; std::getline(std::cin, username);
            std::cout << "Ho ten: "; std::getline(std::cin, fullName);
            std::cout << "Email: "; std::getline(std::cin, email);
            std::cout << "So dien thoai: "; std::getline(std::cin, phone);
            std::cout << "Mat khau (bo trong de tu sinh): "; std::getline(std::cin, password);

            bool autoPw = false;
            if (password.empty()) {
                password = generateRandomPassword();      // Tu dong tao mat khau
                autoPw = true;
                std::cout << "Mat khau tu sinh: " << password << "\n";
            }

            std::string walletId = "WALLET_" + username;   // Tao ID vi du tren username

            // Tao tai khoan nguoi dung moi
            UserAccount acc(
                username,
                sha256(password),      // Ma hoa mat khau
                fullName, email, phone,
                UserRole::USER, autoPw,
                std::time(nullptr),    // Thoi gian tao
                0, walletId
            );

            if (userMgr.registerUser(acc)) {
                // Neu dang ky thanh cong, tao vi moi
                walletMgr.wallets.push_back(Wallet(walletId, username, 0));
                userMgr.saveToFile(USER_FILE);
                walletMgr.saveToFile(WALLET_FILE);
                std::cout << "Dang ky thanh cong!\n";
            } else {
                std::cout << "Ten dang nhap da ton tai!\n";
            }

        } else if (choice == 2) {
            // Chuc nang dang nhap
            std::string username, password;
            std::cout << "Ten dang nhap: "; std::getline(std::cin, username);
            std::cout << "Mat khau: "; std::getline(std::cin, password);

            UserAccount* user = nullptr;
            if (userMgr.login(username, password, user)) {
                std::cout << "Dang nhap thanh cong!\n";

                // Menu nguoi dung sau khi dang nhap
                while (true) {
                    std::cout << "\n--- Xin chao, " << user->fullName << " ---\n";
                    std::cout << "1. Xem so du vi\n";
                    std::cout << "2. Chuyen diem\n";
                    std::cout << "3. Xem lich su giao dich\n";
                    std::cout << "4. Doi mat khau\n";
                    std::cout << "0. Dang xuat\n";
                    std::cout << "Chon: ";
                    int sub;
                    std::cin >> sub; std::cin.ignore();

                    if (sub == 1) {
                        // Xem so du vi
                        Wallet* w = walletMgr.findWalletByUser(user->username);
                        if (w) std::cout << "So du: " << w->balance << " diem\n";
                        else std::cout << "Khong tim thay vi!\n";

                    } else if (sub == 2) {
                        // Chuyen diem
                        std::string toUser;
                        int amount;
                        std::cout << "Chuyen toi (username): "; std::getline(std::cin, toUser);
                        std::cout << "So diem: "; std::cin >> amount; std::cin.ignore();

                        Wallet* fromW = walletMgr.findWalletByUser(user->username);
                        Wallet* toW = walletMgr.findWalletByUser(toUser);

                        if (!fromW || !toW) { std::cout << "Vi khong ton tai!\n"; continue; }
                        if (fromW->balance < amount) { std::cout << "Khong du so du!\n"; continue; }

                        // Xac thuc OTP
                        otpMgr.generateOTP(user->username);
                        std::cout << "Ma OTP gui toi ban (demo): " << otpMgr.currentOTP << "\n";

                        std::string otp;
                        std::cout << "Nhap OTP: "; std::getline(std::cin, otp);
                        if (!otpMgr.verifyOTP(user->username, otp)) {
                            std::cout << "OTP khong hop le!\n"; continue;
                        }

                        // Thuc hien giao dich
                        fromW->balance -= amount;
                        toW->balance += amount;

                        Transaction tx("TX" + std::to_string(txMgr.transactions.size() + 1),
                            fromW->walletId, toW->walletId,
                            amount, std::time(nullptr), "success"
                        );

                        txMgr.logTransaction(tx);                  // Ghi log giao dich
                        walletMgr.saveToFile(WALLET_FILE);         // Luu vi
                        txMgr.saveToFile(TX_FILE);                 // Luu giao dich

                        std::cout << "Chuyen diem thanh cong!\n";

                    } else if (sub == 3) {
                        // Xem lich su giao dich
                        std::cout << "Lich su giao dich:\n";
                        for (const auto& tx : txMgr.transactions) {
                            if (tx.fromWalletId == user->walletId || tx.toWalletId == user->walletId) {
                                std::cout << "ID: " << tx.transactionId
                                          << ", Tu: " << tx.fromWalletId
                                          << ", Den: " << tx.toWalletId
                                          << ", So diem: " << tx.amount
                                          << ", Thoi gian: " << getCurrentTimeString()
                                          << ", Trang thai: " << tx.status << "\n";
                            }
                        }

                    } else if (sub == 4) {
                        // Doi mat khau
                        std::string oldPw, newPw;
                        std::cout << "Mat khau cu: "; std::getline(std::cin, oldPw);
                        if (!userMgr.login(user->username, oldPw, user)) {
                            std::cout << "Sai mat khau!\n"; continue;
                        }
                        std::cout << "Mat khau moi: "; std::getline(std::cin, newPw);
                        userMgr.changePassword(*user, newPw);
                        userMgr.saveToFile(USER_FILE);
                        std::cout << "Doi mat khau thanh cong!\n";

                    } else if (sub == 0) {
                        // Dang xuat
                        break;
                    }
                }

            } else {
                std::cout << "Dang nhap that bai!\n";
            }

        } else if (choice == 3) {
            // Backup du lieu
            userMgr.backup(USER_BK);
            walletMgr.backup(WALLET_BK);
            txMgr.backup(TX_BK);
            std::cout << "Da backup du lieu!\n";

        } else if (choice == 4) {
            // Phuc hoi tu file backup
            userMgr.loadFromFile(USER_BK);
            walletMgr.loadFromFile(WALLET_BK);
            txMgr.loadFromFile(TX_BK);
            userMgr.saveToFile(USER_FILE);
            walletMgr.saveToFile(WALLET_FILE);
            txMgr.saveToFile(TX_FILE);
            std::cout << "Da phuc hoi du lieu tu backup!\n";

        } else if (choice == 0) {
            // Thoat chuong trinh
            break;
        }
    }

    return 0;
}
