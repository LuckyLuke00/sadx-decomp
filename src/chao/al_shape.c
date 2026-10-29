#include "decls.h"
struct task;
struct taskwk;
void FUN_00450d40(struct task *param_1);

// FUNCTION: SADX 0x0044f330
void AL_FreeChaoObject(struct al_object *pObject)
{
	struct al_model *var1;

	if (pObject != 0)
	{
		if (pObject->pChild != 0)
		{
			AL_FreeChaoObject(pObject->pChild);
			pObject->pChild = 0;
		}
		if (pObject->pSibling != 0)
		{
			AL_FreeChaoObject(pObject->pSibling);
			pObject->pSibling = 0;
		}
		var1 = pObject->pModel;
		if (var1 != 0)
		{
			if (var1->VList != 0)
			{
				syFree(var1->VList);
				var1->VList = 0;
			}
			if (var1->PList != 0)
			{
				syFree(var1->PList);
				var1->PList = 0;
			}
			if (var1->pOrgVertexPos != 0)
			{
				syFree(var1->pOrgVertexPos);
				var1->pOrgVertexPos = 0;
			}
			if (var1->pOrgVertexNormal != 0)
			{
				syFree(var1->pOrgVertexNormal);
				var1->pOrgVertexNormal = 0;
			}
			if (var1->pVertexInfo != 0)
			{
				syFree(var1->pVertexInfo);
				var1->pVertexInfo = 0;
			}
			syFree(var1);
		}
		if (pObject->pOldMatrix != 0)
		{
			syFree(pObject->pOldMatrix);
		}
		syFree(pObject);
	}
}

// STUB: SADX 0x0044f6d0
float FUN_0044f6d0(struct task *param_1, struct task *param_2, int param_3, float param_4)
{
	return (float)0;
}

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
