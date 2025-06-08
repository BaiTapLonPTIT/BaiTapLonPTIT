# Hệ Thống Quản Lý Đăng Nhập & Ví Điểm

Đây là một hệ thống quản lý đăng nhập và ví điểm được viết bằng C++. Hệ thống cho phép người dùng đăng ký tài khoản, đăng nhập, quản lý ví điểm và thực hiện các giao dịch.

## Thành viên tham gia dự án và công việc được giao

1. Dương Công Uy - Module 1: Quản lý Người dùng (User Management)
   - Đăng ký tài khoản
   - Đăng nhập
   - Quản lý thông tin người dùng
   - Mã hóa mật khẩu

2. Nguyễn Thế Thanh Phương - Module 2: Quản lý Ví (Wallet Management)
   - Tạo và quản lý ví điểm
   - Xem số dư
   - Cập nhật số dư
   - Quản lý lịch sử ví
   - Phân quyền của admin

3. Phạm Anh Tú - Module 3: Giao dịch (Transaction)
   - Thực hiện giao dịch
   - Xác thực giao dịch
   - Quản lý lịch sử giao dịch
   - Báo cáo giao dịch

4. Đoàn Thị Nhàn - Module 4: Tiện ích và Bảo mật OTP
   - Tạo và xác thực OTP
   - Backup và phục hồi dữ liệu
   - Các tiện ích hệ thống
   - Bảo mật và mã hóa

## Quy trình làm việc nhóm và quản lí dự án với Git

1. Quy tắc kho chứa Git của dự án
   - Main là nhánh chính của dự án và là phiên bản hoàn thiện nhất
   - Không thể push vào nhánh chính main, phải thông qua pull request để merge
   - Pull request phải được ít nhất 1 người approve trước khi merge

2. Quy trình sử dụng Git
   - Thành viên clone code dự án: ~git clone https://github.com/BaiTapLonPTIT/BaiTapLonPTIT.git
   - Tạo nhánh mới từ main: ~git checkout -b [ten_nhanh]
   - Tiến hành code và thêm các file đã chỉnh sửa: ~git add [ten_file]
   - Commit code: ~git commit -m "ten_commit"
   - Đẩy code lên kho chứa Github dự án: ~git push origin [ten_nhanh]
   - Tạo pull request ở github và merge

3. Build và release
   - Mỗi khi có code được push lên github, git action sẽ tự động chạy và build dự án: https://github.com/BaiTapLonPTIT/BaiTapLonPTIT/actions
   - Bản build tạm thời của pull request sẽ được tải lên tại mục Artifacts của git action
   - Mỗi ngày sẽ có 1 bản Release được tạo ra chứa các file Source code và build .exe: https://github.com/BaiTapLonPTIT/BaiTapLonPTIT/releases

4. Lưu ý khi commit
   - Mỗi commit phải là một đơn vị logic hoàn chỉnh
   - Không commit code chưa hoàn thiện
   - Luôn cập nhật tài liệu khi thay đổi API
   - Viết test cho mọi tính năng mới
   - Tuân thủ coding style chung
   - Thường xuyên sync với main branch


## Yêu cầu hệ thống

- Windows 10 trở lên
- MinGW-w64 (phiên bản 8.1.0 trở lên)
- Các thư viện C++ chuẩn

## Cài đặt

1. Tải và cài đặt MinGW-w64 từ trang chủ: https://www.mingw-w64.org/downloads/
   - Chọn phiên bản mới nhất (8.1.0)
   - Architecture: x86_64
   - Threads: posix
   - Exception: seh
   - Build revision: Latest

2. Thêm đường dẫn đến thư mục bin của MinGW-w64 vào biến môi trường PATH:
   - Mở System Properties (Win + Pause/Break)
   - Click vào "Advanced system settings"
   - Click vào "Environment Variables"
   - Trong phần "System variables", tìm và chọn "Path"
   - Click "Edit"
   - Click "New"
   - Thêm đường dẫn đến thư mục bin của MinGW-w64 (thường là C:\mingw64\bin)
   - Click "OK" để lưu

3. Khởi động lại PowerShell hoặc Command Prompt

## Biên dịch và chạy chương trình

1. Mở PowerShell hoặc Command Prompt
2. Di chuyển đến thư mục chứa mã nguồn

## Tính năng chính

1. Đăng ký tài khoản
   - Tạo tài khoản mới với tên đăng nhập, họ tên, email, số điện thoại
   - Tự động tạo ví điểm cho tài khoản mới
   - Hỗ trợ tạo mật khẩu tự động

2. Đăng nhập
   - Xác thực người dùng bằng tên đăng nhập và mật khẩu
   - Mật khẩu được mã hóa bằng SHA-256
   - Phân quyền admin có quyền xem data trên giao diện menu và thay đổi thông tin của người dùng

3. Quản lý ví điểm
   - Xem số dư ví
   - Chuyển điểm cho người dùng khác
   - Xác thực giao dịch bằng OTP

4. Quản lý giao dịch
   - Xem lịch sử giao dịch
   - Theo dõi các giao dịch đã thực hiện

5. Bảo mật
   - Mật khẩu được mã hóa
   - Xác thực OTP cho các giao dịch
   - Backup và phục hồi dữ liệu

## Cấu trúc thư mục

- `main.cpp`: File chính chứa hàm main và menu chương trình
- `UserAccount.h/cpp`: Quản lý thông tin tài khoản người dùng
- `UserManager.h/cpp`: Quản lý các tài khoản người dùng
- `Wallet.h/cpp`: Quản lý thông tin ví điểm
- `WalletManager.h/cpp`: Quản lý các ví điểm
- `Transaction.h/cpp`: Quản lý thông tin giao dịch
- `TransactionManager.h/cpp`: Quản lý các giao dịch
- `OTPManager.h/cpp`: Quản lý mã OTP
- `Hash.h/cpp`: Hàm mã hóa mật khẩu
- `utils.h/cpp`: Các hàm tiện ích
- `data/`: Thư mục chứa dữ liệu
  - `users.dat`: Dữ liệu người dùng
  - `wallets.dat`: Dữ liệu ví điểm
  - `transactions.dat`: Dữ liệu giao dịch
  - `backup/`: Thư mục chứa bản sao lưu
  - `admin`: Lưu trữ ví của admin

## Quản lý Backup và Phục hồi dữ liệu

1. Backup manual
   - Backup được lưu trong thư mục `data/backup/` `
   - Mỗi bản backup bao gồm:
     - Dữ liệu người dùng (users.dat)
     - Dữ liệu ví điểm (wallets.dat)
     - Dữ liệu giao dịch (transactions.dat)
   - Menu có option backup 

2. Phục hồi dữ liệu manual
   - Hệ thống cho phép phục hồi từ bất kỳ bản backup nào
   - Quá trình phục hồi sẽ:
     - Sao chép dữ liệu từ bản backup vào thư mục data
     - Xác thực tính toàn vẹn của dữ liệu
     - Tạo bản backup của dữ liệu hiện tại trước khi phục hồi
   - Ở menu có option phục hồi 

## Lưu ý

- Dữ liệu được lưu trong thư mục `data/`
- Nên thực hiện backup dữ liệu thường xuyên

