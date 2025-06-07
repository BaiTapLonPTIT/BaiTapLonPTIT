#include "Hash.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <functional>

// Ham sha256 la ham gia lap (placeholder), dung std::hash de thay the tam cho viec bam SHA-256
std::string sha256(const std::string& str) {
    std::hash<std::string> hasher; // Tao doi tuong bam chuoi
    size_t hash = hasher(str); // Bam chuoi dau vao thanh gia tri kich thuoc 64 bit (size_t)
    std::ostringstream oss; // Doi tuong dung de tao chuoi xuat
    oss << std::hex  // Chuyen sang he 16
    << std::setw(16) // Dat do rong xuat toi thieu la 16 ky tu
     << std::setfill('0') // Neu chua du thi dien vao bang '0'
      << hash; // Dua gia tri bam vao
    return oss.str(); // Tra ve chuoi bam da dinh dang
}
// Ghi chu: De dam bao bao mat thuc su, nen su dung thu vien SHA-256 thuc te nhu OpenSSL hoac Crypto++