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

// ����ö��
enum Language { ENGLISH, CHINESE };
Language currentLang = CHINESE; // Ĭ������

// �����ַ���ӳ��
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
    {"language_title", {"Language", "����"}}
};

// ��ȡ��ǰ���Ե��ַ���
string getString(const string& key) {
    return langStrings[key][currentLang];
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
    cout << "�U 2. " << getString("network_test") << string(36 - getString("network_test").length(), ' ') << "�U" << endl;
    cout << "�U 3. " << getString("network_connections") << string(36 - getString("network_connections").length(), ' ') << "�U" << endl;
    cout << "�U 4. " << getString("network_sharing") << string(36 - getString("network_sharing").length(), ' ') << "�U" << endl;
    cout << "�U 5. " << getString("windows_firewall") << string(36 - getString("windows_firewall").length(), ' ') << "�U" << endl;
    cout << "�U 0. " << getString("return_main") << string(36 - getString("return_main").length(), ' ') << "�U" << endl;
    
    setColor(10); // ����ɫ
    cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
    cout << endl;
    
    setColor(14); // ��ɫ
    cout << getString("select_prompt");
    setColor(7); // �ָ�Ĭ�ϰ�ɫ
}

// �������繤��ѡ��
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

// �����Դ����ѡ��
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
    static int currentPassword = 20010404;
    
    system("cls");
    showTitle("����Ա��¼");
    
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
    cout << "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
    cout << "�U Login: ";
    cin >> username;
    cout << "�U                                        �U" << endl;
    
    if (username != 500) {
        MessageBox(NULL, "�û�������!", "����", MB_ICONERROR | MB_OK);
        return false;
    }
    
    cout << "�U Password: ";
    cin >> password;
    cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
    
    if (password != currentPassword) {
        MessageBox(NULL, "�������!", "����", MB_ICONERROR | MB_OK);
        return false;
    }

    // ��¼�ɹ����������Ա���ܽ���
    while (true) {
        system("cls");
        showTitle("����Ա����");
        
        setColor(10); // ����ɫ
        cout << "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[" << endl;
        cout << "�U              ����Ա����               �U" << endl;
        cout << "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g" << endl;
        
        setColor(11); // ����ɫ
        cout << "�U 1. �����б�                              �U" << endl;
        cout << "�U 2. ��������                              �U" << endl;
        cout << "�U 3. �鿴ϵͳ��־                          �U" << endl;
        cout << "�U 4. �鿴�û��˻�                          �U" << endl;
        cout << "�U 5. ��Ȩ��Ϣ                              �U" << endl;
        cout << "�U 6. �޸�����                              �U" << endl;
        cout << "�U 0. �������˵�                            �U" << endl;
        
        setColor(10); // ����ɫ
        cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
        cout << endl;
        
        setColor(14); // ��ɫ
        cout << "��ѡ����: ";
        setColor(7); // �ָ�Ĭ�ϰ�ɫ
        
        char adminChoice;
        cin >> adminChoice;
        cin.ignore(); // ������뻺����
        
        switch (adminChoice) {
            case '1': {
                system("tasklist /v > processes.txt");
                ifstream file("processes.txt");
                string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
                file.close();
                remove("processes.txt");
                
                MessageBox(NULL, content.c_str(), "�����б�", MB_ICONINFORMATION | MB_OK);
                break;
            }
            case '2': {
                string pid;
                cout << "������Ҫ�����Ľ���PID: ";
                cin >> pid;
                
                string cmd = "taskkill /F /PID " + pid;
                int result = system(cmd.c_str());
                
                MessageBox(NULL, 
                    result == 0 ? "�����ɹ�!" : "����ʧ��!",
                    result == 0 ? "�ɹ�" : "����",
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
                                      "�汾: 2.7";
                MessageBox(NULL, copyrightText.c_str(), "��Ȩ��Ϣ", MB_ICONINFORMATION | MB_OK);
                break;
            }
            case '6': {
                int newPass, confirmPass;
                cout << "������������: ";
                cin >> newPass;
                cout << "��ȷ��������: ";
                cin >> confirmPass;
                
                if (newPass == confirmPass) {
                    currentPassword = newPass; // ��������
                    MessageBox(NULL, 
                        "�����޸ĳɹ�!", 
                        "�ɹ�", 
                        MB_ICONINFORMATION | MB_OK);
                } else {
                    MessageBox(NULL, 
                        "������������벻ƥ��!", 
                        "����", 
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
    cout << "�U 0. " << (currentLang == CHINESE ? "����Ա����" : "Admin Features") << string(36 - (currentLang == CHINESE ? 10 : 14), ' ') << "�U" << endl;
    cout << "�U L. " << (currentLang == CHINESE ? "�л�����(��/Ӣ)" : "Switch Language(EN/CN)") << string(36 - (currentLang == CHINESE ? 13 : 20), ' ') << "�U" << endl;
    cout << "�U x. " << getString("exit_program") << string(36 - getString("exit_program").length(), ' ') << "�U" << endl;
    
    setColor(10); // ����ɫ
    cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
    cout << endl;
    
    setColor(14); // ��ɫ
    cout << getString("select_prompt");
    setColor(7); // �ָ�Ĭ�ϰ�ɫ
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