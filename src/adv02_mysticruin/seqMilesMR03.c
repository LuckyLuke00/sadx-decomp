#include "decls.h"

// FUNCTION: SADX 0x006aaa10
void initMilesMR03()
{
	if (EV_CheckExec(0x3e))
	{
		SeqSetTime(1);
		return;
	}
	SeqSetTime(0);
}
