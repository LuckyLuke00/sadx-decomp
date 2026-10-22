#include "decls.h"
void FUN_00450d40(struct task *param_1);

// FUNCTION: SADX 0x0044f7f0
int FUN_0044f7f0(int param_1)
{
	long *var1 = NullMergeTreeList;

	while (*var1 != -1)
	{
		if (*var1 == param_1)
		{
			return 1;
		}
		var1 += 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00450210
void AL_ShapeExit(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (*(void **)((char *)var1 + 0x5c8) != NULL)
	{
		syFree(*(void **)((char *)var1 + 0x5c8));
	}
	if (*(void **)((char *)var1 + 0x5cc) != NULL)
	{
		syFree(*(void **)((char *)var1 + 0x5cc));
	}
	if (*(void **)((char *)var1 + 0x5d0) != NULL)
	{
		syFree(*(void **)((char *)var1 + 0x5d0));
	}
	AL_PaletteFree(tp);
	AL_FreeChaoObject(*(struct al_object **)((char *)var1 + 0x524));
}

// FUNCTION: SADX 0x00450270
long AL_ShapeChangeType(struct task *tp, unsigned long type)
{
	void *var1;

	var1 = *(void **)((char *)tp->twp + 0x6c);
	if (type >= 0x1a)
	{
		return 0;
	}
	switch (type)
	{
	case 0:
	case 1:
	case 3:
	case 4:
		return 0;
	default:
		AL_ShapeExit(tp);
		*(char *)((char *)var1 + 0x80) = (char)type;
		AL_ShapeInit(tp);
		AL_FaceInit(tp);
		AL_IconInit(tp);
		FUN_00450d40(tp);
		AL_PerceptionInit(tp);
		return 1;
	}
}
