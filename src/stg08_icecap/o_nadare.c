#include "decls.h"
extern void njPushMatrix(float *);
extern void njTranslateV(float *, struct NJS_POINT3 *);
extern void njRotateX(float *, unsigned short);
extern void njRotateY(float *, unsigned short);
extern void njPopMatrix(int);
extern char DAT_060dba68;
extern struct taskwk *DAT_05b42a7c;
extern int DAT_05b9d838;
extern struct NJS_SPRITE sprite_yukikemu;

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

// STUB: SADX 0x0085d290
void cDispRock(struct task *ctp)
{
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
