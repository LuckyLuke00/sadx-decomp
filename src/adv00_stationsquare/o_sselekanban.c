#include "decls.h"
extern int DAT_05b9d838;
extern struct obj object_ssobj_elekanban_elekanban[];
extern struct NJS_MKEY_F pos_alm_piyo_reg_r[];
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// FUNCTION: SADX 0x0068c3d0
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		SaveControl3D();
		SaveConstantAttr();
		if (var1->smode == 1)
		{
			OnControl3D(4);
			OnConstantAttr(0, 0x2000000);
			OffConstantAttr(0x2000000, 0);
		}
		njPushMatrix(NULL);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, *(unsigned short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		SetObjectTexture();
		FUN_00422560(3);
		ds_DrawObjectClip(&object_ssobj_elekanban_elekanban[0], 1.0f);
		npSetZCompare();
		njPopMatrix(1);
		LoadConstantAttr();
		LoadControl3D();
	}
}

// FUNCTION: SADX 0x0068c4a0
static void Exec(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		Disp(tp);
	}
}

// FUNCTION: SADX 0x0068c4c0
void ObjectSSElekanban(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->mode = 0;
	var1->smode = (SeqGetTime() == 2);
	tp->exec = Exec;
	tp->disp = Disp;
}
