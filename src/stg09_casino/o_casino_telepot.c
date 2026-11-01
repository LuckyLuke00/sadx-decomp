#include "decls.h"

// GLOBAL: SADX 0x0480c088
static struct TEXUVINFO2 texuv2info[2];

extern int DAT_060dc42c;

// FUNCTION: SADX 0x0087af10
void ObjectCasinoTelepotEnd(struct task *tp)
{
	if (tp->twp->mode == 2 && *(short *)((char *)tp->twp + 0x12) == (DAT_05b9d724 << 8 | DAT_05b9d744))
	{
		lig_fillOffsetPalette(2, 0, 1);
	}
	if (DAT_060dc42c == (int)tp)
	{
		DAT_060dc42c = 0;
	}
	FUN_007d21b0(texuv2info, 2);
}

// FUNCTION: SADX 0x0087b370
long ObjectCasinoGetTelepotStatus()
{
	return DAT_060dc42c != 0;
}
