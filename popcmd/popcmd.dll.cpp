// popcmd.dll.cpp
#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        WinExec("cmd.exe", SW_SHOW);  // Pops visible cmd window
    }

    return TRUE;
}
