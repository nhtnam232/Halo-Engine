#include <iostream>
#include <string>
#include "HaloEngine.h"
#include "LogAnalyzer.h"
#include <limits>


void printMenu() {
    std::cout << "\n================ HALO SYSTEM MENU ================" << std::endl;
    std::cout << "1. Hanh trinh truy xuat tai nguyen cua User trong mot khoang thoi gian" << std::endl;
    std::cout << "2. Hanh trinh cua Resource trong mot khoang thoi gian" << std::endl;
    std::cout << "3. Thong ke Top 10 Resource truy xuat nhieu nhat" << std::endl;
    std::cout << "4. Thoat chuong trinh" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "Nhap lua chon cua ban (1-4): ";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    // Khoi tao he thong
    HaloSystem sys;
    initSystem(sys);

    // Nap du lieu
    std::string filePath;
    std::cout << "Nhap duong dan den file CSV (vd: C:\\Data\\log.csv): ";
    std::getline(std::cin >> std::ws, filePath);

    std::cout << "Dang nap du lieu tu file: " << filePath << "..." << std::endl;
    loadDataFromCSV(sys, filePath);

    if (sys.logs.size == 0) {
        std::cout << "Loi: Khong co du lieu hoac nap file that bai! Vui long kiem tra lai duong dan." << std::endl;
        freeSystemMemory(sys);
        return 0;
    }
    std::cout << "Nap thanh cong " << sys.logs.size << " dong log." << std::endl;

    // Tien xu ly: Sap xep log theo timestamp
    std::cout << "Dang sap xep he thong log theo thoi gian..." << std::endl;
    mySort(sys.logs.data, 0, sys.logs.size - 1, compareLogByTimestamp);
    std::cout << "Da sap xep xong!\n";
    std::cout << "Dang don dep cac thong tin trung lap..." << std::endl;
    removeDuplicateLogs(sys);
    std::cout << "He thong san sang hoat dong!" << std::endl;
    // Menu
    int choice;
    while (true) {
        printMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            if (std::cin.eof()) {
                std::cout << "Ngat ket noi dau vao.Dang dong he thong...\n";
                break; 
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Loi: Vui long nhap mot so nguyen hop le!" << std::endl;
            continue;
        }

        if (choice == 4) {
            std::cout << "\nDang dong he thong..." << std::endl;
            break;
        }
        if (choice < 1 || choice > 4) {
            std::cout << "Lua chon khong hop le, vui long nhap lai!" << std::endl;
            continue;
        }
        long long t1, t2;
        std::cout << "Nhap timestamp bat dau (t1): ";
        std::cin >> t1;
        if (std::cin.fail()) {
            if (std::cin.eof()) {
                std::cout << "Ngat ket noi dau vao.Dang dong he thong...\n";
                break;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Loi: Vui long nhap mot so nguyen hop le!" << std::endl;
            continue;
        }
        std::cout << "Nhap timestamp ket thuc (t2): ";
        std::cin >> t2;
        if (std::cin.fail()) {
            if (std::cin.eof()) {
                std::cout << "\nNgat ket noi dau vao.Dang dong he thong...\n";
                break;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Loi: Vui long nhap mot so nguyen hop le!" << std::endl;
            continue;
        }
        if (t1 > t2) {
            std::cout << "Loi: t1 phai nho hon hoac bang t2!" << std::endl;
            continue;
        }
        std::cout << "\n---------------- KET QUA ----------------\n";
        switch (choice) {
        case 1: {
            std::string userId;
            std::cout << "Nhap User ID can tra cuu: ";
            std::cin >> userId;
            if (std::cin.eof()) {
                std::cout << "\nNgat ket noi dau vao. Dang dong he thong...\n";
                freeSystemMemory(sys);
                return 0;
            }
            searchUserJourneyRangeByTime(sys, userId, t1, t2);
            break;
        }
        case 2: {
            std::string resourceId;
            std::cout << "Nhap Resource ID can tra cuu: ";
            std::cin >> resourceId;
            if (std::cin.eof()) {
                std::cout << "\nNgat ket noi dau vao. Dang dong he thong...\n";
                freeSystemMemory(sys);
                return 0;
            }
            searchResourceJourneyRangeByTime(sys, resourceId, t1, t2);
            break;
        }
        case 3: {
            top10MostAccessedResources(sys, t1, t2);
            break;
        }
        }
        std::cout << "-----------------------------------------\n";
        std::cout << "\nBam Enter de tiep tuc...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.get() == EOF) {
            break;
        }
    }

    freeSystemMemory(sys);

    return 0;
}