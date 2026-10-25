#include "decls.h"
void FUN_006cc5e0(struct task *param_1);
void FUN_004a0520(float, float);
extern struct NJS_POINT2 DAT_05b3e080;

// STUB: SADX 0x006cc9a0
void FUN_006cc9a0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	switch (var1->mode)
	{
	case 0:
		((void (*)())FUN_006cc5e0)();
		___njSetBackColor(0xff000000, 0xff000000, 0xff000000);
		var1->mode = 1;
		break;
	case 1:
		break;
	case 2:
		var1->mode = 0;
		break;
	default:
		Free(param_1);
		break;
	}
	FUN_004a0520(DAT_05b3e080.x, DAT_05b3e080.y);
}
