#include <iostream>

using namespace std;

int main() {
    while (true) {
        cout << "============================" << endl;
        cout << "CHUONG TRINH QUAN LY VI DIEN TU" << endl;
        cout << "1. Dang nhap" << endl;
        cout << "2. Dang ky" << endl;
        cout << "3. Thoat" << endl;
        cout << "Chon: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Dang nhap - chua ho tro" << endl;
                break;
            case 2:
                cout << "Dang ky - chua ho tro" << endl;
                break;
            case 3:
                cout << "Tam biet!" << endl;
                return 0;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }

        cout << endl;
    }
}

