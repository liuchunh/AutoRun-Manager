#include "Oxygen.h"

namespace Oxygen{   
    /**
     * @brief 计算 n 的阶乘
     * 
     * @param n 
     * @return Unsigned long long
     */
    ULL fact(int n){
        if (n == 1)
            return 1;
        if (n == 0)
            return 0;
        return fact(n - 1) * n;
    }

    /**
     * @brief 生成一个从 start 到 end 的随机数
     * 
     * @param start 
     * @param end 
     * @return int 
     */
    int random(int start, int end){
        srand((unsigned int)time(NULL));
		int num = rand()%(end - start + 1) + start;
		return num;
	}

    ULL C(ULL a, ULL b){
        ULL ans = 1;
        if (a == b)
            return fact(a);
        if ((b - a) > a){
            for (int i = b - a + 1; i <= b; i ++)
                ans *= i;
                return ans / fact(a);
        }
        else if (b - a == a){
            int lower = 1, upper = 1;
            for (int i = 1; i <= a; i ++)
                lower *= i;

            for (int i = a + 1; i <= b; i ++)
                upper *= i;
            return upper / lower;
        }
        else{
            for (int i = a + 1; i <= b; i ++){
                ans *= i;
                return ans / fact(b - a);
            }
        }
		return ans;
    }

    ULL A(ULL a, ULL b){
        ULL ans = 1;
        if (a == b)
            return fact(a);
        for (int i = b - a + 1; i <= b; i ++){
            ans *= i;
        }
        return ans;
    }

    int lcm(int a, int b){
        return a * b / gcd(a, b);
    }

    // 两个参数 分别是分子和分母 返回依然是两个数
    PII frac(int a, int b){
        int temp = gcd(a, b);
        a /= temp, b /= temp;
        PII result = {a, b};
        return result;
    }
	
    // 延时输出 
	void print(std::string out, int w_t){
		int wait_time = w_t;
		for (int i = 0;i < out.size();i ++){
			if (GetAsyncKeyState(VK_RETURN)) wait_time = 0;
			if (out[i] != '\n') cout << out[i];
			else cout << '\n';
			Sleep(wait_time);
		}
	}

    // 除了一些普通的颜色之外 \
    还有 reseda 浅绿色 bluish 浅蓝色 reddish 浅红色 lavender 淡紫色 FaintYellow 淡黄色
    void PrintColor(std::string type){
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);   
        int target = 0;
        if (type == "black")
            target = 0;
        else if (type == "blue")
            target = 1;
        else if (type == "green")
            target = 2;
        else if (type == "reseda") // 浅绿色
            target = 3;
        else if (type == "red")
            target = 4;
        else if (type == "purple")
            target = 5;
        else if (type == "yellow")
            target = 6;
        else if (type == "white")
            target = 7;
        else if (type == "gray")
            target = 8;
        else if (type == "bluish"){ // 浅蓝色
            target = 9;
        }
        else if (type == "reddish"){ // 浅红色
            target = 12;
        }
        else if (type == "lavender"){ // 淡紫色
            target = 13;
        }
        else if (type == "FaintYellow"){ // 淡黄色
            target = 14;
        }
        else{ // 未知颜色全部用亮白色
            target = 15;
        }
        SetConsoleTextAttribute(hOut, target);
    } 
	
    /**
     * @brief 判断一个数是否为质数
     * 
     * @param n 
     * @return true 
     * @return false 
     */
	bool is_prime(LL n){
        if (n <= 0)
            return false;
		LL temp = std::sqrt(n);
		for (LL i = 2; i <= temp; i ++ ){
			if (n % i == 0){
				return false;
			}
		}	
		return true;
	}

    /**
     * @brief 计算 a 的 b 次方
     * 
     * @param a 
     * @param b 
     * @return result
     */
    LL pow(LL a, LL b){
        if (a == 0 && b == 0){
            throw std::runtime_error("Syntax Error!");
            return 0;
        }
        if (b == 0 && a != 0){
            return 1;
        }

        LL res = 1;
        for (int i = 1; i <= b; i ++){
            res *= a;
        }

        return res;

    }
    
    // Double 类型的pow函数
    LD Dpow(LD a, LD b){
        if (a == 0 && b == 0){
            throw std::runtime_error("Syntax Error!");
            return 0;
        }
        if (b == 0 && a != 0){
            return 1;
        }

        LD res = 1;
        for (LD i = 1; i <= b; i ++){
            res *= a;
        }

        return res;
    }

    bool isminus(char a){
        if (a == '-')
            return true;
        return false;
    }

    bool isminus(std::string a){
        if (a == "-")
            return true;
        return false;
    }

    /**
     * @brief 打开 url(参数) 对应的网站
     * 
     * @param url 
     */
    void OpenWeb(const char* url){
        HINSTANCE result = ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
    }

    // void OpenProcedure(char* file){
    //     // 定义并初始化 PROCESS_INFORMATION 和 STARTUPINFO 结构体
    //     PROCESS_INFORMATION pi;
    //     STARTUPINFO si;
    //     ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    //     ZeroMemory(&si, sizeof(STARTUPINFO));
    //     si.cb = sizeof(STARTUPINFO);

    //     // 可执行文件的路径和命令行参数
    //     LPCTSTR lpApplicationName = file;
    //     LPTSTR lpCommandLine = NULL;

    //     // 调用 CreateProcess 函数创建新进程
    //     BOOL bResult = CreateProcess(lpApplicationName, lpCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

    //     if (bResult == FALSE){
    //         cout << "CreateProcess failed!" << endl;
    //         return;
    //     }

    //     // 等待新进程结束
    //     // WaitForSingleObject(pi.hProcess, INFINITE);

    //     // 关闭进程和线程的句柄
    //     CloseHandle(pi.hProcess);
    //     CloseHandle(pi.hThread);

    // }

    /**
     * @brief 用 notepad.exe 打开 file 所指的文件
     * 
     * @param file 
     */
    void OpenProcedure(char* file){
        ShellExecute(NULL, "open", "notepad.exe", file, NULL, SW_SHOW);
    }

    /**
     * @brief 用 notepad.exe 打开 file 所指的文件
     * 
     * @param file 
     */
    void EditFile(char* file){
        STARTUPINFO si = { sizeof(si) };
        PROCESS_INFORMATION pi;

        std::string TempStr;
        TempStr.assign(file);

        LPSTR lpstr = reinterpret_cast<LPSTR>(file);

        if (CreateProcess("C:\\Windows\\System32\\notepad.exe", lpstr, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            cout << "Success to open " << TempStr;
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        } 
        else {
            std::cerr << "Failed to open " << TempStr;
        }
    }

    /**
     * @brief 将 std::string 类型的数据转换为 char*
     * 
     * @param str 
     * @return char* 
     */
    char* StringToChar(std::string str) {
        // 获取const char*类型的数据
        const char* data = str.c_str();

        // 计算数据长度并创建新的char*数组
        size_t dataSize = std::strlen(data);
        char* newData = new char[dataSize + 1];

        // 复制数据到新的数组中
        std::strcpy(newData, data);

        // 返回新的数组
        return newData;
    }

    LD check(LD a){
        if (a < percent90){
            return -1; // 说明没有关系
        }
        else if (a > percent90 && a < percent95){
            return 90;
        }
        else if (a > percent95 && a < percent99){
            return 95;
        }
        else if (a > percent99 && a < percent999){
            return 99;
        }
        else if (a > percent999)
            return 99.9;
        else return -1; // 不可能触发的捏 只是防止Warning
    }
    
	bool isdigit(char a){
		if (a >= '0' && a <= '9')
			return true;
		return false;
	}
	
	bool isdigit(std::string str){
		int len = str.length();
		for (int i = 0; i < len; i ++ ){
			if (!Oxygen::isdigit(str[i]))
				return false;
		}
		
		return true;
	}
	
    void Average(){
        std::string input;
        int count = 0;
        LD data = 0, sum = 0;
        cout << "Entered Average Mode......" << endl;
        while (cin >> input, input != "end" && isdigit(input)){
        	data = stold(input);
        	sum += data;
        	count ++;
		}
		
		cout << "Average is: " << std::setprecision(6) << sum / count << ", Amount is: " << count << endl;
		
		cout << "Exited Average Mode......" << endl;
		return;
    }

    /**
     * @brief 把此时的时间输出到 ofs 指定的文件中
     * 
     * @param ofs 
     */
    void OutputTime(std::ostream& ofs){
        std::time_t currentTime = std::time(nullptr);
        std::tm* localTime = std::localtime(&currentTime);

        std::string year = std::to_string(localTime -> tm_year + 1900);
        std::string month = std::to_string(localTime -> tm_mon + 1);
        std::string day = std::to_string(localTime -> tm_mday);
        std::string hour = std::to_string(localTime -> tm_hour);

        ofs << year << "/" << month << "/" << day << " " << hour << ":";

        int min = localTime -> tm_min;
        int sec = localTime -> tm_sec;

        std::string minute, second;

        if (min < 10)
            minute = "0";
        if (sec < 10)
            second = "0";

        minute += std::to_string(min); second += std::to_string(sec);

        ofs << minute << ":" << second; 
    }
        
    /**
     * @brief 把当前时间输出到控制台
     * 
     */
    void OutputTime(){
        std::time_t currentTime = std::time(nullptr);
        std::tm* localTime = std::localtime(&currentTime);

        std::cout << localTime -> tm_year + 1900 << "/" << localTime -> tm_mon + 1 << "/" << localTime -> tm_mday << " " << localTime -> tm_hour << ":";

        int min = localTime -> tm_min;
        int sec = localTime -> tm_sec;

        std::string minute, second;

        if (min < 10)
            minute = "0";
        if (sec < 10)
            second = "0";

        minute += std::to_string(min), second += std::to_string(sec);

        std::cout << minute << ":" << second; 
    }
	
    /**
     * @brief 打开 file 所指的文件
     * 
     * @param file 
     */
	void OpenApplication(const char* file){
		ShellExecute(NULL, "open", file, NULL, NULL, SW_SHOWNORMAL);
	}
    
    /**
     * @brief 把 FileOrigin 拷贝到 FileDestination
     * 
     * @param FileOrigin 要拷贝的文件, 要求是路径带文件名
     * @param FileDestination 拷贝的终点, 同样是路径带文件名
     * @param IfCoveredWhenExist 当 IfCoveredWhenExist 为 True 时, 即 当同名文件存在时, 不覆盖, 反之亦然
     */
    void CopyFiles(const char* FileOrigin, const char* FileDestination, bool IfCoveredWhenExist){
        CopyFile(FileOrigin, FileDestination, IfCoveredWhenExist);
    }

    /**
     * @brief 结束 ImageName 所指的进程
     * 
     * @param ImageName 映像名字
     * @return true 
     * @return false 
     */
    bool KillProcess(const std::string& ImageName) {
        std::string lowerName = ImageName;
        std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

        HANDLE hProcessSnap;
        PROCESSENTRY32 pe32;

        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hProcessSnap == INVALID_HANDLE_VALUE) {
            return false;
        }

        pe32.dwSize = sizeof(PROCESSENTRY32);

        if (!Process32First(hProcessSnap, &pe32)) {
            CloseHandle(hProcessSnap);
            return false;
        }

        do {
            std::string processName = pe32.szExeFile;
            std::transform(processName.begin(), processName.end(), processName.begin(), ::tolower);

            if (lowerName == processName) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
                if (hProcess != NULL) {
                    TerminateProcess(hProcess, 0);
                    CloseHandle(hProcess);
                }
            }
        } while (Process32Next(hProcessSnap, &pe32));

        CloseHandle(hProcessSnap);
        return true;
    }

    /**
     * @brief Set the Register Key In Current User object
     * 
     * @param subKey Registry Key Path
     * @param valueName Register Key Name
     * @param filePath value
     * @return true 
     * @return false 
     */
    bool SetRegisterKeyInCurrentUser(const char* subKey, const char* valueName, const char* filePath) {
        HKEY hKey;
        
        // 打开或创建注册表子项
        long result = RegCreateKeyExA(HKEY_CURRENT_USER, subKey, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr, &hKey, nullptr);
        if (result != ERROR_SUCCESS) {
            return false;  // 注册表操作失败
        }

        // 写入键值数据
        result = RegSetValueExA(hKey, valueName, 0, REG_SZ, reinterpret_cast<const BYTE*>(filePath), static_cast<DWORD>(strlen(filePath) + 1));
        if (result != ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return false;  // 注册表操作失败
        }

        // 关闭注册表键句柄
        RegCloseKey(hKey);

        return true;  // 成功完成注册表操作
    }

    /**
     * @brief Set the Registry Key In Local Machine object
     * 
     * @param subKey Registry Key Path
     * @param valueName Register Key Name
     * @param filePath value
     * @return true 
     * @return false 
     */
    bool SetRegisterKeyInLocalMachine(const char* subKey, const char* valueName, const char* filePath) {
        HKEY hKey;
        
        // 打开或创建注册表子项
        long result = RegCreateKeyExA(HKEY_LOCAL_MACHINE, subKey, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr, &hKey, nullptr);
        if (result != ERROR_SUCCESS) {
            return false;  // 注册表操作失败
        }

        // 写入键值数据
        result = RegSetValueExA(hKey, valueName, 0, REG_SZ, reinterpret_cast<const BYTE*>(filePath), static_cast<DWORD>(strlen(filePath) + 1));
        if (result != ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return false;  // 注册表操作失败
        }

        // 关闭注册表键句柄
        RegCloseKey(hKey);

        return true;  // 成功完成注册表操作
    }
    
    /**
     * @brief 获取 HKCU 中的注册表键值
     * 
     * @param path 要获取的注册表键值路径
     * @param name 名字
     * @return value (std::string)
    */
    std::string GetRegisterKeyValueInCurrentUser(std::string path, std::string name) {
        HKEY hKey;
        std::string value;

        if (RegOpenKeyExA(HKEY_CURRENT_USER, path.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
            DWORD dataSize = 1024;
            char data[1024];
            DWORD type;

            if (RegQueryValueExA(hKey, name.c_str(), NULL, &type, (LPBYTE)data, &dataSize) == ERROR_SUCCESS) {
                value = std::string(data);
            }

            RegCloseKey(hKey);
        }

        return value;
    }

    /**
     * @brief 获取 HKLM 中的注册表键值
     * 
     * @param path 要获取的注册表键值路径
     * @param name 名字
     * @return value (std::string)
    */
    std::string GetRegisterKeyValueInLocalMachine(std::string path, std::string name) {
        HKEY hKey;
        std::string value;

        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, path.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
            DWORD dataSize = 1024;
            char data[1024];
            DWORD type;

            if (RegQueryValueExA(hKey, name.c_str(), NULL, &type, (LPBYTE)data, &dataSize) == ERROR_SUCCESS) {
                value = std::string(data);
            }

            RegCloseKey(hKey);
        }

        return value;
    }

    /**
     * @brief Get Location of procedure
     * 
     * @return Location (std::string)
    */
    std::string GetLocation(){
        char buffer[MAX_PATH];
        GetModuleFileName(NULL, buffer, MAX_PATH);
        PathRemoveFileSpec(buffer);
        std::string CurrentDir(buffer);

        return CurrentDir;
    }

    /**
     * @brief 将注册表 HKCU 中 path 路径的名为 name 的注册表键值改为 value
     * 
     * @param path 要修改的注册表键值的路径
     * @param name 名字
     * @param value 修改后的键值
     * @return true 
     * @return false 
     */
    bool ModifyRegisterKeyValueInCurrentUser(std::string path, std::string name, std::string value) {
        HKEY hKey;
        
        if (RegOpenKeyExA(HKEY_CURRENT_USER, path.c_str(), 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
            if (RegSetValueExA(hKey, name.c_str(), 0, REG_SZ, (const BYTE*)value.c_str(), (DWORD)(value.length() + 1)) == ERROR_SUCCESS) {
                RegCloseKey(hKey);
                return true;
            }
            
            RegCloseKey(hKey);
        }
        
        return false;
    }

    /**
     * @brief 将注册表 HKLM 中 path 路径的名为 name 的注册表键值改为 value
     * 
     * @param path 要修改的注册表键值的路径
     * @param name 名字
     * @param value 修改后的键值
     * @return true 
     * @return false 
     */
    bool ModifyRegisterKeyValueInLocalMachine(std::string path, std::string name, std::string value) {
        HKEY hKey;
        
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, path.c_str(), 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
            if (RegSetValueExA(hKey, name.c_str(), 0, REG_SZ, (const BYTE*)value.c_str(), (DWORD)(value.length() + 1)) == ERROR_SUCCESS) {
                RegCloseKey(hKey);
                return true;
            }
            
            RegCloseKey(hKey);
        }
        
        return false;
    }

    /**
     * @brief 删除 HKCU 中 subKey 路径下的 valueName
     * 
     * @param subKey 路径
     * @param valueName 注册表项的名字
     * @return true 
     * @return false 
     */
    bool DeleteRegistryKeyInCurrentUser(const char* subKey, const char* valueName) {
        HKEY hKey;
        
        // 打开注册表子项
        long result = RegOpenKeyExA(HKEY_CURRENT_USER, subKey, 0, KEY_WRITE, &hKey);
        if (result != ERROR_SUCCESS) {
            return false;  // 注册表操作失败
        }

        // 删除键值数据
        result = RegDeleteValueA(hKey, valueName);
        if (result != ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return false;  // 注册表操作失败
        }

        // 关闭注册表键句柄
        RegCloseKey(hKey);

        return true;  // 成功完成注册表操作
    }

    /**
     * @brief 删除 HKLM 中 subKey 路径下的 valueName
     * 
     * @param subKey 路径
     * @param valueName 注册表项的名字
     * @return true 
     * @return false 
     */
    bool DeleteRegistryKeyInLocalMachine(const char* subKey, const char* valueName) {
        HKEY hKey;
        
        // 打开注册表子项
        long result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, subKey, 0, KEY_WRITE, &hKey);
        if (result != ERROR_SUCCESS) {
            return false;  // 注册表操作失败
        }

        // 删除键值数据
        result = RegDeleteValueA(hKey, valueName);
        if (result != ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return false;  // 注册表操作失败
        }

        // 关闭注册表键句柄
        RegCloseKey(hKey);

        return true;  // 成功完成注册表操作
    }

    /**
     * @brief 添加自启项, path 仅限 HKCU 和 HKLM
     * 
     * @param path 限制为 HKCU 和 HKLM, 分别在 HKCU 和 HKLM 添加键值
     * @param name 自启项的名字
     * @param value 自启项的键值
     * @return true 
     * @return false 
     */
    bool AddAutoRun(std::string path, std::string name, std::string value){
        bool result = false;
        if (path == "HKCU" || path == "HKEY_CURRENT_USER"){
            result = SetRegisterKeyInCurrentUser(AutoRun, name.c_str(), value.c_str());
        }
        else if (path == "HKLM" || path == "HKEY_LOCAL_MACHINE"){
            result = SetRegisterKeyInLocalMachine(AutoRun, name.c_str(), value.c_str());
        }

        return result;
    }

    /**
     * @brief 添加 Explorer.exe 的限制项 默认键值为 1
     * 
     * @param path 限制为 HKCU 和 HKLM, 分别在 HKCU 和 HKLM 添加键值
     * @param name 限制项的名字
     * @return true 
     * @return false 
     */
    bool AddExplorerRestrict(std::string path, std::string name){
        bool result = false;
        if (path == "HKCU" || path == "HKEY_CURRENT_USER"){
            result = SetRegisterKeyInCurrentUser(AutoRun, name.c_str(), "1");
        }
        else if (path == "HKLM" || path == "HKEY_LOCAL_MACHINE"){
            result = SetRegisterKeyInLocalMachine(AutoRun, name.c_str(), "1");
        }
        return result;
    }

    /**
     * @brief 删除指定的文件
     * 
     * @param file 指定的文件
     * @return true
     * @return false
     */
    bool DeleteFiles(std::string file) {
        const char* filename = file.c_str();
        if (std::remove(filename) != 0) {
            return false;
        } else {
            return true;
        }
    }
    /**
     * @brief 表示对 procedure 程序执行 file 命令行,
     * 
     * Eg. 比如说我想对 D:\\Compiler.exe 执行 "-f Tester.cpp", 那么就可以调用 Command("D:\\Compiler.exe", " -f Tester.cpp");
     * 
     * @param procedure 
     * @param file 
     */
    void Command(const char* procedure, char *file){
        STARTUPINFO si = {sizeof(si)};
        PROCESS_INFORMATION pi;

        std::string TempStr;
        TempStr.assign(file);

        LPSTR lpstr = reinterpret_cast<LPSTR>(file);

        if (CreateProcess(procedure, lpstr, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
    }

    /**
     * @brief 检测进程是否存在
     * 
     * @param processName 映像名字
     * @return true 
     * @return false 
     */
    bool IsProcessRunning(const char* processName) {
        HANDLE hProcessSnap;
        PROCESSENTRY32 pe32;

        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hProcessSnap == INVALID_HANDLE_VALUE) {
            return false;
        }

        pe32.dwSize = sizeof(PROCESSENTRY32);

        if (!Process32First(hProcessSnap, &pe32)) {
            CloseHandle(hProcessSnap);
            return false;
        }

        do {
            if (_stricmp(processName, pe32.szExeFile) == 0) {
                CloseHandle(hProcessSnap);
                return true;
            }
        } while (Process32Next(hProcessSnap, &pe32));

        CloseHandle(hProcessSnap);
        return false;
    }

    /**
     * @brief 创建一个名为 FileName 的快捷方式
     * 
     * @param FileName 
     * @param Description 
     * @param IconPath 
     * @param TargetPath 
     * @return true 
     * @return false 
     */
    bool CreateLNK(std::string FileName, std::string Description, std::string IconPath, std::string TargetPath) {
        CoInitialize(NULL);

        IShellLink* pShellLink;
        HRESULT hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&pShellLink);
        if (SUCCEEDED(hres)) {
            pShellLink->SetPath(TargetPath.c_str());
            pShellLink->SetDescription(Description.c_str());
            pShellLink->SetIconLocation(IconPath.c_str(), 0);

            IPersistFile* pPersistFile;
            hres = pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pPersistFile);
            if (SUCCEEDED(hres)) {
                std::wstring wsz = std::wstring(FileName.begin(), FileName.end());
                hres = pPersistFile->Save(wsz.c_str(), TRUE);
                pPersistFile->Release();
            }

            pShellLink->Release();
        }

        CoUninitialize();

        return SUCCEEDED(hres);
    }

    /**
     * @brief Open An Application with Admin Privileges.
     * 
     * @param file 
     * @return true
     * @return false
     */
    bool OpenApplicationAsAdmin(const char* file) {
        SHELLEXECUTEINFO shExecInfo = {0};
        shExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        shExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
        shExecInfo.hwnd = NULL;
        shExecInfo.lpVerb = "runas"; // This is what makes it run as admin
        shExecInfo.lpFile = file;
        shExecInfo.lpParameters = NULL;
        shExecInfo.lpDirectory = NULL;
        shExecInfo.nShow = SW_NORMAL;
        shExecInfo.hInstApp = NULL;

        return ShellExecuteEx(&shExecInfo);
    }

    /**
     * @brief Catch Output of a Console Application
     * 
     * @param command You can input the name of application.
     * @return std::string 
     */
    std::string CatchResultOfConsole(const char* command) {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }
    
    /**
     * @brief Open "Open File" Window
     * 
     * @return std::string
     */
    std::string OpenFileWindow(){
        OPENFILENAME ofn;       // 结构体用于保存文件对话框的信息
        char szFile[260];       // 用于保存选择的文件路径

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFile = szFile;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = "All Files\0*.*\0";
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        // 打开文件对话框
        GetOpenFileName(&ofn);

        std::string OpenFile(szFile);

        return OpenFile;
    }
}
