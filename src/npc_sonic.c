#include "decls.h"
extern int DAT_05edbd7c;
extern int DAT_05edbd0c;
extern const struct sMRacePath *PPT_MRaceEachStage[10];
extern float DAT_05edbd00;
void FUN_005a9290(struct taskwk *param_1);
void FUN_005a92d0(struct taskwk *param_1);
extern int DAT_05edbdac;
extern int DAT_05edbd04;

// STUB: SADX 0x005a8640
void InitSonic2PControl(struct task *tp)
{
}

// STUB: SADX 0x005a8cc0
void InitMoble2PControl(struct task *tp)
{
}

// FUNCTION: SADX 0x005a9290
void FUN_005a9290(struct taskwk *param_1)
{
	int local_8;
	local_8 = (DAT_05edbd04 << 1) * 4 + (int)PPT_MRaceEachStage;
	DAT_05edbd7c = *(int *)local_8;
	local_8 += 4;
	DAT_05edbd0c = *(int *)local_8;
	local_8 += 4;
}

// STUB: SADX 0x005a92d0
void FUN_005a92d0(struct taskwk *param_1)
{
}

// STUB: SADX 0x005a9320
void FUN_005a9320(struct sMRacePath *param_1, struct NJS_POINT3 *param_2)
{
}

// STUB: SADX 0x005aa610
int FUN_005aa610(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x005aa7c0
float MakeStrokeWithDist(struct NJS_POINT3 *vec, float range, float ratio)
{
	return (float)0;
}

// FUNCTION: SADX 0x005aa8d0
float FUN_005aa8d0(int param_1)
{
	if (((int)(*(int *)(param_1 + 0x28) & 0x4000000)) != 0)
	{
		return 1.0;
	}
	else
	{
		if (((int)(*(int *)(param_1 + 0x28) & 0x2000000)) != 0)
		{
			return 0.8;
		}
		else
		{
			return DAT_05edbd00;
		}
	}
}

// STUB: SADX 0x005ab220
void VibrateMoble(struct taskwk *twp, struct sMobleCtrl *moble_ctrl)
{
}

// STUB: SADX 0x005ab4a0
int FUN_005ab4a0()
{
	return (int)0;
}

// FUNCTION: SADX 0x005ab560
void DstrReleaseTexture(struct task *tp)
{
	struct task *local_8;
	local_8 = (struct task *)*(int *)((char *)tp + 0x20);
	late_ReleaseTexture((struct NJS_TEXLIST *)*(int *)((char *)local_8 + 0x10));
}

// FUNCTION: SADX 0x005ab580
void DispMilesMeter2P(struct task *tp)
{
	late_SetFunc((void (*)(void *))late_DispMilesMeter2P, tp, 22046.5f, 1);
}

// FUNCTION: SADX 0x005ab800
void FUN_005ab800(unsigned long param_1)
{
	DAT_05edbd04 = param_1;
}

// FUNCTION: SADX 0x005ab810
void SetMilesWin()
{
	DAT_05edbdac = 1;
}

// FUNCTION: SADX 0x005ab820
void SetMilesLose()
{
	DAT_05edbdac = 2;
}

// FUNCTION: SADX 0x005ab830
long GetMRaceResult()
{
	return DAT_05edbdac;
}
