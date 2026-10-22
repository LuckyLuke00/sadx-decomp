#include "decls.h"
extern void (*DAT_01c77460[256])(int);
extern int DAT_05ada440;

// STUB: SADX 0x004350b0
void _njDirectResAdd(struct NJS_MESHSET *param_1)
{
}

// FUNCTION: SADX 0x00435130
void _njDirectResDel(struct NJS_MESHSET *param_1)
{
	void *var1;
	void *var2;

	var1 = param_1->ext;
	if (var1)
	{
		var2 = *(void **)((char *)var1 + 4);
		if (*(void **)var2)
		{
			*(void **)((char *)*(void **)var2 + 4) = *(void **)((char *)var2 + 4);
		}
		if (*(void **)((char *)var2 + 4))
		{
			*(void **)(*(void **)((char *)var2 + 4)) = *(void **)var2;
		}
		else
		{
			*(void **)&DAT_01c77460[142] = *(void **)var2;
		}
		syFree(var1);
		syFree(var2);
		DAT_05ada440--;
		param_1->ext = 0;
	}
}

// FUNCTION: SADX 0x00435190
void _njDirectResDelAll(void)
{
	while (DAT_01c77460[143] != 0)
	{
		_njDirectReleaseMesh(*(NJS_MESHSET **)((char *)DAT_01c77460[143] + 8));
	}
}
