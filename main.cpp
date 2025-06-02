#include <iostream>

int main() {
    while (true) {
        std::cout << "============================\n";
        std::cout << "CHUONG TRINH QUAN LY VI DIEN TU\n";
        std::cout << "1. Dang nhap\n";
        std::cout << "2. Dang ky\n";
        std::cout << "3. Thoat\n";
        std::cout << "Chon: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Dang nhap - chua ho tro\n";
                break;
            case 2:
                std::cout << "Dang ky - chua ho tro\n";
                break;
            case 3:
                std::cout << "Tam biet!\n";
                return 0;
            default:
                std::cout << "Lua chon khong hop le!\n";
        }

        std::cout << "\n";
    }
}

