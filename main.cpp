#include <iostream>
#include <fstream>
#include "Wallet.h"
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include "WalletManager.h"

using namespace std;

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
                    Wallet* wallet = walletManager.findWallet(walletId);
                    if (wallet) {
                        cout << "Thong tin vi:" << endl;
                        cout << "ID vi: " << wallet->walletId << endl;
                        cout << "Chu so huu: " << wallet->ownerUsername << endl;
                        cout << "So du: " << wallet->balance << endl;
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

