#include "decls.h"
extern unsigned char DAT_05cbef64;

// FUNCTION: SADX 0x00847f20
void ObjectSkydeck_c_cyl0_Exec(struct task *tp)
{
	if (SDCheckRangeOut(tp) == 0 && DAT_05cbef64 & 1)
	{
		ObjectSkydeck_c_cyl0_Draw(tp);
		LoopTaskC(tp);
		FUN_004c39c0(tp);
	}
}

// FUNCTION: SADX 0x00848030
void ObjectSkydeck_c_cyl0(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 4410100.0f) == 0)
	{
		ObjectSkydeck_c_cyl0_Init(tp);
	}
}
