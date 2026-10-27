#include "decls.h"
extern int DAT_060dd0c0[21];

// FUNCTION: SADX 0x00891720
void Object_finalegg_saku_End(struct task *tp)
{
	int var2;
	struct task *var1 = (struct task *)tp->twp;

	DAT_060dd0c0[20]--;
	for (var2 = 0; var2 < 20; var2++)
	{
		if (DAT_060dd0c0[var2] == (int)var1)
		{
			DAT_060dd0c0[var2] = 0;
		}
	}
}
