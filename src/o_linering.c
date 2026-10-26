#include "decls.h"
extern int DAT_05b9d838;
extern struct obj object_sphere01;

// STUB: SADX 0x008b9b80
void ObjectLinering(struct task *tp)
{
}

// FUNCTION: SADX 0x008b9f60
void FUN_008b9f60(struct task *param_1)
{
	FreeTaskC(param_1);
}

// STUB: SADX 0x008b9f80
void LineringInit(struct task *tp)
{
}

// FUNCTION: SADX 0x008ba100
void SetLineringEffect(long on)
{
	ring_kiran = on;
}

// FUNCTION: SADX 0x008ba110
void LineringDisp(struct task *tp)
{
	struct taskwk *local_10;
	struct motionwk *local_ci;
	int local_8g;

	local_10 = tp->twp;
	local_ci = tp->mwp;
	if (DAT_05b9d838 != 0)
		return;
	njPushMatrix(0);
	njTranslateV(0, &local_10->pos);
	for (local_8g = 0; local_8g < *(int *)((char *)local_10 + 0xc); local_8g++)
	{
		njPushMatrix(0);
		FUN_0067d2d0(0, 0.3f, 0.3f, 0.3f);
		late_DrawObject(&object_sphere01, 4);
		njPopMatrix(1);
		njTranslateV(0, (struct NJS_POINT3 *)((char *)local_ci + 4));
	}
	njPopMatrix(1);
}
