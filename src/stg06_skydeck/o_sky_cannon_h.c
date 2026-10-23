#include "decls.h"
extern int DAT_05edc104[10];

// FUNCTION: SADX 0x008497b0
void DeadRockets()
{
	int var1;

	for (var1 = 0; var1 < 10; var1++)
	{
		if (DAT_05edc104[var1])
			((char *)DAT_05edc104[var1])[3] |= 8;
	}
}
