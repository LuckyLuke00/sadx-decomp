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
