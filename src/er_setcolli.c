#include "decls.h"
extern const char DAT_00a356a0[];
extern const char DAT_00a356b0[];
extern const char DAT_00a356c0[];
extern const char DAT_00a356cc[];
extern const char DAT_00a356d8[];
extern const char DAT_00a356ec[];
extern const char DAT_00a356f8[];
extern const char DAT_00a35704[];
extern const char DAT_00a35710[];
extern int DAT_04c7bb1c[];

// FUNCTION: SADX 0x008ddd00
void ERSetColli(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	ERSC_CorrectParameter(local_8);
	ERSC_CommonExec(tp);
	tp->exec = ERSC_CommonExec;
}

// STUB: SADX 0x008ddd40
void ERSC_CorrectParameter(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x008de700
void ERSC_DisplayEditInfo(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	local_8->btimer++;
	if (FUN_004c39c0(tp) != 0)
	{
		if ((local_8->btimer & 0x10) != 0)
		{
			njPrintC(0x80008, DAT_00a356a0);
		}
		else
		{
			njPrintC(0x80008, DAT_00a356b0);
		}
		njPrintC(0x110010, DAT_00a356c0);
		njPrintC(0x190010, (const char *)DAT_04c7bb1c[local_8->wtimer]);
		njPrintC(0x110011, DAT_00a356cc);
		if (local_8->wtimer == 2)
		{
			njPrintC(0x110012, DAT_00a356d8);
		}
		else
		{
			njPrintC(0x110012, DAT_00a356ec);
		}
		njPrintC(0x110013, DAT_00a356f8);
		njPrintC(0x110014, DAT_00a35704);
		njPrintC(0x110015, DAT_00a35710);
	}
}
