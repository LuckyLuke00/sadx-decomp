#include "decls.h"
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

// STUB: SADX 0x00438950
long AL_IsHero2(struct task *pChaoTask)
{
	return (long)0;
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

// STUB: SADX 0x00438b40
void AL_ParameterAddGrowth(struct task *tp, float add)
{
}

// STUB: SADX 0x00438bb0
void AL_ParameterAddHPos(struct task *tp, float add)
{
}

// STUB: SADX 0x00438c30
void AL_ParameterAddVPos(struct task *tp, float add)
{
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

// STUB: SADX 0x00438d20
void AL_ParameterAddLife(struct task *tp, long add)
{
}

// STUB: SADX 0x00438d50
void AL_ParameterAddLifeMax(struct task *tp, long add)
{
}

// STUB: SADX 0x00438da0
void AL_ParameterAddUserLike(struct task *tp, long add, float AddAttr)
{
}

// FUNCTION: SADX 0x00438e10
void AL_ParameterControlInit()
{
	DAT_05ade378 = 0;
	DAT_05ade374 = 0;
}

// STUB: SADX 0x00438e20
long AL_IsEmotionTimerReset(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00438e50
void AL_ClearChaoParam(struct CHAO_PARAM_GC *pParam)
{
	memset(pParam, 0, 0x520);
}

// STUB: SADX 0x00438f80
unsigned long AL_ParameterGetSkill(struct task *pChaoTask, unsigned short SkillKind)
{
	return (unsigned long)0;
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
