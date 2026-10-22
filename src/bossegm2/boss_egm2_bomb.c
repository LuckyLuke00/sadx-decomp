#include "decls.h"
extern struct NJS_MKEY_F pos_alm_piyo_reg_r[1];
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
