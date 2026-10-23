#include "decls.h"
#include <windows.h>
int FUN_00422bb0(void);

// STUB: SADX 0x004227d0
LRESULT __stdcall FUN_004227d0(HWND param_1, UINT param_2, WPARAM param_3, LPARAM param_4)
{
	return (LRESULT)0;
}

// FUNCTION: SADX 0x004229f0
void FUN_004229f0(void)
{
	int local_8;
	SystemParametersInfoA(0x11, 0, &local_8, 0);
}

// STUB: SADX 0x00422a10
void FUN_00422a10(void)
{
}

// STUB: SADX 0x00422a30
void FUN_00422a30(void)
{
}

// STUB: SADX 0x00422b20
void FUN_00422b20(void)
{
}

// STUB: SADX 0x00422b50
void FUN_00422b50(void)
{
}

// FUNCTION: SADX 0x00422ba0
void FUN_00422ba0(void)
{
	FUN_00422b50();
	exit(0);
}

// STUB: SADX 0x00422bb0
int FUN_00422bb0(void)
{
	return (int)0;
}

// STUB: SADX 0x00422df0
void G_DestroyGameLoadThread()
{
}

// FUNCTION: SADX 0x00422e20
void FUN_00422e20(void *param_1)
{
	_gjExecServer();
}
