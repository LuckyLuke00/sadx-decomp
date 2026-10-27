#include "decls.h"
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
void late_DrawModelClip(struct NJS_MODEL *mdl, int flgs, float clipScl);
extern int DAT_05b9d838;
extern unsigned char DAT_05bafb94;
extern unsigned char DAT_05bafbd3;
extern unsigned char DAT_05bafc90;
extern int DAT_060b9104;

// FUNCTION: SADX 0x006b0d60
void WindyValleyDestructor(struct task *tp)
{
	DAT_060b9104 = 0;
}

// FUNCTION: SADX 0x006b0d70
int chk_windyvalley()
{
	switch (GetPlayerNumber())
	{
		case 0:
			if (SeqCheckFlag(0xa7))
				return SeqCheckFlag(0xa8);
			return DAT_05bafb94;
		case 2:
			if (SeqCheckFlag(0xe1))
				return SeqCheckFlag(0xe2);
			return DAT_05bafbd3;
		case 6:
			if (SeqCheckFlag(0x19c))
				return SeqCheckFlag(0x19d);
			return DAT_05bafc90;
	}
	return 0;
}

// STUB: SADX 0x006b1080
void Leaf1Displayer(struct task *tp)
{
}

// STUB: SADX 0x006b1140
void spexec_smoke(struct sp_task *tp, struct sp_link *lp)
{
}

// FUNCTION: SADX 0x006b12d0
void WoodyTrashDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	float var2;

	if (DAT_05b9d838)
	{
		return;
	}
	var2 = var1->scl.x;
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	njRotateXYZ(0, var1->ang.x, var1->ang.y, var1->ang.z);
	FUN_0067d2d0(0, var2, var2, var2);
	late_DrawModelClip((struct NJS_MODEL *)var1->value.ptr, 0, var2);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006b1360
void FUN_006b1360(void)
{
	switch (GetPlayerNumber())
	{
	case 0:
		FUN_004f5550(0x95);
		break;
	case 2:
		FUN_004f5550(0xd4);
		break;
	case 6:
		FUN_004f5550(0x191);
		break;
	}
}

// STUB: SADX 0x006b1d40
void create_leaf(float x, float y, float z, float rad)
{
}
