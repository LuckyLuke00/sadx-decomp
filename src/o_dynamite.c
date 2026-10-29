#include "decls.h"
extern struct obj DAT_05a9014c;
extern int DAT_05b9d838;
extern unsigned char DAT_05edc100;

// FUNCTION: SADX 0x005b7170
void objDisplay(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
		return;
	if (local_8->mode != 0)
		return;
	if (dsCheckViewV(&local_8->pos, 10.0) == 0)
		return;
	___dsSetPalette(2);
	SetRegularTexture();
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.z != 0)
		njRotateZ(0, (unsigned short)local_8->ang.z);
	if (local_8->ang.x != 0)
		njRotateX(0, (unsigned short)local_8->ang.x);
	if (local_8->ang.y != 0)
		njRotateY(0, (unsigned short)local_8->ang.y);
	___dsDrawObject(&DAT_05a9014c);
	njPopMatrix(1);
	___dsSetPalette(0);
}

// STUB: SADX 0x005b7490
int CheckDynamiteBroken(int id)
{
	return (int)0;
}

// FUNCTION: SADX 0x005b7520
void InitialDynamite()
{
	DAT_05edc100 = 0;
}
