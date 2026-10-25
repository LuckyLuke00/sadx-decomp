#include "decls.h"
extern struct obj object_suimen_wt_j2h_wt_j2h[];
extern float DAT_05b3df40;
extern int DAT_05b9d838;

// FUNCTION: SADX 0x008b5090
void SideExec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckCollisionCylinderP(&var1->pos, 150.0f, 50.0f))
	{
		var1->flag |= 0x100;
		return;
	}
	var1->flag &= 0xfeff;
}

// FUNCTION: SADX 0x008b50e0
void TubeDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_shelter_suimen);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	DAT_05b3df40 = -17952.0f;
	late_DrawObjectClipMS(object_suimen_wt_j2h_wt_j2h, 0, 1.0f);
	DAT_05b3df40 = 0.0f;
	njPopMatrix(1);
}

// STUB: SADX 0x008b5170
void SideInit(struct task *tp)
{
}

// STUB: SADX 0x008b5230
void SideInit2(struct task *tp)
{
}

// STUB: SADX 0x008b52f0
void TubeExec(struct task *tp)
{
}

// STUB: SADX 0x008b5370
void TubeInit(struct task *tp)
{
}
