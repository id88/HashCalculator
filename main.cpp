#include "MainWindow.h"
#include "version.h"
#include <windows.h>
#include <vector>
#include <string>
#include <shellapi.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // 初始化 Common Controls
    INITCOMMONCONTROLSEX icc;
    icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icc.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icc);

    // 获取命令行参数
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    std::vector<std::wstring> files;
    
    // 跳过第一个参数（程序路径）
    for (int i = 1; i < argc; i++) {
        files.push_back(argv[i]);
    }
    LocalFree(argv);

    if (files.empty()) {
        MessageBoxW(NULL, L"请通过右键菜单选择文件！", L"错误", MB_OK | MB_ICONERROR);
        return 1;
    }

    // 注册窗口类
    if (!MainWindow::RegisterWindowClass(hInstance)) {
        return 1;
    }

    // 创建主窗口（只创建一个窗口）
    HWND hwnd = MainWindow::Create(hInstance, files);
    if (!hwnd) {
        return 1;
    }

    // 消息循环
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
} 