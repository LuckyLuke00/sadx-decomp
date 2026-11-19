#include "decls.h"
extern struct NJS_POINT3 door_pos[2];
extern float door_limit[2];

// GLOBAL: SADX 0x04c2c408
static struct CCL_INFO c_info_a[1];

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

// FUNCTION: SADX 0x008b4940
void CreateUkidoor()
{
	struct task *var1;
	struct taskwk *var2;
	int var3;

	for (var3 = 0; var3 < 2; var3++)
	{
		var1 = CreateElementalTask(2, 3, ObjShelterUkidoor);
		var2 = var1->twp;
		var2->pos.x = door_pos[var3].x;
		var2->pos.y = door_pos[var3].y;
		var2->pos.z = door_pos[var3].z;
		var2->counter.f = door_limit[var3];
	}
}
