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
#include <conio.h> // ���� _getch() ����
using namespace std;

// ����ö��
enum Language { ENGLISH, CHINESE };
Language currentLang = CHINESE; // Ĭ������

// Language strings map - fixed initialization
std::map<std::string, std::vector<std::string>> langStrings = {
    {"title", {"Windows Toolz 2.0", "Windows������ 2.0"}},
    {"power_management", {"Power Management", "��Դ����"}},
    {"shutdown", {"Shutdown", "�ػ�"}},
    {"restart", {"Restart", "����"}},
    {"logout", {"Logout", "ע��"}},
    {"lock", {"Lock", "����"}},
    {"sleep", {"Sleep", "˯��"}},
    {"return_main", {"Return to Main Menu", "�������˵�"}},
    {"select_prompt", {"Please enter your choice: ", "��ѡ����: "}},
    {"invalid_input", {"Invalid input!", "��Ч����!"}},
    {"error", {"Error", "����"}},
    {"system_info", {"System Information", "ϵͳ��Ϣ"}},
    {"ip_config", {"IP Configuration", "IP����"}},
    {"disk_cleanup", {"Disk Cleanup", "��������"}},
    {"network_test", {"Network Test", "�������"}},
    {"exit_program", {"Exit Program", "�˳�����"}},
    {"language_switched", {"Language switched successfully", "�����л��ɹ�"}},
    {"language_title", {"Language", "����"}},
    {"admin_login", {"Admin Login", "����Ա��¼"}},
    {"admin_features", {"Admin Features", "����Ա����"}},
    {"process_list", {"Process List", "�����б�"}},
    {"kill_process", {"Kill Process", "��������"}},
    {"view_logs", {"View System Logs", "�鿴ϵͳ��־"}},
    {"view_users", {"View User Accounts", "�鿴�û��˻�"}},
    {"change_pass", {"Change Password", "�޸�����"}},
    {"invalid_username", {"Invalid username!", "�û�������!"}},
    {"invalid_password", {"Invalid password!", "�������!"}},
    {"pass_changed", {"Password changed successfully!", "�����޸ĳɹ�!"}},
    {"pass_mismatch", {"Passwords do not match!", "������������벻ƥ��!"}},
    {"process_killed", {"Process killed successfully!", "�����ɹ�!"}},
    {"kill_failed", {"Failed to kill process!", "����ʧ��!"}},
    {"enter_pid", {"Enter PID to kill: ", "������Ҫ�����Ľ���PID: "}},
    {"enter_new_pass", {"Enter new password: ", "������������: "}},
    {"confirm_pass", {"Confirm new password: ", "��ȷ��������: "}},
    {"success", {"Success", "�ɹ�"}},
    {"username_prompt", {"Username: ", "�û���: "}},
    {"password_prompt", {"Password: ", "����: "}},
    {"ipconfig_all", {"Display All IP Config", "��ʾ����IP����"}},
    {"ipconfig_release", {"Release IP Address", "�ͷ�IP��ַ"}},
    {"ipconfig_renew", {"Renew IP Address", "����IP��ַ"}},
    {"ipconfig_flushdns", {"Flush DNS Cache", "���DNS����"}},
    {"ipconfig_displaydns", {"Display DNS Cache", "��ʾDNS����"}},
    {"ip_released", {"IP address released successfully", "IP��ַ�ͷųɹ�"}},
    {"ip_renewed", {"IP address renewed successfully", "IP��ַ�����ɹ�"}},
    {"dns_flushed", {"DNS cache flushed successfully", "DNS��������ɹ�"}},
    {"help_title", {"Help", "����"}},
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
        
        "Windows������ 2.0 ����\n\n"
        "�������ṩ����Windowsϵͳ����:\n"
        "1. ϵͳ���� - ���������������ע���༭����ϵͳ����\n"
        "2. ʵ�ù��� - �򿪼����������±��ȳ���Windows����\n"
        "3. ϵͳά�� - ִ��ϵͳά������\n"
        "4. ���繤�� - �������úͲ��Թ���\n"
        "5. ��Դ���� - ϵͳ�ػ�/����ѡ��\n"
        "6. ϵͳ��Ϣ - �鿴ϵͳ��Ϣ\n"
        "7. ��ȡʱ���ͼ - ���񲢱����ʱ�������Ļ��ͼ\n"
        "0. ����Ա���� - �߼�ϵͳ����(��Ҫ��¼)\n"
        "L. �л����� - ��Ӣ�ĺ�����֮���л�\n"
        "X. �˳� - �˳�����\n\n"
        "�����������..."
    }},
    {"troubleshooting", {"Troubleshooting", "���ѽ��"}},
    {"search_system", {"Search System", "ϵͳ����"}},
    {"troubleshoot_network", {"Network Troubleshooting", "�����������"}},
    {"troubleshoot_hardware", {"Hardware Troubleshooting", "Ӳ���������"}},
    {"troubleshoot_software", {"Software Troubleshooting", "����������"}},
    {"troubleshoot_performance", {"Performance Issues", "�����������"}},
    {"search_files", {"Search Files", "�ļ�����"}},
    {"search_settings", {"Search Settings", "��������"}},
    {"search_programs", {"Search Programs", "��������"}},
    {"enter_search_term", {"Enter search term: ", "������������: "}},
    {"search_results", {"Search Results", "�������"}},
    {"no_results_found", {"No results found", "δ�ҵ����"}},
    {"category_network", {"Network", "����"}},
    {"category_hardware", {"Hardware", "Ӳ��"}},
    {"category_software", {"Software", "���"}},
    {"category_performance", {"Performance", "����"}},
    {"category_other", {"Other", "����"}}
};

// Add function declarations before they are used
void showTitle(const string& title);
void setColor(int color);

// ��ȡ��ǰ���Ե��ַ���
string getString(const string& key) {
    return langStrings[key][currentLang];
}
// ���ѽ����
void troubleshootSystem() {
    system("cls");
    showTitle(getString("troubleshooting"));
    
    setColor(10);
    cout << "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
    cout << "�U              " << getString("troubleshooting") << "              �U" << endl;
    cout << "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g" << endl;
    
    setColor(11);
    cout << "�U 1. " << getString("troubleshoot_network") << string(36 - getString("troubleshoot_network").length(), ' ') << "�U" << endl;
    cout << "�U 2. " << getString("troubleshoot_hardware") << string(36 - getString("troubleshoot_hardware").length(), ' ') << "�U" << endl;
    cout << "�U 3. " << getString("troubleshoot_software") << string(36 - getString("troubleshoot_software").length(), ' ') << "�U" << endl;
    cout << "�U 4. " << getString("troubleshoot_performance") << string(36 - getString("troubleshoot_performance").length(), ' ') << "�U" << endl;
    cout << "�U 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "�U" << endl;
    
    setColor(10);
    cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
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
// ϵͳ��������
void searchSystem() {
    system("cls");
    showTitle(getString("search_system"));
    
    setColor(10);
    cout << "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
    cout << "�U              " << getString("search_system") << "              �U" << endl;
    cout << "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g" << endl;
    
    setColor(11);
    cout << "�U 1. " << getString("search_files") << string(36 - getString("search_files").length(), ' ') << "�U" << endl;
    cout << "�U 2. " << getString("search_settings") << string(36 - getString("search_settings").length(), ' ') << "�U" << endl;
    cout << "�U 3. " << getString("search_programs") << string(36 - getString("search_programs").length(), ' ') << "�U" << endl;
    cout << "�U 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "�U" << endl;
    
    setColor(10);
    cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
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
                // ʹ��Windows����API���г�������
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
        
        // �Զ�������
        string categorizedResults = "[" + category + "]\n" + content;
        
        MessageBox(NULL, categorizedResults.c_str(), getString("search_results").c_str(), MB_ICONINFORMATION | MB_OK);
    }
}
// �л�����
void switchLanguage() {
    currentLang = (currentLang == CHINESE) ? ENGLISH : CHINESE;
    MessageBox(NULL, 
        getString("language_switched").c_str(),
        getString("language_title").c_str(), 
        MB_ICONINFORMATION | MB_OK);
}

// ���ÿ���̨��ɫ
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// ��ʾ���߿�ı���
void showTitle(const string& title) {
    setColor(11); // ����ɫ
    cout << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
    cout << "�U               " << title << "               �U" << endl;
    cout << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
    setColor(7); // �ָ�Ĭ�ϰ�ɫ
}

// ��ʾϵͳ��Ϣ
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
    ss << "�T�T�T�T�T�T�T�T�T�T�T�T ϵͳ��Ϣ �T�T�T�T�T�T�T�T�T�T�T�T\n\n";
    ss << "�� ����ϵͳ: Windows " << osvi.dwMajorVersion << "." << osvi.dwMinorVersion << "\n";
    ss << "�� �������ܹ�: ";
    switch(si.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64: ss << "x64"; break;
        case PROCESSOR_ARCHITECTURE_ARM: ss << "ARM"; break;
        case PROCESSOR_ARCHITECTURE_IA64: ss << "Itanium"; break;
        case PROCESSOR_ARCHITECTURE_INTEL: ss << "x86"; break;
        default: ss << "δ֪"; break;
    }
    ss << "\n�� ����������: " << si.dwNumberOfProcessors << "\n";
    ss << "�� �ڴ�����: " << memInfo.ullTotalPhys/1024/1024 << " MB\n";
    ss << "�� �����ڴ�: " << memInfo.ullAvailPhys/1024/1024 << " MB\n\n";
    ss << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T";

    MessageBox(NULL, ss.str().c_str(), "ϵͳ��Ϣ", MB_ICONINFORMATION | MB_OK);
}

// ��������
void diskCleanup() {
    if (MessageBox(NULL, "ȷ��Ҫִ�д���������?", "��������", MB_ICONQUESTION | MB_YESNO) == IDYES) {
        system("cleanmgr /sagerun:1");
        MessageBox(NULL, "�������������", "��Ϣ", MB_ICONINFORMATION | MB_OK);
    }
}

// �������
void testNetwork() {
    system("ping 8.8.8.8 -n 4 > ping.txt");
    ifstream file("ping.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("ping.txt");
    
    MessageBox(NULL, content.c_str(), "�������Ӳ���", MB_ICONINFORMATION | MB_OK);
}

// ��ȡʱ�䲢��ͼ
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
    
    MessageBox(NULL, ("��ͼ�ѱ���Ϊ: " + ss.str()).c_str(), "��ͼ���", MB_ICONINFORMATION | MB_OK);
}

// ��ʱ�ػ�
void delayedShutdown() {
    int minutes;
    cout << "�����붨ʱ�ػ�ʱ��(����): ";
    cin >> minutes;
    
    stringstream cmd;
    cmd << "shutdown -s -t " << minutes * 60;
    system(cmd.str().c_str());
    
    stringstream msg;
    msg << "ϵͳ���� " << minutes << " ���Ӻ�ر�";
    MessageBox(NULL, msg.str().c_str(), "��ʱ�ػ�", MB_ICONINFORMATION | MB_OK);
}

// ��ʱ����
void delayedRestart() {
    int minutes;
    cout << "�����붨ʱ����ʱ��(����): ";
    cin >> minutes;
    
    stringstream cmd;
    cmd << "shutdown -r -t " << minutes * 60;
    system(cmd.str().c_str());
    
    stringstream msg;
    msg << "ϵͳ���� " << minutes << " ���Ӻ�����";
    MessageBox(NULL, msg.str().c_str(), "��ʱ����", MB_ICONINFORMATION | MB_OK);
}

// ��ʱע��
void delayedLogout() {
    int minutes;
    cout << "�����붨ʱע��ʱ��(����): ";
    cin >> minutes;
    
    stringstream cmd;
    cmd << "shutdown -l -t " << minutes * 60;
    system(cmd.str().c_str());
    
    stringstream msg;
    msg << "ϵͳ���� " << minutes << " ���Ӻ�ע��";
    MessageBox(NULL, msg.str().c_str(), "��ʱע��", MB_ICONINFORMATION | MB_OK);
}

// ��������վ
void lockWorkstation() {
    system("rundll32.exe user32.dll,LockWorkStation");
    MessageBox(NULL, "����վ������", "��ʾ", MB_ICONINFORMATION | MB_OK);
}

// ����˯��ģʽ
void sleepComputer() {
    if (MessageBox(NULL, "ȷ��Ҫ�ü��������˯��ģʽ��?", "˯��ģʽ", MB_ICONQUESTION | MB_YESNO) == IDYES) {
        system("rundll32.exe powrprof.dll,SetSuspendState 0,1,0");
    }
}

// ��ʾIP����
void showIPConfig() {
    system("ipconfig > ipconfig.txt");
    ifstream file("ipconfig.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("ipconfig.txt");
    
    MessageBox(NULL, content.c_str(), "IP������Ϣ", MB_ICONINFORMATION | MB_OK);
}

// ��ʾϵͳ�����Ӳ˵�
void showSystemToolsMenu() {
    system("cls");
    showTitle(getString("system_tools"));
    
    setColor(10); // ����ɫ
    cout << "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
    cout << "�U              " << getString("system_tools") << "              �U" << endl;
    cout << "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g" << endl;
    
    setColor(11); // ����ɫ
    cout << "�U 1. " << getString("file_explorer") << string(36 - getString("file_explorer").length(), ' ') << "�U" << endl;
    cout << "�U 2. " << getString("task_manager") << string(36 - getString("task_manager").length(), ' ') << "�U" << endl;
    cout << "�U 3. " << getString("registry_editor") << string(36 - getString("registry_editor").length(), ' ') << "�U" << endl;
    cout << "�U 4. " << getString("control_panel") << string(36 - getString("control_panel").length(), ' ') << "�U" << endl;
    cout << "�U 5. " << getString("command_prompt") << string(36 - getString("command_prompt").length(), ' ') << "�U" << endl;
    cout << "�U 6. PowerShell" << string(36 - 10, ' ') << "�U" << endl;
    cout << "�U 7. " << getString("device_manager") << string(36 - getString("device_manager").length(), ' ') << "�U" << endl;
    cout << "�U 8. " << getString("disk_management") << string(36 - getString("disk_management").length(), ' ') << "�U" << endl;
    cout << "�U 9. " << getString("services") << string(36 - getString("services").length(), ' ') << "�U" << endl;
    cout << "�U 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "�U" << endl;
    
    setColor(10); // ����ɫ
    cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
    cout << endl;
    
    setColor(14); // ��ɫ
    cout << getString("select_prompt");
    setColor(7); // �ָ�Ĭ�ϰ�ɫ
}

// ����ϵͳ����ѡ��
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

// ��ʾʵ�ù����Ӳ˵�
void showUtilitiesMenu() {
    system("cls");
    showTitle(getString("utilities"));
    
    setColor(10); // ����ɫ
    cout << "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
    cout << "�U              " << getString("utilities") << "              �U" << endl;
    cout << "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g" << endl;
    
    setColor(11); // ����ɫ
    cout << "�U 1. " << getString("calculator") << string(36 - getString("calculator").length(), ' ') << "�U" << endl;
    cout << "�U 2. " << getString("notepad") << string(36 - getString("notepad").length(), ' ') << "�U" << endl;
    cout << "�U 3. " << getString("paint") << string(36 - getString("paint").length(), ' ') << "�U" << endl;
    cout << "�U 4. " << getString("character_map") << string(36 - getString("character_map").length(), ' ') << "�U" << endl;
    cout << "�U 5. " << getString("snipping_tool") << string(36 - getString("snipping_tool").length(), ' ') << "�U" << endl;
    cout << "�U 6. " << getString("sound_recorder") << string(36 - getString("sound_recorder").length(), ' ') << "�U" << endl;
    cout << "�U 7. " << getString("math_input") << string(36 - getString("math_input").length(), ' ') << "�U" << endl;
    cout << "�U 8. " << getString("remote_desktop") << string(36 - getString("remote_desktop").length(), ' ') << "�U" << endl;
    cout << "�U 9. " << getString("magnifier") << string(36 - getString("magnifier").length(), ' ') << "�U" << endl;
    cout << "�U 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "�U" << endl;
    
    setColor(10); // ����ɫ
    cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
    cout << endl;
    
    setColor(14); // ��ɫ
    cout << getString("select_prompt");
    setColor(7); // �ָ�Ĭ�ϰ�ɫ
}

// ����ʵ�ù���ѡ��
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

// ��ʾϵͳά���Ӳ˵�
void showMaintenanceMenu() {
    system("cls");
    showTitle(getString("system_maintenance"));
    
    setColor(10); // ����ɫ
    cout << "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
    cout << "�U              " << getString("system_maintenance") << "              �U" << endl;
    cout << "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g" << endl;
    
    setColor(11); // ����ɫ
    cout << "�U 1. " << getString("malware_removal") << string(36 - getString("malware_removal").length(), ' ') << "�U" << endl;
    cout << "�U 2. " << getString("disk_cleanup") << string(36 - getString("disk_cleanup").length(), ' ') << "�U" << endl;
    cout << "�U 3. " << getString("disk_defrag") << string(36 - getString("disk_defrag").length(), ' ') << "�U" << endl;
    cout << "�U 4. " << getString("system_file_check") << string(36 - getString("system_file_check").length(), ' ') << "�U" << endl;
    cout << "�U 5. " << getString("check_disk") << string(36 - getString("check_disk").length(), ' ') << "�U" << endl;
    cout << "�U 6. " << getString("system_restore") << string(36 - getString("system_restore").length(), ' ') << "�U" << endl;
    cout << "�U 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "�U" << endl;
    
    setColor(10); // ����ɫ
    cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
    cout << endl;
    
    setColor(14); // ��ɫ
    cout << getString("select_prompt");
    setColor(7); // �ָ�Ĭ�ϰ�ɫ
}

// ����ϵͳά��ѡ��
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

// ��ʾ���繤���Ӳ˵�
void showNetworkToolsMenu() {
    system("cls");
    showTitle(getString("network_tools"));
    
    setColor(10); // ����ɫ
    cout << "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
    cout << "�U              " << getString("network_tools") << "              �U" << endl;
    cout << "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g" << endl;
    
    setColor(11); // ����ɫ
    cout << "�U 1. " << getString("ip_config") << string(36 - getString("ip_config").length(), ' ') << "�U" << endl;
    cout << "�U 2. " << getString("ipconfig_all") << string(36 - getString("ipconfig_all").length(), ' ') << "�U" << endl;
    cout << "�U 3. " << getString("ipconfig_release") << string(36 - getString("ipconfig_release").length(), ' ') << "�U" << endl;
    cout << "�U 4. " << getString("ipconfig_renew") << string(36 - getString("ipconfig_renew").length(), ' ') << "�U" << endl;
    cout << "�U 5. " << getString("ipconfig_flushdns") << string(36 - getString("ipconfig_flushdns").length(), ' ') << "�U" << endl;
    cout << "�U 6. " << getString("ipconfig_displaydns") << string(36 - getString("ipconfig_displaydns").length(), ' ') << "�U" << endl;
    cout << "�U 7. " << getString("network_test") << string(36 - getString("network_test").length(), ' ') << "�U" << endl;
    cout << "�U 8. " << getString("network_connections") << string(36 - getString("network_connections").length(), ' ') << "�U" << endl;
    cout << "�U 9. " << getString("network_sharing") << string(36 - getString("network_sharing").length(), ' ') << "�U" << endl;
    cout << "�U A. " << getString("windows_firewall") << string(36 - getString("windows_firewall").length(), ' ') << "�U" << endl;
    cout << "�U 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "�U" << endl;
    
    setColor(10); // ����ɫ
    cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
    cout << endl;
    
    setColor(14); // ��ɫ
    cout << getString("select_prompt");
    setColor(7); // �ָ�Ĭ�ϰ�ɫ
}
// ��ʾ����IP����
void showFullIPConfig() {
    system("ipconfig /all > ipconfig.txt");
    ifstream file("ipconfig.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("ipconfig.txt");
    
    MessageBox(NULL, content.c_str(), getString("ipconfig_all").c_str(), MB_ICONINFORMATION | MB_OK);
}

// �ͷ�IP��ַ
void releaseIP() {
    system("ipconfig /release > ip_release.txt");
    ifstream file("ip_release.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("ip_release.txt");
    
    MessageBox(NULL, getString("ip_released").c_str(), getString("success").c_str(), MB_ICONINFORMATION | MB_OK);
}

// ����IP��ַ
void renewIP() {
    system("ipconfig /renew > ip_renew.txt");
    ifstream file("ip_renew.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("ip_renew.txt");
    
    MessageBox(NULL, getString("ip_renewed").c_str(), getString("success").c_str(), MB_ICONINFORMATION | MB_OK);
}

// ���DNS����
void flushDNS() {
    system("ipconfig /flushdns > dns_flush.txt");
    ifstream file("dns_flush.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("dns_flush.txt");
    
    MessageBox(NULL, getString("dns_flushed").c_str(), getString("success").c_str(), MB_ICONINFORMATION | MB_OK);
}

// ��ʾDNS����
void displayDNSCache() {
    system("ipconfig /displaydns > dns_cache.txt");
    ifstream file("dns_cache.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("dns_cache.txt");
    
    MessageBox(NULL, content.c_str(), getString("ipconfig_displaydns").c_str(), MB_ICONINFORMATION | MB_OK);
}

// �������繤��ѡ��
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

// ��ʾ��Դ�����Ӳ˵�
void showPowerMenu() {
    system("cls");
    showTitle(getString("power_management"));
    
    setColor(10); // ����ɫ
    cout << "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
    cout << "�U              " << getString("power_management") << "              �U" << endl;
    cout << "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g" << endl;
    
    setColor(11); // ����ɫ
    cout << "�U 1. " << getString("shutdown") << string(36 - getString("shutdown").length(), ' ') << "�U" << endl;
    cout << "�U 2. " << getString("restart") << string(36 - getString("restart").length(), ' ') << "�U" << endl;
    cout << "�U 3. " << getString("logout") << string(36 - getString("logout").length(), ' ') << "�U" << endl;
    cout << "�U 4. " << getString("lock") << string(36 - getString("lock").length(), ' ') << "�U" << endl;
    cout << "�U 5. " << getString("sleep") << string(36 - getString("sleep").length(), ' ') << "�U" << endl;
    cout << "�U 6. " << (currentLang == CHINESE ? "��ʱ�ػ�" : "Delayed Shutdown") << string(36 - (currentLang == CHINESE ? 8 : 15), ' ') << "�U" << endl;
    cout << "�U 7. " << (currentLang == CHINESE ? "��ʱ����" : "Delayed Restart") << string(36 - (currentLang == CHINESE ? 8 : 14), ' ') << "�U" << endl;
    cout << "�U 8. " << (currentLang == CHINESE ? "��ʱע��" : "Delayed Logout") << string(36 - (currentLang == CHINESE ? 8 : 14), ' ') << "�U" << endl;
    cout << "�U 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "�U" << endl;
    
    setColor(10); // ����ɫ
    cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
    cout << endl;
    
    setColor(14); // ��ɫ
    cout << getString("select_prompt");
    setColor(7); // �ָ�Ĭ�ϰ�ɫ
}
// ��ʾ������Ϣ
void showHelp() {
    system("cls");
    showTitle(getString("help_title"));
    
    // ��������ϸ�İ�������
    vector<string> helpSections;
    
    // ���ⲿ��
    helpSections.push_back("�T�T�T�T�T�T�T�T�T�T " + getString("title") + " �T�T�T�T�T�T�T�T�T�T");
    helpSections.push_back("");
    helpSections.push_back(getString("title") + " " + (currentLang == CHINESE ? "��һ���๦��Windowsϵͳ������" : "is a multi-functional Windows system toolbox"));
    helpSections.push_back(currentLang == CHINESE ? "�汾: 2.7.1" : "Version: 2.7.1");
    helpSections.push_back(currentLang == CHINESE ? "����: ZhangW3944" : "Author: ZhangW3944");
    helpSections.push_back(currentLang == CHINESE ? "���֤: MIT" : "License: MIT");
    helpSections.push_back("");
    
    // ��Ҫ���ܲ���
    helpSections.push_back("�T�T�T�T�T�T�T�T " + string(currentLang == CHINESE ? "��Ҫ����" : "Main Features") + " �T�T�T�T�T�T�T�T");
    helpSections.push_back("");
    helpSections.push_back("1. " + getString("system_tools") + " - " + 
        (currentLang == CHINESE ? "����ϵͳʵ�ù���" : "Access system utilities"));
    helpSections.push_back("2. " + getString("utilities") + " - " + 
        (currentLang == CHINESE ? "�򿪳���Windows����" : "Open common Windows tools"));
    helpSections.push_back("3. " + getString("system_maintenance") + " - " + 
        (currentLang == CHINESE ? "ִ��ϵͳά������" : "Perform system maintenance"));
    helpSections.push_back("4. " + getString("network_tools") + " - " + 
        (currentLang == CHINESE ? "�������úͲ���" : "Network configuration and testing"));
    helpSections.push_back("5. " + getString("power_management") + " - " + 
        (currentLang == CHINESE ? "ϵͳ��Դ����ѡ��" : "System power management options"));
    helpSections.push_back("6. " + getString("system_info") + " - " + 
        (currentLang == CHINESE ? "�鿴��ϸϵͳ��Ϣ" : "View detailed system information"));
    helpSections.push_back("7. " + string(currentLang == CHINESE ? "��ͼ����" : "Screenshot Tool") + " - " + 
        (currentLang == CHINESE ? "��ʱ�������Ļ��ͼ" : "Timestamped screenshots"));
    helpSections.push_back("8. " + getString("troubleshooting") + " - " + 
        (currentLang == CHINESE ? "ϵͳ������Ϲ���" : "System troubleshooting tools"));
    helpSections.push_back("9. " + getString("search_system") + " - " + 
        (currentLang == CHINESE ? "ϵͳ������������" : "System content search feature"));
    helpSections.push_back("0. " + getString("admin_features") + " - " + 
        (currentLang == CHINESE ? "�߼�ϵͳ������" : "Advanced system administration"));
    helpSections.push_back("");
    
    // �������ܲ���
    helpSections.push_back("�T�T�T�T�T�T�T�T " + string(currentLang == CHINESE ? "��������" : "Other Features") + " �T�T�T�T�T�T�T�T");
    helpSections.push_back("");
    helpSections.push_back("L. " + string(currentLang == CHINESE ? "�л�����" : "Switch Language") + " - " + 
        (currentLang == CHINESE ? "��Ӣ���л�" : "Toggle between English/Chinese"));
    helpSections.push_back("H. " + string(currentLang == CHINESE ? "������Ϣ" : "Help") + " - " + 
        (currentLang == CHINESE ? "��ʾ�˰���" : "Show this help"));
    helpSections.push_back("X. " + getString("exit_program") + " - " + 
        (currentLang == CHINESE ? "�˳�����" : "Exit the program"));
    helpSections.push_back("");
    
    // ʹ����ʾ����
    helpSections.push_back("�T�T�T�T�T�T�T�T " + string(currentLang == CHINESE ? "ʹ����ʾ" : "Usage Tips") + " �T�T�T�T�T�T�T�T");
    helpSections.push_back("");
    helpSections.push_back(currentLang == CHINESE ? 
        "- ʹ�����ּ�ѡ��˵�ѡ��" : 
        "- Use number keys to select menu options");
    helpSections.push_back(currentLang == CHINESE ? 
        "- ����Ա������Ҫ������֤" : 
        "- Admin features require password authentication");
    helpSections.push_back(currentLang == CHINESE ? 
        "- ��Դ����������ɳ����������ʹ��" : 
        "- Power management actions cannot be undone, use with caution");
    helpSections.push_back(currentLang == CHINESE ? 
        "- ϵͳά�����ܿ�����Ҫ����ԱȨ��" : 
        "- System maintenance may require admin privileges");

    // ������г������ڱ߿����
    size_t maxLength = 0;
    for (const auto& line : helpSections) {
        if (line.length() > maxLength) {
            maxLength = line.length();
        }
    }
    maxLength += 4; // ��ӱ߿�����

    // ��ʾ��������
    setColor(11); // ����ɫ
    
    // �����߿�
    cout << "�X" << string(maxLength - 2, '�T') << "�[" << endl;
    
    // ��������
    for (const auto& line : helpSections) {
        if (line.empty()) {
            cout << "�U" << string(maxLength - 2, ' ') << "�U" << endl;
        } else if (line.find("�T�T�T") != string::npos) {
            cout << "�d" << string(maxLength - 2, '�T') << "�g" << endl;
        } else {
            size_t padding = maxLength - line.length() - 2;
            size_t leftPad = padding / 2;
            size_t rightPad = padding - leftPad;
            
            cout << "�U" << string(leftPad, ' ') << line << string(rightPad, ' ') << "�U" << endl;
        }
    }
    
    // �ײ��߿�
    cout << "�^" << string(maxLength - 2, '�T') << "�a" << endl;
    
    // ��Ӽ�����ʾ
    setColor(14); // ��ɫ
    cout << endl << (currentLang == CHINESE ? "��������������˵�..." : "Press any key to return to main menu...");
    setColor(7); // �ָ�Ĭ�ϰ�ɫ
    
    _getch(); // �ȴ��û�����
}
void handlePowerOptions() {
    char choice;
    while (true) {
        showPowerMenu();
        cin >> choice;
        
        switch (choice) {
            case '1':
                if (MessageBox(NULL, "ȷ��Ҫ�ػ���?", "�ػ�ȷ��", MB_ICONQUESTION | MB_YESNO) == IDYES) {
                    system("shutdown -s -t 0");
                }
                return;
            case '2':
                if (MessageBox(NULL, "ȷ��Ҫ������?", "����ȷ��", MB_ICONQUESTION | MB_YESNO) == IDYES) {
                    system("shutdown -r -t 0");
                }
                return;
            case '3':
                if (MessageBox(NULL, "ȷ��Ҫע����?", "ע��ȷ��", MB_ICONQUESTION | MB_YESNO) == IDYES) {
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

// ����Ա��¼����
bool adminLogin() {
    // �洢��ǰ����(��ʼΪĬ������)
    static string currentPassword = "123";
    
    system("cls");
    showTitle(currentLang == CHINESE ? "����Ա��¼" : "Admin Login");
    
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
    cout << "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
    cout << "�U " << (currentLang == CHINESE ? "�û���: " : "Username: ");
    cin >> username;
    
    if (username != "Admin") {
        MessageBox(NULL, 
            currentLang == CHINESE ? "�û�������!" : "Invalid username!",
            currentLang == CHINESE ? "����" : "Error", 
            MB_ICONERROR | MB_OK);
        return false;
    }
    
    cout << "�U " << (currentLang == CHINESE ? "����: " : "Password: ");
    
    // ������������
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
    
    cin >> password;
    SetConsoleMode(hStdin, mode); // �ָ�����
    
    cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
    
    if (password != currentPassword) {
        MessageBox(NULL, 
            currentLang == CHINESE ? "�������!" : "Invalid password!",
            currentLang == CHINESE ? "����" : "Error", 
            MB_ICONERROR | MB_OK);
        return false;
    }

    // ��¼�ɹ����������Ա���ܽ���
    while (true) {
        system("cls");
        showTitle(currentLang == CHINESE ? "����Ա����" : "Admin Features");
        
        setColor(10);
        cout << "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
        cout << "�U " << (currentLang == CHINESE ? "            ����Ա����            " : "            Admin Features            ") << "�U" << endl;
        cout << "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g" << endl;
        
        setColor(11);
        cout << "�U 1. " << (currentLang == CHINESE ? "�����б�" : "Process List") << string(36 - (currentLang == CHINESE ? 8 : 12), ' ') << "�U" << endl;
        cout << "�U 2. " << (currentLang == CHINESE ? "��������" : "Kill Process") << string(36 - (currentLang == CHINESE ? 8 : 11), ' ') << "�U" << endl;
        cout << "�U 3. " << (currentLang == CHINESE ? "�鿴ϵͳ��־" : "View System Logs") << string(36 - (currentLang == CHINESE ? 10 : 15), ' ') << "�U" << endl;
        cout << "�U 4. " << (currentLang == CHINESE ? "�鿴�û��˻�" : "View User Accounts") << string(36 - (currentLang == CHINESE ? 10 : 17), ' ') << "�U" << endl;
        cout << "�U 5. " << (currentLang == CHINESE ? "��Ȩ��Ϣ" : "Copyright Info") << string(36 - (currentLang == CHINESE ? 8 : 14), ' ') << "�U" << endl;
        cout << "�U 6. " << (currentLang == CHINESE ? "�޸�����" : "Change Password") << string(36 - (currentLang == CHINESE ? 8 : 15), ' ') << "�U" << endl;
        cout << "�U 0. " << (currentLang == CHINESE ? "�������˵�" : "Return to Main Menu") << string(36 - (currentLang == CHINESE ? 10 : 19), ' ') << "�U" << endl;
        
        setColor(10);
        cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
        cout << endl;
        
        setColor(14);
        cout << (currentLang == CHINESE ? "��ѡ����: " : "Please select: ");
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
                    currentLang == CHINESE ? "�����б�" : "Process List", 
                    MB_ICONINFORMATION | MB_OK);
                break;
            }
            case '2': {
                string pid;
                cout << (currentLang == CHINESE ? "������Ҫ�����Ľ���PID: " : "Enter PID to kill: ");
                cin >> pid;
                
                string cmd = "taskkill /F /PID " + pid;
                int result = system(cmd.c_str());
                
                MessageBox(NULL, 
                    result == 0 ? 
                        (currentLang == CHINESE ? "�����ɹ�!" : "Process killed successfully!") : 
                        (currentLang == CHINESE ? "����ʧ��!" : "Failed to kill process!"),
                    result == 0 ? 
                        (currentLang == CHINESE ? "�ɹ�" : "Success") : 
                        (currentLang == CHINESE ? "����" : "Error"),
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
                         string(currentLang == CHINESE ? "�汾: 2.7" : "Version: 2.7");
    MessageBox(NULL, copyrightText.c_str(), 
        currentLang == CHINESE ? "��Ȩ��Ϣ" : "Copyright Info", 
        MB_ICONINFORMATION | MB_OK);
    break;
			}
            case '6': {
                string newPass, confirmPass;
                cout << (currentLang == CHINESE ? "������������: " : "Enter new password: ")<<endl;
                
                HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
                DWORD mode = 0;
                GetConsoleMode(hStdin, &mode);
                SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
                
                cin >> newPass;
                SetConsoleMode(hStdin, mode);
                
                cout << (currentLang == CHINESE ? "��ȷ��������: " : "Confirm new password: ");
                SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
                cin >> confirmPass;
                SetConsoleMode(hStdin, mode);
                
                if (newPass == confirmPass) {
                    currentPassword = newPass;
                    MessageBox(NULL, 
                        currentLang == CHINESE ? "�����޸ĳɹ�!" : "Password changed successfully!", 
                        currentLang == CHINESE ? "�ɹ�" : "Success", 
                        MB_ICONINFORMATION | MB_OK);
                } else {
                    MessageBox(NULL, 
                        currentLang == CHINESE ? "������������벻ƥ��!" : "Passwords do not match!", 
                        currentLang == CHINESE ? "����" : "Error", 
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
// ��ʾ���˵�
void showMainMenu() {
    system(currentLang == CHINESE ? "title Windows������" : "title Windows Toolz");
    system("cls");
    
    setColor(14); // ��ɫ
    cout << R"(
   __      __.__  __  .__       _________                      
  /  \    /  \__|/  |_|  |__   /   _____/ ____ _____    ____  
  \   \/\/   /  \   __\  |  \  \_____  \_/ ___\\__  \  /    \ 
   \        /|  ||  | |   Y  \ /        \  \___ / __ \|   |  \
    \__/\  / |__||__| |___|  //_______  /\___  >____  /___|  /
         \/                \/          \/     \/     \/     \/ 
    )" << endl;
    
    setColor(10); // ����ɫ
    cout << "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
    cout << "�U             " << getString("title") << "             �U" << endl;
    cout << "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g" << endl;
    
    setColor(11); // ����ɫ
    cout << "�U 1. " << getString("system_tools") << string(36 - getString("system_tools").length(), ' ') << "�U" << endl;
    cout << "�U 2. " << getString("utilities") << string(36 - getString("utilities").length(), ' ') << "�U" << endl;
    cout << "�U 3. " << getString("system_maintenance") << string(36 - getString("system_maintenance").length(), ' ') << "�U" << endl;
    cout << "�U 4. " << getString("network_tools") << string(36 - getString("network_tools").length(), ' ') << "�U" << endl;
    cout << "�U 5. " << getString("power_management") << string(36 - getString("power_management").length(), ' ') << "�U" << endl;
    cout << "�U 6. " << getString("system_info") << string(36 - getString("system_info").length(), ' ') << "�U" << endl;
    cout << "�U 7. " << (currentLang == CHINESE ? "��ȡʱ���ͼ" : "Take Screenshot") << string(36 - (currentLang == CHINESE ? 12 : 15), ' ') << "�U" << endl;
    // �� showMainMenu() �����У��ڰ���ѡ��ǰ�����������
	cout << "�U 8. " << getString("troubleshooting") << string(36 - getString("troubleshooting").length(), ' ') << "�U" << endl;
	cout << "�U 9. " << getString("search_system") << string(36 - getString("search_system").length(), ' ') << "�U" << endl;
    cout << "�U 0. " << (currentLang == CHINESE ? "����Ա����" : "Admin Features") << string(36 - (currentLang == CHINESE ? 10 : 14), ' ') << "�U" << endl;
    cout << "�U L. " << (currentLang == CHINESE ? "�л�����(��/Ӣ)" : "Switch Language(EN/CN)") << string(36 - (currentLang == CHINESE ? 13 : 20), ' ') << "�U" << endl;
    // �ڲ˵�ѡ���б�������������ݣ������˳�ѡ��֮ǰ��
	cout << "�U H. " << (currentLang == CHINESE ? "����" : "Help") << string(36 - (currentLang == CHINESE ? 4 : 6), ' ') << "�U" << endl;
    cout << "�U x. " << getString("exit_program") << string(36 - getString("exit_program").length(), ' ') << "�U" << endl;
    
    setColor(10); // ����ɫ
    cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
    cout << endl;
    
    setColor(14); // ��ɫ
    cout << getString("select_prompt");
    setColor(7); // �ָ�Ĭ�ϰ�ɫ
}
// ��ǿ���������ܣ������Զ�����
void enhancedSearchSystem() {
    system("cls");
    showTitle(getString("search_system"));
    
    cout << getString("enter_search_term");
    string searchTerm;
    getline(cin, searchTerm);
    
    // �������������Զ�ȷ�����
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
    
    // ִ������
    string cmd = "where /r C:\\ *" + searchTerm + "* > search_results.txt 2>&1";
    system(cmd.c_str());
    
    // ��ȡ����ʾ���
    ifstream file("search_results.txt");
    if (file.peek() == ifstream::traits_type::eof()) {
        MessageBox(NULL, getString("no_results_found").c_str(), getString("search_results").c_str(), MB_ICONINFORMATION | MB_OK);
    } else {
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        remove("search_results.txt");
        
        // ��������Ϣ
        string categorizedResults = "[" + category + " " + getString("search_results") + "]\n\n" + content;
        
        MessageBox(NULL, categorizedResults.c_str(), getString("search_results").c_str(), MB_ICONINFORMATION | MB_OK);
    }
}
// ������
int main() {
    // ��������ӳ�����ȱʧ���ַ���
    langStrings["system_tools"] = {"System Tools", "ϵͳ����"};
    langStrings["utilities"] = {"Utilities", "ʵ�ù���"};
    langStrings["system_maintenance"] = {"System Maintenance", "ϵͳά��"};
    langStrings["network_tools"] = {"Network Tools", "���繤��"};
    langStrings["file_explorer"] = {"File Explorer", "��Դ������"};
    langStrings["task_manager"] = {"Task Manager", "���������"};
    langStrings["registry_editor"] = {"Registry Editor", "ע���༭��"};
    langStrings["control_panel"] = {"Control Panel", "�������"};
    langStrings["command_prompt"] = {"Command Prompt", "������ʾ��"};
    langStrings["device_manager"] = {"Device Manager", "�豸������"};
    langStrings["disk_management"] = {"Disk Management", "���̹���"};
    langStrings["services"] = {"Services", "����"};
    langStrings["calculator"] = {"Calculator", "������"};
    langStrings["notepad"] = {"Notepad", "���±�"};
    langStrings["paint"] = {"Paint", "��ͼ"};
    langStrings["character_map"] = {"Character Map", "�ַ�ӳ���"};
    langStrings["snipping_tool"] = {"Snipping Tool", "��ͼ����"};
    langStrings["sound_recorder"] = {"Sound Recorder", "¼����"};
    langStrings["math_input"] = {"Math Input", "��ѧ�����"};
    langStrings["remote_desktop"] = {"Remote Desktop", "Զ����������"};
    langStrings["magnifier"] = {"Magnifier", "�Ŵ�"};
    langStrings["malware_removal"] = {"Malware Removal", "�������ɾ������"};
    langStrings["disk_defrag"] = {"Disk Defragmenter", "������Ƭ����"};
    langStrings["system_file_check"] = {"System File Check", "ϵͳ�ļ����"};
    langStrings["check_disk"] = {"Check Disk", "���̼��"};
    langStrings["system_restore"] = {"System Restore", "ϵͳ��ԭ"};
    langStrings["network_connections"] = {"Network Connections", "��������"};
    langStrings["network_sharing"] = {"Network Sharing", "����͹�������"};
    langStrings["windows_firewall"] = {"Windows Firewall", "����ǽ����"};

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
            // �� main() ������ switch ��������
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