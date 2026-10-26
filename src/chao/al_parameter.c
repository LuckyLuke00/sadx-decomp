#include "decls.h"
void FUN_004389d0(int param_1, int param_2);
extern const unsigned long nbMaxEntry[11];
extern struct CHAO_GLOBAL ChaoGlobal;
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);
struct taskwk;
struct CHAO_GLOBAL;
extern int DAT_05ade378;
extern int DAT_05ade374;

// FUNCTION: SADX 0x004388f0
long AL_IsHero(unsigned char type)
{
	if (type >= 6 && (type - 6) % 3 == 0)
	{
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00438920
long AL_IsDark(unsigned char type)
{
	if (type >= 7 && (type - 7) % 3 == 0)
	{
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00438950
long AL_IsHero2(struct task *pChaoTask)
{
	char *var1 = *(char **)((char *)pChaoTask->twp + 0x6c);
	int var2 = (int)(unsigned char)(*(unsigned char *)(var1 + 0x80));
	if (var2 >= 6 && var2 < 0x17 && (var2 - 6) % 3 == 0)
	{
		return 1;
	}
	return 0;
}

// STUB: SADX 0x00438990
long AL_IsDark2(struct task *pChaoTask)
{
	return (long)0;
}

// STUB: SADX 0x004389d0
void FUN_004389d0(int param_1, int param_2)
{
}

// FUNCTION: SADX 0x00438a50
void AL_ParameterCatchup(struct task *pChaoTask)
{
	struct taskwk *var1;
	struct anywk *var2;

	var1 = pChaoTask->twp;
	var2 = *(struct anywk **)((char *)var1 + 0x6c);
	*(unsigned char *)((char *)var1 + 0x70) = *(unsigned char *)((char *)var2 + 0x20);
	*(unsigned char *)((char *)var1 + 0x80) = *(unsigned char *)((char *)var2 + 0x30);
	*(unsigned short *)((char *)var1 + 0x88) = *(unsigned short *)((char *)var2 + 0x38);
	*(unsigned char *)((char *)var1 + 0x71) = *(unsigned char *)((char *)var2 + 0x21);
	*(unsigned char *)((char *)var1 + 0x81) = *(unsigned char *)((char *)var2 + 0x31);
	*(unsigned short *)((char *)var1 + 0x8a) = *(unsigned short *)((char *)var2 + 0x3a);
	*(unsigned char *)((char *)var1 + 0x72) = *(unsigned char *)((char *)var2 + 0x22);
	*(unsigned char *)((char *)var1 + 0x82) = *(unsigned char *)((char *)var2 + 0x32);
	*(unsigned short *)((char *)var1 + 0x8c) = *(unsigned short *)((char *)var2 + 0x3c);
	*(unsigned char *)((char *)var1 + 0x73) = *(unsigned char *)((char *)var2 + 0x23);
	*(unsigned char *)((char *)var1 + 0x83) = *(unsigned char *)((char *)var2 + 0x33);
	*(unsigned short *)((char *)var1 + 0x8e) = *(unsigned short *)((char *)var2 + 0x3e);
	*(unsigned char *)((char *)var1 + 0x74) = *(unsigned char *)((char *)var2 + 0x24);
	*(unsigned char *)((char *)var1 + 0x84) = *(unsigned char *)((char *)var2 + 0x34);
	*(unsigned short *)((char *)var1 + 0x90) = *(unsigned short *)((char *)var2 + 0x40);
	*(unsigned char *)((char *)var1 + 0x75) = *(unsigned char *)((char *)var2 + 0x25);
	*(unsigned char *)((char *)var1 + 0x85) = *(unsigned char *)((char *)var2 + 0x35);
	*(unsigned short *)((char *)var1 + 0x92) = *(unsigned short *)((char *)var2 + 0x42);
	*(unsigned char *)((char *)var1 + 0x76) = *(unsigned char *)((char *)var2 + 0x26);
	*(unsigned char *)((char *)var1 + 0x86) = *(unsigned char *)((char *)var2 + 0x36);
	*(unsigned short *)((char *)var1 + 0x94) = *(unsigned short *)((char *)var2 + 0x44);
	*(unsigned char *)((char *)var1 + 0x77) = *(unsigned char *)((char *)var2 + 0x27);
	*(unsigned char *)((char *)var1 + 0x87) = *(unsigned char *)((char *)var2 + 0x37);
	*(unsigned short *)((char *)var1 + 0x96) = *(unsigned short *)((char *)var2 + 0x46);
}

// FUNCTION: SADX 0x00438b40
void AL_ParameterAddGrowth(struct task *tp, float add)
{
	struct taskwk *var1;
	struct anywk *var2;
	float var3;

	var1 = tp->twp;
	var2 = *(struct anywk **)((char *)var1 + 0x6c);
	var3 = *(float *)((char *)var2 + 0xc0) + add;
	*(float *)((char *)var2 + 0xc0) = var3;
	if (ChaoGlobal.GrowthLimit < var3)
	{
		*(float *)((char *)var2 + 0xc0) = ChaoGlobal.GrowthLimit;
	}
	if (*(float *)((char *)var2 + 0xc0) < 0.0f)
	{
		*(float *)((char *)var2 + 0xc0) = 0.0f;
	}
	*(short *)((char *)var1 + 0x688) |= 2;
}

// FUNCTION: SADX 0x00438bb0
void AL_ParameterAddHPos(struct task *tp, float add)
{
	struct taskwk *var1;
	struct anywk *var2;
	float var3;

	var1 = tp->twp;
	var2 = *(struct anywk **)((char *)var1 + 0x6c);
	var3 = *(float *)((char *)var2 + 0xa8) + add;
	*(float *)((char *)var2 + 0xa8) = var3;
	if (var3 > ChaoGlobal.DeformLimit)
		*(float *)((char *)var2 + 0xa8) = ChaoGlobal.DeformLimit;
	if (*(float *)((char *)var2 + 0xa8) < -ChaoGlobal.DeformLimit)
		*(float *)((char *)var2 + 0xa8) = -ChaoGlobal.DeformLimit;
	*(short *)((char *)var1 + 0x688) |= 2;
}

// FUNCTION: SADX 0x00438c30
void AL_ParameterAddVPos(struct task *tp, float add)
{
	struct taskwk *var1;
	struct anywk *var2;
	float var3;

	var1 = tp->twp;
	var2 = *(struct anywk **)((char *)var1 + 0x6c);
	var3 = *(float *)((char *)var2 + 0xac) + add;
	*(float *)((char *)var2 + 0xac) = var3;
	if (var3 > *(float *)((char *)&ChaoGlobal + 0x40))
		*(float *)((char *)var2 + 0xac) = *(float *)((char *)&ChaoGlobal + 0x40);
	if (*(float *)((char *)var2 + 0xac) < -*(float *)((char *)&ChaoGlobal + 0x40))
		*(float *)((char *)var2 + 0xac) = -*(float *)((char *)&ChaoGlobal + 0x40);
	*(short *)((char *)var1 + 0x688) |= 2;
}

// FUNCTION: SADX 0x00438cb0
void AL_ParameterAddAPos(struct task *tp, float add)
{
	struct taskwk *var1;
	struct anywk *var2;
	float var3;

	var1 = tp->twp;
	var2 = *(struct anywk **)((char *)var1 + 0x6c);
	var3 = *(float *)((char *)var2 + 0xb0) + add;
	*(float *)((char *)var2 + 0xb0) = var3;
	if (var3 > 1.0f)
		*(float *)((char *)var2 + 0xb0) = 1.0f;
	if (*(float *)((char *)var2 + 0xb0) < -1.0f)
		*(float *)((char *)var2 + 0xb0) = -1.0f;
	*(short *)((char *)var1 + 0x688) |= 2;
}

// FUNCTION: SADX 0x00438d20
void AL_ParameterAddLife(struct task *tp, long add)
{
	char *var1 = *(char **)((char *)tp->twp + 0x6c);
	int var2 = (int)(unsigned short)(*(unsigned short *)(var1 + 0x8a)) + add;
	int var3 = (int)(unsigned short)(*(unsigned short *)(var1 + 0x8c));
	if (var2 > var3)
	{
		var2 = var3;
	}
	if (var2 < 0)
	{
		var2 = 0;
	}
	*(unsigned short *)(var1 + 0x8a) = (unsigned short)var2;
}

// FUNCTION: SADX 0x00438d50
void AL_ParameterAddLifeMax(struct task *tp, long add)
{
	struct taskwk *var1 = tp->twp;
	struct taskwk *var2 = *(struct taskwk **)((char *)var1 + 0x6c);
	int var3 = *(unsigned short *)((char *)var2 + 0x8c);
	int var4 = *(unsigned short *)((char *)var2 + 0x8a);
	int var5 = *(unsigned short *)((char *)&ChaoGlobal + 0x36);
	var3 += add;
	if (var3 > var5)
		var3 = var5;
	if (var3 < 0)
		var3 = 0;
	if (var4 > var3)
	{
		*(unsigned short *)((char *)var2 + 0x8c) = (unsigned short)var3;
		*(unsigned short *)((char *)var2 + 0x8a) = (unsigned short)var3;
	}
	else
	{
		*(unsigned short *)((char *)var2 + 0x8c) = (unsigned short)var3;
		*(unsigned short *)((char *)var2 + 0x8a) = (unsigned short)var4;
	}
}

// FUNCTION: SADX 0x00438da0
void AL_ParameterAddUserLike(struct task *tp, long add, float AddAttr)
{
	struct taskwk *var1;
	struct anywk *var2;
	int var3;

	var1 = tp->twp;
	var2 = *(struct anywk **)((char *)var1 + 0x6c);
	var3 = (int)(short)*(short *)((char *)var2 + 0x82) + (int)add;
	if (var3 > 100)
		var3 = 100;
	if (var3 < -100)
		var3 = -100;
	*(short *)((char *)var2 + 0x82) = (short)var3;
	AL_KW_AddPlayerLike(tp, add);
	if (add > 0)
		AL_IconSet(tp, 4, 0xb4);
	else
		AL_IconSet(tp, 5, 0xb4);
}

// FUNCTION: SADX 0x00438e10
void AL_ParameterControlInit()
{
	DAT_05ade378 = 0;
	DAT_05ade374 = 0;
}

// FUNCTION: SADX 0x00438e20
long AL_IsEmotionTimerReset(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	void *var2 = *(void **)((char *)var1 + 0x6c);
	if (*(short *)((char *)var2 + 0x12a) == 0)
	{
		*(short *)((char *)var2 + 0x12a) = 1;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00438e50
void AL_ClearChaoParam(struct CHAO_PARAM_GC *pParam)
{
	memset(pParam, 0, 0x520);
}

// FUNCTION: SADX 0x00438f80
unsigned long AL_ParameterGetSkill(struct task *pChaoTask, unsigned short SkillKind)
{
	if (SkillKind >= 8)
	{
		SkillKind = 0;
	}
	return (unsigned long)*(unsigned short *)((char *)(*(void **)((char *)pChaoTask->twp + 0x6c)) + 0x38 + SkillKind * 2) * 3;
}

// STUB: SADX 0x0043a120
void AL_ParameterGrow(struct task *pChaoTask, unsigned short category, unsigned short kind, long finish)
{
}

// FUNCTION: SADX 0x0043a220
void AL_ParameterControl()
{
	unsigned int var1;
	unsigned short var2;
	var1 = (unsigned int)DAT_05ade378 + 1;
	var2 = *(unsigned short *)((char *)&ChaoGlobal + 0x19a);
	DAT_05ade378 = (int)var1;
	if (var1 >= (unsigned int)var2)
	{
		struct task *var3;
		DAT_05ade378 = 0;
		var3 = ALW_GetTask(0, DAT_05ade374 % nbMaxEntry[0]);
		if (var3)
		{
			AL_CalcParameter(var3);
		}
		DAT_05ade374 = DAT_05ade374 + 1;
	}
}

// FUNCTION: SADX 0x0043a270
void AL_ParameterDrawName(unsigned char *name, float xpos, float ypos, float xsize, float ysize, enum DrawAnchorH ancH, enum DrawAnchorV ancV, union NJS_COLOR col)
{
	AL_ParameterDrawNameFreeLength(name, xpos, ypos, xsize, ysize, ancH, ancV, col, 0);
}
