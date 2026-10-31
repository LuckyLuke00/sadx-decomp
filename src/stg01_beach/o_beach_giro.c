#include "decls.h"

// GLOBAL: SADX 0x03a0c968
static struct CCL_INFO object_c_info[2];

// FUNCTION: SADX 0x007ffb60
void GiroColliOnly(struct task *tp)
{
	struct task *var1 = tp->ptp;
	struct taskwk *var2 = tp->twp;
	struct taskwk *var3 = var1->twp;

	switch (var2->mode)
	{
	case 0:
		CCL_Init(tp, object_c_info, 2, 4);
		var2->mode = 1;
		var2->pos.x = var3->pos.x;
		var2->pos.y = var3->pos.y;
		var2->pos.z = var3->pos.z;
		var2->ang.x = var3->ang.x;
		var2->ang.y = var3->ang.y;
		var2->ang.z = var3->ang.z;
		break;
	case 1:
		EntryColliList(var2);
		break;
	}
}
