#include "decls.h"
extern void FUN_005a9320(struct sMRacePath *param_1, struct NJS_POINT3 *param_2);
extern char DAT_009960fc[1];
void DispMilesMeter2P(struct task *tp);
void SetInputP(unsigned char pno, signed char mode);
void SetPositionP(unsigned char pno, float x, float y, float z);
void CharColliOn(struct taskwk *twp);
long ChkParabolaEnd(struct sParabola *para);
extern char DAT_05edbd80[0x24];
extern int DAT_05edbdd0;
extern float DAT_05edbd08;
extern float DAT_05edbd78;
extern unsigned long DAT_05b3ea20;
void FUN_005a9100(int param_1, unsigned short param_2, struct sMobleCtrl *param_3);
extern int DAT_05edbd7c;
extern int DAT_05edbd0c;
extern const struct sMRacePath *PPT_MRaceEachStage[10];
extern float DAT_05edbd00;
void FUN_005a9290(struct taskwk *param_1);
void FUN_005a92d0(struct taskwk *param_1);
extern int DAT_05edbdac;
extern int DAT_05edbd04;
float njSqrt(float param_1);

// STUB: SADX 0x005a8640
void InitSonic2PControl(struct task *tp)
{
}

// STUB: SADX 0x005a86c0
void Sonic2PControl(struct task *tp)
{
}

// FUNCTION: SADX 0x005a8990
void FUN_005a8990(float *param_1, float *param_2, float *param_3)
{
	*param_3 = *param_1 + *param_2;
	param_3++;
	param_2++;
	param_1++;
	*param_3 = *param_1 + *param_2;
	param_3++;
	param_2++;
	param_1++;
	*param_3 = *param_1 + *param_2;
	param_3++;
	param_2++;
	param_1++;
}

// FUNCTION: SADX 0x005a8ae0
void FUN_005a8ae0(float *param_1, float *param_2, float *param_3)
{
	*param_3 = *param_2 - *param_1;
	param_3 += 1;
	param_1 += 1;
	param_2 += 1;
	*param_3 = *param_2 - *param_1;
	param_3++;
	param_1 += 1;
	param_2 += 1;
	*param_3 = *param_2 - *param_1;
	param_3 += 1;
	++param_1;
	param_2 += 1;
}

// STUB: SADX 0x005a8b70
void Icecap_Init(struct taskwk *twp, struct taskwk *stwp, struct taskwk *mtwp)
{
}

// STUB: SADX 0x005a8cc0
void InitMoble2PControl(struct task *tp)
{
}

// STUB: SADX 0x005a8d10
void Moble2PControl(struct task *tp)
{
}

// FUNCTION: SADX 0x005a8e10
void Highway_Init(struct task *tp, struct sMobleCtrl *moble_ctrl)
{
	int local_cg;
	int local_8g;
	local_cg = *(int *)((char *)tp + 0x20);
	local_8g = *(int *)((char *)GetPlayerTaskPointer(0) + 0x20);
	*(char *)local_cg = 1;
	if (DAT_05edbdd0 == 1)
	{
		DAT_05edbd08 = 3.5;
		DAT_05edbd78 = 2.2;
		DAT_05b3ea20 = 1;
	}
	else
	{
		DAT_05edbd08 = 2.0;
		DAT_05edbd78 = 0.08;
	}
	*(short *)((char *)local_cg + 0xc) = GetNearestPath((struct NJS_POINT3 *)(local_8g + 0x20), (struct sMRacePath *)DAT_05edbd7c, *(short *)((char *)local_cg + 8));
	*(short *)((char *)local_cg + 0xe) = GetNearestPath((struct NJS_POINT3 *)(local_8g + 0x20), (struct sMRacePath *)DAT_05edbd0c, *(short *)((char *)local_cg + 0xa));
	FUN_005a9100(local_cg, *(unsigned short *)((char *)local_cg + 0xe), moble_ctrl);
	CCL_Init(tp, CLI_MobleDamageCsn, 1, 4);
}

// STUB: SADX 0x005a8f00
void Highway_Nomal(struct task *tp, struct sMobleCtrl *moble_ctrl)
{
}

// STUB: SADX 0x005a9060
void FUN_005a9060(short param_1)
{
}

// STUB: SADX 0x005a9100
void FUN_005a9100(int param_1, unsigned short param_2, struct sMobleCtrl *param_3)
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

// STUB: SADX 0x005a9350
short GetNearestPath(struct NJS_POINT3 *pos, struct sMRacePath *path_tbl, short max_path)
{
	return (short)0;
}

// STUB: SADX 0x005aa480
void InitJumpSonicToPoint(struct taskwk *stwp, struct NJS_POINT3 *pos, long time)
{
}

// FUNCTION: SADX 0x005aa520
long ChkEndSonicFakeJump(struct taskwk *stwp)
{
	char *local_cg;
	int local_8g;
	local_cg = DAT_05edbd80;
	SetPositionP(1, stwp->pos.x + *(float *)(local_cg + 0x20), stwp->pos.y + *(float *)(local_cg + 0x24), stwp->pos.z + *(float *)(local_cg + 0x28));
	*(float *)(local_cg + 0x24) = *(float *)(local_cg + 0x24) - *(float *)(local_cg + 0x18);
	if (*(float *)(local_cg + 0x24) < 0.0)
	{
		CharColliOn(stwp);
	}
	local_8g = ChkParabolaEnd((struct sParabola *)local_cg);
	if (local_8g == 0)
	{
		return 0;
	}
	SetInputP(1, 0x18);
	if (local_8g == 2)
	{
		SetPositionP(1, *(float *)(local_cg + 0xc), *(float *)(local_cg + 0x10), *(float *)(local_cg + 0x14));
	}
	return 1;
}

// STUB: SADX 0x005aa610
int FUN_005aa610(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x005aa660
long MakeDirAngle(struct taskwk *twp, struct taskwk *stwp, struct sSonicCtrl *sonic_ctrl)
{
	return (long)0;
}

// FUNCTION: SADX 0x005aa7c0
float MakeStrokeWithDist(struct NJS_POINT3 *vec, float range, float ratio)
{
	float local_8g;
	float local_cg;

	local_8g = njSqrt(vec->x * vec->x + vec->z * vec->z);
	if (local_8g > range)
	{
		local_8g = range;
	}
	local_cg = ratio * local_8g / range;
	if (local_cg < 0.2f)
	{
		local_cg = 0.2f;
	}
	return local_cg;
}

// STUB: SADX 0x005aa840
long ChkSonicStack(struct taskwk *stwp)
{
	return (long)0;
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

// STUB: SADX 0x005aa910
short SetSonicNextPath(struct taskwk *twp, struct taskwk *stwp, struct sSonicCtrl *sonic_ctrl, short sonic_path)
{
	return (short)0;
}

// STUB: SADX 0x005aaa70
void DrawMoble2P(struct task *tp)
{
}

// STUB: SADX 0x005aab20
void EggmobleJetEntry(struct task *tp, struct eggmoble_effect *egg)
{
}

// STUB: SADX 0x005aac80
void EggmobleHeadLightEntry(struct task *tp)
{
}

// STUB: SADX 0x005aae10
short ChkMoblePathPos(struct taskwk *twp, struct sMobleCtrl *moble_ctrl)
{
	return (short)0;
}

// STUB: SADX 0x005aafa0
void AddMobleSpeed(struct taskwk *twp, struct sMobleCtrl *moble_ctrl)
{
}

// STUB: SADX 0x005ab160
void FUN_005ab160(int param_1, int param_2)
{
}

// STUB: SADX 0x005ab220
void VibrateMoble(struct taskwk *twp, struct sMobleCtrl *moble_ctrl)
{
}

// STUB: SADX 0x005ab280
void MRaceVoiceCtrl(struct task *tp, short new_m_path, short new_s_path)
{
}

// STUB: SADX 0x005ab3e0
void MRaceSetVoice(struct anywk *awp, long type)
{
}

// STUB: SADX 0x005ab4a0
int FUN_005ab4a0()
{
	return (int)0;
}

// FUNCTION: SADX 0x005ab510
void SetTexture_EggMoble(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	local_8->value.ptr = &texlist_MRace_Eggmoble;
	texLoadTexturePvmFile(DAT_009960fc, (struct NJS_TEXLIST *)local_8->value.ptr);
	tp->exec = (void (*)(struct task *))FUN_005b5aa0;
	tp->dest = DstrReleaseTexture;
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

// STUB: SADX 0x005ab840
void MRaceDispResult(struct task *tp)
{
}

// STUB: SADX 0x005ab930
void DrawResult(struct task *tp)
{
}
