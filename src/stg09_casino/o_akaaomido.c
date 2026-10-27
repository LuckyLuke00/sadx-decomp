#include "decls.h"

// FUNCTION: SADX 0x00883320
void __fastcall TenmetuSub(struct task *ctp)
{
	struct taskwk *var1 = ctp->twp;
	struct task *var2 = ctp->ptp;
	if (var2->twp->flag & 0x100)
	{
		if (var1->value.l > 0xc000)
		{
			var1->value.l = 0x4000;
			return;
		}
		var1->value.l += 0x200;
	}
}
