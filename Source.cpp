#include <windows.h>
#include <bits/stdc++.h>
using namespace std;

const LPCWSTR pathCreateFolder = L"E:\\Nhom12";
const LPCWSTR pathCopyFile = L"C:\\Users\\MINH\\Pictures\\Wallpaper\\retro-punk-anime-girl-lying-on-bed-5k-aj-1920x1080.jpg";
const LPCWSTR pathRouteFolder = L"E:\\Nhom12";
const LPCWSTR pathRunFile = L"E:\\test.txt";

map<string, set<string> > folder_and_file;
const set<string> fileTags = {".txt", ".jpg", ".mp3", ".png", ".mp4", ".cpp"};

void init() {
    folder_and_file["E:"] = {"Pictures", "TM7", "C_C++", "Musics_Videos", "test.txt"};
    folder_and_file["Pictures"] = {"OnePiece.jpg", "Rem.png", "YourLieInApril.jpg", "retro-punk.jpg"};
    folder_and_file["Musics_Videos"] = {"CupidWithTea.mp4", "InLoveByMikeHao.mp3", "RapChamThoi.mp3"};
    folder_and_file["C_C++"] = { "test.cpp" };
}

bool isFile(string name) {

    if (name.size() >= 5) {
        int idx = name.size() - 1;
        string tag = "";
        bool fl = false;
        for (int i = idx; i >= 0; --i) {
            tag += name[i];
            if (name[i] == '.') {
                if (i == name.size() - 5 && name.size() == 5) {
                    fl = false;
                    break;
                }
                fl = true;
                break;
            }
        }
        if (fl) {
            reverse(tag.begin(), tag.end());
            return (fileTags.count(tag));
        }
    }
    return false;
}

void msb(LPCWSTR noti) {
    MessageBox(NULL, noti, L"Thong bao", MB_OK);
}

LPCWSTR convertStrToLPCW(string str) {
    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wchar_t* wideStr = new wchar_t[size];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wideStr, size);
    LPCWSTR lpcwstr = wideStr;
    return lpcwstr;
}

string getPath() {
    string path = "E:\\";
    string root = "E:";
    while (!folder_and_file[root].empty()) {
        set<string> son = folder_and_file[root];
        cout << "Danh sach tep va thu muc co trong " << root << " la:\n";
        for (string x : son) {
            cout << x << "\t";
        }
        cout << "\n";
        cout << "Moi ban chon tep (chon go \"!!!\" de lay thu muc nay hoac \"~\" de thoat) : ";
        string name;
        do {
            std::cin >> name;
            if (name == "!!!") {
                return path;
            }
            else if (name == "~") {
                msb(L"Thoat");
                return name;
            }
            else if (son.count(name) && isFile(name)) {
                path += name;
                return path;
            }
            else if (son.count(name)) {
                path += name;
                root = name;
                break;
            }
            else {
                cout << "Nhap lai ten tep: ";
            }
        } while (true);
    }
    return path;
}

void createDirectory(LPCWSTR path) {
    if (CreateDirectory(path, NULL)) {
        // Thư mục đã được tạo thành công
        msb(L"Thư mục tạo thành công");
    }
    else {
        // Không thể tạo thư mục
        DWORD error = GetLastError();
        if (error == ERROR_ALREADY_EXISTS) {
            msb(L"Thư mục đã tồn tại.");
        }
        else {
            msb(L"tạo thư mục thất bại");
        }
    }
}

void copyFile(LPCWSTR source, LPCWSTR route) {

    // Chuyển đổi giá trị của biến sourceDirectory và destinationDirectory thành chuỗi
    std::wstring sourceString(source);
    std::wstring destinationString(route);

    // Tạo lệnh cmd.exe bằng cách cắt ghép giá trị của hai biến vào chuỗi
    std::wstring cmdCommand = L"/c copy " + sourceString + L" " + destinationString;

    // Chuyển đổi lệnh thành LPCWSTR để sử dụng với ShellExecute
    LPCWSTR cmdCommandWstr = cmdCommand.c_str();

    HINSTANCE hInstance = ShellExecute(NULL, L"runas", L"cmd.exe", cmdCommandWstr, NULL, SW_SHOWNORMAL);

    if ((int)hInstance > 32) {
        // Lệnh đã được thực hiện thành công
        msb(L"Đã sao file chép thành công");
    }
    else {
        // Lệnh không thực hiện được, xảy ra lỗi
        msb(L"Lỗi tạo file (trùng, không tồn tại file)");
    }
}

void createProcess() {
    //// Định nghĩa các biến cần thiết
    //LPWSTR commandLine = NULL; // Dòng lệnh của chương trình
    //LPSECURITY_ATTRIBUTES processAttributes = NULL;
    //LPSECURITY_ATTRIBUTES threadAttributes = NULL;
    //BOOL inheritHandles = FALSE;
    //DWORD creationFlags = 0;
    //LPVOID environment = NULL; // Môi trường của tiến trình con
    //LPCTSTR currentDirectory = NULL; // Thư mục làm việc hiện tại
    //STARTUPINFO startupInfo;
    //PROCESS_INFORMATION processInfo;

    //ZeroMemory(&startupInfo, sizeof(startupInfo));
    //startupInfo.cb = sizeof(startupInfo);
    //ZeroMemory(&processInfo, sizeof(processInfo));

    //// Tạo tiến trình
    //if (CreateProcess(
    //    pathRunFile,
    //    commandLine,
    //    processAttributes,
    //    threadAttributes,
    //    inheritHandles,
    //    creationFlags,
    //    environment,
    //    currentDirectory,
    //    &startupInfo,
    //    &processInfo)) {
    //    // Tiến trình đã được tạo thành công

    //    // Gửi các tác vụ hoặc tiếp tục xử lý tiến trình con (tùy ý)

    //    // Đóng handle không cần thiết
    //    CloseHandle(processInfo.hProcess);
    //    CloseHandle(processInfo.hThread);
    //    msb(L"Tạo thành công tiến trình");
    //}
    //else {
    //    // Lỗi khi tạo tiến trình
    //    DWORD error = GetLastError();
    //    msb(L"Lỗi mở tạo tiến trình");
    //}

    // Cấu trúc để lưu trữ thông tin về tiến trình mới
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;

    // Khởi tạo cấu trúc STARTUPINFO
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);

    // Mở tiến trình
    if (CreateProcess(pathRunFile, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo)) {
        std::cout << "Tiến trình được mở thành công!" << std::endl;

        // Đóng handles không cần thiết
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    }
    else {
        std::cerr << "Lỗi khi mở tiến trình!" << std::endl;
    }
}

void accessAndOpen(LPCWSTR path) {
    WIN32_FIND_DATA findFile;

    HANDLE hFind = FindFirstFile(path, &findFile);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {

            // Sử dụng ShellExecute để mở tệp
            HINSTANCE result = ShellExecute(NULL, L"open", path, NULL, NULL, SW_SHOWNORMAL);

            if ((intptr_t)result > 32) {
                msb(L"Mở thành công tệp");
                // Mở tệp thành công
                // intptr_t được sử dụng để so sánh giá trị trả về với 32
                // Giá trị trả về lớn hơn 32 thường đại diện cho việc thành công
            }
            else {
                // Không thể mở tệp
                DWORD error = (DWORD)result;
                if (error == ERROR_FILE_NOT_FOUND) {
                    // Tệp không tồn tại
                    msb(L"Tệp không tồn tại");
                }
                else {
                    // Lỗi mở tệp
                    msb(L"Lỗi mở file");
                }
            }
        } while (FindNextFile(hFind, &findFile) != 0);
        FindClose(hFind);
    }
    else {
        MessageBox(NULL, L"Lỗi", L"title", MB_OK);
    }
}

void brightness(char type) {
    if (type == '1') {
        cout << "Do sang man hinh hien tai la: ";
        system("powershell.exe -Command \"Get-Ciminstance -Namespace root/WMI -ClassName WmiMonitorBrightness | Select -ExpandProperty \"CurrentBrightness\"\"");
        cout << "\n";
    }
    else {
        cout << "Nhap vao do sang mong muon (0 - 100) : "; int level; std::cin >> level;
        SHELLEXECUTEINFO info = { 0 };
        info.cbSize = sizeof(info);
        info.fMask = SEE_MASK_NOCLOSEPROCESS;
        info.lpVerb = L"runas";
        info.lpFile = L"powershell.exe";
        string cmd = "-Command (Get-WmiObject -Namespace root/WMI -Class WmiMonitorBrightnessMethods).WmiSetBrightness(1," + to_string(level) +  ")";
        info.lpParameters = convertStrToLPCW(cmd);
        if (!ShellExecuteEx(&info)) {
            std::cout << "Failed to run PowerShell with admin privileges." << std::endl;
            return;
        }
        if (info.hProcess == 0) {
            return;
        }
        WaitForSingleObject(info.hProcess, INFINITE);
        CloseHandle(info.hProcess);
    }
}

void systeminfo(){

    //SYSTEM_INFO si;
    //GetSystemInfo(&si);

    //printf("Hardware information: \n");
    //printf("OEM ID: %u\n", si.dwOemId);
    //printf("Number of processors: %u\n", si.dwNumberOfProcessors);
    //printf("Processor type: %u\n", si.dwProcessorType);

    //std::cout << "Processor Architecture: ";
    //switch (si.wProcessorArchitecture) {
    //case PROCESSOR_ARCHITECTURE_INTEL:
    //    std::cout << "x86 (32-bit)" << std::endl;
    //    break;
    //case PROCESSOR_ARCHITECTURE_AMD64:
    //    std::cout << "x64 (64-bit)" << std::endl;
    //    break;
    //case PROCESSOR_ARCHITECTURE_ARM:
    //    std::cout << "ARM" << std::endl;
    //    break;
    //default:
    //    std::cout << "Unknown" << std::endl;
    //    break;
    //}

    //std::cout << "Number of Processor Cores: " << si.dwNumberOfProcessors << std::endl;
    //std::cout << "Page Size: " << si.dwPageSize << " bytes" << std::endl;
    //std::cout << "Minimum Application Address: 0x" << si.lpMinimumApplicationAddress << std::endl;
    //std::cout << "Maximum Application Address: 0x" << si.lpMaximumApplicationAddress << std::endl;
    //std::cout << "Allocation Granularity: " << si.dwAllocationGranularity << " bytes" << std::endl;
    //std::cout << "Active Processor Mask: 0x" << si.dwActiveProcessorMask << std::endl;

    std::wstring cmd(L"systeminfo");

    // Tạo lệnh cmd.exe bằng cách cắt ghép giá trị của hai biến vào chuỗi
    std::wstring cmdCommand = L"/k " + cmd;

    // Chuyển đổi lệnh thành LPCWSTR để sử dụng với ShellExecute
    LPCWSTR cmdCommandWstr = cmdCommand.c_str();

    HINSTANCE hInstance = ShellExecute(NULL, L"runas", L"cmd.exe", cmdCommandWstr, NULL, SW_SHOWNORMAL);

}

void changeBackground() {
    string path = getPath();
    if (isFile(path)) {
        const wchar_t* imagePath = convertStrToLPCW(path);
        // Sử dụng API để đặt hình nền máy tính
        SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (PVOID)imagePath, SPIF_UPDATEINIFILE);
    }
    else {
        msb(L"Link ảnh sai");
    }
}

void changePosTaskbar() {
    // Định nghĩa các hằng số cho vị trí của thanh taskbar
    int LEFT = 0;
    int TOP = 1;
    int RIGHT = 2;
    int BOTTOM = 3;

    // Lấy handle của thanh taskbar
    HWND taskbar = FindWindow(L"Shell_TrayWnd", NULL);

    // Lấy kích thước của thanh taskbar
    RECT taskbarRect;
    GetWindowRect(taskbar, &taskbarRect);

    // Di chuyển thanh taskbar đến vị trí mới (trên cùng)
    APPBARDATA abd;
    abd.cbSize = sizeof(APPBARDATA);
    abd.hWnd = taskbar;
    abd.uEdge = TOP;
    abd.rc.left = taskbarRect.left;
    abd.rc.top = taskbarRect.top;
    abd.rc.right = taskbarRect.right - taskbarRect.left;
    abd.rc.bottom = taskbarRect.bottom - taskbarRect.top;

    SHAppBarMessage(ABM_SETPOS, &abd);

    return;
}

void wifi(char type) {
    set<string> wifiList;
    // Thực thi lệnh và ghi kết quả vào tệp tin temp.txt
    system("netsh wlan show profiles > temp.txt");
    // Đọc nội dung của tệp tin temp.txt và lưu vào mảng wifiList
    ifstream file("temp.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t nameStart = line.find(": ");
            if (nameStart != string::npos) {
                string wifiName = line.substr(nameStart + 2);
                wifiList.insert(wifiName);
            }
        }
        file.close();
    }
    remove("temp.txt");
    if (type == '1') {
        for (const string& wifiName : wifiList) {
            cout << wifiName << endl;
        }
    }
    else {
        cin.ignore();
        cout << "Nhap ten wifi muon xem: "; string name; getline(cin, name);
        if (wifiList.count(name)) {
            string cmd = "netsh wlan show profile name=\"" + name + "\" key=clear";
            system(cmd.c_str());
        }
    }
}

void menu() {
    while (true) {
        cout << "\n\n";
        cout << "==============================\n";
        cout << "Chuong trinh quan li file\n";
        cout << "1. Tao mot thu muc moi\n";
        cout << "2. Sao chep tep\n";
        cout << "3. Chay mot tep\n";
        cout << "4. Mo mot tien trinh\n";
        cout << "5. Do sang man hinh\n";
        cout << "6. Thong tin may\n";
        cout << "7. Thay hinh nen may tinh\n";
        cout << "8. Doi vi tri thanh taskbar\n";
        cout << "9. Thong tin ve wifi\n";
        cout << "E/e. Ket thuc chuong trinh\n";
        char choice; std::cin >> choice;
        switch (choice)
        {
        case '1': {
            cout << "Chon mot thu muc:\n";
            string path = getPath();
            if (path == "~") {
                break;
            }
            cout << "Nhap ten thu muc can tao: ";
            string newFolder; std::cin >> newFolder;
            createDirectory(convertStrToLPCW(path + newFolder));
            break;
        }
        case '2': {
            cout << "Chon tep nguon:\n";
            string source = getPath();
            if (source == "~") {
                break;
            }
            if (!isFile(source)) {
                msb(L"Duong dan sai dinh dang");
                break;
            }
            //msb(convertStrToLPCW(source));
            cout << "Chon tep dich:\n";
            string route = getPath();
            if (route == "~") {
                break;
            }
            if (isFile(route)) {
                msb(L"Duong dan sai dinh dang");
                break;
            }
            //msb(convertStrToLPCW(route));
            copyFile(convertStrToLPCW(source), convertStrToLPCW(route));
            break;
        }
        case '3': {
            cout << "Chon tep can mo:\n";
            string path = getPath();
            if (path == "~") {
                break;
            }
            if (isFile(path)) {
                msb(convertStrToLPCW(path));
                accessAndOpen(convertStrToLPCW(path));
            }
            else {
                cout << "Duong dan sai dinh dang\n";
                break;
            }
            break;
        }
        case '4': {
            createProcess();
            break;
        }
        case '5': {
            cout << "Ban muon xem do sang hien tai hay chinh do sang:\n";
            cout << "1. Xem do sang\n";
            cout << "2. Sua do sang\n";
            char type; std::cin >> type;
            brightness(type);
            break;
        }
        case '6': {
            systeminfo();
            break;
        }
        case '7': {
            changeBackground();
            break;
        }
        case '8': {
            changePosTaskbar();
            break;
        }
        case '9': {
            cout << "Chon che do:\n";
            cout << "1. Xem danh sach ten wifi\n";
            cout << "2. Xem thong tin chi tiet 1 wifi\n";
            cout << "Chon : "; char type; cin >> type;
            wifi(type);
            break;
        }
        case 'E' | 'e': {
            cout << "Chuong trinh ket thuc!!!";
            exit(0);
            break;
        }
        default:
            break;
        }
    }
}

signed main() {
    /*
    *   Viết thêm vào đây vài câu để đỡ trống trải
    *   Chỉ một ít chứ nhóm em không thích kiểu dông dài
    *   Bài làm nhóm là của chung chứ không phải công ai
    *   Và những thứ nhóm em làm chỉ đúng chứ không sai
    */
    init();
    menu();
}