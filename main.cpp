#include <iostream>
#include <fstream>
#include "Wallet.h"
#include <vector>
#include <map>
#include <string>
#include <ctime>

using namespace std;

class WalletManager {
private:
    map<string, Wallet> wallets;
    const string WALLET_FILE = "data/wallets.dat";

public:
    void createWallet(const string& username) {
        string walletId = "WALLET_" + username;
        wallets[walletId] = Wallet(walletId, username, 0);
        cout << "Tao vi thanh cong! ID vi: " << walletId << endl;
        saveToFile(WALLET_FILE);
    }

    void showWalletInfo(const string& walletId) {
        if (wallets.find(walletId) == wallets.end()) {
            cout << "Khong tim thay vi!" << endl;
            return;
        }
        cout << "Thong tin vi:" << endl;
        cout << "ID vi: " << wallets[walletId].walletId << endl;
        cout << "Chu so huu: " << wallets[walletId].ownerUsername << endl;
        cout << "So du: " << wallets[walletId].balance << endl;
    }

    Wallet* findWalletByUser(const string& username) {
        for (auto& pair : wallets) {
            if (pair.second.ownerUsername == username) {
                return &pair.second;
            }
        }
        return nullptr;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file) {
            cout << "Khong the mo file " << filename << endl;
            return;
        }

        wallets.clear();
        Wallet wallet;
        while (file.read(reinterpret_cast<char*>(&wallet), sizeof(Wallet))) {
            wallets[wallet.walletId] = wallet;
        }
        file.close();
    }

    void saveToFile(const string& filename) {
        ofstream file(filename, ios::binary);
        if (!file) {
            cout << "Khong the mo file " << filename << endl;
            return;
        }

        for (const auto& pair : wallets) {
            file.write(reinterpret_cast<const char*>(&pair.second), sizeof(Wallet));
        }
        file.close();
    }
};

// Global variables
WalletManager walletManager;
string currentUser;

int main() {
    // Load existing wallets
    walletManager.loadFromFile("data/wallets.dat");

    while (true) {
        cout << "============================" << endl;
        cout << "CHUONG TRINH QUAN LY VI DIEN TU" << endl;
        cout << "1. Dang nhap" << endl;
        cout << "2. Dang ky" << endl;
        cout << "3. Xem thong tin vi" << endl;
        cout << "4. Thoat" << endl;
        cout << "Chon: ";

        int choice;
        cin >> choice;
        cin.ignore();

        string walletId;

        switch (choice) {
            case 1:
                cout << "Nhap username: ";
                getline(cin, currentUser);
                if (walletManager.findWalletByUser(currentUser)) {
                    cout << "Dang nhap thanh cong!" << endl;
                } else {
                    cout << "Tai khoan khong ton tai!" << endl;
                    currentUser.clear();
                }
                break;
            case 2:
                cout << "Nhap username: ";
                getline(cin, currentUser);
                if (walletManager.findWalletByUser(currentUser)) {
                    cout << "Tai khoan da ton tai!" << endl;
                    currentUser.clear();
                } else {
                    walletManager.createWallet(currentUser);
                    cout << "Dang ky thanh cong!" << endl;
                }
                break;
            case 3:
                if (currentUser.empty()) {
                    cout << "Vui long dang nhap truoc!" << endl;
                } else {
                    Wallet* wallet = walletManager.findWalletByUser(currentUser);
                    if (wallet) {
                        walletManager.showWalletInfo(wallet->walletId);
                    } else {
                        cout << "Khong tim thay vi!" << endl;
                    }
                }
                break;
            case 4:
                cout << "Tam biet!" << endl;
                return 0;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }

        cout << endl;
    }
}

