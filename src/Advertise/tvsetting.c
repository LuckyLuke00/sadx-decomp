#include "decls.h"
extern struct task *DAT_05cda18c;
void FUN_005fd5d0(struct anywk *param_1);
void FUN_00574140(int param_1, float param_2, float param_3, float param_4);
void FUN_005fd510(int param_1, int param_2);
void FUN_005fd320(struct task *param_1);
void FUN_005fd760(struct task *param_1);
extern struct task *DAT_05edd9a0;

// STUB: SADX 0x005fd240
struct task *FUN_005fd240(struct ModeSelPrmType *param_1)
{
	return (struct task *)0;
}

// STUB: SADX 0x005fd2b0
struct task *SetAdvaTvSettingTask(struct ModeSelPrmType *prmp)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x005fd300
void FUN_005fd300(struct anywk *param_1)
{
	*(unsigned char *)((char *)param_1 + 0x34) = 0;
	*(int *)((char *)param_1 + 0x18) = 0;
	*(unsigned char *)((char *)param_1 + 0x29) = 0;
}

// FUNCTION: SADX 0x005fd320
void FUN_005fd320(struct task *param_1)
{
	struct anywk *local_8;

	local_8 = param_1->awp;
	if (*(int *)((char *)DAT_05cda18c->awp + 4) == 0xc && *(int *)local_8 == 0)
	{
		FUN_005fd4c0(local_8);
		*(float *)((char *)local_8 + 0x10) = 0.0f;
		*(int *)local_8 = 1;
	}
	if (*(int *)((char *)DAT_05cda18c->awp + 8) == 0xc && *(int *)local_8 == 2)
	{
		FUN_005fd4e0((int)local_8);
		*(float *)((char *)local_8 + 0x10) = 0.0f;
		*(int *)local_8 = 3;
	}
	switch (*(int *)local_8)
	{
	case 0:
		*(float *)((char *)local_8 + 0x10) = 0.0f;
		*(int *)((char *)local_8 + 0x14) = 0;
		break;
	case 1:
		*(int *)((char *)local_8 + 0x14) = GetFadeInColFromT(*(float *)((char *)local_8 + 0x10));
		*(float *)((char *)local_8 + 0x10) += 0.1f;
		if (*(float *)((char *)local_8 + 0x10) >= 1.0f)
		{
			*(int *)local_8 = 2;
		}
		break;
	case 2:
		*(float *)((char *)local_8 + 0x10) = 0.0f;
		*(int *)((char *)local_8 + 0x14) = 0xffffffff;
		*(int *)((char *)DAT_05cda18c->awp + 0xc) = 0xc;
		FUN_005fd5d0(local_8);
		break;
	case 3:
		*(int *)((char *)local_8 + 0x14) = GetFadeOutColFromT(*(float *)((char *)local_8 + 0x10));
		*(float *)((char *)local_8 + 0x10) += 0.1f;
		if (*(float *)((char *)local_8 + 0x10) >= 1.0f)
		{
			AvaReleaseTexForEachMode((AdvaModeEnum)0xc);
			*(char *)((char *)DAT_05cda18c->awp + 0x1f) = 1;
			*(int *)local_8 = 0;
		}
		break;
	}
}

// FUNCTION: SADX 0x005fd4c0
void FUN_005fd4c0(struct anywk *param_1)
{
	AvaLoadTexForEachMode(ADVA_MODE_TVSETTING);
	FUN_005fd300(param_1);
}

// FUNCTION: SADX 0x005fd4e0
void FUN_005fd4e0(int param_1)
{
	if (*(char *)(param_1 + 0x34) != 0)
	{
		FUN_005fd510(*(char *)(param_1 + 0x34), 1);
	}
}

// STUB: SADX 0x005fd510
void FUN_005fd510(int param_1, int param_2)
{
}

// STUB: SADX 0x005fd5d0
void FUN_005fd5d0(struct anywk *param_1)
{
}

// FUNCTION: SADX 0x005fd7e0
void FUN_005fd7e0(struct TvSettingWk *param_1)
{
	ghSetPvrTexMaterial(0xffffffff);
	___njSetTexture(&texlist_tvsetting);
	FUN_00574140(0x16, 32.0f, 42.0f, *(float *)((char *)param_1 + 0xc) + -12.0);
	DrawTitleBack(0.0f, 32.0f, *(float *)((char *)param_1 + 0xc) + -10.0, 565.0f, 42.0f);
}

// STUB: SADX 0x005fdb60
void DrawSprite2DR(unsigned long material, struct NJS_TEXLIST *tlist, short pvrindex, float posx, float posy, float posz, float sclx, float scly, long rot)
{
}
