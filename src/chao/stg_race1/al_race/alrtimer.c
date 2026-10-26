#include "decls.h"

// STUB: SADX 0x00488110
void AlrMemory_Clear(struct AlrMemory *___this)
{
}

// FUNCTION: SADX 0x00488150
void AlrTimer_Clear(struct AlrTimer *___this)
{
	FUN_00487e70((short *)___this);
}

// STUB: SADX 0x00488160
void AlrTimer_SetBest(struct AlrTimer *___this, struct AlrMemory *memory, int cup)
{
}

// FUNCTION: SADX 0x004881d0
void FUN_004881d0(struct AlrTimer *param_1)
{
	FUN_00487ea0((unsigned char *)param_1);
}

// STUB: SADX 0x004882d0
void AlrRank_Clear(struct AlrRank *___this)
{
}

// FUNCTION: SADX 0x00488680
int AlrRank_GetId(struct AlrRank *___this, int rank)
{
	if ((unsigned)rank <= 7)
	{
		return ___this->rank[rank];
	}
	return -1;
}
