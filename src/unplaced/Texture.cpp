#include "decls.h"
#include <list>
#include "../advertise.h"

// FUNCTION: SADX 0x009225a0
int __fastcall FUN_009225a0(int param_1)
{
	return *(int *)(param_1 + 8);
}

// FUNCTION: SADX 0x009225b0
int __fastcall FUN_009225b0(int param_1)
{
	return *(int *)(param_1 + 4);
}

// FUNCTION: SADX 0x009225c0
int __fastcall FUN_009225c0(int param_1)
{
	return *(int *)param_1;
}

// STUB: SADX 0x009225d0
void __stdcall FUN_009225d0(int param_1, int param_2)
{
}

// FUNCTION: SADX 0x00922640
void FUN_00922640(void *param_1)
{
	return;
}

// STUB: SADX 0x00922710
char __fastcall FUN_00922710(void *param_1)
{
	return (char)0;
}

// STUB: SADX 0x00922720
int __fastcall FUN_00922720(int param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x00922750
void Magic::RenderCore::Texture::FUN_00922750()
{
}

// FUNCTION: SADX 0x009227b0
int __fastcall FUN_009227b0(int param_1)
{
	return *(int *)(param_1 + 0x50);
}

// FUNCTION: SADX 0x009227d0
int __fastcall FUN_009227d0(int param_1)
{
	return *(int *)(param_1 + 0x6c);
}

// FUNCTION: SADX 0x009227f0
int __fastcall FUN_009227f0(int param_1)
{
	return *(int *)(param_1 + 0x64);
}

// STUB: SADX 0x00922810
void __fastcall FUN_00922810(int param_1, int param_2)
{
}

// FUNCTION: SADX 0x00922820
int __fastcall FUN_00922820(int param_1)
{
	return *(int *)(param_1 + 0x54);
}

// STUB: SADX 0x00922830
void __fastcall FUN_00922830(int param_1)
{
}

// STUB: SADX 0x00922840
void __fastcall FUN_00922840(int param_1)
{
}

// FUNCTION: SADX 0x00922850
int __fastcall FUN_00922850(int param_1)
{
	return *(int *)(param_1 + 0x5c);
}

// STUB: SADX 0x00922860
void __fastcall FUN_00922860(int param_1)
{
}

// FUNCTION: SADX 0x00922870
int __fastcall FUN_00922870(int param_1)
{
	return *(int *)(param_1 + 0x58);
}

// Local placement and conditional branch code still differ.
// FUNCTION: SADX 0x00922900
bool Magic::RenderCore::Texture::Load(void* param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
	if (((bool (__thiscall *)(Texture*))(*(void***)this)[2])(this))
	{
		return false;
	}
	if (param_1 == 0 || param_3 <= 0)
	{
		return false;
	}
	int local_8;
	int local_c;
	int local_10;
	int local_14;
	int local_18;
	int local_1c;
	if ((unsigned int)param_2 <= 3)
	{
		local_8 = 0;
		local_c = 0;
		local_10 = 0;
		local_14 = param_4;
		local_18 = param_5;
		local_1c = param_6;
		if (((bool (__thiscall *)(void*, Texture*, int, void*, int, int*, int*, int*, int*, int*, int*))
			(*(void***)DAT_062992fc)[0x138 / 4])((void*)DAT_062992fc, this, param_2, param_1, param_3,
			&local_8, &local_c, &local_10, &local_14, &local_18, &local_1c))
		{
			local_50 = param_3;
			local_4c = param_2;
			if (local_8 > 0)
				local_58 = local_8;
			if (local_c > 0)
				local_5c = local_c;
			if (local_10 > 0)
				local_60 = local_10;
			if (local_14 > 0)
			{
				if (local_14 <= 32)
				{
					local_64 = local_14;
				}
			}
			if (local_18 >= 0)
				local_6c = local_18;
			this->local_8 = 1;
			local_54 = local_1c;
		}
		return ((bool (__thiscall *)(Texture*))(*(void***)this)[2])(this);
	}
	return false;
}

#pragma optimize("", off)
// STUB: SADX 0x00922bf0
Magic::RenderCore::Texture::~Texture()
{
}
#pragma optimize("", on)

// Member initialization and list registration code still differ.
// FUNCTION: SADX 0x00922c80
Magic::RenderCore::Texture::Texture()
{
	local_50 = 0;
	local_54 = 0;
	local_58 = 0;
	local_5c = 0;
	local_60 = 0;
	local_64 = 0;
	local_68 = 0;
	local_6c = 0;
	local_70 = false;
	local_4 = 0;
	local_4c = 1;
	int* var1 = *(int**)(DAT_062992fc + 8);
	int* var2 = (int*)var1[1];
	void* var4 = (void*)var2[1];
	Resource* local_14 = this;
	int* var3 = (int*)FUN_0040c470(var2, var4, &local_14);
	if (0x3ffffffeU - (unsigned int)var1[2] < 1)
	{
		std::_Xlength_error("list<T> too long");
	}
	var1[2]++;
	var2[1] = (int)var3;
	*(int*)var3[1] = (int)var3;
}
