#pragma once
#include <windows.h>
#include "HashCalculator.h"

class MainWindow {
public:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static bool RegisterWindowClass(HINSTANCE hInstance);
    static HWND Create(HINSTANCE hInstance, const std::vector<std::wstring>& files);

private:
    static void CreateControls(HWND hwnd);
    static void ProcessFiles(HWND hwnd, const std::vector<std::wstring>& files);
    static void CopyToClipboard(HWND hwnd);
}; 