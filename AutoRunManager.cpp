#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "Oxygen.h"
using namespace Oxygen;

// 结构体用于存储注册表项信息
struct RegistryItem
{
    int index;
    std::string name;
    std::string value;
    std::string path;
};

// 函数用于读取注册表项
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

// 函数用于显示注册表项列表
void DisplayRegistryItems(const std::vector<RegistryItem> &items)
{
    for (const auto &item : items)
    {
        std::cout << "序号: " << item.index << ": Name: " << item.name << std::endl;
        std::cout << "        Value: " << item.value << std::endl;
        std::cout << "        Path: " << item.path << std::endl;
    }
}

// 函数用于修改注册表项
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

// 函数用于删除注册表项
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

// 函数用于新建注册表项
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

        // 调整 Wow6432NodeItems 中每个元素的序号
        for (auto& item : Wow6432NodeItems) {
            item.index += amount;
        }

        // 将调整好序号的 Wow6432NodeItems 插入到 hklmItems 末尾
        hklmItems.insert(hklmItems.end(), Wow6432NodeItems.begin(), Wow6432NodeItems.end());
        
        std::cout << "HKCU 自启项：" << std::endl;
        DisplayRegistryItems(hkcuItems);
        std::cout << "HKLM 自启项：" << std::endl;
        DisplayRegistryItems(hklmItems);

        std::string choice, path;
        std::cout << "请输入操作 (修改: M, 删除: D, 新建: C, 退出: E): ";
        std::cin >> choice;

        if (choice == "M"){
            while (true){
                std::cout << "请输入需要修改的路径(仅支持 HKCU 和 HKLM 两个输入): ";
                std::cin >> path;
                if (path == "HKCU"){
                    int index = 0;
                    std::string value;
                    std::cout << "请输入要修改的序号: ";
                    std::cin >> index;
                    if (index > hkcuItems.size())
                        std::cerr << "输入不合法, 请重新输入!" << std::endl;
                    else {
                        std::string name;
                        std::cout << "请输入修改后的键值: ";
                        std::cin >> value;
                        for (auto &i : hkcuItems)
                            if (i.index == index){
                                name = i.name;
                                break;
                            }
                        
                        if (ModifyRegisterKeyValueInCurrentUser(AutoRun, name, value))
                            std::cout << "操作成功!" << std::endl;
                        else
                            std::cerr << "操作失败!" << std::endl;
                        Sleep(2000);
                        std::system("cls");
                        break;
                    }
                }
                else if (path == "HKLM"){
                    int index = 0;
                    std::string value;
                    std::cout << "请输入要修改的序号: ";
                    std::cin >> index;
                    if (index > hklmItems.size()){
                        std::cerr << "输入不合法, 请重新输入!" << std::endl;
                    }
                    else {
                        std::string name;
                        std::cout << "请输入修改后的键值: ";
                        std::cin >> value;
                        for (auto &i : hklmItems)
                            if (i.index == index){
                                name = i.name;
                                break;
                            }
                        
                        if (ModifyRegisterKeyValueInLocalMachine(AutoRun, name, value))
                            std::cout << "操作成功!" << std::endl;
                        
                        else
                            std::cerr << "操作失败!" << std::endl;
                        
                        Sleep(2000);
                        std::system("cls");
                        break;
                    }
                }
                else{
                    std::cout << "输入不合法, 请重新输入!" << std::endl;
                    Sleep(2000);
                }
            }
        }
        else if (choice == "D"){
            while (true){
                std::cout << "请输入需要删除的路径(仅支持 HKCU 和 HKLM 两个输入): ";
                std::cin >> path;
                if (path == "HKCU") {
                    int index = 0;
                    std::cout << "请输入要修改的序号: ";
                    std::cin >> index;
                    if (index > hkcuItems.size())
                        std::cerr << "输入不合法, 请重新输入!" << std::endl;
                    else {
                        // 把名字整出来
                        std::string name;
                        for (auto &i : hkcuItems)
                            if (i.index == index){
                                name = i.name;
                                break;
                            }
                        char DeleteConfirmation;
                        std::cout << "删除注册表项存在一定风险, 确定删除吗? (y = yes, n = no): ";
                        std::cin >> DeleteConfirmation;
                        if (DeleteConfirmation == 'y'){
                            if (DeleteRegistryKeyInCurrentUser(AutoRun, name.c_str())){
                                std::cout << "操作成功!";
                            }
                            else{
                                std::cerr << "操作失败!";
                            }
                        }
                        else{
                            std::cout << "操作已取消!";
                            break;
                        }
                        Sleep(2000);
                        std::system("cls");
                        break;
                    }
                }
                else if (path == "HKLM"){
                    int index = 0;
                    std::cout << "请输入要修改的序号: ";
                    std::cin >> index;
                    if (index > hklmItems.size())
                        std::cerr << "输入不合法, 请重新输入!" << std::endl;
                    else {
                        // 把名字整出来
                        std::string name;
                        for (auto &i : hklmItems)
                            if (i.index == index){
                                name = i.name;
                                break;
                            }
                        char DeleteConfirmation;
                        std::cout << "删除注册表项存在一定风险, 确定删除吗? (y = yes, n = no): ";
                        std::cin >> DeleteConfirmation;
                        if (DeleteConfirmation == 'y'){
                            if (DeleteRegistryKeyInLocalMachine(AutoRun, name.c_str())){
                                std::cout << "操作成功!";
                            }
                            else{
                                std::cerr << "操作失败!";
                            }
                        }
                        else{
                            std::cout << "操作已取消!";
                            break;
                        }
                        Sleep(2000);
                        std::system("cls");
                        break;
                    }
                }
                else{
                    std::cout << "输入不合法, 请重新输入!" << std::endl;
                    Sleep(2000);
                    std::system("cls");
                }
                break;
            }
        }
        else if (choice == "C"){
            std::cout << "请输入新建自启项的位置(仅支持 HKCU 和 HKLM 两个输入): ";
            std::cin >> path;
            if (path == "HKCU"){
                std::string name, value;
                std::cout << "请输入新键值的名字(推荐全英文): ";
                std::cin >> name;
                while (true){
                    std::cout << "请输入新键值的数据(全路径 + 文件名): ";
                    std::cin >> value;
                    if (value.find("\\") == EOF){
                        std::cout << "输入数据不合法, 请重新输入!" << std::endl;
                    }
                    else{
                        break;
                    }
                }
                if (SetRegisterKeyInCurrentUser(AutoRun, name.c_str(), value.c_str())){
                    std::cout << "操作成功!";
                }
                else{
                    std::cerr << "操作失败!";
                }
                Sleep(2000);
                std::system("cls");
            }
            else if (path == "HKLM"){
                std::string name, value;
                std::cout << "请输入新键值的名字(推荐全英文): ";
                std::cin >> name;
                while (true){
                    std::cout << "请输入新键值的数据(全路径 + 文件名): ";
                    std::cin >> value;
                    if (value.find("\\") == EOF){
                        std::cout << "输入数据不合法, 请重新输入!" << std::endl;
                    }
                    else{
                        break;
                    }
                }
                if (SetRegisterKeyInLocalMachine(AutoRun, name.c_str(), value.c_str())){
                    std::cout << "操作成功!";
                }
                else{
                    std::cerr << "操作失败!";
                }
                Sleep(2000);
                std::system("cls");
            }
            else{
                std::cout << "输入不合法, 请重新输入!" << std::endl;
                Sleep(2000);
                std::system("cls");
            }
        }
        else if (choice == "E")
            break;
    }
    return 0;
}
