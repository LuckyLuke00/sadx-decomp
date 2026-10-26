#include "decls.h"
extern int DAT_00a5a974;
void FUN_00907d40();
extern int DAT_060ee5a0;

// FUNCTION: SADX 0x009094c0
int * FUN_009094c0()
{
	return &DAT_060ee5a0;
}

// FUNCTION: SADX 0x009096d0
void __fastcall FUN_009096d0(int *param_1)
{
	*param_1 = (int)&DAT_00a5a974;
	FUN_00907d40();
}

// STUB: SADX 0x009097a0
void __fastcall FUN_009097a0(int param_1)
{
}

// STUB: SADX 0x00909810
void __fastcall FUN_00909810(int param_1)
{
}

// FUNCTION: SADX 0x00909e30
void __fastcall FUN_00909e30(int param_1)
{
	if (*(int *)(param_1 + 0x24) != 0)
	{
		FUN_009097a0(*(int *)(param_1 + 0x24));
		return;
	}
}

// FUNCTION: SADX 0x00909e50
void __fastcall FUN_00909e50(int param_1)
{
	if (*(int *)(param_1 + 0x24) != 0)
	{
		FUN_00909810(*(int *)(param_1 + 0x24));
		return;
	}
}
