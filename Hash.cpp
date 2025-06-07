#include "Hash.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <functional>

using namespace std;

// Hàm tạo mã băm SHA-256 giả lập (placeholder)
// Trong thực tế nên thay bằng thư viện SHA-256 thực sự để bảo mật
string sha256(const string& str) {
    hash<string> hasher;         // Tạo đối tượng băm kiểu string
    size_t hash = hasher(str);   // Tính mã băm từ chuỗi đầu vào, kết quả là số size_t

    ostringstream oss;                                // Tạo luồng ghi chuỗi
    oss << hex << setw(16) << setfill('0') << hash;   // Định dạng số thành chuỗi hex: đủ 16 chữ số, thêm số 0 nếu thiếu
    return oss.str();                                 // Trả về chuỗi băm ở dạng hex
}
