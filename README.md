# 项目介绍

面向大一学生C++课程设计，大家可以参考一下

# 五子棋 (Gomoku)

基于 EasyX 图形库的 C++ 五子棋双人对战游戏，支持账户系统、排行榜、存档和悔棋功能。

## 功能特性

- **双人对战**：19×19 标准棋盘，黑白双方交替落子
- **账户系统**：登录/注册账户，支持持久化存储（UTF-8编码）
- **排行榜**：按累计胜场降序排列，实时更新
- **存档功能**：退出游戏时自动保存棋盘，下次可继续
- **悔棋功能**：按 Backspace 撤销上一步落子
- **胜利高亮**：五连棋子以金色双圈标记
- **批量绘图**：使用 EasyX 的批量绘图机制，减少闪烁

## 操作说明

| 操作 | 玩家1 (黑子) | 玩家2 (白子) |
|------|-------------|-------------|
| 移动光标 | W/A/S/D | ↑/←/↓/→ |
| 落子 | F | 0 (数字零) |
| 悔棋 | Backspace | Backspace |
| 退出游戏 | ESC | ESC |

## 项目结构

```
chengxu/
├── main.cpp              # 程序入口
├── Initialization.h/cpp  # 图形窗口初始化/销毁
├── Mouse.h               # 主消息循环和页面切换逻辑
├── Page.h                # 页面基类和各页面子类声明
├── Page_menu.cpp         # 主菜单页面
├── Page_game.cpp         # 游戏核心逻辑（棋盘、落子、判胜、悔棋）
├── Page_setting.cpp      # 设置页面（开发中）
├── Page_help.cpp         # 存档/帮助页面
├── Page_rank.cpp         # 排行榜页面
├── Button.h/cpp          # 按钮组件封装
├── Account.h/cpp         # 账户系统（登录、注册、排行榜）
├── Player.h              # 玩家结构体
├── Currentpage.h         # 页面状态枚举
├── Toolbox.h             # 工具函数（myMax/myMin）
├── Account.txt           # 账户数据文件（UTF-8）
├── Date.text             # 棋盘存档文件
├── Easyx/                # EasyX 库文件
│   ├── include/          # 头文件
│   ├── lib x64/          # 64位库
│   └── lib x86/          # 32位库
└── CMakeLists.txt        # CMake 构建配置
```

## 依赖

- **EasyX 图形库**：项目自带（`Easyx/` 目录），需配置 include 和 lib 路径
- **编译器**：MSVC（Visual Studio），需支持 C++20
- **平台**：Windows

## 构建方式

### Visual Studio

1. 打开 `chengxu.slnx` 或 `chengxu.vcxproj`
2. 配置 EasyX 的 include 和 lib 路径：
   - 包含目录：`Easyx/include/`
   - 库目录：`Easyx/lib x64/`（64位）或 `Easyx/lib x86/`（32位）
3. 链接 `EasyXa.lib`（静态库）或 `EasyXw.lib`（动态库）
4. 构建并运行

### CMake

```bash
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

> 注意：使用 CMake 构建时需手动配置 EasyX 的头文件和库文件路径。

## 数据文件

| 文件 | 说明 |
|------|------|
| `Account.txt` | 账户数据，格式：`用户名 密码 胜场数`（UTF-8编码，每行一个账户） |
| `Date.text` | 棋盘存档，格式：19行×19列的数字矩阵（0=空, 1=黑, 2=白） |

## 注意事项

- 退出游戏请使用 **ESC键**，直接关闭窗口可能导致后台进程残留
- 存档为一次性使用：加载后存档文件会被清空
- 账户用户名和密码建议不超过15个字符
- 设置页面功能尚在开发中