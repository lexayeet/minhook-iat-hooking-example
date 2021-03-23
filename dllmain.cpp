#include "pch.h"
decltype(&MessageBoxA) oMessageBoxA;

int hkMessageBoxA(HWND   hWnd,
    LPCSTR lpText,
    LPCSTR lpCaption,
    UINT   uType) {
    //you can do what you want, you can do alot of things. it's up to you.
    return oMessageBoxA(hWnd, "WARF WARF! we hijacked the flow!", lpCaption, uType); //we are just executing our original function that originally used by the program.
}

void InitializeHooks() {
	if (MH_Initialize() != MH_OK)
		return;

	MH_CreateHook(&MessageBoxA, hkMessageBoxA, (LPVOID*)&oMessageBoxA);
	MH_EnableHook(&MessageBoxA);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        InitializeHooks();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

