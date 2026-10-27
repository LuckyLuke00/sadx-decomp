#include "decls.h"
extern long SetObjectTexture();
extern void njRotateZ(float *, int);
extern void njPushMatrix(float *);
extern void njTranslateV(float *, struct NJS_POINT3 *);
extern void njRotateX(float *, unsigned short);
extern void njRotateY(float *, unsigned short);
extern void njPopMatrix(int);
extern char DAT_060dba68;
extern struct taskwk *DAT_05b42a7c;
extern int DAT_05b9d838;
extern struct NJS_SPRITE sprite_yukikemu;

// STUB: SADX 0x0085c040
void Exit2(struct task *tp)
{
}

// STUB: SADX 0x0085c0a0
void Disp1(struct task *tp)
{
}

// FUNCTION: SADX 0x0085ced0
void cDispYukikemu(struct task *ctp)
{
	struct taskwk *var1 = ctp->twp;
	if (DAT_05b9d838 == 0)
	{
		njPushMatrix((float *)0);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)DAT_05b42a7c + 0x18) != 0)
		{
			njRotateY((float *)0, (unsigned short)*(short *)((char *)DAT_05b42a7c + 0x18));
		}
		if (*(int *)((char *)DAT_05b42a7c + 0x14) != 0)
		{
			njRotateX((float *)0, *(unsigned short *)((char *)DAT_05b42a7c + 0x14));
		}
		late_DrawSprite3D(&sprite_yukikemu, var1->timer.l / 2, 0x20, 4);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x0085d080
void cDispSnow(struct task *ctp)
{
}

// FUNCTION: SADX 0x0085d290
void cDispRock(struct task *ctp)
{
	struct taskwk *var1 = ctp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix((float *)0);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, *(unsigned short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x10) != 0)
		{
			ds_DrawModelClip((struct NJS_MODEL *)&model_sky_h_hahen01a_h_hahen01a, 1.0f);
		}
		else
		{
			ds_DrawModelClip((struct NJS_MODEL *)&model_sky_h_hahen02a_h_hahen02a, 1.0f);
		}
		njPopMatrix(1);
	}
}

// STUB: SADX 0x0085d560
void PlayerJump(struct task *ctp)
{
}

// FUNCTION: SADX 0x0085d630
void ObjectNadareStart()
{
	DAT_060dba68 = 1;
}
