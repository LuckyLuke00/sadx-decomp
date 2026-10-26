#include "decls.h"
extern struct obj *untei_objtbl[4];

// FUNCTION: SADX 0x00835aa0
void Object_Mountain_Untei_Display(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct obj *var2 = untei_objtbl[var1->smode];

	if (dsCheckViewV(&var1->pos, 200.0f))
	{
		___njSetTexture(&texlist_obj_mountain);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(0, (unsigned short)*(short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(0, (unsigned short)*(short *)((char *)var1 + 0x18));
		}
		ds_DrawObjectClip(var2, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00835d90
void Object_Mountain_Untei1(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		tp->twp->smode = 0;
		tp->twp->wtimer = 0x11;
		tp->twp->scl.x = 0.0f;
		tp->twp->scl.y = 0.0f;
		tp->twp->scl.z = -3.0f;
	}
	Object_Mountain_Untei(tp);
}

// FUNCTION: SADX 0x00835de0
void Object_Mountain_Untei2(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		tp->twp->smode = 1;
		tp->twp->wtimer = 0x11;
		tp->twp->scl.x = 0.0f;
		tp->twp->scl.y = 0.0f;
		tp->twp->scl.z = -3.0f;
	}
	Object_Mountain_Untei(tp);
}

// FUNCTION: SADX 0x00835e30
void Object_Mountain_Untei3(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		tp->twp->smode = 2;
		tp->twp->wtimer = 2;
		tp->twp->scl.x = -10.0f;
		tp->twp->scl.y = 0.0f;
		tp->twp->scl.z = 3.0f;
	}
	Object_Mountain_Untei(tp);
}

// FUNCTION: SADX 0x00835e80
void Object_Mountain_Untei6(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		tp->twp->smode = 3;
		tp->twp->wtimer = 5;
		tp->twp->scl.x = -10.0f;
		tp->twp->scl.y = 0.0f;
		tp->twp->scl.z = 12.0f;
	}
	Object_Mountain_Untei(tp);
}
