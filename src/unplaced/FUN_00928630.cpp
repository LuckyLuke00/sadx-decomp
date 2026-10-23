#include "decls.h"
#include <stdio.h>
#include <windows.h>

// STUB: SADX 0x00928630
int __fastcall FUN_00928630(struct SADX_file *param_1, int param_2, int param_3)
{
	return (int)0;
}

// STUB: SADX 0x00928680
int __fastcall FUN_00928680(int *param_1, int param_2, void *param_3, int param_4, int *param_5)
{
	return (int)0;
}

// STUB: SADX 0x009286c0
int __fastcall FUN_009286c0(int param_1, void *param_2, size_t param_3, size_t *param_4)
{
	return (int)0;
}

// STUB: SADX 0x00928700
int FUN_00928700(FILE **param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x00928720
int FUN_00928720(void *param_1)
{
	return (int)(DeleteFileA((LPCSTR)(*(void **)((char *)param_1 + 0x14) >= (void *)0x10 ? *(void **)param_1 : param_1)) != 0);
}

// STUB: SADX 0x00928740
int FUN_00928740()
{
	return (int)0;
}
