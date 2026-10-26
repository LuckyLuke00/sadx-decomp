#include "decls.h"
extern int DAT_060cb32c;

// FUNCTION: SADX 0x00717030
void ChaoSelectWindowDestructor(struct task *tp)
{
	struct task **var1 = (struct task **)((char *)tp->awp + 0x2c);
	int var2 = 8;
	do
	{
		if (*var1 != 0)
		{
			FreeTask(*var1);
			*var1 = 0;
		}
		var1 = var1 + 1;
		var2 = var2 - 1;
	}
	while (var2 != 0);
	DAT_060cb32c = var2;
}
