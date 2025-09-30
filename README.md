# HashCalculator

一个简单易用的 Windows 文件哈希计算器，集成到右键菜单中，可以快速计算文件的 MD5 和 SHA1 哈希值。

## 功能特性

- 🔒 **双重哈希算法**：同时计算 MD5 和 SHA1 哈希值
- 🖱️ **右键菜单集成**：在文件资源管理器中右键即可使用
- 📋 **一键复制**：点击复制按钮将哈希值复制到剪贴板
- 📦 **批量处理**：支持同时处理多个文件
- 🎨 **友好界面**：简洁的中文用户界面
- ⚡ **高性能**：使用 Windows 原生 API，计算速度快

## 快速开始

### 下载安装

1. 访问 [Releases 页面](https://github.com/id88/HashCalculator/releases)
2. 下载最新版本的 `HashCalculator-v*.zip`
3. 解压到任意目录
4. 将 `HashCalculator.exe` 复制到 `C:\Program Files\HashCalculator\` 目录
5. 以管理员身份运行 `register.reg` 注册右键菜单

### 使用方法

1. 在文件资源管理器中，右键单击任意文件
2. 在右键菜单中选择"文件MD5和SHA1"
3. 在弹出的窗口中查看文件的哈希值
4. 点击"复制"按钮可将信息复制到剪贴板

## 开发者指南

### 环境要求

- Windows 7/8/10/11 (x64)
- Visual Studio 2019/2022 或 Visual Studio Build Tools
- Windows SDK

### 本地编译

1. **设置编译环境**:
   ```cmd
   call "D:\VisualStudio_BuildTools\VC\Auxiliary\Build\vcvars64.bat"
   ```

2. **编译源文件**:
   ```cmd
   cl /c /EHsc /std:c++17 /DUNICODE /D_UNICODE HashCalculator.cpp MainWindow.cpp main.cpp
   ```

3. **链接可执行文件**:
   ```cmd
   link /OUT:HashCalculator.exe HashCalculator.obj MainWindow.obj main.obj user32.lib gdi32.lib comctl32.lib advapi32.lib Shell32.lib
   ```

### 项目结构

```
HashCalculator/
├── HashCalculator.cpp      # 哈希计算核心逻辑
├── HashCalculator.h        # 哈希计算头文件
├── MainWindow.cpp          # 主窗口实现
├── MainWindow.h            # 主窗口头文件
├── main.cpp               # 程序入口点
├── register.reg           # 右键菜单注册文件
└── README.md              # 项目说明文档
```

## 自动化构建

本项目使用 GitHub Actions 进行自动化构建和发布：

- ✅ 每次推送到 `main` 分支自动构建
- ✅ 推送版本标签自动创建 Release
- ✅ 自动打包完整安装包
- ✅ 详细的构建日志和错误报告

查看 [发布指南](RELEASE_GUIDE.md) 了解更多详情。

## 技术特性

- **编程语言**：C++17
- **UI 框架**：Windows API (Win32)
- **哈希算法**：Windows Cryptography API
- **编译器**：MSVC
- **架构**：x64

## 系统要求

- **操作系统**：Windows 7 SP1 或更高版本
- **处理器**：x64 兼容处理器
- **运行时**：Visual C++ Redistributable for Visual Studio 2019/2022
- **权限**：安装时需要管理员权限

## 注意事项

- 需要管理员权限来注册右键菜单
- 确保系统已安装 Visual C++ Runtime
- 如遇到问题，检查系统环境变量是否正确设置
- 卸载时需要手动删除程序文件和注册表项

## 许可证

本项目采用 MIT 许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。

## 贡献

欢迎提交 Issue 和 Pull Request！

## 更新日志

查看 [Releases](https://github.com/id88/HashCalculator/releases) 页面了解版本更新历史。

