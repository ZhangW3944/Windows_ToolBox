// Copyright (c) 2024-2025 Desperate lnc.
// SPDX-License-Identifier: MIT
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <ctime>

using namespace std;

// 设置控制台颜色
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// 显示带边框的标题
void showTitle(const string& title) {
    setColor(11); // 亮青色
    cout << "==============================================" << endl;
    cout << "||               " << title << "               ||" << endl;
    cout << "==============================================" << endl;
    setColor(7); // 恢复默认白色
}

// 显示系统信息
void showSystemInfo() {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(memInfo);
    GlobalMemoryStatusEx(&memInfo);

    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);

    stringstream ss;
    ss << "════════════ 系统信息 ════════════\n\n";
    ss << "□ 操作系统: Windows " << osvi.dwMajorVersion << "." << osvi.dwMinorVersion << "\n";
    ss << "□ 处理器架构: ";
    switch(si.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64: ss << "x64"; break;
        case PROCESSOR_ARCHITECTURE_ARM: ss << "ARM"; break;
        case PROCESSOR_ARCHITECTURE_IA64: ss << "Itanium"; break;
        case PROCESSOR_ARCHITECTURE_INTEL: ss << "x86"; break;
        default: ss << "未知"; break;
    }
    ss << "\n□ 处理器数量: " << si.dwNumberOfProcessors << "\n";
    ss << "□ 内存总量: " << memInfo.ullTotalPhys/1024/1024 << " MB\n";
    ss << "□ 可用内存: " << memInfo.ullAvailPhys/1024/1024 << " MB\n\n";
    ss << "═══════════════════════════════════";

    MessageBox(NULL, ss.str().c_str(), "系统信息", MB_ICONINFORMATION | MB_OK);
}

// 显示IP配置
void showIPConfig() {
    system("ipconfig > ipconfig.txt");
    ifstream file("ipconfig.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("ipconfig.txt");
    
    MessageBox(NULL, content.c_str(), "IP配置信息", MB_ICONINFORMATION | MB_OK);
}

// 执行磁盘清理
void diskCleanup() {
    if (MessageBox(NULL, "确定要执行磁盘清理吗?", "磁盘清理", MB_ICONQUESTION | MB_YESNO) == IDYES) {
        system("cleanmgr /sagerun:1");
        MessageBox(NULL, "磁盘清理已启动", "信息", MB_ICONINFORMATION | MB_OK);
    }
}

// 测试网络连接
void testNetwork() {
    system("ping 8.8.8.8 -n 4 > ping.txt");
    ifstream file("ping.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("ping.txt");
    
    MessageBox(NULL, content.c_str(), "网络测试结果", MB_ICONINFORMATION | MB_OK);
}

// 获取时间截图功能
void takeScreenshot() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << "screenshot_" 
       << 1900 + ltm->tm_year << "_"
       << 1 + ltm->tm_mon << "_"
       << ltm->tm_mday << "_"
       << ltm->tm_hour << "_"
       << ltm->tm_min << "_"
       << ltm->tm_sec << ".bmp";
    
    string cmd = "nircmd savescreenshot " + ss.str();
    system(cmd.c_str());
    
    MessageBox(NULL, ("截图已保存为: " + ss.str()).c_str(), "截图完成", MB_ICONINFORMATION | MB_OK);
}

// 显示主菜单
void showMainMenu() {
    system("title Windows 工具箱");
    system("cls");
    
    setColor(14); // 黄色
    cout << R"(
   __      __.__  __  .__       _________                      
  /  \    /  \__|/  |_|  |__   /   _____/ ____ _____    ____  
  \   \/\/   /  \   __\  |  \  \_____  \_/ ___\\__  \  /    \ 
   \        /|  ||  | |   Y  \ /        \  \___ / __ \|   |  \
    \__/\  / |__||__| |___|  //_______  /\___  >____  /___|  /
         \/                \/          \/     \/     \/     \/ 
    )" << endl;
    
    setColor(10); // 亮绿色
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║             Windows 工具箱              ║" << endl;
    cout << "╠══════════════════════════════════════════╣" << endl;
    
    setColor(11); // 亮青色
    cout << "║ 1. 资源管理器                            ║" << endl;
    cout << "║ 2. 任务管理器                            ║" << endl;
    cout << "║ 3. 注册表编辑器                          ║" << endl;
    cout << "║ 4. 恶意软件删除工具                      ║" << endl;
    cout << "║ 5. 控制面板                              ║" << endl;
    cout << "║ 6. 关机                                  ║" << endl;
    cout << "║ 7. 注销                                  ║" << endl;
    cout << "║ 8. 重启                                  ║" << endl;
    cout << "║ 9. 系统信息                              ║" << endl;
    cout << "║ a. IP配置                                ║" << endl;
    cout << "║ b. 磁盘清理                              ║" << endl;
    cout << "║ c. 网络测试                              ║" << endl;
    cout << "║ d. 计算器                                ║" << endl;
    cout << "║ e. 记事本                                ║" << endl;
    cout << "║ f. 获取时间截图                          ║" << endl;
    cout << "║ 0. 管理员功能                            ║" << endl;
    cout << "║ x. 退出                                  ║" << endl;
    
    setColor(10); // 亮绿色
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;
    
    setColor(14); // 黄色
    cout << "请选择功能: ";
    setColor(7); // 恢复默认白色
}

// 管理员登录界面
bool adminLogin() {
    system("cls");
    showTitle("管理员登录");
    
    setColor(14);
    cout << R"(
   _____                           .__          
  /     \   ____   ____   ____    |__| _____   
 /  \ /  \ /  _ \ /    \ /  _ \   |  |/     \  
/    Y    (  <_> )   |  (  <_> )  |  |  Y Y  \ 
\____|__  /\____/|___|  /\____/\__|  |__|_|  / 
        \/            \/      \______|     \/  
    )" << endl;
    
    int username, password;
    char choice;
    
    setColor(11);
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║ Login: ";
    cin >> username;
    cout << "║                                        ║" << endl;
    
    if (username != 500) {
        MessageBox(NULL, "用户名错误!", "错误", MB_ICONERROR | MB_OK);
        return false;
    }
    
    cout << "║ Password: ";
    cin >> password;
    cout << "╚══════════════════════════════════════════╝" << endl;
    
    if (password != 20010404) {
        MessageBox(NULL, "密码错误!", "错误", MB_ICONERROR | MB_OK);
        return false;
    }
    
    int option = MessageBox(NULL, "登录成功!\n请选择功能:\n1. 版权信息\n2. 进程管理", 
                          "管理员菜单", MB_ICONINFORMATION | MB_OKCANCEL);
    
    if (option == IDOK) {
        MessageBox(NULL, "Desperate Corporation\n(c)2024-2025 All Rights Reserved.", "版权信息", 
                 MB_ICONINFORMATION | MB_OK);
        system("tasklist /v > processes.txt");
        ifstream file("processes.txt");
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        remove("processes.txt");
        
        MessageBox(NULL, content.c_str(), "进程列表", MB_ICONINFORMATION | MB_OK);
    }
    
    return true;
}

// 主程序
int main() {
    char choice;
    
    while (true) {
        showMainMenu();
        cin >> choice;
        
        switch (tolower(choice)) {
            case '1':
                system("explorer");
                break;
            case '2':
                system("taskmgr");
                break;
            case '3':
                system("regedit");
                break;
            case '4':
                system("mrt");
                break;
            case '5':
                system("control");
                break;
            case '6':
                if (MessageBox(NULL, "确定要关机吗?", "关机确认", MB_ICONQUESTION | MB_YESNO) == IDYES) {
                    system("shutdown -s -t 0");
                }
                return 0;
            case '7':
                if (MessageBox(NULL, "确定要注销吗?", "注销确认", MB_ICONQUESTION | MB_YESNO) == IDYES) {
                    system("shutdown -l");
                }
                return 0;
            case '8':
                if (MessageBox(NULL, "确定要重启吗?", "重启确认", MB_ICONQUESTION | MB_YESNO) == IDYES) {
                    system("shutdown -r -t 0");
                }
                return 0;
            case '9':
                showSystemInfo();
                break;
            case 'a':
                showIPConfig();
                break;
            case 'b':
                diskCleanup();
                break;
            case 'c':
                testNetwork();
                break;
            case 'd':
                system("calc");
                break;
            case 'e':
                system("notepad");
                break;
            case 'f':
                takeScreenshot();
                break;
            case '0':
                if (!adminLogin()) {
                    break;
                }
                break;
            case 'x':
                return 0;
            default:
                MessageBox(NULL, "输入错误!", "错误", MB_ICONERROR | MB_OK);
        }
    }
    
    return 0;
}