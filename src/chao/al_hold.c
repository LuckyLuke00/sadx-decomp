#include "decls.h"

// FUNCTION: SADX 0x00459e40
long AL_TraceHoldingPosition(struct task *pObjTask)
{
	struct taskwk *var1;
	struct forcewk *var2;

	var1 = pObjTask->twp;
	var2 = pObjTask->fwp;
	if (ALW_IsHeld(pObjTask) != 0)
	{
		if (ALW_IsCommunicationEx(pObjTask, 0) != 0)
		{
			var1->pos.x = var1->pos.x + (var2->pos_spd.x - var1->pos.x) * 0.30000001192092896;
			var1->pos.y = var1->pos.y + (var2->pos_spd.y - var1->pos.y) * 0.30000001192092896;
			var1->pos.z = var1->pos.z + (var2->pos_spd.z - var1->pos.z) * 0.30000001192092896;
			ALW_HeldOff((struct al_entry_work *)var2);
			return 1;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x00459ec0
void AL_GrabObjectBothHands(struct task *pChaoTask, struct task *pObjTask)
{
	struct taskwk *var1;

	var1 = pChaoTask->twp;
	ALW_CommunicationOn(pChaoTask, pObjTask);
	ALW_HeldOn(ALW_IsCommunication(pChaoTask));
	AL_MoveHoldingObject(pChaoTask);
	*(int *)((char *)var1 + 0xb0) |= 0xc00;
}
