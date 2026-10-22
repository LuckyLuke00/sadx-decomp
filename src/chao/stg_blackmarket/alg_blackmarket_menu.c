#include "decls.h"
int FUN_0046ffb0();

// STUB: SADX 0x0046f6e0
void FUN_0046f6e0(int param_1)
{
}

// STUB: SADX 0x0046f700
void FUN_0046f700(int param_1, int param_2)
{
}

// STUB: SADX 0x0046f9e0
void FUN_0046f9e0(char param_1, char param_2)
{
}

// FUNCTION: SADX 0x0046ffd0
int FUN_0046ffd0()
{
	return FUN_0046ffb0();
}

// FUNCTION: SADX 0x00471aa0
long AL_BlackmarketMenuOver(struct task *tp)
{
	if (tp->awp != 0 && tp->awp->work.ul[1] == 0xf)
	{
		return 1;
	}
	return 0;
}
