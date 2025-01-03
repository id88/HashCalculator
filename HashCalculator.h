#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <wincrypt.h>
#include <commctrl.h>

class HashCalculator {
public:
    struct FileInfo {
        std::wstring fileName;
        uint64_t fileSize;
        std::wstring md5Hash;
        std::wstring sha1Hash;
    };

    static std::wstring CalculateMD5(const std::wstring& filePath);
    static std::wstring CalculateSHA1(const std::wstring& filePath);
    static std::wstring FormatFileSize(uint64_t bytes);
    static std::vector<FileInfo> ProcessFiles(const std::vector<std::wstring>& filePaths);
}; 