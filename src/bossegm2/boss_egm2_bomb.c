#include "decls.h"
extern struct NJS_TEXLIST texlist_egm2_common;
extern struct obj object_egm2_mine[1];
extern int DAT_05b9d838;

// FUNCTION: SADX 0x006ca110
void Dsp_bomb(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_egm2_common);
	MirenEffSaveState();
	OnConstantAttr(0, 0x2000000);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	late_DrawObjectClipEx(object_egm2_mine, 1, 1.0f);
	njPopMatrix(1);
	MirenEffLoadState();
}

// FUNCTION: SADX 0x006ca180
void End_bomb(struct task *pTask)
{
	EraseDolbyCtrl(pTask->twp);
}

// FUNCTION: SADX 0x006ca290
void Egm2bombSet(struct NJS_POINT3 *base_pos, struct NJS_POINT3 *speed, long first)
{
	struct task *var1;
	struct taskwk *var2;
	struct enemywk *var3;

	var1 = CreateElementalTask(2, 3, Exe_bomb);
	if (!var1)
	{
		return;
	}
	var2 = var1->twp;
	var3 = (struct enemywk *)CAlloc(1, 0x10);
	if (!var3)
	{
		FreeTask(var1);
		return;
	}
	var1->awp = (struct anywk *)var3;
	EnemyInitialize(var1, var2);
	var2->pos = *base_pos;
	*(NJS_POINT3 *)var3 = *speed;
	*(long *)((char *)var3 + 0xc) = first;
	var1->exec = Exe_bomb;
	var1->disp = Dsp_bomb;
	var1->dest = End_bomb;
	CCL_Init(var1, colliInfo, 1, 4);
	if (!first)
	{
		dsPlay_oneshot_Dolby(0x1e4, 0, 0, 0xffffff6a, 0x78, var2);
	}
}

// STUB: SADX 0x006ca360
void Egm2Bomb(struct task *tp)
{
}
