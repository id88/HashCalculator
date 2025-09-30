# 贡献指南 / Contributing Guide

感谢您对 HashCalculator 项目的兴趣！我们欢迎所有形式的贡献。

Thank you for your interest in contributing to HashCalculator! We welcome all forms of contributions.

## 贡献方式 / Ways to Contribute

### 🐛 报告错误 / Report Bugs
- 使用 [Bug Report 模板](https://github.com/id88/HashCalculator/issues/new?template=bug_report.md)
- 提供详细的重现步骤和环境信息
- 包含错误截图或日志（如果适用）

### ✨ 提出功能请求 / Feature Requests
- 使用 [Feature Request 模板](https://github.com/id88/HashCalculator/issues/new?template=feature_request.md)
- 详细描述功能的用途和价值
- 提供使用场景和实现建议

### 💬 提问和讨论 / Questions and Discussions
- 使用 [Question 模板](https://github.com/id88/HashCalculator/issues/new?template=question.md)
- 查看现有 Issues 避免重复提问
- 参与社区讨论和帮助其他用户

### 🔧 代码贡献 / Code Contributions
- 修复 Bug
- 实现新功能
- 改进性能
- 优化代码质量
- 更新文档

## 开发环境设置 / Development Setup

### 环境要求 / Prerequisites
- Windows 7/8/10/11 (x64)
- Visual Studio 2019/2022 或 Visual Studio Build Tools
- Windows SDK
- Git

### 本地开发 / Local Development

1. **Fork 和克隆仓库 / Fork and Clone**
   ```bash
   git clone https://github.com/your-username/HashCalculator.git
   cd HashCalculator
   ```

2. **设置编译环境 / Setup Build Environment**
   ```cmd
   call "D:\VisualStudio_BuildTools\VC\Auxiliary\Build\vcvars64.bat"
   ```

3. **编译项目 / Build Project**
   ```cmd
   cl /c /EHsc /std:c++17 /DUNICODE /D_UNICODE HashCalculator.cpp MainWindow.cpp main.cpp
   link /OUT:HashCalculator.exe HashCalculator.obj MainWindow.obj main.obj user32.lib gdi32.lib comctl32.lib advapi32.lib Shell32.lib
   ```

4. **测试 / Testing**
   - 手动测试右键菜单功能
   - 测试各种文件类型的哈希计算
   - 验证复制功能
   - 测试多文件处理

## 提交流程 / Submission Process

### Pull Request 流程 / PR Workflow

1. **创建分支 / Create Branch**
   ```bash
   git checkout -b feature/your-feature-name
   # 或 / or
   git checkout -b fix/your-bug-fix
   ```

2. **进行更改 / Make Changes**
   - 遵循代码规范
   - 添加必要的注释
   - 保持提交信息清晰

3. **提交更改 / Commit Changes**
   ```bash
   git add .
   git commit -m "feat: add new feature description"
   # 或 / or
   git commit -m "fix: resolve specific bug issue"
   ```

4. **推送分支 / Push Branch**
   ```bash
   git push origin feature/your-feature-name
   ```

5. **创建 Pull Request / Create Pull Request**
   - 使用提供的 PR 模板
   - 详细描述更改内容
   - 关联相关 Issues
   - 请求代码审查

### 提交信息规范 / Commit Message Guidelines

使用 [Conventional Commits](https://www.conventionalcommits.org/) 格式：

```
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
```

**类型 / Types:**
- `feat`: 新功能 / new feature
- `fix`: 错误修复 / bug fix
- `docs`: 文档更新 / documentation
- `style`: 代码格式 / formatting
- `refactor`: 代码重构 / refactoring
- `perf`: 性能优化 / performance
- `test`: 测试相关 / testing
- `chore`: 其他更改 / other changes

**示例 / Examples:**
```
feat: add SHA256 hash calculation support
fix: resolve file handle leak in hash calculation
docs: update installation instructions
style: format code according to style guide
refactor: simplify hash calculation logic
perf: optimize large file processing
```

## 代码规范 / Code Standards

### C++ 代码风格 / C++ Style Guide

1. **命名规范 / Naming Conventions**
   - 类名使用 PascalCase: `HashCalculator`
   - 函数名使用 PascalCase: `CalculateMD5`
   - 变量名使用 camelCase: `fileSize`
   - 常量使用 UPPER_CASE: `WINDOW_WIDTH`

2. **代码格式 / Code Formatting**
   - 使用 4 个空格缩进
   - 大括号另起一行
   - 行长度不超过 100 字符
   - 操作符前后添加空格

3. **注释规范 / Comment Guidelines**
   - 使用中英文双语注释
   - 为复杂逻辑添加解释
   - 更新注释与代码保持同步

### 示例代码 / Example Code

```cpp
class HashCalculator {
public:
    // 计算文件MD5哈希值 / Calculate MD5 hash of file
    static std::wstring CalculateMD5(const std::wstring& filePath);
    
private:
    // 内部辅助函数 / Internal helper function
    static bool ProcessFileData(HANDLE hFile, HCRYPTHASH hHash);
};
```

## 测试指南 / Testing Guidelines

### 测试清单 / Testing Checklist

在提交 PR 之前，请确保：
Before submitting a PR, please ensure:

- [ ] **基本功能测试 / Basic Functionality**
  - [ ] 右键菜单正常显示 / Context menu displays correctly
  - [ ] MD5 计算准确 / MD5 calculation is accurate
  - [ ] SHA1 计算准确 / SHA1 calculation is accurate
  - [ ] 复制功能正常 / Copy functionality works

- [ ] **兼容性测试 / Compatibility Testing**
  - [ ] Windows 10 测试 / Windows 10 testing
  - [ ] Windows 11 测试 / Windows 11 testing
  - [ ] 不同文件类型测试 / Different file types testing
  - [ ] 大文件测试 / Large file testing

- [ ] **边界条件测试 / Edge Case Testing**
  - [ ] 空文件测试 / Empty file testing
  - [ ] 特殊字符文件名 / Special character filenames
  - [ ] 网络路径文件 / Network path files
  - [ ] 权限受限文件 / Permission-restricted files

## 发布流程 / Release Process

### 版本号规范 / Version Numbering
遵循 [语义化版本控制](https://semver.org/lang/zh-CN/)：
Follow [Semantic Versioning](https://semver.org/):

- `v1.0.0` - 主版本 / Major version
- `v1.1.0` - 次版本 / Minor version  
- `v1.0.1` - 补丁版本 / Patch version

### 发布步骤 / Release Steps
1. 更新版本号和更新日志
2. 创建版本标签
3. GitHub Actions 自动构建和发布
4. 验证发布包完整性

## 社区准则 / Community Guidelines

### 行为规范 / Code of Conduct

- 🤝 **尊重他人** / Be respectful
- 💬 **建设性交流** / Constructive communication
- 🎯 **专注项目目标** / Stay focused on project goals
- 📚 **乐于学习和分享** / Be willing to learn and share
- 🐛 **耐心处理问题** / Be patient with issues

### 沟通语言 / Communication Language
- 支持中文和英文 / Support both Chinese and English
- Issue 和 PR 可以使用任一语言 / Issues and PRs can use either language
- 重要文档提供双语版本 / Important docs provide bilingual versions

## 获得帮助 / Getting Help

### 联系方式 / Contact Methods

- 🐛 **Bug 报告** / Bug Reports: [创建 Issue](https://github.com/id88/HashCalculator/issues/new/choose)
- 💡 **功能建议** / Feature Suggestions: [功能请求](https://github.com/id88/HashCalculator/issues/new?template=feature_request.md)
- ❓ **使用问题** / Usage Questions: [提问](https://github.com/id88/HashCalculator/issues/new?template=question.md)
- 💬 **讨论** / Discussions: [GitHub Discussions](https://github.com/id88/HashCalculator/discussions)

### 响应时间 / Response Time
- 一般问题：1-3 工作日 / General issues: 1-3 business days
- 紧急 Bug：24 小时内 / Critical bugs: within 24 hours
- 功能请求：1 周内 / Feature requests: within 1 week

## 致谢 / Acknowledgments

感谢所有为 HashCalculator 项目做出贡献的开发者和用户！
Thanks to all developers and users who contribute to the HashCalculator project!

---

通过贡献代码，您同意您的贡献将在 MIT 许可证下发布。
By contributing code, you agree that your contributions will be licensed under the MIT License.