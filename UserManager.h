#pragma once
// Chi thi bao ve file header, dam bao chi duoc include mot lan trong mot file .cpp

#include "UserAccount.h"
// Bao gom dinh nghia cua lop UserAccount, vi UserManager se su dung doi tuong UserAccount

#include <vector>   // Su dung vector de luu danh sach tai khoan
#include <string>   // Su dung string cho ten file va ten dang nhap

// Dinh nghia lop quan ly nguoi dung
class UserManager {
public:
    std::vector<UserAccount> users;
    // Danh sach cac tai khoan nguoi dung, luu tru trong vector

    bool loadFromFile(const std::string& filename);
    // Doc danh sach nguoi dung tu file, tra ve true neu thanh cong

    bool saveToFile(const std::string& filename);
    // Ghi danh sach nguoi dung ra file, tra ve true neu thanh cong

    bool backup(const std::string& backupFile);
    // Tao ban sao luu danh sach nguoi dung ra file khac

    UserAccount* findUser(const std::string& username);
    // Tim kiem nguoi dung theo ten dang nhap, tra ve con tro toi tai khoan (neu tim thay)

    bool registerUser(const UserAccount& user);
    // Dang ky nguoi dung moi, tra ve true neu dang ky thanh cong (khong trung username)

    bool login(const std::string& username, const std::string& password, UserAccount*& outUser);
    // Dang nhap nguoi dung: kiem tra username va mat khau
    // Neu dung, gan con tro outUser vao tai khoan do va tra ve true

    bool changePassword(UserAccount& user, const std::string& newPassword);
    // Doi mat khau cho tai khoan cu the, tra ve true neu thanh cong
};
