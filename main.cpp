#include <iostream>
#include "Wallet.h"
#include <vector>
#include <map>

using namespace std;

class WalletManager {
private:
    map<string, Wallet> wallets;

public:
    void createWallet(const string& username) {
        string walletId = "W" + to_string(wallets.size() + 1);
        wallets[walletId] = Wallet(walletId, username, 0);
        cout << "Tao vi thanh cong! ID vi: " << walletId << endl;
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
};

// Global variables
WalletManager walletManager;
string currentUser;

int main() {
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

        string walletId;

        switch (choice) {
            case 1:
                cout << "Nhap username: ";
                cin >> currentUser;
                cout << "Dang nhap thanh cong!" << endl;
                break;
            case 2:
                cout << "Nhap username: ";
                cin >> currentUser;
                walletManager.createWallet(currentUser);
                cout << "Dang ky thanh cong!" << endl;
                break;
            case 3:
                if (currentUser.empty()) {
                    cout << "Vui long dang nhap truoc!" << endl;
                } else {
                    cout << "Nhap ID vi: ";
                    cin >> walletId;
                    walletManager.showWalletInfo(walletId);
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

