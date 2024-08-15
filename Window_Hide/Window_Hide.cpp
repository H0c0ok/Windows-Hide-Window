#include <iostream>
#include <Windows.h>
#include <string.h>

void HideWindow(HWND&);
std::string get_prog_name(const std::string&);


int main(uint8_t argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Usage: " << get_prog_name(argv[0]) << " <path_to_program>" << "\n";
        std::cout << "Warning: Works only for cli programs!" << "\n";
        return 1;
    }
    //Hiding self program window
    HWND CurWindow = GetConsoleWindow();
    HideWindow(CurWindow);
    
    //Setting params for target program window
    PROCESS_INFORMATION pi{};
    STARTUPINFOA inf = {sizeof(STARTUPINFOA)};
    ZeroMemory(&inf, sizeof(STARTUPINFOA));
    inf.dwFlags = STARTF_USESHOWWINDOW;
    inf.wShowWindow = SW_HIDE;
    
    BOOL CreationRes = CreateProcessA(
        (LPSTR)argv[1],
        NULL,
        NULL,
        NULL,
        FALSE,
        NULL,
        NULL,
        NULL,
        &inf,
        &pi
    );

    if(!CreationRes) { return 1; }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    WaitForSingleObject(pi.hProcess, INFINITE);
    return 0;
}

void HideWindow(HWND& to_hide) {
    ::ShowWindow(to_hide, SW_HIDE);
}

std::string get_prog_name(const std::string& path) {
    size_t last_backslash = path.find_last_of("\\");
    std::string pname = path.substr(last_backslash + 1);
    return pname;
}
