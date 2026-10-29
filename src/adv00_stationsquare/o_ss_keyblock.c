#include "decls.h"
extern struct obj object_sssikake_blockbase_blockbase[];
extern int DAT_05b9d838;
extern struct CCL_INFO key_c_info[1];

// FUNCTION: SADX 0x006869a0
void DispPut(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawObjectClip(object_sssikake_blockbase_blockbase, 1.0f);
	ds_DrawObjectClip(object_sssikake_keyblock_keyblock, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00686aa0
void KeyDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawObjectClip(object_sssikake_keyblock_keyblock, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00686b10
void ExecPut(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp) == 0)
	{
		EntryColliList(var1);
		DispPut(tp);
	}
}

// FUNCTION: SADX 0x00686cd0
void KeyInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct motionwk *var2 = tp->mwp;

	var1->mode = 2;
	ObjectMovableInitialize(var1, var2, 4);
	var1->flag |= 2;
	CCL_Init(tp, key_c_info, 2, 4);
	tp->exec = KeyExec;
	tp->disp = KeyDisp;
}

// STUB: SADX 0x00686d10
void ObjectSSKeyblock(struct task *tp)
{
}
