#include <iostream>
#include "WalletManager.h"
#include <fstream>
#include <sstream>
using namespace std;

void WalletManager::createWallet(const string& username) {
    string walletId = "W" + to_string(wallets.size() + 1);
    wallets.push_back(Wallet(walletId, username, 0));
    cout << "Tao vi thanh cong! ID vi: " << walletId << endl;
}

bool WalletManager::loadFromFile(const string& filename) {
    wallets.clear();
    ifstream fin(filename);
    if (!fin) return false;
    string line;
    while (getline(fin, line)) {
        if (!line.empty()) wallets.push_back(Wallet::deserialize(line));
    }
    return true;
}

bool WalletManager::saveToFile(const string& filename) {
    ofstream fout(filename);
    if (!fout) return false;
    for (const auto& wallet : wallets) {
        fout << wallet.serialize() << "\n";
    }
    return true;
}

bool WalletManager::backup(const string& backupFile) {
    return saveToFile(backupFile);
}

Wallet* WalletManager::findWallet(const string& walletId) {
    for (auto& wallet : wallets) {
        if (wallet.walletId == walletId) return &wallet;
    }
    return nullptr;
}

Wallet* WalletManager::findWalletByUser(const string& username) {
    for (auto& wallet : wallets) {
        if (wallet.ownerUsername == username) return &wallet;
    }
    return nullptr; 
} 