#include "decls.h"

// FUNCTION: SADX 0x0046b990
void AL_WalkSelect(struct task *tp)
{
	unsigned short var1;

	var1 = (unsigned short)AL_ParameterGetSkill(tp, 2);
	if (var1 < *(unsigned short *)((char *)&ChaoGlobal + 0x126))
	{
		AL_SetBehavior(tp, ALBHV_PostureChangeSit);
		AL_SetNextBehavior(tp, ALBHV_HaiHai);
		return;
	}
	if (var1 < *(unsigned short *)((char *)&ChaoGlobal + 0x128))
	{
		AL_SetBehavior(tp, ALBHV_PostureChangeStand);
		AL_SetNextBehavior(tp, ALBHV_WalkNormal);
		return;
	}
	if (var1 < *(unsigned short *)((char *)&ChaoGlobal + 0x12a))
	{
		AL_SetBehavior(tp, ALBHV_PostureChangeStand);
		AL_SetNextBehavior(tp, ALBHV_Run);
		return;
	}
	AL_SetBehavior(tp, ALBHV_PostureChangeStand);
	AL_SetNextBehavior(tp, ALBHV_Run2);
}
