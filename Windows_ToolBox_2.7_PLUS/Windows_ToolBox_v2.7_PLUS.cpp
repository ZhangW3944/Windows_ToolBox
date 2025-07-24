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
#include <conio.h> // 用于 _getch() 函数
using namespace std;

// 语言枚举
enum Language { ENGLISH, CHINESE };
Language currentLang = CHINESE; // 默认中文

// Language strings map - fixed initialization
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
    {"language_title", {"Language", "语言"}},
    {"admin_login", {"Admin Login", "管理员登录"}},
    {"admin_features", {"Admin Features", "管理员功能"}},
    {"process_list", {"Process List", "进程列表"}},
    {"kill_process", {"Kill Process", "结束进程"}},
    {"view_logs", {"View System Logs", "查看系统日志"}},
    {"view_users", {"View User Accounts", "查看用户账户"}},
    {"change_pass", {"Change Password", "修改密码"}},
    {"invalid_username", {"Invalid username!", "用户名错误!"}},
    {"invalid_password", {"Invalid password!", "密码错误!"}},
    {"pass_changed", {"Password changed successfully!", "密码修改成功!"}},
    {"pass_mismatch", {"Passwords do not match!", "两次输入的密码不匹配!"}},
    {"process_killed", {"Process killed successfully!", "结束成功!"}},
    {"kill_failed", {"Failed to kill process!", "结束失败!"}},
    {"enter_pid", {"Enter PID to kill: ", "请输入要结束的进程PID: "}},
    {"enter_new_pass", {"Enter new password: ", "请输入新密码: "}},
    {"confirm_pass", {"Confirm new password: ", "请确认新密码: "}},
    {"success", {"Success", "成功"}},
    {"username_prompt", {"Username: ", "用户名: "}},
    {"password_prompt", {"Password: ", "密码: "}},
    {"ipconfig_all", {"Display All IP Config", "显示完整IP配置"}},
    {"ipconfig_release", {"Release IP Address", "释放IP地址"}},
    {"ipconfig_renew", {"Renew IP Address", "续订IP地址"}},
    {"ipconfig_flushdns", {"Flush DNS Cache", "清除DNS缓存"}},
    {"ipconfig_displaydns", {"Display DNS Cache", "显示DNS缓存"}},
    {"ip_released", {"IP address released successfully", "IP地址释放成功"}},
    {"ip_renewed", {"IP address renewed successfully", "IP地址续订成功"}},
    {"dns_flushed", {"DNS cache flushed successfully", "DNS缓存清除成功"}},
    {"help_title", {"Help", "帮助"}},
    {"help_content", {
        "Windows Toolz 2.0 Help\n\n"
        "This program provides various Windows system utilities:\n"
        "1. System Tools - Access system utilities like Task Manager, Registry Editor, etc.\n"
        "2. Utilities - Open common Windows utilities like Calculator, Notepad, etc.\n"
        "3. System Maintenance - Perform system maintenance tasks.\n"
        "4. Network Tools - Network configuration and testing tools.\n"
        "5. Power Management - System shutdown/restart options.\n"
        "6. System Info - View system information.\n"
        "7. Take Screenshot - Capture and save screen with timestamp.\n"
        "0. Admin Features - Advanced system tools (requires login).\n"
        "L. Switch Language - Toggle between English and Chinese.\n"
        "X. Exit - Quit the program.\n\n"
        "Press any key to return...",
        
        "Windows工具箱 2.0 帮助\n\n"
        "本程序提供多种Windows系统工具:\n"
        "1. 系统工具 - 访问任务管理器、注册表编辑器等系统工具\n"
        "2. 实用工具 - 打开计算器、记事本等常用Windows工具\n"
        "3. 系统维护 - 执行系统维护任务\n"
        "4. 网络工具 - 网络配置和测试工具\n"
        "5. 电源管理 - 系统关机/重启选项\n"
        "6. 系统信息 - 查看系统信息\n"
        "7. 获取时间截图 - 捕获并保存带时间戳的屏幕截图\n"
        "0. 管理员功能 - 高级系统工具(需要登录)\n"
        "L. 切换语言 - 在英文和中文之间切换\n"
        "X. 退出 - 退出程序\n\n"
        "按任意键返回..."
    }},
    {"troubleshooting", {"Troubleshooting", "疑难解答"}},
    {"search_system", {"Search System", "系统搜索"}},
    {"troubleshoot_network", {"Network Troubleshooting", "网络问题诊断"}},
    {"troubleshoot_hardware", {"Hardware Troubleshooting", "硬件问题诊断"}},
    {"troubleshoot_software", {"Software Troubleshooting", "软件问题诊断"}},
    {"troubleshoot_performance", {"Performance Issues", "性能问题诊断"}},
    {"search_files", {"Search Files", "文件搜索"}},
    {"search_settings", {"Search Settings", "设置搜索"}},
    {"search_programs", {"Search Programs", "程序搜索"}},
    {"enter_search_term", {"Enter search term: ", "输入搜索内容: "}},
    {"search_results", {"Search Results", "搜索结果"}},
    {"no_results_found", {"No results found", "未找到结果"}},
    {"category_network", {"Network", "网络"}},
    {"category_hardware", {"Hardware", "硬件"}},
    {"category_software", {"Software", "软件"}},
    {"category_performance", {"Performance", "性能"}},
    {"category_other", {"Other", "其他"}}
};

// Add function declarations before they are used
void showTitle(const string& title);
void setColor(int color);

// 获取当前语言的字符串
string getString(const string& key) {
    return langStrings[key][currentLang];
}
// 疑难解答功能
void troubleshootSystem() {
    system("cls");
    showTitle(getString("troubleshooting"));
    
    setColor(10);
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║              " << getString("troubleshooting") << "              ║" << endl;
    cout << "╠══════════════════════════════════════════╣" << endl;
    
    setColor(11);
    cout << "║ 1. " << getString("troubleshoot_network") << string(36 - getString("troubleshoot_network").length(), ' ') << "║" << endl;
    cout << "║ 2. " << getString("troubleshoot_hardware") << string(36 - getString("troubleshoot_hardware").length(), ' ') << "║" << endl;
    cout << "║ 3. " << getString("troubleshoot_software") << string(36 - getString("troubleshoot_software").length(), ' ') << "║" << endl;
    cout << "║ 4. " << getString("troubleshoot_performance") << string(36 - getString("troubleshoot_performance").length(), ' ') << "║" << endl;
    cout << "║ 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "║" << endl;
    
    setColor(10);
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;
    
    setColor(14);
    cout << getString("select_prompt");
    setColor(7);
    
    char choice;
    cin >> choice;
    
    switch (choice) {
        case '1':
            system("msdt.exe /id NetworkDiagnostics");
            break;
        case '2':
            system("msdt.exe /id DeviceDiagnostic");
            break;
        case '3':
            system("msdt.exe /id WindowsUpdateDiagnostic");
            break;
        case '4':
            system("msdt.exe /id PerformanceDiagnostic");
            break;
        case '0':
            return;
        default:
            MessageBox(NULL, getString("invalid_input").c_str(), getString("error").c_str(), MB_ICONERROR | MB_OK);
    }
}
// 系统搜索功能
void searchSystem() {
    system("cls");
    showTitle(getString("search_system"));
    
    setColor(10);
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║              " << getString("search_system") << "              ║" << endl;
    cout << "╠══════════════════════════════════════════╣" << endl;
    
    setColor(11);
    cout << "║ 1. " << getString("search_files") << string(36 - getString("search_files").length(), ' ') << "║" << endl;
    cout << "║ 2. " << getString("search_settings") << string(36 - getString("search_settings").length(), ' ') << "║" << endl;
    cout << "║ 3. " << getString("search_programs") << string(36 - getString("search_programs").length(), ' ') << "║" << endl;
    cout << "║ 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "║" << endl;
    
    setColor(10);
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;
    
    setColor(14);
    cout << getString("select_prompt");
    setColor(7);
    
    char choice;
    cin >> choice;
    cin.ignore();
    
    if (choice == '0') return;
    
    string searchTerm;
    cout << getString("enter_search_term");
    getline(cin, searchTerm);
    
    string cmd;
    string category;
    
    switch (choice) {
        case '1':
            cmd = "dir /s /b \"C:\\*" + searchTerm + "*\" > search_results.txt";
            category = getString("category_other");
            break;
        case '2':
            cmd = "start ms-settings:search?query=" + searchTerm;
            system(cmd.c_str());
            return;
        case '3':
            {
                // 使用Windows搜索API进行程序搜索
                SHELLEXECUTEINFO sei = { sizeof(sei) };
                sei.lpVerb = "open";
                sei.lpFile = "search:query=";
                sei.lpParameters = searchTerm.c_str();
                sei.nShow = SW_SHOW;
                
                if (!ShellExecuteEx(&sei)) {
                    MessageBox(NULL, getString("no_results_found").c_str(), getString("search_results").c_str(), MB_ICONINFORMATION | MB_OK);
                }
                return;
            }
        default:
            MessageBox(NULL, getString("invalid_input").c_str(), getString("error").c_str(), MB_ICONERROR | MB_OK);
            return;
    }
    
    system(cmd.c_str());
    
    ifstream file("search_results.txt");
    if (file.peek() == ifstream::traits_type::eof()) {
        MessageBox(NULL, getString("no_results_found").c_str(), getString("search_results").c_str(), MB_ICONINFORMATION | MB_OK);
    } else {
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        remove("search_results.txt");
        
        // 自动归类结果
        string categorizedResults = "[" + category + "]\n" + content;
        
        MessageBox(NULL, categorizedResults.c_str(), getString("search_results").c_str(), MB_ICONINFORMATION | MB_OK);
    }
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
    cout << "║ 2. " << getString("ipconfig_all") << string(36 - getString("ipconfig_all").length(), ' ') << "║" << endl;
    cout << "║ 3. " << getString("ipconfig_release") << string(36 - getString("ipconfig_release").length(), ' ') << "║" << endl;
    cout << "║ 4. " << getString("ipconfig_renew") << string(36 - getString("ipconfig_renew").length(), ' ') << "║" << endl;
    cout << "║ 5. " << getString("ipconfig_flushdns") << string(36 - getString("ipconfig_flushdns").length(), ' ') << "║" << endl;
    cout << "║ 6. " << getString("ipconfig_displaydns") << string(36 - getString("ipconfig_displaydns").length(), ' ') << "║" << endl;
    cout << "║ 7. " << getString("network_test") << string(36 - getString("network_test").length(), ' ') << "║" << endl;
    cout << "║ 8. " << getString("network_connections") << string(36 - getString("network_connections").length(), ' ') << "║" << endl;
    cout << "║ 9. " << getString("network_sharing") << string(36 - getString("network_sharing").length(), ' ') << "║" << endl;
    cout << "║ A. " << getString("windows_firewall") << string(36 - getString("windows_firewall").length(), ' ') << "║" << endl;
    cout << "║ 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "║" << endl;
    
    setColor(10); // 亮绿色
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;
    
    setColor(14); // 黄色
    cout << getString("select_prompt");
    setColor(7); // 恢复默认白色
}
// 显示完整IP配置
void showFullIPConfig() {
    system("ipconfig /all > ipconfig.txt");
    ifstream file("ipconfig.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("ipconfig.txt");
    
    MessageBox(NULL, content.c_str(), getString("ipconfig_all").c_str(), MB_ICONINFORMATION | MB_OK);
}

// 释放IP地址
void releaseIP() {
    system("ipconfig /release > ip_release.txt");
    ifstream file("ip_release.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("ip_release.txt");
    
    MessageBox(NULL, getString("ip_released").c_str(), getString("success").c_str(), MB_ICONINFORMATION | MB_OK);
}

// 续订IP地址
void renewIP() {
    system("ipconfig /renew > ip_renew.txt");
    ifstream file("ip_renew.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("ip_renew.txt");
    
    MessageBox(NULL, getString("ip_renewed").c_str(), getString("success").c_str(), MB_ICONINFORMATION | MB_OK);
}

// 清除DNS缓存
void flushDNS() {
    system("ipconfig /flushdns > dns_flush.txt");
    ifstream file("dns_flush.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("dns_flush.txt");
    
    MessageBox(NULL, getString("dns_flushed").c_str(), getString("success").c_str(), MB_ICONINFORMATION | MB_OK);
}

// 显示DNS缓存
void displayDNSCache() {
    system("ipconfig /displaydns > dns_cache.txt");
    ifstream file("dns_cache.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("dns_cache.txt");
    
    MessageBox(NULL, content.c_str(), getString("ipconfig_displaydns").c_str(), MB_ICONINFORMATION | MB_OK);
}

// 处理网络工具选项
void handleNetworkTools() {
    char choice;
    while (true) {
        showNetworkToolsMenu();
        cin >> choice;
        
        switch (tolower(choice)) {
            case '1':
                showIPConfig();
                break;
            case '2':
                showFullIPConfig();
                break;
            case '3':
                releaseIP();
                break;
            case '4':
                renewIP();
                break;
            case '5':
                flushDNS();
                break;
            case '6':
                displayDNSCache();
                break;
            case '7':
                testNetwork();
                break;
            case '8':
                system("ncpa.cpl");
                break;
            case '9':
                system("control.exe /name Microsoft.NetworkAndSharingCenter");
                break;
            case 'a':
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
// 显示帮助信息
void showHelp() {
    system("cls");
    showTitle(getString("help_title"));
    
    // 创建更详细的帮助内容
    vector<string> helpSections;
    
    // 标题部分
    helpSections.push_back("══════════ " + getString("title") + " ══════════");
    helpSections.push_back("");
    helpSections.push_back(getString("title") + " " + (currentLang == CHINESE ? "是一个多功能Windows系统工具箱" : "is a multi-functional Windows system toolbox"));
    helpSections.push_back(currentLang == CHINESE ? "版本: 2.7.1" : "Version: 2.7.1");
    helpSections.push_back(currentLang == CHINESE ? "作者: ZhangW3944" : "Author: ZhangW3944");
    helpSections.push_back(currentLang == CHINESE ? "许可证: MIT" : "License: MIT");
    helpSections.push_back("");
    
    // 主要功能部分
    helpSections.push_back("════════ " + string(currentLang == CHINESE ? "主要功能" : "Main Features") + " ════════");
    helpSections.push_back("");
    helpSections.push_back("1. " + getString("system_tools") + " - " + 
        (currentLang == CHINESE ? "访问系统实用工具" : "Access system utilities"));
    helpSections.push_back("2. " + getString("utilities") + " - " + 
        (currentLang == CHINESE ? "打开常用Windows工具" : "Open common Windows tools"));
    helpSections.push_back("3. " + getString("system_maintenance") + " - " + 
        (currentLang == CHINESE ? "执行系统维护任务" : "Perform system maintenance"));
    helpSections.push_back("4. " + getString("network_tools") + " - " + 
        (currentLang == CHINESE ? "网络配置和测试" : "Network configuration and testing"));
    helpSections.push_back("5. " + getString("power_management") + " - " + 
        (currentLang == CHINESE ? "系统电源管理选项" : "System power management options"));
    helpSections.push_back("6. " + getString("system_info") + " - " + 
        (currentLang == CHINESE ? "查看详细系统信息" : "View detailed system information"));
    helpSections.push_back("7. " + string(currentLang == CHINESE ? "截图工具" : "Screenshot Tool") + " - " + 
        (currentLang == CHINESE ? "带时间戳的屏幕截图" : "Timestamped screenshots"));
    helpSections.push_back("8. " + getString("troubleshooting") + " - " + 
        (currentLang == CHINESE ? "系统问题诊断工具" : "System troubleshooting tools"));
    helpSections.push_back("9. " + getString("search_system") + " - " + 
        (currentLang == CHINESE ? "系统内容搜索功能" : "System content search feature"));
    helpSections.push_back("0. " + getString("admin_features") + " - " + 
        (currentLang == CHINESE ? "高级系统管理功能" : "Advanced system administration"));
    helpSections.push_back("");
    
    // 其他功能部分
    helpSections.push_back("════════ " + string(currentLang == CHINESE ? "其他功能" : "Other Features") + " ════════");
    helpSections.push_back("");
    helpSections.push_back("L. " + string(currentLang == CHINESE ? "切换语言" : "Switch Language") + " - " + 
        (currentLang == CHINESE ? "中英文切换" : "Toggle between English/Chinese"));
    helpSections.push_back("H. " + string(currentLang == CHINESE ? "帮助信息" : "Help") + " - " + 
        (currentLang == CHINESE ? "显示此帮助" : "Show this help"));
    helpSections.push_back("X. " + getString("exit_program") + " - " + 
        (currentLang == CHINESE ? "退出程序" : "Exit the program"));
    helpSections.push_back("");
    
    // 使用提示部分
    helpSections.push_back("════════ " + string(currentLang == CHINESE ? "使用提示" : "Usage Tips") + " ════════");
    helpSections.push_back("");
    helpSections.push_back(currentLang == CHINESE ? 
        "- 使用数字键选择菜单选项" : 
        "- Use number keys to select menu options");
    helpSections.push_back(currentLang == CHINESE ? 
        "- 管理员功能需要密码验证" : 
        "- Admin features require password authentication");
    helpSections.push_back(currentLang == CHINESE ? 
        "- 电源管理操作不可撤销，请谨慎使用" : 
        "- Power management actions cannot be undone, use with caution");
    helpSections.push_back(currentLang == CHINESE ? 
        "- 系统维护功能可能需要管理员权限" : 
        "- System maintenance may require admin privileges");

    // 计算最长行长度用于边框调整
    size_t maxLength = 0;
    for (const auto& line : helpSections) {
        if (line.length() > maxLength) {
            maxLength = line.length();
        }
    }
    maxLength += 4; // 添加边框和填充

    // 显示帮助内容
    setColor(11); // 亮青色
    
    // 顶部边框
    cout << "╔" << string(maxLength - 2, '═') << "╗" << endl;
    
    // 帮助内容
    for (const auto& line : helpSections) {
        if (line.empty()) {
            cout << "║" << string(maxLength - 2, ' ') << "║" << endl;
        } else if (line.find("═══") != string::npos) {
            cout << "╠" << string(maxLength - 2, '═') << "╣" << endl;
        } else {
            size_t padding = maxLength - line.length() - 2;
            size_t leftPad = padding / 2;
            size_t rightPad = padding - leftPad;
            
            cout << "║" << string(leftPad, ' ') << line << string(rightPad, ' ') << "║" << endl;
        }
    }
    
    // 底部边框
    cout << "╚" << string(maxLength - 2, '═') << "╝" << endl;
    
    // 添加键盘提示
    setColor(14); // 黄色
    cout << endl << (currentLang == CHINESE ? "按任意键返回主菜单..." : "Press any key to return to main menu...");
    setColor(7); // 恢复默认白色
    
    _getch(); // 等待用户按键
}
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
    static string currentPassword = "123";
    
    system("cls");
    showTitle(currentLang == CHINESE ? "管理员登录" : "Admin Login");
    
    setColor(14);
    cout << R"(
   _____                           .__          
  /     \   ____   ____   ____    |__| _____   
 /  \ /  \ /  _ \ /    \ /  _ \   |  |/     \  
/    Y    (  <_> )   |  (  <_> )  |  |  Y Y  \ 
\____|__  /\____/|___|  /\____/\__|  |__|_|  / 
        \/            \/      \______|     \/  
)" << endl;
    
    string username, password;
    
    setColor(11);
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║ " << (currentLang == CHINESE ? "用户名: " : "Username: ");
    cin >> username;
    
    if (username != "Admin") {
        MessageBox(NULL, 
            currentLang == CHINESE ? "用户名错误!" : "Invalid username!",
            currentLang == CHINESE ? "错误" : "Error", 
            MB_ICONERROR | MB_OK);
        return false;
    }
    
    cout << "║ " << (currentLang == CHINESE ? "密码: " : "Password: ");
    
    // 隐藏密码输入
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
    
    cin >> password;
    SetConsoleMode(hStdin, mode); // 恢复回显
    
    cout << "╚══════════════════════════════════════════╝" << endl;
    
    if (password != currentPassword) {
        MessageBox(NULL, 
            currentLang == CHINESE ? "密码错误!" : "Invalid password!",
            currentLang == CHINESE ? "错误" : "Error", 
            MB_ICONERROR | MB_OK);
        return false;
    }

    // 登录成功，进入管理员功能界面
    while (true) {
        system("cls");
        showTitle(currentLang == CHINESE ? "管理员功能" : "Admin Features");
        
        setColor(10);
        cout << "╔══════════════════════════════════════════╗" << endl;
        cout << "║ " << (currentLang == CHINESE ? "            管理员功能            " : "            Admin Features            ") << "║" << endl;
        cout << "╠══════════════════════════════════════════╣" << endl;
        
        setColor(11);
        cout << "║ 1. " << (currentLang == CHINESE ? "进程列表" : "Process List") << string(36 - (currentLang == CHINESE ? 8 : 12), ' ') << "║" << endl;
        cout << "║ 2. " << (currentLang == CHINESE ? "结束进程" : "Kill Process") << string(36 - (currentLang == CHINESE ? 8 : 11), ' ') << "║" << endl;
        cout << "║ 3. " << (currentLang == CHINESE ? "查看系统日志" : "View System Logs") << string(36 - (currentLang == CHINESE ? 10 : 15), ' ') << "║" << endl;
        cout << "║ 4. " << (currentLang == CHINESE ? "查看用户账户" : "View User Accounts") << string(36 - (currentLang == CHINESE ? 10 : 17), ' ') << "║" << endl;
        cout << "║ 5. " << (currentLang == CHINESE ? "版权信息" : "Copyright Info") << string(36 - (currentLang == CHINESE ? 8 : 14), ' ') << "║" << endl;
        cout << "║ 6. " << (currentLang == CHINESE ? "修改密码" : "Change Password") << string(36 - (currentLang == CHINESE ? 8 : 15), ' ') << "║" << endl;
        cout << "║ 0. " << (currentLang == CHINESE ? "返回主菜单" : "Return to Main Menu") << string(36 - (currentLang == CHINESE ? 10 : 19), ' ') << "║" << endl;
        
        setColor(10);
        cout << "╚══════════════════════════════════════════╝" << endl;
        cout << endl;
        
        setColor(14);
        cout << (currentLang == CHINESE ? "请选择功能: " : "Please select: ");
        setColor(7);
        
        char adminChoice;
        cin >> adminChoice;
        cin.ignore();
        
        switch (adminChoice) {
            case '1': {
                system("tasklist /v > processes.txt");
                ifstream file("processes.txt");
                string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
                file.close();
                remove("processes.txt");
                
                MessageBox(NULL, content.c_str(), 
                    currentLang == CHINESE ? "进程列表" : "Process List", 
                    MB_ICONINFORMATION | MB_OK);
                break;
            }
            case '2': {
                string pid;
                cout << (currentLang == CHINESE ? "请输入要结束的进程PID: " : "Enter PID to kill: ");
                cin >> pid;
                
                string cmd = "taskkill /F /PID " + pid;
                int result = system(cmd.c_str());
                
                MessageBox(NULL, 
                    result == 0 ? 
                        (currentLang == CHINESE ? "结束成功!" : "Process killed successfully!") : 
                        (currentLang == CHINESE ? "结束失败!" : "Failed to kill process!"),
                    result == 0 ? 
                        (currentLang == CHINESE ? "成功" : "Success") : 
                        (currentLang == CHINESE ? "错误" : "Error"),
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
                         "(c) 2024-2025 ZhangW3944 Corporation.\n"
                         "All rights reserved.\n"
                         "This project is licensed under the MIT License.\n\n" +
                         string(currentLang == CHINESE ? "版本: 2.7" : "Version: 2.7");
    MessageBox(NULL, copyrightText.c_str(), 
        currentLang == CHINESE ? "版权信息" : "Copyright Info", 
        MB_ICONINFORMATION | MB_OK);
    break;
			}
            case '6': {
                string newPass, confirmPass;
                cout << (currentLang == CHINESE ? "请输入新密码: " : "Enter new password: ")<<endl;
                
                HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
                DWORD mode = 0;
                GetConsoleMode(hStdin, &mode);
                SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
                
                cin >> newPass;
                SetConsoleMode(hStdin, mode);
                
                cout << (currentLang == CHINESE ? "请确认新密码: " : "Confirm new password: ");
                SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
                cin >> confirmPass;
                SetConsoleMode(hStdin, mode);
                
                if (newPass == confirmPass) {
                    currentPassword = newPass;
                    MessageBox(NULL, 
                        currentLang == CHINESE ? "密码修改成功!" : "Password changed successfully!", 
                        currentLang == CHINESE ? "成功" : "Success", 
                        MB_ICONINFORMATION | MB_OK);
                } else {
                    MessageBox(NULL, 
                        currentLang == CHINESE ? "两次输入的密码不匹配!" : "Passwords do not match!", 
                        currentLang == CHINESE ? "错误" : "Error", 
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
    // 在 showMainMenu() 函数中，在帮助选项前添加以下内容
	cout << "║ 8. " << getString("troubleshooting") << string(36 - getString("troubleshooting").length(), ' ') << "║" << endl;
	cout << "║ 9. " << getString("search_system") << string(36 - getString("search_system").length(), ' ') << "║" << endl;
    cout << "║ 0. " << (currentLang == CHINESE ? "管理员功能" : "Admin Features") << string(36 - (currentLang == CHINESE ? 10 : 14), ' ') << "║" << endl;
    cout << "║ L. " << (currentLang == CHINESE ? "切换语言(中/英)" : "Switch Language(EN/CN)") << string(36 - (currentLang == CHINESE ? 13 : 20), ' ') << "║" << endl;
    // 在菜单选项列表中添加以下内容（放在退出选项之前）
	cout << "║ H. " << (currentLang == CHINESE ? "帮助" : "Help") << string(36 - (currentLang == CHINESE ? 4 : 6), ' ') << "║" << endl;
    cout << "║ x. " << getString("exit_program") << string(36 - getString("exit_program").length(), ' ') << "║" << endl;
    
    setColor(10); // 亮绿色
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;
    
    setColor(14); // 黄色
    cout << getString("select_prompt");
    setColor(7); // 恢复默认白色
}
// 增强版搜索功能，包含自动归类
void enhancedSearchSystem() {
    system("cls");
    showTitle(getString("search_system"));
    
    cout << getString("enter_search_term");
    string searchTerm;
    getline(cin, searchTerm);
    
    // 根据搜索内容自动确定类别
    string category;
    if (searchTerm.find("network") != string::npos || 
        searchTerm.find("wifi") != string::npos || 
        searchTerm.find("ethernet") != string::npos) {
        category = getString("category_network");
    } else if (searchTerm.find("driver") != string::npos || 
               searchTerm.find("device") != string::npos || 
               searchTerm.find("hardware") != string::npos) {
        category = getString("category_hardware");
    } else if (searchTerm.find("software") != string::npos || 
               searchTerm.find("program") != string::npos || 
               searchTerm.find("app") != string::npos) {
        category = getString("category_software");
    } else if (searchTerm.find("slow") != string::npos || 
               searchTerm.find("performance") != string::npos || 
               searchTerm.find("speed") != string::npos) {
        category = getString("category_performance");
    } else {
        category = getString("category_other");
    }
    
    // 执行搜索
    string cmd = "where /r C:\\ *" + searchTerm + "* > search_results.txt 2>&1";
    system(cmd.c_str());
    
    // 读取并显示结果
    ifstream file("search_results.txt");
    if (file.peek() == ifstream::traits_type::eof()) {
        MessageBox(NULL, getString("no_results_found").c_str(), getString("search_results").c_str(), MB_ICONINFORMATION | MB_OK);
    } else {
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        remove("search_results.txt");
        
        // 添加类别信息
        string categorizedResults = "[" + category + " " + getString("search_results") + "]\n\n" + content;
        
        MessageBox(NULL, categorizedResults.c_str(), getString("search_results").c_str(), MB_ICONINFORMATION | MB_OK);
    }
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
            // 在 main() 函数的 switch 语句中添加
			case '8':
    			troubleshootSystem();
   				break;
			case '9':
    			searchSystem();
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
            case 'h':
    			showHelp();
    			break;
            default:
                MessageBox(NULL, getString("invalid_input").c_str(), getString("error").c_str(), MB_ICONERROR | MB_OK);
        }
    }
    
    return 0;
}