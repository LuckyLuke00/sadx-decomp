#include "decls.h"
void AL_SetCurrMatrixSub(struct al_object *pObject);

// STUB: SADX 0x004638a0
void AL_InitCalcMotionMatrix(struct task *tp)
{
}

// STUB: SADX 0x00463e50
void AL_CalcMotionMartix(struct al_object *pObject)
{
}

// FUNCTION: SADX 0x00463ec0
void AL_SetCurrMatrixSub(struct al_object *pObject)
{
	do
	{
		njPushMatrixEx();
		njTranslateV(0, (struct NJS_POINT3 *)&pObject->Pos[0]);
		njRotateXYZ(0, pObject->Ang[0], pObject->Ang[1], pObject->Ang[2]);
		njGetMatrix((float *)pObject->pOldMatrix);
		if (pObject->pChild != 0)
		{
			AL_SetCurrMatrixSub(pObject->pChild);
		}
		njPopMatrixEx();
		pObject = pObject->pSibling;
	} while (pObject != 0);
}

// FUNCTION: SADX 0x00463f20
void AL_SetCurrMatrix(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	njPushMatrixEx();
	njUnitMatrix(0);
	njTranslateV(0, &var1->pos);
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(0, *(unsigned short *)((char *)var1 + 0x18));
	}
	AL_SetCurrMatrixSub(*(struct al_object **)((char *)var1 + 0x524));
	njPopMatrixEx();
}

// FUNCTION: SADX 0x004649b0
void AL_BuyoBuyoControl(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	*(unsigned short *)0x5b32d88 = 0;
	AL_InitCalcMotionMatrix(tp);
	njPushMatrixEx();
	njUnitMatrix(0);
	njTranslateV(0, &var1->pos);
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(0, *(unsigned short *)((char *)var1 + 0x18));
	}
	AL_BuyoBuyoObject(tp, *(struct al_object **)((char *)var1 + 0x524));
	njPopMatrixEx();
}
