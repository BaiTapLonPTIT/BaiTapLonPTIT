#pragma once
#include "Wallet.h"
#include <vector>
#include <string>
using namespace std;

class WalletManager {
public:
    vector<Wallet> wallets;
    bool loadFromFile(const string& filename);
    bool saveToFile(const string& filename);
    bool backup(const string& backupFile);
    Wallet* findWallet(const string& walletId);
    Wallet* findWalletByUser(const string& username);
    void createWallet(const string& username);
};