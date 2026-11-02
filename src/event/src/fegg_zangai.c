#include "decls.h"
extern struct obj *ZANGAI_OBJ_TBL[8];
extern struct NJS_TEXLIST texlist_f_egg_zangai;

// FUNCTION: SADX 0x007e27d0
void fegg_zangai_dest(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (var1->value.ptr != 0)
	{
		Free(var1->value.ptr);
		var1->value.ptr = 0;
	}
}

// FUNCTION: SADX 0x007e2800
void fegg_zangai_draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	unsigned int var2 = *(unsigned char *)(var1->value.ptr);
	___njSetTexture(&texlist_f_egg_zangai);
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX(NULL, (unsigned short)*(short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(NULL, (unsigned short)*(short *)((char *)var1 + 0x18));
	}
	FUN_0067d2d0((float *)0, var1->scl.x, var1->scl.y, var1->scl.z);
	ds_DrawObjectClip(ZANGAI_OBJ_TBL[var2], FUN_00500c70(var1->scl.x, var1->scl.y, var1->scl.z));
	njPopMatrix(1);
}

// FUNCTION: SADX 0x007e2b60
void fegg_zangai_cons(struct task *tp)
{
	tp->exec = fegg_zangai_exec;
	tp->disp = fegg_zangai_draw;
	tp->dest = fegg_zangai_dest;
}
