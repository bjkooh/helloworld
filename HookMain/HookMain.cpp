#include "stdio.h"
#include "conio.h"
#include "windows.h"

typedef void (*PFN_HOOKSTART)();
typedef void (*PFN_HOOKSTOP)();

void main()
{
	HMODULE			hDll = NULL;
	PFN_HOOKSTART	HookStart = NULL;
	PFN_HOOKSTOP	HookStop = NULL;
	char			ch = 0;

    // KeyHook.dll �ε�
	hDll = LoadLibraryA("c:\\KeyHook.dll");
    if( hDll == NULL )
    {
        printf("LoadLibrary(%s) failed!!! [%d]", "KeyHook.dll", GetLastError());
        return;
    }

    // export �Լ� �ּ� ���
	HookStart = (PFN_HOOKSTART)GetProcAddress(hDll, "HookStart");
	HookStop = (PFN_HOOKSTOP)GetProcAddress(hDll, "HookStop");

    // ��ŷ ����
	HookStart();

    // ����ڰ� 'q' �� �Է��� ������ ���
	printf("press 'q' to quit!\n");
	while( _getch() != 'q' )	;

    // ��ŷ ����
	HookStop();
	
    // KeyHook.dll ��ε�
	FreeLibrary(hDll);
}