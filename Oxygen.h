#ifndef Oxygen_H
#define Oxygen_H

#pragma once
#pragma GCC optimize(2)

#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <windows.h>
#include <stdexcept>
#include <array>
#include <memory>

using std::cin;
using std::cout;
using std::endl;
using std::stoi;
using std::to_string;
using std::stoll;
using std::stold;
using std::sqrt;
using std::cbrt;
using std::memset;

using LL = long long;
using ULL = unsigned long long;
using LD = long double;

typedef std::pair<int, int> PII;

#define gcd std::__gcd
#define let auto
#define constant const
using Boolean = bool;

#define HKCU HKEY_CURRENT_USER
#define HKLM HKEY_LOCAL_MACHINE

#include <shobjidl.h>
#include <objbase.h>
#include <shlguid.h>

#include <commdlg.h> // CompileLine += "-lcomdlg32"

constexpr auto AutoRun = "Software\\Microsoft\\Windows\\Currentversion\\Run";
constexpr auto ExplorerOptions = "Software\\Microsoft\\Windows\\Currentversion\\Policies\\Explorer";
constexpr auto SystemTools = "Software\\Microsoft\\Windows\\Currentversion\\Policies\\System";
constexpr auto Execution = "Software\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options";
#define SLDF_HASLINKNAME 0x00000001
#define SLDF_HASWORKINGDIR 0x00000002
#define SLDF_HASARGS 0x00000004
#define SLDF_RUNAS_USER 0x00000008

constexpr LD percent90 = 2.706;
constexpr LD percent95 = 3.841;
constexpr LD percent99 = 6.635;
constexpr LD percent999 = 10.828;
constexpr LD e = 2.7182818284590452353602874713527;
constexpr LD sqrt2 = 1.4142135623730950488016887242097;
constexpr LD sqrt3 = 1.7320508075688772935274463415059;
constexpr LD sqrt5 = 2.2360679774997896964091736687313;
constexpr LD sqrt6 = 2.4494897427831780981972840747059;
constexpr LD sqrt7 = 2.6457513110645905905016157536393;
constexpr LD pi = 3.1415926535897932384626433832795;

// EasyX
// #include <graphics.h>
// #define color settextcolor
// #define out outtextxy

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib");

#include <Shellapi.h>

struct Clock{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int CurrentDay;
	Clock(){
		std::time_t currentTime = std::time(nullptr);
        std::tm* localTime = std::localtime(&currentTime);
		
		year = localTime -> tm_hour + 1900, month = localTime -> tm_mon + 1, day = localTime -> tm_mday;
		hour = localTime -> tm_hour, minute = localTime -> tm_min, second = localTime -> tm_sec;
		CurrentDay = localTime -> tm_yday;
		
	}
};

#include <tlhelp32.h>

namespace Oxygen{    
    ULL fact(int n);

    int random(int start, int end);

    ULL C(ULL a, ULL b);

    ULL A(ULL a, ULL b);

    int lcm(int a, int b);

    PII frac(int a, int b);

    void print(std::string type, int w_t);

    void PrintColor(std::string type);

	bool is_prime(LL n);

    LL pow(LL a, LL b);

    LD Dpow(LD a, LD b);

    bool isminus(char a);

    bool isminus(std::string a);

    void OpenWeb(const char* url);

    void OpenProcedure(char* file);

    void EditFile(char* file);

    char* StringToChar(std::string str);

    LD check(LD a);

    void OutputTime(std::ostream& ofs);

    void OutputTime();
	
    // Windows API
	void OpenApplication(const char* file);

    void CopyFiles(const char* FileOrigin, const char* FileDestination, bool IfCoveredWhenExist);

    bool KillProcess(const std::string& ImageName);

    bool SetRegisterKeyInCurrentUser(const char* subKey, const char* valueName, const char* filePath);

    bool SetRegisterKeyInLocalMachine(const char* subKey, const char* valueName, const char* filePath);

    std::string GetRegisterKeyValueInCurrentUser(std::string path, std::string name);

    std::string GetRegisterKeyValueInLocalMachine(std::string path, std::string name);

    std::string GetLocation();

    bool ModifyRegisterKeyValueInCurrentUser(std::string path, std::string name, std::string value);

    bool ModifyRegisterKeyValueInLocalMachine(std::string path, std::string name, std::string value);

    bool DeleteRegistryKeyInCurrentUser(const char* subKey, const char* valueName);

    bool DeleteRegistryKeyInLocalMachine(const char* subKey, const char* valueName);

    bool AddAutoRun(std::string path, std::string name, std::string value);

    bool AddExplorerRestrict(std::string path, std::string name);

    bool DeleteFiles(std::string file);

    void Command(const char* procedure, char *file);

    bool IsProcessRunning(const char* processName);

    bool CreateLNK(std::string FileName, std::string Description, std::string IconPath, std::string TargetPath);

    bool OpenApplicationAsAdmin(const char* file);

    std::string CatchResultOfConsole(const char* command);

    std::string OpenFileWindow();
}

#endif
