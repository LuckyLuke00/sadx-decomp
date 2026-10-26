#include "decls.h"
struct FUN_00924db0_t;
struct MC_AudioSystemFactory * __fastcall FUN_00924b10(struct MC_AudioSystemFactory *param_1, int param_2);
struct MC_AudioSystemFactory;

// STUB: SADX 0x00924ae0
void __fastcall FUN_00924ae0(MC_AudioSystemFactory *param_1, int param_2)
{
}

// STUB: SADX 0x00924b10
struct MC_AudioSystemFactory * __fastcall FUN_00924b10(struct MC_AudioSystemFactory *param_1, int param_2)
{
	return (struct MC_AudioSystemFactory *)0;
}

// STUB: SADX 0x00924b40
int __fastcall FUN_00924b40(struct MC_AudioSystemFactory *param_1)
{
	return (int)0;
}

// STUB: SADX 0x00924d50
int __fastcall FUN_00924d50(int *param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x00924db0
int __fastcall FUN_00924db0(FUN_00924db0_t *param_1, int param_2)
{
	return (int)0;
}

// FUNCTION: SADX 0x00924eb0
char __fastcall FUN_00924eb0(int param_1)
{
	return *(char *)(param_1 + 0xb8);
}

// FUNCTION: SADX 0x00924ec0
void __fastcall FUN_00924ec0(int param_1)
{
	int var1 = *(int *)(param_1 + 8);
	if (var1 != 0)
	{
		(*(void (__stdcall **)(int))(*(int *)var1 + 0x20))(var1);
	}
	*(int *)(param_1 + 8) = 0;
}
