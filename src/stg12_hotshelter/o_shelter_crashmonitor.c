#include "decls.h"
struct task;
void DispBTask(struct task *tp);

// FUNCTION: SADX 0x008af150
void DispBTask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_HotShelter2);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	late_DrawModelClip((struct NJS_MODEL *)&model_tv_clash_base_tv_clash_base, 1, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x008af2d0
void ShutterParts(struct task *tp)
{
}

// STUB: SADX 0x008af650
void FUN_008af650(struct task *param_1)
{
}

// STUB: SADX 0x008af7e0
void ShutterBrokenPiece(struct task *tp)
{
}
