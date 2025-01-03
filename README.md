### 编译步骤

1. **设置编译环境**:
   打开命令提示符，运行以下命令设置编译环境：
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

4. **安装步骤**:
   - 创建目录：`C:\Program Files\HashCalculator`
   - 复制 HashCalculator.exe 到该目录
   - 以管理员身份运行 register.reg 注册右键菜单

### 使用说明
1. 在文件资源管理器中，右键单击任意文件
2. 在右键菜单中选择"文件MD5和SHA1"
3. 在弹出的窗口中查看文件的哈希值
4. 点击"复制"按钮可将信息复制到剪贴板

### 注意事项
- 需要管理员权限来注册右键菜单
- 确保系统已安装 Visual C++ Runtime
- 如遇到问题，检查系统环境变量是否正确设置

