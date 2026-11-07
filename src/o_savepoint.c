#include "decls.h"
extern int DAT_05eda288;
extern float DAT_05eda270;
extern float DAT_05eda274;
extern float DAT_05eda278;
extern float DAT_05eda27c;
extern float DAT_05eda280;
extern float DAT_05eda284;
extern unsigned char DAT_05eda24e;
extern unsigned char DAT_05eda24f;
extern void FUN_005d96c0(void *param_1, int param_2, int param_3);
extern void *DAT_05eda248;
void InitContinueData();

// STUB: SADX 0x005a5490
void InitContinueData()
{
}

// STUB: SADX 0x005a54d0
long CheckContinueData()
{
	return (long)0;
}

// STUB: SADX 0x005a5500
void RestoreContinueData(struct NJS_POINT3 *pos, struct Angle3 *ang)
{
}

// STUB: SADX 0x005a55e0
void updateContinueData(struct NJS_POINT3 *pos, struct Angle3 *ang)
{
}

// FUNCTION: SADX 0x005a58c0
void savepointExit(struct task *tp)
{
	if (tp->awp->work.ptr[0] != 0)
	{
		Free(tp->awp->work.ptr[0]);
		tp->awp->work.ptr[0] = 0;
	}
}

// STUB: SADX 0x005a58f0
void savepointDisplay(struct task *tp)
{
}

// STUB: SADX 0x005a5a20
void *FUN_005a5a20()
{
	return (void *)0;
}

// STUB: SADX 0x005a5a70
void rotateBall(struct obj *obj)
{
}

// STUB: SADX 0x005a5cf0
void FUN_005a5cf0(struct task *param_1, struct taskwk *param_2)
{
}

// FUNCTION: SADX 0x005a60a0
void savepointPrintLaptime(struct task *tp, struct taskwk *twp)
{
	if ((DAT_05eda288 & 1) == 0)
	{
		DAT_05eda288 = DAT_05eda288 | 1;
		DAT_05eda270 = ScreenRaitoX * 450.0f;
		DAT_05eda274 = ScreenRaitoY * 400.0f;
		DAT_05eda278 = 1.0f * ScreenRaitoX;
		DAT_05eda27c = 1.0f * ScreenRaitoY;
		DAT_05eda280 = ScreenRaitoX * 30.0f;
		DAT_05eda284 = 0.0f;
	}
	if (*(int *)((char *)DAT_05eda248 + 0x30) <= 0)
	{
		return;
	}
	*(int *)((char *)DAT_05eda248 + 0x30) = *(int *)((char *)DAT_05eda248 + 0x30) - 1;
	switch ((0x12c - *(int *)((char *)DAT_05eda248 + 0x30)) / 0xa)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 9:
	case 11:
		break;
	default:
		FUN_005d96c0(&DAT_05eda270, DAT_05eda24e, DAT_05eda24f);
		break;
	}
}
