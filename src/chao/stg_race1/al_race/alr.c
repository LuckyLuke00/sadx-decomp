#include "decls.h"

// FUNCTION: SADX 0x00486880
void Alr_SetWorkData(struct Alr *___this, struct taskwk *twp, struct alifewk *awp)
{
	___this->flag |= 2;
	___this->awp = awp;
	___this->twp = twp;
	if (___this->flag & 1)
	{
		___this->flag |= 4;
	}
}

// FUNCTION: SADX 0x004868c0
void Alr_Close(struct Alr *___this)
{
	___this->flag &= 0xfff8;
	___this->awp = 0;
	___this->twp = 0;
}

// FUNCTION: SADX 0x004868e0
void Alr_Kill(struct Alr *___this)
{
	if (___this->awp)
	{
		DestroyTask(*(struct task **)((char *)___this->awp + 0x8cc));
		___this->flag = 0;
	}
}

// FUNCTION: SADX 0x00486910
int Alr_CheckOpen(struct Alr *___this)
{
	return *(unsigned char *)(&___this->flag) >> 2 & 1;
}

// FUNCTION: SADX 0x00486930
struct alifewk *Alr_GetAwp(struct Alr *___this)
{
	if ((___this->flag & 4) != 0)
	{
		return ___this->awp;
	}
	return 0;
}

// FUNCTION: SADX 0x00486950
struct taskwk *Alr_GetTwp(struct Alr *___this)
{
	if (___this->flag & 4)
		return ___this->twp;
	return 0;
}

// FUNCTION: SADX 0x00486970
void Alr_ExeWaterEff(struct Alr *___this, struct NJS_POINT3 *trans, struct NJS_POINT3 *velo)
{
	___this->flag |= 0x20;
	AlrEff_SetFlag(&___this->eff, 0x10);
	AlrEff_Exe(&___this->eff, trans, velo);
}

// STUB: SADX 0x004869a0
int Alr_CheckRace(const struct Alr *___this)
{
	return (int)0;
}

// STUB: SADX 0x004869c0
int Alr_CheckGoal(const struct Alr *___this)
{
	return (int)0;
}
