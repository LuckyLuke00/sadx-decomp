#include "decls.h"

// FUNCTION: SADX 0x0080a490
void __fastcall FUN_0080a490(struct stg02_poline *param_1)
{
	struct stg02_poline *var1 = (struct stg02_poline *)DAT_05baf368[*(char *)((char *)param_1 + 1)];
	if (var1 != NULL)
	{
		if ((*(char *)((char *)var1 + 4) & 3) != 0)
		{
			*(int *)((char *)param_1 + 8) = 0;
			*(char *)param_1 = 1;
		}
		else
		{
			if (*(float *)((char *)var1 + 0x24) <= *(float *)((char *)param_1 + 0x24) + 19.0f + 20.0f)
			{
				*(short *)((char *)param_1 + 0xa) = *(short *)((char *)param_1 + 0xa) + 1;
				*(char *)param_1 = 3;
			}
		}
	}
}
