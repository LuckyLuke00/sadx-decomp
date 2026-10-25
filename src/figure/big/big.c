#include "decls.h"
long FUN_0050aa70(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3);
extern unsigned short DAT_05cd296c;
void FUN_004bee10(void);
long FUN_0050aa70(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3);
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern int DAT_06298cac;
extern int DAT_05cc3fe0;
extern int DAT_05cc3ff0;
extern int DAT_05cc4000;
extern int DAT_05cc4010;
extern int DAT_05cc4020;

// FUNCTION: SADX 0x00508980
void BigDestruct(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	PDestruct(local_8->counter.b[0]);
	dsStop_id((int)local_8);
	if ((((DAT_05b9d724 << 8) | (short)DAT_05b9d744) & 0xff00) == 0x1300)
	{
		late_ReleaseTexture(&texlist_big);
	}
	else
	{
		ReleasePlayersTexture(7);
	}
}

// STUB: SADX 0x005089f0
void BigResetPosition(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x005090e0
void BigChangeRunningMotion(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x00509620
long BigCheckDamage(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x00509740
long BigCheckJump(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x005098c0
long BigCheckWater(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x00509950
long BigCheckAtack(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00509a00
long BigCheckAtack_W(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	if (BigCheckWater(twp, mwp, pwp) != 0 && (*(long *)((char *)DAT_05b932f8 + twp->counter.b[0] * 0x34) & action_button) != 0)
	{
		*(short *)((char *)pwp + 0x124) = 0x42;
		twp->mode = 0x28;
		return 1;
	}
	return 0;
}

// STUB: SADX 0x0050a9a0
long BigCheckFloat(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// FUNCTION: SADX 0x0050aa30
long BigCheckBeInTheWater(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	if (FUN_0050aa70(twp, mwp, pwp) != 0)
	{
		twp->mode = 0x2f;
		*(short *)((char *)pwp + 0x124) = 0x5c;
		return 1;
	}
	return 0;
}

// STUB: SADX 0x0050aa70
long FUN_0050aa70(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	return (long)0;
}

// FUNCTION: SADX 0x0050aaf0
long BigCheckBeInTheAir(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	if ((((short)twp->flag | pwp->flag) & 3) == 0)
	{
		if ((twp->flag & 0x800) != 0)
		{
			if ((PCheckHoldObject(twp) & 0x200) != 0)
			{
				twp->mode = 0x16;
				*(short *)((char *)pwp + 0x124) = 0x27;
				return 1;
			}
			BigThrowTheObjectOut(twp, mwp, pwp);
		}
		twp->mode = 8;
		*(short *)((char *)pwp + 0x124) = 0xe;
		return 1;
	}
	else
	{
		return 0;
	}
}

// STUB: SADX 0x0050ab80
long BigCheckStop(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// FUNCTION: SADX 0x0050ac30
long FUN_0050ac30(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	long local_8;

	PAdjustHoldingPosition(param_1, param_2, param_3);
	if (param_3->mj.nframe >= 6.0f)
	{
		local_8 = PCheckHoldObject(param_1);
		if (local_8)
		{
			switch (PCheckColliAngle(param_1, param_2))
			{
			case 4:
				if ((local_8 & 0x200) != 0)
				{
					param_1->mode = 0x34;
					return 1;
				}
				break;
			}
			FUN_0050ce80((char *)param_1, (int)param_2, (char *)param_3);
		}
	}
	return 0;
}

// STUB: SADX 0x0050acd0
long BigCheckHoldObject(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0050ae10
long BigCheckPickObject(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0050bc80
void BigGetFloat(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x0050c310
void BigEarsSwingEnd(struct task *tp)
{
}

// STUB: SADX 0x0050c330
long FUN_0050c330(long param_1, float *param_2)
{
	return (long)0;
}

// STUB: SADX 0x0050c8b0
void BigDirectAheadEnd(struct task *tp)
{
}

// STUB: SADX 0x0050c950
void BigStareAt(struct pheadeyewk *phewp)
{
}

// STUB: SADX 0x0050cb50
long ChkFishingThrowNow(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x0050cbb0
int FUN_0050cbb0(char *param_1)
{
	return (int)0;
}

// STUB: SADX 0x0050cbf0
void FUN_0050cbf0(struct playerwk *pwp)
{
}

// FUNCTION: SADX 0x0050cd80
void bigActMissSet(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// FUNCTION: SADX 0x0050ce30
void BigCameraSetFishingCamera()
{
	if (GM_CheckMode() == 1)
	{
		CameraSetEventCamera(8, 5);
	}
	else
	{
		CameraSetEventCameraFunc(CameraFishing, 3, 2);
	}
}

// FUNCTION: SADX 0x0050ce60
void FUN_0050ce60()
{
	if ((DAT_05cd296c & 0x40) != 0)
	{
		FUN_004bee10();
	}
	else
	{
		CameraReleaseEventCamera();
	}
}

// FUNCTION: SADX 0x0050ce80
void FUN_0050ce80(char *param_1, int param_2, char *param_3)
{
	*param_1 = 1;
	*(short *)(param_3 + 0x124) = 0;
	*(short *)(param_3 + 0xe) = 0;
	*(short *)(param_3 + 0x120) = 1;
}

// FUNCTION: SADX 0x0050ceb0
long IsBigWhistling(struct taskwk *twp)
{
	if (twp->mode == 0x36)
	{
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x0050ced0
long IsBigPutting(struct taskwk *twp)
{
	if (twp->mode == 0x10)
	{
		return 1;
	}
	return 0;
}

// STUB: SADX 0x0050d120
long checkturipoint2()
{
	return (long)0;
}

// FUNCTION: SADX 0x0050d320
void _bigmot_init()
{
	DAT_05cc3fe0 = *(int *)(DAT_06298cac + 0x10);
	DAT_05cc3ff0 = *(int *)(DAT_06298cac + 0x10);
	DAT_05cc4000 = *(int *)(DAT_06298cac + 0x74);
	DAT_05cc4020 = *(int *)(DAT_06298cac + 0x78);
	DAT_05cc4010 = DAT_05cc4020;
}
