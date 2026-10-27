#include "decls.h"
void njRotateEx(long *param_1, int param_2);
extern void *DAT_05ad9a9c;

// STUB: SADX 0x0042b7e0
void _njEndModel(void)
{
}

// FUNCTION: SADX 0x0042b810
void _njTransformObject(struct obj *param_1, void (*param_2)(struct NJS_MODEL *))
{
	unsigned long var1;
	do
	{
		var1 = param_1->evalflags;
		if ((var1 & 7) == 7)
		{
			if ((var1 & 8) == 0)
			{
				param_2(param_1->model);
			}
			if ((var1 & 0x10) == 0)
			{
				_njTransformObject(param_1->child, param_2);
			}
		}
		else
		{
			njPushMatrixEx();
			if ((var1 & 1) == 0)
			{
				njTranslateEx(&param_1->pos);
			}
			if ((var1 & 2) == 0)
			{
				njRotateEx((long *)&param_1->ang, var1 & 0x20);
			}
			if ((var1 & 4) == 0)
			{
				njScaleEx(&param_1->scl);
			}
			if ((var1 & 8) == 0)
			{
				param_2(param_1->model);
			}
			if ((var1 & 0x10) == 0)
			{
				_njTransformObject(param_1->child, param_2);
			}
			njPopMatrixEx();
		}
		param_1 = param_1->sibling;
	} while (param_1);
}

// FUNCTION: SADX 0x0042ba90
void njSetMaterialCallBackFunc(void (*param_1)(void))
{
	DAT_05ad9a9c = param_1;
}
