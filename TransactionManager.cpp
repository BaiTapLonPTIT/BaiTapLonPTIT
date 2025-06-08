#include "TransactionManager.h"
#include <fstream>
#include <sstream>

// Ham doc du lieu giao dich tu file
bool TransactionManager::loadFromFile(const std::string& filename) {
    transactions.clear(); // Xoa danh sach giao dich hien tai

    std::ifstream fin(filename); // Mo file de doc
    if (!fin) return false;      // Neu khong mo duoc file thi tra ve false

    std::string line;            // Bien luu tung dong doc duoc
    while (std::getline(fin, line)) {         // Doc tung dong tu file
        if (!line.empty())                    // Neu dong khong rong
            transactions.push_back(Transaction::deserialize(line)); // Chuyen chuoi thanh doi tuong va them vao danh sach
    }

    return true; // Doc file thanh cong
}

// Ham luu danh sach giao dich vao file
bool TransactionManager::saveToFile(const std::string& filename) {
    std::ofstream fout(filename); // Mo file de ghi
    if (!fout) return false;      // Neu khong mo duoc file thi tra ve false

    for (const auto& tx : transactions) { // Duyet tung giao dich trong danh sach
        fout << tx.serialize() << "\n";   // Chuyen thanh chuoi va ghi xuong file
    }

    return true; // Luu file thanh cong
}

// Ham sao luu du lieu giao dich sang file khac
bool TransactionManager::backup(const std::string& backupFile) {
    return saveToFile(backupFile); // Su dung lai ham saveToFile de ghi ra file backup
}

// Ham ghi nhat ky giao dich moi
void TransactionManager::logTransaction(const Transaction& tx) {
    transactions.push_back(tx); // Them giao dich moi vao danh sach
}
