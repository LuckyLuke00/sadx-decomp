#include "decls.h"
void FUN_0045ffc0(int param_1);
void AL_WalkSelect(struct task *tp);

// FUNCTION: SADX 0x0045ffe0
long ALBHV_Move(struct task *tp)
{
	FUN_0045ffc0((int)tp);
	AL_WalkSelect(tp);
	return 0;
}

// STUB: SADX 0x004609a0
long AL_CheckWhistle(struct task *tp)
{
	return (long)0;
}
