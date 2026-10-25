#include "decls.h"
extern void *syCalloc(unsigned int param_1, unsigned int param_2);
extern void syFree(void *param_1);
extern void (*DAT_01c77460[256])(int);
extern int DAT_05ada440;

// FUNCTION: SADX 0x004350b0
void _njDirectResAdd(struct NJS_MESHSET *param_1)
{
	void *var1;
	void *var2;
	void *var3;

	if (param_1->ext == 0)
	{
		var1 = syCalloc(0xc, 1);
		var2 = syCalloc(0x28, 1);
		if (var2)
		{
			if (var1)
			{
				DAT_05ada440++;
				var3 = DAT_01c77460[142];
				*(void **)var1 = var3;
				*(void **)((char *)var1 + 4) = 0;
				*(void **)((char *)var3 + 4) = var1;
				DAT_01c77460[142] = (void (__cdecl *)(int))var1;
				*(void **)((char *)var1 + 8) = param_1;
				param_1->ext = var2;
				*(void **)((char *)var2 + 4) = var1;
				*(void **)var2 = param_1;
			}
			else
			{
				syFree(var2);
			}
		}
		else
		{
			if (var1)
			{
				syFree(var1);
			}
		}
	}
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
