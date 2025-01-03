#include <windows.h>
#include <string>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // 检查管理员权限
    BOOL isAdmin = FALSE;
    PSID adminGroup = NULL;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup)) {
        CheckTokenMembership(NULL, adminGroup, &isAdmin);
        FreeSid(adminGroup);
    }

    if (!isAdmin) {
        MessageBox(NULL, L"请以管理员权限运行此程序", L"错误", MB_OK | MB_ICONERROR);
        return 1;
    }

    // 注册右键菜单
    HKEY hKey;
    std::wstring keyPath = L"*\\shell\\HashCalculator";
    if (RegCreateKeyEx(HKEY_CLASSES_ROOT, keyPath.c_str(), 0, NULL, 
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
        
        // 设置菜单显示文字
        std::wstring menuText = L"文件MD5和SHA1";
        RegSetValueEx(hKey, NULL, 0, REG_SZ, 
            (BYTE*)menuText.c_str(), 
            (menuText.length() + 1) * sizeof(wchar_t));

        // 设置图标
        std::wstring iconPath = L"\"C:\\Program Files\\HashCalculator\\HashCalculator.exe\"";
        RegSetValueEx(hKey, L"Icon", 0, REG_SZ,
            (BYTE*)iconPath.c_str(),
            (iconPath.length() + 1) * sizeof(wchar_t));

        RegCloseKey(hKey);

        // 注册命令
        std::wstring cmdKeyPath = keyPath + L"\\command";
        if (RegCreateKeyEx(HKEY_CLASSES_ROOT, cmdKeyPath.c_str(), 0, NULL,
            REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
            
            std::wstring command = L"\"C:\\Program Files\\HashCalculator\\HashCalculator.exe\" \"%V\"";
            RegSetValueEx(hKey, NULL, 0, REG_SZ,
                (BYTE*)command.c_str(),
                (command.length() + 1) * sizeof(wchar_t));

            RegCloseKey(hKey);
            MessageBox(NULL, L"右键菜单注册成功！", L"成功", MB_OK | MB_ICONINFORMATION);
        }
    }

    return 0;
}