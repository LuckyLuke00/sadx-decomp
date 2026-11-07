#include "decls.h"
#include <new>
#include "../advertise.h"
#include <wchar.h>
#include <string.h>
extern int DAT_05ab3998;
extern int DAT_05ab39a0;
extern int DAT_05ab39a4;
extern int DAT_05ab41f4;
extern int DAT_05ab421c;
extern int DAT_05ab4220;
void FUN_004207b0(void);
void UnknowTochar(char *param_1, unsigned long param_2);
extern unsigned char DAT_05ab4243;

// FUNCTION: SADX 0x004198d0
int SOCGetInputLayout(int param_1)
{
	switch (param_1)
	{
		case 66:
			return DAT_05ab4220;
		case 68:
			return DAT_05ab39a4;
		case 82:
			return DAT_05ab3998;
		case 322:
			return DAT_05ab39a0;
		case 324:
			return DAT_05ab421c;
		case 338:
			return DAT_05ab41f4;
	}
	return 0;
}

// STUB: SADX 0x004199b0
void SOCRender::SetSpecularEnable(bool param_1)
{
}

// FUNCTION: SADX 0x00419ac0
void __fastcall FUN_00419ac0(void *param_1, int param_2, int param_3)
{
	*(int *)((char *)param_1 + 0x18) = param_3;
	DAT_05ab4243 = 0;
}

// FUNCTION: SADX 0x00419ae0
void __fastcall FUN_00419ae0(void *param_1, void *param_2, int param_3)
{
	*(void **)((char *)param_1 + 8) = (void *)param_3;
	DAT_05ab4243 = 0;
}

// FUNCTION: SADX 0x00419b00
void __fastcall FUN_00419b00(void *param_1, float param_2)
{
	*(float *)((char *)param_1 + 0x14) = param_2;
	DAT_05ab4243 = 0;
}

// FUNCTION: SADX 0x00419b20
void __fastcall FUN_00419b20(int param_1, float param_2)
{
	*(float *)(param_1 + 0x10) = param_2;
	DAT_05ab4243 = 0;
}

// FUNCTION: SADX 0x00419b40
void __fastcall FUN_00419b40(float param_1, void *param_2)
{
	*(float *)((char *)param_2 + 0xc) = param_1;
	DAT_05ab4243 = 0;
}

// FUNCTION: SADX 0x00419d00
void __fastcall FUN_00419d00(int param_1, int param_2, int param_3)
{
	*(int *)((char *)param_1 + 0x279c) = param_3;
}

// STUB: SADX 0x00419d40
void __fastcall FUN_00419d40(int param_1, float param_2)
{
}

// STUB: SADX 0x00419d80
void __fastcall FUN_00419d80(int param_1, int param_2)
{
}

struct FUN_0041b7e0_0
{
	float field_0x0;
	float field_0x4;
	float field_0x8;
	float field_0xc;
	unsigned long field_0x10;
	float field_0x14;
	float field_0x18;
};

extern void *DAT_05ab39ac;
extern unsigned char DAT_05ab4239;
extern unsigned char DAT_05ab423b;
extern class Magic::RenderCore::VertexBuffer *DAT_05ab4284;
extern class Magic::RenderCore::Material *DAT_05ab4278;
extern unsigned int DAT_05ab4288;
extern void *DAT_05ab8060;



// STUB: SADX 0x0041a170
void UnknowTochar(char *param_1, unsigned long param_2)
{
}

// STUB: SADX 0x0041a1c0
void SOCsetZwrite(bool param_1)
{
}

// STUB: SADX 0x0041a1e0
bool SOCGetZwrite(void)
{
	return (bool)0;
}

// STUB: SADX 0x0041b120
void SOCRender::FUN_0041b120(int param_1, int param_2)
{
}

// FUNCTION: SADX 0x0041b7e0
void RenderTexture(int param_1, int param_2, int param_3, int param_4, float param_5, Magic::RenderCore::Texture *param_6, float param_7, float param_8, float param_9, float param_10, int param_11)
{
	DAT_05ab423b = 1;
	float local_8 = (float)param_1;
	float local_c = (float)param_2;
	float var1 = (float)param_3;
	float var2 = (float)param_4;
	if (*(Magic::RenderCore::Texture **)((char *)DAT_05ab39ac + 0x168) != param_6)
	{
		*(Magic::RenderCore::Texture **)((char *)DAT_05ab39ac + 0x168) = param_6;
	}
	*(int *)((char *)DAT_05ab39ac + 0x150) = 2;
	*(int *)((char *)DAT_05ab39ac + 0x14c) = 2;
	DAT_05ab4239 = 0;
	*(int *)((char *)DAT_05ab39ac + 0x154) = 2;
	FUN_0041b7e0_0 local_7c[4] = {
		{local_8, local_c + var2, param_5, 1.0f, (unsigned long)param_11, param_7, param_10},
		{local_8, local_c, param_5, 1.0f, (unsigned long)param_11, param_7, param_8},
		{local_8 + var1, local_c + var2, param_5, 1.0f, (unsigned long)param_11, param_9, param_10},
		{local_8 + var1, local_c, param_5, 1.0f, (unsigned long)param_11, param_9, param_8}
	};
	void *var3 = 0;
	if (DAT_05ab4284->Lock(&var3, DAT_05ab4288, 112, 0))
	{
		memcpy(var3, local_7c, sizeof(local_7c));
		DAT_05ab4284->Unlock();
	}
	((SOCRender *)DAT_05ab39ac)->UIShaderSet();
	DAT_05ab4278->CommitDeviceShader();
	((void (__thiscall *)(void *, int, Magic::RenderCore::VertexBuffer *, unsigned int, int, int, int, int))(*(void ***)DAT_05ab8060)[14])(DAT_05ab8060, DAT_05ab421c, DAT_05ab4284, DAT_05ab4288 / 28, 4, 0, 0, 0);
	DAT_05ab4288 += 112;
	if (DAT_05ab4288 >= 112000)
		DAT_05ab4288 = 0;
}

// STUB: SADX 0x0041cc20
void __fastcall FUN_0041cc20(int param_1)
{
}

// STUB: SADX 0x0041cf30
void __fastcall FUN_0041cf30(void *param_1, void *param_2)
{
}

// STUB: SADX 0x0041cfb0
void __fastcall FUN_0041cfb0(void *param_1, void *param_2, int param_3)
{
}

// STUB: SADX 0x0041d020
void __fastcall FUN_0041d020(int param_1, int param_2)
{
}

// STUB: SADX 0x0041d130
void __fastcall FUN_0041d130(void *param_1, void *param_2, int param_3)
{
}

// FUNCTION: SADX 0x0041dc60
void GetTextSize(const wchar_t *param_1, int& param_2, int& param_3)
{
	DAT_05ab4280->GetTextSize(param_1, FUN_0040e170_0(), param_2, param_3);
	param_2 = (int)(param_2 * ScreenRaitoX);
	param_3 = (int)(param_3 * ScreenRaitoY);
}

extern struct FUN_0040e170_1 *DAT_05ab4280;





// STUB: SADX 0x0041e270
void __fastcall FUN_0041e270(void *param_1, void *param_2, int param_3, int param_4)
{
}

// STUB: SADX 0x004207b0
void FUN_004207b0(void)
{
}

// STUB: SADX 0x004207c0
void FUN_004207c0(void)
{
}

struct FUN_004208c0_0
{
	int field_0x0;
	int field_0x4;
	int field_0x8;
	int field_0xc;
	int field_0x10;
	float field_0x14;
	float field_0x18;
};

template class std::vector<FUN_004208c0_0>;

extern int DAT_05ab42ac;
extern wchar_t DAT_05ab39b0[1024];
// GLOBAL: SADX 0x05ab42cc
static std::vector<FUN_004208c0_0> DAT_05ab42cc;

// FUNCTION: SADX 0x004208c0
void FUN_004208c0(int param_1, int param_2, const wchar_t *param_3, int param_4, float param_5, float param_6)
{
	int var1 = wcslen(param_3);
	int var2 = DAT_05ab42ac + var1;
	if (var2 <= 1024)
	{
		FUN_004208c0_0 local_24;
		local_24.field_0x0 = param_1;
		local_24.field_0x18 = param_6;
		local_24.field_0x4 = param_2;
		local_24.field_0x14 = param_5;
		local_24.field_0x8 = DAT_05ab42ac;
		local_24.field_0xc = var2;
		local_24.field_0x10 = param_4;
		memcpy(&DAT_05ab39b0[DAT_05ab42ac], param_3, var1 * 2);
		DAT_05ab42ac = var2;
		DAT_05ab42cc.push_back(local_24);
	}
}

extern unsigned char DAT_05ab423b;
// GLOBAL: SADX 0x05ab42dc
std::vector<struct FUN_00420960_0, std::allocator<struct FUN_00420960_0> > DAT_05ab42dc;

// FUNCTION: SADX 0x00420960
void DrawTexture(int param_1, int param_2, int param_3, int param_4, float param_5, Magic::RenderCore::Texture *param_6, float param_7, float param_8, float param_9, float param_10, int param_11)
{
	DAT_05ab423b = 1;
	FUN_00420960_0 local_30;
	local_30.field_0x0 = param_1;
	local_30.field_0x4 = param_2;
	local_30.field_0x8 = param_3;
	local_30.field_0xc = param_4;
	local_30.field_0x10 = param_5;
	local_30.field_0x14 = param_6;
	local_30.field_0x18 = param_7;
	local_30.field_0x1c = param_8;
	local_30.field_0x20 = param_9;
	local_30.field_0x24 = param_10;
	local_30.field_0x28 = param_11;
	DAT_05ab42dc.push_back(local_30);
}

// FUNCTION: SADX 0x00421180
void DrawStringW(int param_1, int param_2, const wchar_t *param_3, int param_4, float param_5)
{
	FUN_004208c0(param_1, param_2, param_3, param_4, param_5, 0.0f);
}
