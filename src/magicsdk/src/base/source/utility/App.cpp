#include "decls.h"
void FUN_00403bb0(int param_1, int param_2, int param_3, int param_4);
void FUN_00406150(void *param_1);

// STUB: SADX 0x00406150
void FUN_00406150(void *param_1)
{
}

// FUNCTION: SADX 0x00406210
__declspec(naked) int __fastcall FUN_00406210(int param_1)
{
	__asm
	{
		cmp dword ptr [eax + 0x14], 0x10
		mov edx, dword ptr [eax + 0x10]
		jb short loc1
		mov eax, dword ptr [eax]
		loc1:
		push edx
		push eax
		mov eax, dword ptr [ecx + 0x10]
		push eax
		push 0
		call FUN_00403bb0
		xor ecx, ecx
		test eax, eax
		sets al
		ret
	}
}
