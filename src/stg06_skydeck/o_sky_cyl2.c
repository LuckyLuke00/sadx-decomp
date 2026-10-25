#include "decls.h"
extern int DAT_05cbef64;

// FUNCTION: SADX 0x00847040
void ObjectSkydeck_c_cyl2_Exec(struct task *tp)
{
	if (SDCheckRangeOut(tp) == 0 && (DAT_05cbef64 & 1) != 0)
	{
		ObjectSkydeck_c_cyl2_Draw(tp);
		LoopTaskC(tp);
		FUN_004c39c0(tp);
	}
}

// FUNCTION: SADX 0x00847150
void ObjectSkydeck_c_cyl2(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 4410100.0f) == 0)
	{
		ObjectSkydeck_c_cyl2_Init(tp);
	}
}
