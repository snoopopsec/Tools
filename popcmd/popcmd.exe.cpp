// popcmd.exe.cpp
#include <windows.h>

int main() {
    WinExec("cmd.exe", SW_SHOW);  // Visible interactive cmd shell
    return 0;
}
