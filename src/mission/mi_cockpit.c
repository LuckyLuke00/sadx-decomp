#include "decls.h"
extern int DAT_05b37308;

// FUNCTION: SADX 0x00497340
int IsDisplayMiClearStatus()
{
	return DAT_05b37308 == 2;
}

// FUNCTION: SADX 0x00497350
void DispMiClearStatusOn()
{
	if (DAT_05b37308 == 0)
	{
		DAT_05b37308 = 1;
	}
}

// FUNCTION: SADX 0x00497370
long GetMiClearStatus()
{
	return DAT_05b37308 != 0;
}
