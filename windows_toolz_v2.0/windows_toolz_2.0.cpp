// Copyright (c) 2024-2025 Desperate lnc.
// SPDX-License-Identifier: MIT
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <ctime>

using namespace std;

// ���ÿ���̨��ɫ
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// ��ʾ���߿�ı���
void showTitle(const string& title) {
    setColor(11); // ����ɫ
    cout << "==============================================" << endl;
    cout << "||               " << title << "               ||" << endl;
    cout << "==============================================" << endl;
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

// ��ʾIP����
void showIPConfig() {
    system("ipconfig > ipconfig.txt");
    ifstream file("ipconfig.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("ipconfig.txt");
    
    MessageBox(NULL, content.c_str(), "IP������Ϣ", MB_ICONINFORMATION | MB_OK);
}

// ִ�д�������
void diskCleanup() {
    if (MessageBox(NULL, "ȷ��Ҫִ�д���������?", "��������", MB_ICONQUESTION | MB_YESNO) == IDYES) {
        system("cleanmgr /sagerun:1");
        MessageBox(NULL, "��������������", "��Ϣ", MB_ICONINFORMATION | MB_OK);
    }
}

// ������������
void testNetwork() {
    system("ping 8.8.8.8 -n 4 > ping.txt");
    ifstream file("ping.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    remove("ping.txt");
    
    MessageBox(NULL, content.c_str(), "������Խ��", MB_ICONINFORMATION | MB_OK);
}

// ��ȡʱ���ͼ����
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

// ��ʾ���˵�
void showMainMenu() {
    system("title Windows ������");
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
    cout << "�U             Windows ������              �U" << endl;
    cout << "�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g" << endl;
    
    setColor(11); // ����ɫ
    cout << "�U 1. ��Դ������                            �U" << endl;
    cout << "�U 2. ���������                            �U" << endl;
    cout << "�U 3. ע���༭��                          �U" << endl;
    cout << "�U 4. �������ɾ������                      �U" << endl;
    cout << "�U 5. �������                              �U" << endl;
    cout << "�U 6. �ػ�                                  �U" << endl;
    cout << "�U 7. ע��                                  �U" << endl;
    cout << "�U 8. ����                                  �U" << endl;
    cout << "�U 9. ϵͳ��Ϣ                              �U" << endl;
    cout << "�U a. IP����                                �U" << endl;
    cout << "�U b. ��������                              �U" << endl;
    cout << "�U c. �������                              �U" << endl;
    cout << "�U d. ������                                �U" << endl;
    cout << "�U e. ���±�                                �U" << endl;
    cout << "�U f. ��ȡʱ���ͼ                          �U" << endl;
    cout << "�U 0. ����Ա����                            �U" << endl;
    cout << "�U x. �˳�                                  �U" << endl;
    
    setColor(10); // ����ɫ
    cout << "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a" << endl;
    cout << endl;
    
    setColor(14); // ��ɫ
    cout << "��ѡ����: ";
    setColor(7); // �ָ�Ĭ�ϰ�ɫ
}

// ����Ա��¼����
bool adminLogin() {
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
    char choice;
    
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
    
    if (password != 20010404) {
        MessageBox(NULL, "�������!", "����", MB_ICONERROR | MB_OK);
        return false;
    }
    
    int option = MessageBox(NULL, "��¼�ɹ�!\n��ѡ����:\n1. ��Ȩ��Ϣ\n2. ���̹���", 
                          "����Ա�˵�", MB_ICONINFORMATION | MB_OKCANCEL);
    
    if (option == IDOK) {
        MessageBox(NULL, "Desperate Corporation\n(c)2024-2025 All Rights Reserved.", "��Ȩ��Ϣ", 
                 MB_ICONINFORMATION | MB_OK);
        system("tasklist /v > processes.txt");
        ifstream file("processes.txt");
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        remove("processes.txt");
        
        MessageBox(NULL, content.c_str(), "�����б�", MB_ICONINFORMATION | MB_OK);
    }
    
    return true;
}

// ������
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
                if (MessageBox(NULL, "ȷ��Ҫ�ػ���?", "�ػ�ȷ��", MB_ICONQUESTION | MB_YESNO) == IDYES) {
                    system("shutdown -s -t 0");
                }
                return 0;
            case '7':
                if (MessageBox(NULL, "ȷ��Ҫע����?", "ע��ȷ��", MB_ICONQUESTION | MB_YESNO) == IDYES) {
                    system("shutdown -l");
                }
                return 0;
            case '8':
                if (MessageBox(NULL, "ȷ��Ҫ������?", "����ȷ��", MB_ICONQUESTION | MB_YESNO) == IDYES) {
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
                MessageBox(NULL, "�������!", "����", MB_ICONERROR | MB_OK);
        }
    }
    
    return 0;
}