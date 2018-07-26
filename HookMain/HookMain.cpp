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

    // KeyHook.dll 로딩
	hDll = LoadLibraryA("c:\\KeyHook.dll");
    if( hDll == NULL )
    {
        printf("LoadLibrary(%s) failed!!! [%d]", "KeyHook.dll", GetLastError());
        return;
    }

    // export 함수 주소 얻기
	HookStart = (PFN_HOOKSTART)GetProcAddress(hDll, "HookStart");
	HookStop = (PFN_HOOKSTOP)GetProcAddress(hDll, "HookStop");

    // 후킹 시작
	HookStart();

    // 사용자가 'q' 를 입력할 때까지 대기
	printf("press 'q' to quit!\n");
	while( _getch() != 'q' )	;

    // 후킹 종료
	HookStop();
	
    // KeyHook.dll 언로딩
	FreeLibrary(hDll);
}