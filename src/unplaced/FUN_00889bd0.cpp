#include "decls.h"

// FUNCTION: SADX 0x00889bd0
void FUN_00889bd0(struct TEXANIMINFO *param_1, int param_2)
{
	if (param_2 != 0)
	{
		while (1)
		{
			param_1->pmat->attr_texId = param_1->newtexid;
			param_1++;
			param_2--;
			if (param_2 == 0)
			{
				break;
			}
		}
	}
}
