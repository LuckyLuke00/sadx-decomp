#include "decls.h"
extern int DAT_05edc134;
extern unsigned char DAT_05cc43a1;
extern int DAT_05edc138;

// FUNCTION: SADX 0x005ba1d0
void AddTimeComboAfterDest(struct task *tp)
{
	DAT_05edc138--;
}

// FUNCTION: SADX 0x005ba3b0
void E102AddSecTotalNewDest(struct task *tp)
{
	DAT_05edc134 = 0;
	DAT_05cc43a1 = 1;
	if (((signed char)tp->twp->mode) != 0x7f)
	{
		DAT_05edc138 = DAT_05edc138 - 1;
	}
}
