#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "Oxygen.h"
using namespace Oxygen;

// �ṹ�����ڴ洢ע�������Ϣ
struct RegistryItem
{
    int index;
    std::string name;
    std::string value;
    std::string path;
};

// �������ڶ�ȡע�����
std::vector<RegistryItem> ReadRegistryEntries(HKEY rootKey, const std::string &subKey)
{
    std::vector<RegistryItem> items;
    HKEY hKey;
    if (RegOpenKeyExA(rootKey, subKey.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        DWORD index = 0;
        char name[256];
        DWORD nameSize = sizeof(name);
        char value[256];
        DWORD valueSize = sizeof(value);
        DWORD type;
        while (RegEnumValueA(hKey, index, name, &nameSize, NULL, &type, (BYTE *)value, &valueSize) == ERROR_SUCCESS)
        {
            RegistryItem item;
            item.index = items.size() + 1;
            item.name = name;
            item.value = value;
            item.path = subKey;
            items.push_back(item);
            index ++;
            nameSize = sizeof(name);
            valueSize = sizeof(value);
        }
        RegCloseKey(hKey);
    }
    return items;
}

// ����������ʾע������б�
void DisplayRegistryItems(const std::vector<RegistryItem> &items)
{
    for (const auto &item : items)
    {
        std::cout << "���: " << item.index << ": Name: " << item.name << std::endl;
        std::cout << "        Value: " << item.value << std::endl;
        std::cout << "        Path: " << item.path << std::endl;
    }
}

// ���������޸�ע�����
void ModifyRegistryEntry(HKEY rootKey, const std::string &subKey, int index, const std::string &newValue)
{
    HKEY hKey;
    if (RegOpenKeyExA(rootKey, subKey.c_str(), 0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
    {
        std::vector<RegistryItem> items = ReadRegistryEntries(rootKey, subKey);
        if (index > 0 && index <= items.size())
        {
            const RegistryItem &item = items[index - 1];
            RegSetValueExA(hKey, item.name.c_str(), 0, REG_SZ, (const BYTE *)newValue.c_str(), (newValue.size() + 1));
        }
        RegCloseKey(hKey);
    }
}

// ��������ɾ��ע�����
void DeleteRegistryEntry(HKEY rootKey, const std::string &subKey, int index)
{
    HKEY hKey;
    if (RegOpenKeyExA(rootKey, subKey.c_str(), 0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
    {
        std::vector<RegistryItem> items = ReadRegistryEntries(rootKey, subKey);
        if (index > 0 && index <= items.size())
        {
            const RegistryItem &item = items[index - 1];
            RegDeleteValueA(hKey, item.name.c_str());
        }
        RegCloseKey(hKey);
    }
}

// ���������½�ע�����
void CreateRegistryEntry(HKEY rootKey, const std::string &subKey, const std::string &name, const std::string &value)
{
    HKEY hKey;
    if (RegOpenKeyExA(rootKey, subKey.c_str(), 0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueExA(hKey, name.c_str(), 0, REG_SZ, (const BYTE *)value.c_str(), (value.size() + 1));
        RegCloseKey(hKey);
    }
}

int main(){
    while (true){
        // HKLM\Software\Wow6432Node\Microsoft\Windows\Currentversion\Run
        std::vector<RegistryItem> hkcuItems = ReadRegistryEntries(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
        std::vector<RegistryItem> hklmItems = ReadRegistryEntries(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

        std::vector<RegistryItem> Wow6432NodeItems = ReadRegistryEntries(HKEY_LOCAL_MACHINE, "Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run");
        int amount = hklmItems.size();

        // ���� Wow6432NodeItems ��ÿ��Ԫ�ص����
        for (auto& item : Wow6432NodeItems) {
            item.index += amount;
        }

        // ����������ŵ� Wow6432NodeItems ���뵽 hklmItems ĩβ
        hklmItems.insert(hklmItems.end(), Wow6432NodeItems.begin(), Wow6432NodeItems.end());
        
        std::cout << "HKCU �����" << std::endl;
        DisplayRegistryItems(hkcuItems);
        std::cout << "HKLM �����" << std::endl;
        DisplayRegistryItems(hklmItems);

        std::string choice, path;
        std::cout << "��������� (�޸�: M, ɾ��: D, �½�: C, �˳�: E): ";
        std::cin >> choice;

        if (choice == "M"){
            while (true){
                std::cout << "��������Ҫ�޸ĵ�·��(��֧�� HKCU �� HKLM ��������): ";
                std::cin >> path;
                if (path == "HKCU"){
                    int index = 0;
                    std::string value;
                    std::cout << "������Ҫ�޸ĵ����: ";
                    std::cin >> index;
                    if (index > hkcuItems.size())
                        std::cerr << "���벻�Ϸ�, ����������!" << std::endl;
                    else {
                        std::string name;
                        std::cout << "�������޸ĺ�ļ�ֵ: ";
                        std::cin >> value;
                        for (auto &i : hkcuItems)
                            if (i.index == index){
                                name = i.name;
                                break;
                            }
                        
                        if (ModifyRegisterKeyValueInCurrentUser(AutoRun, name, value))
                            std::cout << "�����ɹ�!" << std::endl;
                        else
                            std::cerr << "����ʧ��!" << std::endl;
                        Sleep(2000);
                        std::system("cls");
                        break;
                    }
                }
                else if (path == "HKLM"){
                    int index = 0;
                    std::string value;
                    std::cout << "������Ҫ�޸ĵ����: ";
                    std::cin >> index;
                    if (index > hklmItems.size()){
                        std::cerr << "���벻�Ϸ�, ����������!" << std::endl;
                    }
                    else {
                        std::string name;
                        std::cout << "�������޸ĺ�ļ�ֵ: ";
                        std::cin >> value;
                        for (auto &i : hklmItems)
                            if (i.index == index){
                                name = i.name;
                                break;
                            }
                        
                        if (ModifyRegisterKeyValueInLocalMachine(AutoRun, name, value))
                            std::cout << "�����ɹ�!" << std::endl;
                        
                        else
                            std::cerr << "����ʧ��!" << std::endl;
                        
                        Sleep(2000);
                        std::system("cls");
                        break;
                    }
                }
                else{
                    std::cout << "���벻�Ϸ�, ����������!" << std::endl;
                    Sleep(2000);
                }
            }
        }
        else if (choice == "D"){
            while (true){
                std::cout << "��������Ҫɾ����·��(��֧�� HKCU �� HKLM ��������): ";
                std::cin >> path;
                if (path == "HKCU") {
                    int index = 0;
                    std::cout << "������Ҫ�޸ĵ����: ";
                    std::cin >> index;
                    if (index > hkcuItems.size())
                        std::cerr << "���벻�Ϸ�, ����������!" << std::endl;
                    else {
                        // ������������
                        std::string name;
                        for (auto &i : hkcuItems)
                            if (i.index == index){
                                name = i.name;
                                break;
                            }
                        char DeleteConfirmation;
                        std::cout << "ɾ��ע��������һ������, ȷ��ɾ����? (y = yes, n = no): ";
                        std::cin >> DeleteConfirmation;
                        if (DeleteConfirmation == 'y'){
                            if (DeleteRegistryKeyInCurrentUser(AutoRun, name.c_str())){
                                std::cout << "�����ɹ�!";
                            }
                            else{
                                std::cerr << "����ʧ��!";
                            }
                        }
                        else{
                            std::cout << "������ȡ��!";
                            break;
                        }
                        Sleep(2000);
                        std::system("cls");
                        break;
                    }
                }
                else if (path == "HKLM"){
                    int index = 0;
                    std::cout << "������Ҫ�޸ĵ����: ";
                    std::cin >> index;
                    if (index > hklmItems.size())
                        std::cerr << "���벻�Ϸ�, ����������!" << std::endl;
                    else {
                        // ������������
                        std::string name;
                        for (auto &i : hklmItems)
                            if (i.index == index){
                                name = i.name;
                                break;
                            }
                        char DeleteConfirmation;
                        std::cout << "ɾ��ע��������һ������, ȷ��ɾ����? (y = yes, n = no): ";
                        std::cin >> DeleteConfirmation;
                        if (DeleteConfirmation == 'y'){
                            if (DeleteRegistryKeyInLocalMachine(AutoRun, name.c_str())){
                                std::cout << "�����ɹ�!";
                            }
                            else{
                                std::cerr << "����ʧ��!";
                            }
                        }
                        else{
                            std::cout << "������ȡ��!";
                            break;
                        }
                        Sleep(2000);
                        std::system("cls");
                        break;
                    }
                }
                else{
                    std::cout << "���벻�Ϸ�, ����������!" << std::endl;
                    Sleep(2000);
                    std::system("cls");
                }
                break;
            }
        }
        else if (choice == "C"){
            std::cout << "�������½��������λ��(��֧�� HKCU �� HKLM ��������): ";
            std::cin >> path;
            if (path == "HKCU"){
                std::string name, value;
                std::cout << "�������¼�ֵ������(�Ƽ�ȫӢ��): ";
                std::cin >> name;
                while (true){
                    std::cout << "�������¼�ֵ������(ȫ·�� + �ļ���): ";
                    std::cin >> value;
                    if (value.find("\\") == EOF){
                        std::cout << "�������ݲ��Ϸ�, ����������!" << std::endl;
                    }
                    else{
                        break;
                    }
                }
                if (SetRegisterKeyInCurrentUser(AutoRun, name.c_str(), value.c_str())){
                    std::cout << "�����ɹ�!";
                }
                else{
                    std::cerr << "����ʧ��!";
                }
                Sleep(2000);
                std::system("cls");
            }
            else if (path == "HKLM"){
                std::string name, value;
                std::cout << "�������¼�ֵ������(�Ƽ�ȫӢ��): ";
                std::cin >> name;
                while (true){
                    std::cout << "�������¼�ֵ������(ȫ·�� + �ļ���): ";
                    std::cin >> value;
                    if (value.find("\\") == EOF){
                        std::cout << "�������ݲ��Ϸ�, ����������!" << std::endl;
                    }
                    else{
                        break;
                    }
                }
                if (SetRegisterKeyInLocalMachine(AutoRun, name.c_str(), value.c_str())){
                    std::cout << "�����ɹ�!";
                }
                else{
                    std::cerr << "����ʧ��!";
                }
                Sleep(2000);
                std::system("cls");
            }
            else{
                std::cout << "���벻�Ϸ�, ����������!" << std::endl;
                Sleep(2000);
                std::system("cls");
            }
        }
        else if (choice == "E")
            break;
    }
    return 0;
}
