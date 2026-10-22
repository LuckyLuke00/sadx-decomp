#include "decls.h"
extern int DAT_05edc134;
extern unsigned char DAT_05cc43a1;
extern int DAT_05edc138;

// STUB: SADX 0x005b9d40
void E102AddRestTime(int add_time)
{
}

// FUNCTION: SADX 0x005ba1d0
void AddTimeComboAfterDest(struct task *tp)
{
	DAT_05edc138--;
}

// STUB: SADX 0x005ba1f0
void E102AddSecTotalNewDisplay(struct task *tp)
{
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
