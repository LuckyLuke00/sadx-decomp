#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);
extern short DAT_05b9d724;
extern short DAT_05b9d744;

// FUNCTION: SADX 0x008b47c0
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	ds_DrawObjectClip((struct obj *)&object_ukidoor_ukidoor_ukidoor, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x008b4810
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x008b48d0
void ObjShelterUkidoor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->mode = GetPlayerCharacterName(0) == 7;
	var1->wtimer = (DAT_05b9d724 << 8) | DAT_05b9d744;
	CCL_Init(tp, c_info_a, 1, 4);
	SET_COLLI_RANGE(var1->cwp, 50.0f);
	tp->exec = Exec;
	tp->disp = Disp;
}

// STUB: SADX 0x008b4940
void CreateUkidoor()
{
}
