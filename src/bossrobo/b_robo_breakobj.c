#include "decls.h"
extern int DAT_05b9d838;
void njMultiMatrix(float *, struct NJS_POINT3 *);

// FUNCTION: SADX 0x006e0a20
void calcModelNum(struct obj *pObj, int *pNum)
{
	do
	{
		*pNum = *pNum + 1;
		if (pObj->child != 0)
		{
			calcModelNum(pObj->child, pNum);
		}
		pObj = pObj->sibling;
	} while (pObj != 0);
}

// FUNCTION: SADX 0x006e0af0
void dispUnit(struct obj *pObj, struct OBJ_UNIT * *ppUnit)
{
	if (DAT_05b9d838 == 0)
	{
		do
		{
			if (pObj->model != 0)
			{
				njPushMatrix(0);
				njTranslateV(0, (struct NJS_POINT3 *)((char *)*ppUnit + 0x40));
				njMultiMatrix(0, (struct NJS_POINT3 *)*ppUnit);
				ds_DrawModelClip(pObj->model, 1.0f);
				njPopMatrix(1);
			}
			*ppUnit = (struct OBJ_UNIT *)((char *)*ppUnit + 0x68);
			if (pObj->child != 0)
			{
				dispUnit(pObj->child, ppUnit);
			}
			pObj = pObj->sibling;
		}
		while (pObj != 0);
	}
}
