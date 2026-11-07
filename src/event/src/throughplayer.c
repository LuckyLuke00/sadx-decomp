#include "decls.h"

// FUNCTION: SADX 0x007dbf90
void throughplayer_on(struct task *tp)
{
	struct colliwk *var1;
	int var2;

	var1 = tp->twp->cwp;
	var2 = 0;
	while (var2 < (int)(unsigned short)(var1->nbInfo))
	{
		*(unsigned char *)((char *)var1->info + var2 * 0x30 + 2) |= 0x30;
		var2++;
	}
}
