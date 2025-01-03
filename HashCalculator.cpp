#include "HashCalculator.h"
#include <sstream>
#include <iomanip>

std::wstring HashCalculator::CalculateMD5(const std::wstring& filePath) {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    BYTE rgbHash[16];
    DWORD cbHash = 0;
    std::wstring hashStr;

    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        return L"";
    }

    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
        CryptReleaseContext(hProv, 0);
        return L"";
    }

    HANDLE hFile = CreateFile(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, 
                            OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return L"";
    }

    BYTE buffer[4096];
    DWORD dwRead = 0;

    while (ReadFile(hFile, buffer, sizeof(buffer), &dwRead, NULL)) {
        if (dwRead == 0) break;
        if (!CryptHashData(hHash, buffer, dwRead, 0)) {
            CloseHandle(hFile);
            CryptDestroyHash(hHash);
            CryptReleaseContext(hProv, 0);
            return L"";
        }
    }

    cbHash = sizeof(rgbHash);
    if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0)) {
        std::wstringstream ss;
        for (DWORD i = 0; i < cbHash; i++) {
            ss << std::hex << std::setfill(L'0') << std::setw(2) << (int)rgbHash[i];
        }
        hashStr = ss.str();
    }

    CloseHandle(hFile);
    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    return hashStr;
}

std::wstring HashCalculator::CalculateSHA1(const std::wstring& filePath) {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    BYTE rgbHash[20];
    DWORD cbHash = 0;
    std::wstring hashStr;

    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        return L"";
    }

    if (!CryptCreateHash(hProv, CALG_SHA1, 0, 0, &hHash)) {
        CryptReleaseContext(hProv, 0);
        return L"";
    }

    HANDLE hFile = CreateFile(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, 
                            OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return L"";
    }

    BYTE buffer[4096];
    DWORD dwRead = 0;

    while (ReadFile(hFile, buffer, sizeof(buffer), &dwRead, NULL)) {
        if (dwRead == 0) break;
        if (!CryptHashData(hHash, buffer, dwRead, 0)) {
            CloseHandle(hFile);
            CryptDestroyHash(hHash);
            CryptReleaseContext(hProv, 0);
            return L"";
        }
    }

    cbHash = sizeof(rgbHash);
    if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0)) {
        std::wstringstream ss;
        for (DWORD i = 0; i < cbHash; i++) {
            ss << std::hex << std::setfill(L'0') << std::setw(2) << (int)rgbHash[i];
        }
        hashStr = ss.str();
    }

    CloseHandle(hFile);
    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    return hashStr;
}

std::wstring HashCalculator::FormatFileSize(uint64_t bytes) {
    const wchar_t* units[] = { L"B", L"KiB", L"MiB", L"GiB", L"TiB" };
    int unitIndex = 0;
    double size = static_cast<double>(bytes);

    while (size >= 1024.0 && unitIndex < 4) {
        size /= 1024.0;
        unitIndex++;
    }

    std::wstringstream ss;
    ss << bytes << L" 字节 : ";
    if (unitIndex == 0) {
        ss << static_cast<int>(size) << L" " << units[unitIndex];
    } else {
        ss << std::fixed << std::setprecision(2) << size << L" " << units[unitIndex];
    }
    return ss.str();
}

std::vector<HashCalculator::FileInfo> HashCalculator::ProcessFiles(
    const std::vector<std::wstring>& filePaths) {
    std::vector<FileInfo> results;

    for (const auto& path : filePaths) {
        FileInfo info;
        info.fileName = path;

        WIN32_FILE_ATTRIBUTE_DATA fileAttr;
        if (GetFileAttributesEx(path.c_str(), GetFileExInfoStandard, &fileAttr)) {
            ULARGE_INTEGER fileSize;
            fileSize.HighPart = fileAttr.nFileSizeHigh;
            fileSize.LowPart = fileAttr.nFileSizeLow;
            info.fileSize = fileSize.QuadPart;
        }

        info.md5Hash = CalculateMD5(path);
        info.sha1Hash = CalculateSHA1(path);
        results.push_back(info);
    }

    return results;
} 