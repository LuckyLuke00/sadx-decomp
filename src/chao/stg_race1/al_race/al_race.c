#include "decls.h"
struct task;
struct taskwk;

// FUNCTION: SADX 0x0048b540
void ALR_ALRE_Happy(struct taskwk *twp, struct alifewk *awp)
{
	switch (twp->smode)
	{
		case 0:
			ADV1toADV2_SetMotionLink(awp, 0xb);
			*(float *)((char *)awp + 0x144) = 7.0f;
			*(float *)((char *)awp + 0x134) = 1.0f;
			twp->smode++;
			twp->btimer = 0;
			twp->wtimer = 0;
			break;
		case 1:
			break;
		default:
			return;
	}
	awp->acc.x = awp->acc.x - (awp->velo.x * 0.10000000149011612f);
	awp->acc.z = awp->acc.z - (awp->velo.z * 0.10000000149011612f);
	if (awp->velo.x < 0.009999999776482582f)
	{
		awp->velo.x = 0.0f;
	}
	if (awp->velo.z < 0.009999999776482582f)
	{
		awp->velo.z = 0.0f;
	}
	ADV1_AL_SetEyeNum(awp, 2, 2);
	ADV1_AL_SetMouseNum(awp, 1, 2);
	*(unsigned short *)((char *)awp + 0x812) = 5;
	*(unsigned short *)((char *)awp + 0x848) = 0;
	*(unsigned short *)((char *)awp + 0x888) = 0;
	*(unsigned short *)((char *)awp + 0x814) = 2;
}

// STUB: SADX 0x0048ba20
void ALR_ALRE_Dance(struct taskwk *twp, struct alifewk *awp)
{
}

// STUB: SADX 0x0048c3a0
void ALR_Destructor(struct task *tp)
{
}

// STUB: SADX 0x0048c3d0
void ALR_Clear(struct task *tp)
{
}

// STUB: SADX 0x0048c4f0
void FUN_0048c4f0(struct Alr *param_1, struct AlrEffUnit *param_2)
{
}

// STUB: SADX 0x0048c610
float FUN_0048c610(struct al_race *ar)
{
	return (float)0;
}
