#include "MainWindow.h"
#include <commctrl.h>
#include <windowsx.h>
#include <string>

#pragma comment(lib, "comctl32.lib")

namespace {
    const wchar_t CLASS_NAME[] = L"HashCalculatorWindow";
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const int IDC_EDIT = 1001;
    const int IDC_COPY = 1002;
    std::vector<HashCalculator::FileInfo> g_fileInfos;
}

LRESULT CALLBACK MainWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateControls(hwnd);
        return 0;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_COPY) {
            CopyToClipboard(hwnd);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool MainWindow::RegisterWindowClass(HINSTANCE hInstance) {
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    return RegisterClassEx(&wc) != 0;
}

HWND MainWindow::Create(HINSTANCE hInstance, const std::vector<std::wstring>& files) {
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int x = (screenWidth - WINDOW_WIDTH) / 2;
    int y = (screenHeight - WINDOW_HEIGHT) / 2;

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"文件哈希计算器",
        WS_OVERLAPPEDWINDOW,
        x, y, WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd) {
        ProcessFiles(hwnd, files);
        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);
    }

    return hwnd;
}

void MainWindow::CreateControls(HWND hwnd) {
    // 创建多行文本框
    CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL,
        10, 10,
        WINDOW_WIDTH - 40, WINDOW_HEIGHT - 100,
        hwnd,
        (HMENU)IDC_EDIT,
        GetModuleHandle(NULL),
        NULL
    );

    // 创建复制按钮
    CreateWindowW(
        L"BUTTON",
        L"复制",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        10, WINDOW_HEIGHT - 80,
        100, 30,
        hwnd,
        (HMENU)IDC_COPY,
        GetModuleHandle(NULL),
        NULL
    );
}

void MainWindow::ProcessFiles(HWND hwnd, const std::vector<std::wstring>& files) {
    g_fileInfos = HashCalculator::ProcessFiles(files);
    
    std::wstring display;
    for (const auto& info : g_fileInfos) {
        display += L"名称: " + info.fileName + L"\r\n";
        display += L"大小: " + HashCalculator::FormatFileSize(info.fileSize) + L"\r\n";
        display += L"SHA1: " + info.sha1Hash + L"\r\n";
        display += L"MD5: " + info.md5Hash + L"\r\n\r\n";
    }

    // 设置文本框内容
    HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
    SetWindowTextW(hEdit, display.c_str());

    // 设置文本框字体
    HFONT hFont = CreateFontW(
        16,                     // 字体高度
        0,                      // 字体宽度
        0,                      // 倾斜角度
        0,                      // 旋转角度
        FW_NORMAL,             // 字体粗细
        FALSE,                 // 是否斜体
        FALSE,                 // 是否有下划线
        FALSE,                 // 是否有删除线
        DEFAULT_CHARSET,       // 字符集
        OUT_DEFAULT_PRECIS,    // 输出精度
        CLIP_DEFAULT_PRECIS,   // 裁剪精度
        DEFAULT_QUALITY,       // 输出质量
        DEFAULT_PITCH | FF_DONTCARE,  // 字体间距和字体族
        L"Microsoft YaHei"     // 字体名称
    );
    SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
}

void MainWindow::CopyToClipboard(HWND hwnd) {
    HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
    int length = GetWindowTextLength(hEdit);
    
    if (length > 0 && OpenClipboard(hwnd)) {
        EmptyClipboard();
        
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, (length + 1) * sizeof(wchar_t));
        if (hMem) {
            wchar_t* buffer = (wchar_t*)GlobalLock(hMem);
            GetWindowText(hEdit, buffer, length + 1);
            GlobalUnlock(hMem);
            
            SetClipboardData(CF_UNICODETEXT, hMem);
        }
        CloseClipboard();
    }
} 