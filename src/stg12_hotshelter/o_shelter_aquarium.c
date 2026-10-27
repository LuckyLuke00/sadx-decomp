#include "decls.h"
static void Exec(struct task *tp);
extern float DAT_060dd79c;
extern int DAT_060dd798;
extern float DAT_05b3df40;
extern struct obj object_suisou_taki_o_garass_o_garass[];
long SetObjectTexture();
static void Disp(struct task *tp);

// FUNCTION: SADX 0x008b4d40
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	DAT_05b3df40 = -17952.0f;
	late_DrawObjectClip(object_suisou_taki_o_garass_o_garass, 0, 1.0f);
	DAT_05b3df40 = 0.0f;
	njPopMatrix(1);
}

#pragma optimize("", off)
// STUB: SADX 0x008b4da0
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008b4fa0
void ObjShelterAquarium(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->mode = 0;
	var1->wtimer = (short)(DAT_05b9d724 << 8 | DAT_05b9d744);
	var1->pos.x = 750.0f;
	var1->pos.y = 0.0f;
	var1->pos.z = -650.0f;
	var1->timer.f = 75.0f;
	DAT_060dd79c = 65.0f;
	FUN_0058b860(0, 0);
	DAT_060dd798 = 0;
	CreateChildTask(2, ObjShelterAqusuimen, tp);
	tp->exec = Exec;
	tp->disp = Disp;
	tp->dest = ExplosionRockDestructor;
}
