# GitHub Actions 自动发布指南

## 概述

现在您的 HashCalculator 项目已经配置了完整的 GitHub Actions 工作流，可以自动构建和发布可执行文件。

## 工作流功能

### 构建流程
- ✅ 自动编译 C++ 源代码
- ✅ 链接生成 `HashCalculator.exe`
- ✅ 打包完整的发布包（包含 exe、注册文件、说明文档）
- ✅ 上传构建产物到 GitHub Actions

### 发布流程
- ✅ 检测版本标签 (v1.0.0, v1.1.0 等)
- ✅ 自动创建 GitHub Release
- ✅ 上传完整的发布包到 Release Assets
- ✅ 生成详细的发布说明

## 如何触发自动发布

### 方法一：通过 GitHub 网页界面创建 Release

1. 访问您的 GitHub 仓库页面
2. 点击右侧的 "Releases" 
3. 点击 "Create a new release"
4. 在 "Tag version" 中输入版本号，格式：`v1.0.0`
5. 填写 Release 标题和描述
6. 点击 "Publish release"

### 方法二：通过命令行创建标签

```bash
# 创建并推送标签
git tag v1.0.0
git push origin v1.0.0
```

### 方法三：使用 GitHub CLI

```bash
# 创建发布
gh release create v1.0.0 --title "HashCalculator v1.0.0" --notes "首个正式版本"
```

## 版本号规范

请使用语义化版本控制 (Semantic Versioning)：

- `v1.0.0` - 主要版本（重大更改）
- `v1.1.0` - 次要版本（新功能）
- `v1.0.1` - 补丁版本（Bug 修复）

## 发布包内容

每次自动发布会生成 `HashCalculator-v{版本号}.zip` 文件，包含：

```
HashCalculator-v1.0.0.zip
├── HashCalculator.exe      # 主程序
├── register.reg           # 右键菜单注册文件
└── Installation_Guide.txt # 详细安装指南（中英文双语）
```

## 工作流触发条件

### 构建触发条件
- 推送到 `main` 分支
- 创建针对 `main` 分支的 Pull Request
- 推送版本标签 (v*.*.*)

### 发布触发条件
- **仅在推送版本标签时触发** (如 `v1.0.0`)

## 查看构建状态

1. 访问仓库的 "Actions" 页面
2. 查看最新的工作流运行状态
3. 点击具体的运行查看详细日志

## 下载构建产物

### 开发版本 (每次推送)
1. 进入 Actions 页面
2. 点击对应的工作流运行
3. 在 "Artifacts" 部分下载构建结果

### 正式版本 (标签发布)
1. 进入 Releases 页面
2. 直接下载对应版本的 Assets

## 故障排除

### 构建失败
- 检查 C++ 代码是否有语法错误
- 确认所有必需的头文件和库都已包含
- 查看 Actions 日志获取详细错误信息

### 发布失败
- 确认标签格式正确 (v1.0.0)
- 检查仓库权限设置
- 确认 GITHUB_TOKEN 有足够权限

### 常见问题

**Q: 为什么推送代码后没有自动发布？**
A: 自动发布只在推送版本标签时触发，普通代码推送只会构建不会发布。

**Q: 如何修改发布说明模板？**
A: 编辑 `.github/workflows/build.yml` 文件中的 `body` 部分。

**Q: 如何添加更多文件到发布包？**
A: 在工作流的 "创建发布包" 步骤中添加更多 `Copy-Item` 命令。

## 下一步

1. 创建您的第一个发布：`git tag v1.0.0 && git push origin v1.0.0`
2. 观察自动构建和发布过程
3. 根据需要调整工作流配置

---

祝您使用愉快！如有问题，请查看 GitHub Actions 日志或创建 Issue。
