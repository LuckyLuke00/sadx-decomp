#include "decls.h"

// STUB: SADX 0x00455460
long ALBHV_Bakuten(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x004556c0
long ALBHV_BreakDance(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00455710
long ALBHV_GoGoDanceMini(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00456030
long ALBHV_Fukkin(struct task *tp)
{
	AL_SetBehavior(tp, ALBHV_PostureChangeSit);
	AL_SetNextBehavior(tp, ALBHV_Fukkin2);
	return 0;
}
