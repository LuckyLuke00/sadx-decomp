#include "decls.h"
extern struct obj object_cas_cl_kinko_wall_kinko_wall[1];

// FUNCTION: SADX 0x008799c0
void CasinoClearCollisionExec(struct task *tp)
{
	if (GetKinkaiNum() >= 0x190)
	{
		FreeTask(tp);
	}
}

// FUNCTION: SADX 0x008799e0
void CasinoClearCollisionDest(struct task *tp)
{
	WithdrawCollisionEntry(tp, (struct obj *)&object_cas_cl_kinko_wall_kinko_wall);
}

// STUB: SADX 0x0087a440
void CasinoClearCollisionInit(struct task *tp)
{
}

// FUNCTION: SADX 0x0087a520
void ObjectCasinoShakeHand(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 62510.0f) == 0)
	{
		if (GetPlayerNumber() == 0)
		{
			CreateElementalTask(2, 6, CasinoClearCollisionInit);
		}
		ObjectCasinoShakeHandInit(tp);
	}
}
