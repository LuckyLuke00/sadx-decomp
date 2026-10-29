#include "decls.h"
void FUN_00450d20(struct al_object *param_1);
void FUN_00450d20(struct al_object *param_1);
void FUN_00450d20(struct al_object *param_1);
void FUN_00450d20(struct al_object *param_1);
void AL_SetMiminalParts(struct task *tp, long PartsKind, long MinimalType);
void FUN_00450c30(int param_1);
extern struct cnkobj **pPartsObjectListAdult[1];
extern long PartsObjectListNumber[8][2];
extern struct cnkobj * pPartsObjectListChild[];

// FUNCTION: SADX 0x004507f0
long AL_IsExistPartsChild(long MinimalNum, long PartsKind)
{
	return *(struct cnkobj **)((char *)pPartsObjectListChild[MinimalNum] + PartsObjectListNumber[PartsKind][0] * 4) != 0;
}

// FUNCTION: SADX 0x00450820
long AL_IsExistPartsAdult(long MinimalNum, long PartsKind)
{
	return pPartsObjectListAdult[MinimalNum][PartsObjectListNumber[PartsKind][0]] != NULL;
}

// FUNCTION: SADX 0x00450850
void AL_ClearPartsSub(struct al_object *pObject)
{
	while (pObject != 0)
	{
		pObject->pPartsObject = 0;
		if (pObject->pChild != 0)
		{
			AL_ClearPartsSub(pObject->pChild);
		}
		pObject = pObject->pSibling;
	}
}

// FUNCTION: SADX 0x00450890
void AL_ClearParts(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x11c) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x4e4) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x11d) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x4e5) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x11e) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x4e6) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x11f) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x4e7) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x120) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x4e8) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x121) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x4e9) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x122) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x4ea) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x123) = -1;
	*(char *)((char *)*(void **)((char *)var1 + 0x6c) + 0x4eb) = -1;
	AL_ClearPartsSub((struct al_object *)*(void **)((char *)var1 + 0x524));
}

// FUNCTION: SADX 0x00450a50
void AL_RemoveMinimalParts(struct task *tp, long PartsKind)
{
	AL_SetMiminalParts(tp, PartsKind, -1);
}

// STUB: SADX 0x00450a70
void AL_SetObakeHead(struct task *tp, enum eHEAD_PARTS HeadType)
{
}

// STUB: SADX 0x00450a90
void AL_SetItem(struct task *tp, long TreeNum, struct cnkobj *pObject, struct NJS_TEXLIST *pTexlist)
{
}

// STUB: SADX 0x00450b00
void AL_SetItemOffset(struct task *tp, long TreeNum, struct AL_ITEM_INFO *pInfo)
{
}

// FUNCTION: SADX 0x00450bd0
void AL_SetItemParallelLeftHand(struct task *tp, struct cnkobj *pObject, struct NJS_TEXLIST *pTexlist)
{
	struct taskwk *var1 = tp->twp;
	*(float *)((char *)var1 + 0x66c) = 0.0f;
	*(float *)((char *)var1 + 0x670) = 1.0f;
	*(struct cnkobj **)((char *)var1 + 0x664) = pObject;
	*(struct NJS_TEXLIST **)((char *)var1 + 0x668) = pTexlist;
}

// FUNCTION: SADX 0x00450c00
void AL_SetItemParallelRightHand(struct task *tp, struct cnkobj *pObject, struct NJS_TEXLIST *pTexlist)
{
	struct taskwk *var1;

	var1 = tp->twp;
	*(float *)((char *)var1 + 0x67c) = 0.0f;
	*(float *)((char *)var1 + 0x680) = 1.0f;
	*(struct cnkobj **)((char *)var1 + 0x674) = pObject;
	*(struct NJS_TEXLIST **)((char *)var1 + 0x678) = pTexlist;
}

// FUNCTION: SADX 0x00450c30
void FUN_00450c30(int param_1)
{
	*(int *)(param_1 + 0xa4) = 0;
}

// FUNCTION: SADX 0x00450c40
void AL_RemoveItemAllSub(struct al_object *pObject)
{
	while (pObject != 0)
	{
		FUN_00450c30((int)pObject);
		if (pObject->pChild != 0)
		{
			AL_RemoveItemAllSub(pObject->pChild);
		}
		pObject = pObject->pSibling;
	}
}

// FUNCTION: SADX 0x00450c80
void AL_RemoveItemAll(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	AL_RemoveItemAllSub(*(struct al_object **)((char *)var1 + 0x524));
	*(float *)((char *)var1 + 0x670) = 0.0f;
	*(float *)((char *)var1 + 0x680) = 0.0f;
}

// FUNCTION: SADX 0x00450cb0
void AL_ClearItemAllSub(struct al_object *pObject)
{
	pObject->pItemObject = (struct cnkobj *)0;
	pObject->pItemTexlist = (struct NJS_TEXLIST *)0;
	pObject->ItemScale = 0.0f;
	pObject->ItemActiveFlag = 0;
}

// FUNCTION: SADX 0x00450ce0
void FUN_00450ce0(struct al_object *param_1)
{
	for (; param_1 != 0; param_1 = param_1->pSibling)
	{
		AL_ClearItemAllSub(param_1);
		if (param_1->pChild != 0)
		{
			FUN_00450ce0(param_1->pChild);
		}
	}
}

#pragma optimize("", off)
// STUB: SADX 0x00450d20
void FUN_00450d20(struct al_object *param_1)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00450d40
void FUN_00450d40(struct task *param_1)
{
	int var1;
	struct taskwk *var2;

	var2 = param_1->twp;
	for (var1 = 0; var1 < 8; var1++)
	{
		AL_SetMiminalParts(param_1, var1, *(signed char *)((char *)(*(void **)((char *)var2 + 0x6c)) + 0x4e4 + var1));
	}
	FUN_00450d20((struct al_object *)param_1);
}

// FUNCTION: SADX 0x00450d80
void AL_PartsMinimalFlagOn_BTL(struct task *tp, long MinimalType)
{
	struct taskwk *var1 = tp->twp;
	*(unsigned long *)((char *)(*(unsigned long *)((char *)var1 + 0x6c)) + 0x118) |= (1UL << MinimalType);
}

// FUNCTION: SADX 0x00450da0
void AL_PartsMinimalFlagOff_BTL(struct task *tp, long MinimalType)
{
	struct taskwk *var1 = tp->twp;
	*(unsigned long *)((char *)(*(unsigned long *)((char *)var1 + 0x6c)) + 0x118) &= ~(1UL << MinimalType);
}

// STUB: SADX 0x00450dc0
long AL_PartsIsMinimalFlagOn_BTL(struct task *tp, long MinimalType)
{
	return (long)0;
}

// FUNCTION: SADX 0x00450df0
void AL_PartsMinimalFlagOn_DX(struct task *tp, long MinimalType)
{
	struct taskwk *var1 = tp->twp;
	*(unsigned long *)((char *)(*(unsigned long *)((char *)var1 + 0x6c)) + 0x4e0) |= (1UL << MinimalType);
}

// FUNCTION: SADX 0x00450e10
void AL_PartsMinimalFlagOff_DX(struct task *tp, long MinimalType)
{
	struct taskwk *var1 = tp->twp;
	*(unsigned long *)((char *)(*(unsigned long *)((char *)var1 + 0x6c)) + 0x4e0) &= ~(1UL << MinimalType);
}

// STUB: SADX 0x00450e30
long AL_PartsIsMinimalFlagOn_DX(struct task *tp, long MinimalType)
{
	return (long)0;
}
