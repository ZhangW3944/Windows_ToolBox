// Copyright (c) 2024-2025 ZhangW3944 lnc.
// SPDX-License-Identifier: MIT

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <vector>
#include <map>
using namespace std;

// 语言枚举
enum Language { ENGLISH, CHINESE };
Language currentLang = CHINESE; // 默认中文

// 语言字符串映射
std::map<std::string, std::vector<std::string>> langStrings = {
    {"title", {"Windows Toolz 2.0", "Windows工具箱 2.0"}},
    {"power_management", {"Power Management", "电源管理"}},
    {"shutdown", {"Shutdown", "关机"}},
    {"restart", {"Restart", "重启"}},
    {"logout", {"Logout", "注销"}},
    {"lock", {"Lock", "锁定"}},
    {"sleep", {"Sleep", "睡眠"}},
    {"return_main", {"Return to Main Menu", "返回主菜单"}},
    {"select_prompt", {"Please enter your choice: ", "请选择功能: "}},
    {"invalid_input", {"Invalid input!", "无效输入!"}},
    {"error", {"Error", "错误"}},
    {"system_info", {"System Information", "系统信息"}},
    {"ip_config", {"IP Configuration", "IP配置"}},
    {"disk_cleanup", {"Disk Cleanup", "磁盘清理"}},
    {"network_test", {"Network Test", "网络测试"}},
    {"exit_program", {"Exit Program", "退出程序"}},
    {"language_switched", {"Language switched successfully", "语言切换成功"}},
    {"language_title", {"Language", "语言"}}
};

// 获取当前语言的字符串
string getString(const string& key) {
    return langStrings[key][currentLang];
}

// 切换语言
void switchLanguage() {
    currentLang = (currentLang == CHINESE) ? ENGLISH : CHINESE;
    MessageBox(NULL, 
        getString("language_switched").c_str(),
        getString("language_title").c_str(), 
        MB_ICONINFORMATION | MB_OK);
}

// 设置控制台颜色
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// 显示带边框的标题
void showTitle(const string& title) {
    setColor(11); // 亮青色
    cout << "════════════════════════════════════════════" << endl;
    cout << "║               " << title << "               ║" << endl;
    cout << "════════════════════════════════════════════" << endl;
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

// 磁盘清理
void diskCleanup() {
    if (MessageBox(NULL, "确定要执行磁盘清理吗?", "磁盘清理", MB_ICONQUESTION | MB_YESNO) == IDYES) {
        system("cleanmgr /sagerun:1");
        MessageBox(NULL, "磁盘清理已完成", "信息", MB_ICONINFORMATION | MB_OK);
    }
}

// 网络测试
void testNetwork() {
    system("ping 8.8.8.8 -n 4 > ping.txt");
    ifstream file("ping.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("ping.txt");
    
    MessageBox(NULL, content.c_str(), "网络连接测试", MB_ICONINFORMATION | MB_OK);
}

// 获取时间并截图
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

// 定时关机
void delayedShutdown() {
    int minutes;
    cout << "请输入定时关机时间(分钟): ";
    cin >> minutes;
    
    stringstream cmd;
    cmd << "shutdown -s -t " << minutes * 60;
    system(cmd.str().c_str());
    
    stringstream msg;
    msg << "系统将在 " << minutes << " 分钟后关闭";
    MessageBox(NULL, msg.str().c_str(), "定时关机", MB_ICONINFORMATION | MB_OK);
}

// 定时重启
void delayedRestart() {
    int minutes;
    cout << "请输入定时重启时间(分钟): ";
    cin >> minutes;
    
    stringstream cmd;
    cmd << "shutdown -r -t " << minutes * 60;
    system(cmd.str().c_str());
    
    stringstream msg;
    msg << "系统将在 " << minutes << " 分钟后重启";
    MessageBox(NULL, msg.str().c_str(), "定时重启", MB_ICONINFORMATION | MB_OK);
}

// 定时注销
void delayedLogout() {
    int minutes;
    cout << "请输入定时注销时间(分钟): ";
    cin >> minutes;
    
    stringstream cmd;
    cmd << "shutdown -l -t " << minutes * 60;
    system(cmd.str().c_str());
    
    stringstream msg;
    msg << "系统将在 " << minutes << " 分钟后注销";
    MessageBox(NULL, msg.str().c_str(), "定时注销", MB_ICONINFORMATION | MB_OK);
}

// 锁定工作站
void lockWorkstation() {
    system("rundll32.exe user32.dll,LockWorkStation");
    MessageBox(NULL, "工作站已锁定", "提示", MB_ICONINFORMATION | MB_OK);
}

// 进入睡眠模式
void sleepComputer() {
    if (MessageBox(NULL, "确定要让计算机进入睡眠模式吗?", "睡眠模式", MB_ICONQUESTION | MB_YESNO) == IDYES) {
        system("rundll32.exe powrprof.dll,SetSuspendState 0,1,0");
    }
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

// 显示系统工具子菜单
void showSystemToolsMenu() {
    system("cls");
    showTitle(getString("system_tools"));
    
    setColor(10); // 亮绿色
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║              " << getString("system_tools") << "              ║" << endl;
    cout << "╠══════════════════════════════════════════╣" << endl;
    
    setColor(11); // 亮青色
    cout << "║ 1. " << getString("file_explorer") << string(36 - getString("file_explorer").length(), ' ') << "║" << endl;
    cout << "║ 2. " << getString("task_manager") << string(36 - getString("task_manager").length(), ' ') << "║" << endl;
    cout << "║ 3. " << getString("registry_editor") << string(36 - getString("registry_editor").length(), ' ') << "║" << endl;
    cout << "║ 4. " << getString("control_panel") << string(36 - getString("control_panel").length(), ' ') << "║" << endl;
    cout << "║ 5. " << getString("command_prompt") << string(36 - getString("command_prompt").length(), ' ') << "║" << endl;
    cout << "║ 6. PowerShell" << string(36 - 10, ' ') << "║" << endl;
    cout << "║ 7. " << getString("device_manager") << string(36 - getString("device_manager").length(), ' ') << "║" << endl;
    cout << "║ 8. " << getString("disk_management") << string(36 - getString("disk_management").length(), ' ') << "║" << endl;
    cout << "║ 9. " << getString("services") << string(36 - getString("services").length(), ' ') << "║" << endl;
    cout << "║ 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "║" << endl;
    
    setColor(10); // 亮绿色
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;
    
    setColor(14); // 黄色
    cout << getString("select_prompt");
    setColor(7); // 恢复默认白色
}

// 处理系统工具选项
void handleSystemTools() {
    char choice;
    while (true) {
        showSystemToolsMenu();
        cin >> choice;
        
        switch (choice) {
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
                system("control");
                break;
            case '5':
                system("cmd");
                break;
            case '6':
                system("powershell");
                break;
            case '7':
                system("devmgmt.msc");
                break;
            case '8':
                system("diskmgmt.msc");
                break;
            case '9':
                system("services.msc");
                break;
            case '0':
                return;
            default:
                MessageBox(NULL, getString("invalid_input").c_str(), getString("error").c_str(), MB_ICONERROR | MB_OK);
        }
    }
}

// 显示实用工具子菜单
void showUtilitiesMenu() {
    system("cls");
    showTitle(getString("utilities"));
    
    setColor(10); // 亮绿色
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║              " << getString("utilities") << "              ║" << endl;
    cout << "╠══════════════════════════════════════════╣" << endl;
    
    setColor(11); // 亮青色
    cout << "║ 1. " << getString("calculator") << string(36 - getString("calculator").length(), ' ') << "║" << endl;
    cout << "║ 2. " << getString("notepad") << string(36 - getString("notepad").length(), ' ') << "║" << endl;
    cout << "║ 3. " << getString("paint") << string(36 - getString("paint").length(), ' ') << "║" << endl;
    cout << "║ 4. " << getString("character_map") << string(36 - getString("character_map").length(), ' ') << "║" << endl;
    cout << "║ 5. " << getString("snipping_tool") << string(36 - getString("snipping_tool").length(), ' ') << "║" << endl;
    cout << "║ 6. " << getString("sound_recorder") << string(36 - getString("sound_recorder").length(), ' ') << "║" << endl;
    cout << "║ 7. " << getString("math_input") << string(36 - getString("math_input").length(), ' ') << "║" << endl;
    cout << "║ 8. " << getString("remote_desktop") << string(36 - getString("remote_desktop").length(), ' ') << "║" << endl;
    cout << "║ 9. " << getString("magnifier") << string(36 - getString("magnifier").length(), ' ') << "║" << endl;
    cout << "║ 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "║" << endl;
    
    setColor(10); // 亮绿色
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;
    
    setColor(14); // 黄色
    cout << getString("select_prompt");
    setColor(7); // 恢复默认白色
}

// 处理实用工具选项
void handleUtilities() {
    char choice;
    while (true) {
        showUtilitiesMenu();
        cin >> choice;
        
        switch (choice) {
            case '1':
                system("calc");
                break;
            case '2':
                system("notepad");
                break;
            case '3':
                system("mspaint");
                break;
            case '4':
                system("charmap");
                break;
            case '5':
                system("snippingtool");
                break;
            case '6':
                system("soundrecorder");
                break;
            case '7':
                system("mip");
                break;
            case '8':
                system("mstsc");
                break;
            case '9':
                system("magnify");
                break;
            case '0':
                return;
            default:
                MessageBox(NULL, getString("invalid_input").c_str(), getString("error").c_str(), MB_ICONERROR | MB_OK);
        }
    }
}

// 显示系统维护子菜单
void showMaintenanceMenu() {
    system("cls");
    showTitle(getString("system_maintenance"));
    
    setColor(10); // 亮绿色
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║              " << getString("system_maintenance") << "              ║" << endl;
    cout << "╠══════════════════════════════════════════╣" << endl;
    
    setColor(11); // 亮青色
    cout << "║ 1. " << getString("malware_removal") << string(36 - getString("malware_removal").length(), ' ') << "║" << endl;
    cout << "║ 2. " << getString("disk_cleanup") << string(36 - getString("disk_cleanup").length(), ' ') << "║" << endl;
    cout << "║ 3. " << getString("disk_defrag") << string(36 - getString("disk_defrag").length(), ' ') << "║" << endl;
    cout << "║ 4. " << getString("system_file_check") << string(36 - getString("system_file_check").length(), ' ') << "║" << endl;
    cout << "║ 5. " << getString("check_disk") << string(36 - getString("check_disk").length(), ' ') << "║" << endl;
    cout << "║ 6. " << getString("system_restore") << string(36 - getString("system_restore").length(), ' ') << "║" << endl;
    cout << "║ 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "║" << endl;
    
    setColor(10); // 亮绿色
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;
    
    setColor(14); // 黄色
    cout << getString("select_prompt");
    setColor(7); // 恢复默认白色
}

// 处理系统维护选项
void handleMaintenance() {
    char choice;
    while (true) {
        showMaintenanceMenu();
        cin >> choice;
        
        switch (choice) {
            case '1':
                system("mrt");
                break;
            case '2':
                diskCleanup();
                break;
            case '3':
                system("dfrgui");
                break;
            case '4':
                system("sfc /scannow");
                break;
            case '5':
                system("chkdsk /f");
                break;
            case '6':
                system("rstrui");
                break;
            case '0':
                return;
            default:
                MessageBox(NULL, getString("invalid_input").c_str(), getString("error").c_str(), MB_ICONERROR | MB_OK);
        }
    }
}

// 显示网络工具子菜单
void showNetworkToolsMenu() {
    system("cls");
    showTitle(getString("network_tools"));
    
    setColor(10); // 亮绿色
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║              " << getString("network_tools") << "              ║" << endl;
    cout << "╠══════════════════════════════════════════╣" << endl;
    
    setColor(11); // 亮青色
    cout << "║ 1. " << getString("ip_config") << string(36 - getString("ip_config").length(), ' ') << "║" << endl;
    cout << "║ 2. " << getString("network_test") << string(36 - getString("network_test").length(), ' ') << "║" << endl;
    cout << "║ 3. " << getString("network_connections") << string(36 - getString("network_connections").length(), ' ') << "║" << endl;
    cout << "║ 4. " << getString("network_sharing") << string(36 - getString("network_sharing").length(), ' ') << "║" << endl;
    cout << "║ 5. " << getString("windows_firewall") << string(36 - getString("windows_firewall").length(), ' ') << "║" << endl;
    cout << "║ 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "║" << endl;
    
    setColor(10); // 亮绿色
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;
    
    setColor(14); // 黄色
    cout << getString("select_prompt");
    setColor(7); // 恢复默认白色
}

// 处理网络工具选项
void handleNetworkTools() {
    char choice;
    while (true) {
        showNetworkToolsMenu();
        cin >> choice;
        
        switch (choice) {
            case '1':
                showIPConfig();
                break;
            case '2':
                testNetwork();
                break;
            case '3':
                system("ncpa.cpl");
                break;
            case '4':
                system("control.exe /name Microsoft.NetworkAndSharingCenter");
                break;
            case '5':
                system("WF.msc");
                break;
            case '0':
                return;
            default:
                MessageBox(NULL, getString("invalid_input").c_str(), getString("error").c_str(), MB_ICONERROR | MB_OK);
        }
    }
}

// 显示电源管理子菜单
void showPowerMenu() {
    system("cls");
    showTitle(getString("power_management"));
    
    setColor(10); // 亮绿色
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║              " << getString("power_management") << "              ║" << endl;
    cout << "╠══════════════════════════════════════════╣" << endl;
    
    setColor(11); // 亮青色
    cout << "║ 1. " << getString("shutdown") << string(36 - getString("shutdown").length(), ' ') << "║" << endl;
    cout << "║ 2. " << getString("restart") << string(36 - getString("restart").length(), ' ') << "║" << endl;
    cout << "║ 3. " << getString("logout") << string(36 - getString("logout").length(), ' ') << "║" << endl;
    cout << "║ 4. " << getString("lock") << string(36 - getString("lock").length(), ' ') << "║" << endl;
    cout << "║ 5. " << getString("sleep") << string(36 - getString("sleep").length(), ' ') << "║" << endl;
    cout << "║ 6. " << (currentLang == CHINESE ? "定时关机" : "Delayed Shutdown") << string(36 - (currentLang == CHINESE ? 8 : 15), ' ') << "║" << endl;
    cout << "║ 7. " << (currentLang == CHINESE ? "定时重启" : "Delayed Restart") << string(36 - (currentLang == CHINESE ? 8 : 14), ' ') << "║" << endl;
    cout << "║ 8. " << (currentLang == CHINESE ? "定时注销" : "Delayed Logout") << string(36 - (currentLang == CHINESE ? 8 : 14), ' ') << "║" << endl;
    cout << "║ 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "║" << endl;
    
    setColor(10); // 亮绿色
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;
    
    setColor(14); // 黄色
    cout << getString("select_prompt");
    setColor(7); // 恢复默认白色
}

// 处理电源管理选项
void handlePowerOptions() {
    char choice;
    while (true) {
        showPowerMenu();
        cin >> choice;
        
        switch (choice) {
            case '1':
                if (MessageBox(NULL, "确定要关机吗?", "关机确认", MB_ICONQUESTION | MB_YESNO) == IDYES) {
                    system("shutdown -s -t 0");
                }
                return;
            case '2':
                if (MessageBox(NULL, "确定要重启吗?", "重启确认", MB_ICONQUESTION | MB_YESNO) == IDYES) {
                    system("shutdown -r -t 0");
                }
                return;
            case '3':
                if (MessageBox(NULL, "确定要注销吗?", "注销确认", MB_ICONQUESTION | MB_YESNO) == IDYES) {
                    system("shutdown -l");
                }
                return;
            case '4':
                lockWorkstation();
                break;
            case '5':
                sleepComputer();
                break;
            case '6':
                delayedShutdown();
                break;
            case '7':
                delayedRestart();
                break;
            case '8':
                delayedLogout();
                break;
            case '0':
                return;
            default:
                MessageBox(NULL, getString("invalid_input").c_str(), getString("error").c_str(), MB_ICONERROR | MB_OK);
        }
    }
}

// 管理员登录功能
bool adminLogin() {
    // 存储当前密码(初始为默认密码)
    static int currentPassword = 20010404;
    
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
    
    if (password != currentPassword) {
        MessageBox(NULL, "密码错误!", "错误", MB_ICONERROR | MB_OK);
        return false;
    }

    // 登录成功，进入管理员功能界面
    while (true) {
        system("cls");
        showTitle("管理员功能");
        
        setColor(10); // 亮绿色
        cout << "╔══════════════════════════════════════════╗" << endl;
        cout << "║              管理员功能               ║" << endl;
        cout << "╠══════════════════════════════════════════╣" << endl;
        
        setColor(11); // 亮青色
        cout << "║ 1. 进程列表                              ║" << endl;
        cout << "║ 2. 结束进程                              ║" << endl;
        cout << "║ 3. 查看系统日志                          ║" << endl;
        cout << "║ 4. 查看用户账户                          ║" << endl;
        cout << "║ 5. 版权信息                              ║" << endl;
        cout << "║ 6. 修改密码                              ║" << endl;
        cout << "║ 0. 返回主菜单                            ║" << endl;
        
        setColor(10); // 亮绿色
        cout << "╚══════════════════════════════════════════╝" << endl;
        cout << endl;
        
        setColor(14); // 黄色
        cout << "请选择功能: ";
        setColor(7); // 恢复默认白色
        
        char adminChoice;
        cin >> adminChoice;
        cin.ignore(); // 清除输入缓冲区
        
        switch (adminChoice) {
            case '1': {
                system("tasklist /v > processes.txt");
                ifstream file("processes.txt");
                string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
                file.close();
                remove("processes.txt");
                
                MessageBox(NULL, content.c_str(), "进程列表", MB_ICONINFORMATION | MB_OK);
                break;
            }
            case '2': {
                string pid;
                cout << "请输入要结束的进程PID: ";
                cin >> pid;
                
                string cmd = "taskkill /F /PID " + pid;
                int result = system(cmd.c_str());
                
                MessageBox(NULL, 
                    result == 0 ? "结束成功!" : "结束失败!",
                    result == 0 ? "成功" : "错误",
                    result == 0 ? MB_ICONINFORMATION : MB_ICONERROR | MB_OK);
                break;
            }
            case '3': {
                system("eventvwr.msc");
                break;
            }
            case '4': {
                system("lusrmgr.msc");
                break;
            }
            case '5': {
                string copyrightText = "Windows Toolz 2.7\n"
                                      "<c>2024-2025 ZhangW3944 Corporation.\n"
                                      "All rights reserved.\n"
                                      "This project is licensed under the MIT License.\n\n"
                                      "版本: 2.7";
                MessageBox(NULL, copyrightText.c_str(), "版权信息", MB_ICONINFORMATION | MB_OK);
                break;
            }
            case '6': {
                int newPass, confirmPass;
                cout << "请输入新密码: ";
                cin >> newPass;
                cout << "请确认新密码: ";
                cin >> confirmPass;
                
                if (newPass == confirmPass) {
                    currentPassword = newPass; // 更新密码
                    MessageBox(NULL, 
                        "密码修改成功!", 
                        "成功", 
                        MB_ICONINFORMATION | MB_OK);
                } else {
                    MessageBox(NULL, 
                        "两次输入的密码不匹配!", 
                        "错误", 
                        MB_ICONERROR | MB_OK);
                }
                break;
            }
            case '0':
                return true;
            default:
                MessageBox(NULL, 
                    getString("invalid_input").c_str(),
                    getString("error").c_str(), 
                    MB_ICONERROR | MB_OK);
        }
    }
}

// 显示主菜单
void showMainMenu() {
    system(currentLang == CHINESE ? "title Windows工具箱" : "title Windows Toolz");
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
    cout << "║             " << getString("title") << "             ║" << endl;
    cout << "╠══════════════════════════════════════════╣" << endl;
    
    setColor(11); // 亮青色
    cout << "║ 1. " << getString("system_tools") << string(36 - getString("system_tools").length(), ' ') << "║" << endl;
    cout << "║ 2. " << getString("utilities") << string(36 - getString("utilities").length(), ' ') << "║" << endl;
    cout << "║ 3. " << getString("system_maintenance") << string(36 - getString("system_maintenance").length(), ' ') << "║" << endl;
    cout << "║ 4. " << getString("network_tools") << string(36 - getString("network_tools").length(), ' ') << "║" << endl;
    cout << "║ 5. " << getString("power_management") << string(36 - getString("power_management").length(), ' ') << "║" << endl;
    cout << "║ 6. " << getString("system_info") << string(36 - getString("system_info").length(), ' ') << "║" << endl;
    cout << "║ 7. " << (currentLang == CHINESE ? "获取时间截图" : "Take Screenshot") << string(36 - (currentLang == CHINESE ? 12 : 15), ' ') << "║" << endl;
    cout << "║ 0. " << (currentLang == CHINESE ? "管理员功能" : "Admin Features") << string(36 - (currentLang == CHINESE ? 10 : 14), ' ') << "║" << endl;
    cout << "║ L. " << (currentLang == CHINESE ? "切换语言(中/英)" : "Switch Language(EN/CN)") << string(36 - (currentLang == CHINESE ? 13 : 20), ' ') << "║" << endl;
    cout << "║ x. " << getString("exit_program") << string(36 - getString("exit_program").length(), ' ') << "║" << endl;
    
    setColor(10); // 亮绿色
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;
    
    setColor(14); // 黄色
    cout << getString("select_prompt");
    setColor(7); // 恢复默认白色
}

// 主函数
int main() {
    // 补充语言映射表中缺失的字符串
    langStrings["system_tools"] = {"System Tools", "系统工具"};
    langStrings["utilities"] = {"Utilities", "实用工具"};
    langStrings["system_maintenance"] = {"System Maintenance", "系统维护"};
    langStrings["network_tools"] = {"Network Tools", "网络工具"};
    langStrings["file_explorer"] = {"File Explorer", "资源管理器"};
    langStrings["task_manager"] = {"Task Manager", "任务管理器"};
    langStrings["registry_editor"] = {"Registry Editor", "注册表编辑器"};
    langStrings["control_panel"] = {"Control Panel", "控制面板"};
    langStrings["command_prompt"] = {"Command Prompt", "命令提示符"};
    langStrings["device_manager"] = {"Device Manager", "设备管理器"};
    langStrings["disk_management"] = {"Disk Management", "磁盘管理"};
    langStrings["services"] = {"Services", "服务"};
    langStrings["calculator"] = {"Calculator", "计算器"};
    langStrings["notepad"] = {"Notepad", "记事本"};
    langStrings["paint"] = {"Paint", "画图"};
    langStrings["character_map"] = {"Character Map", "字符映射表"};
    langStrings["snipping_tool"] = {"Snipping Tool", "截图工具"};
    langStrings["sound_recorder"] = {"Sound Recorder", "录音机"};
    langStrings["math_input"] = {"Math Input", "数学输入板"};
    langStrings["remote_desktop"] = {"Remote Desktop", "远程桌面连接"};
    langStrings["magnifier"] = {"Magnifier", "放大镜"};
    langStrings["malware_removal"] = {"Malware Removal", "恶意软件删除工具"};
    langStrings["disk_defrag"] = {"Disk Defragmenter", "磁盘碎片整理"};
    langStrings["system_file_check"] = {"System File Check", "系统文件检查"};
    langStrings["check_disk"] = {"Check Disk", "磁盘检查"};
    langStrings["system_restore"] = {"System Restore", "系统还原"};
    langStrings["network_connections"] = {"Network Connections", "网络连接"};
    langStrings["network_sharing"] = {"Network Sharing", "网络和共享中心"};
    langStrings["windows_firewall"] = {"Windows Firewall", "防火墙设置"};

    char choice;
    
    while (true) {
        showMainMenu();
        cin >> choice;
        
        switch (tolower(choice)) {
            case '1':
                handleSystemTools();
                break;
            case '2':
                handleUtilities();
                break;
            case '3':
                handleMaintenance();
                break;
            case '4':
                handleNetworkTools();
                break;
            case '5':
                handlePowerOptions();
                break;
            case '6':
                showSystemInfo();
                break;
            case '7':
                takeScreenshot();
                break;
            case '0':
                if (!adminLogin()) {
                    break;
                }
                break;
            case 'l':
                switchLanguage();
                break;
            case 'x':
                return 0;
            default:
                MessageBox(NULL, getString("invalid_input").c_str(), getString("error").c_str(), MB_ICONERROR | MB_OK);
        }
    }
    
    return 0;
}