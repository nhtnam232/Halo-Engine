#include <iostream>
#include <string>
#include "HaloEngine.h" // Đảm bảo file này đã include DataModels.h, DynamicArray.h, HashTable.h, CSVParser.h

using namespace std;

int main() {
    // 1. Khai báo hệ thống
    HaloSystem sys;

    // 2. Khởi tạo - Cấp phát bộ nhớ cho mảng động và bảng băm trên Heap
    initSystem(sys);

    cout << "=================================================" << endl;
    cout << "   TEST LOADER - KIEM TRA LOI DOC FILE CSV       " << endl;
    cout << "=================================================" << endl;

    // 3. Nhập đường dẫn file từ bàn phím
    string filePath;
    cout << "Nhap duong dan file CSV de test: ";
    getline(cin, filePath);

    // Tự động xóa dấu ngoặc kép nếu bạn xài tính năng "Copy as path" trên Windows
    if (!filePath.empty() && filePath.front() == '"') filePath.erase(0, 1);
    if (!filePath.empty() && filePath.back() == '"') filePath.erase(filePath.size() - 1);

    cout << "\n[INFO] Dang tien hanh doc file..." << endl;

    // 4. Gọi hàm load của bạn (bản chưa sửa hàm splitCSVLine)
    loadDataFromCSV(sys, filePath);

    // 5. In thử 3 dòng log đầu tiên để kiểm tra "sức khỏe" dữ liệu
    if (sys.logs.size > 0) {
        cout << "\n=================================================" << endl;
        cout << "      KET QUA KIEM TRA 3 DONG LOG DAU TIEN      " << endl;
        cout << "=================================================" << endl;

        // Lấy tối đa 3 dòng để in
        int testCount = (sys.logs.size < 3) ? sys.logs.size : 3;

        for (int i = 0; i < testCount; i++) {
            LogEntry entry = sys.logs.data[i];
            cout << "Log thu " << i + 1 << ":" << endl;
            cout << "  - User Index:     " << entry.userIndex << endl;
            cout << "  - Device Index:   " << entry.deviceIndex << endl;
            cout << "  - App Index:      " << entry.appIndex << endl;
            cout << "  - Resource Index: " << entry.resourceIndex << endl;
            cout << "  - Location:       [" << entry.location << "]" << endl;
            cout << "  - Timestamp:      " << entry.timestamp;

            // Bắt bài lỗi gán về 0
            if (entry.timestamp == 0) {
                cout << "  <-- [NGUY HIEM] Bi dinh loi ve 0 do dinh ky tu \\r!" << endl;
            }
            else {
                cout << "  <-- [OK] Doc dung so!" << endl;
            }
            cout << "-------------------------------------------------" << endl;
        }
    }
    else {
        cout << "\n[LOI] Khong doc duoc dong log nao. Vui long kiem tra lai file hoac duong dan!" << endl;
    }

    // 6. Giải phóng bộ nhớ (Bảo vệ RAM)
    cout << "\n[INFO] Dang giai phong bo nho he thong..." << endl;
    freeSystemMemory(sys);

    cout << "--- Chuong trinh test ket thuc an toan! ---" << endl;

    system("pause");
    return 0;
}