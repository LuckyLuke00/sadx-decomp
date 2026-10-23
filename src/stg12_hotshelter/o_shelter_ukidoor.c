#include "decls.h"
extern short DAT_05b9d724;
extern short DAT_05b9d744;

// FUNCTION: SADX 0x008b48d0
void ObjShelterUkidoor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->mode = (GetPlayerCharacterName(0) == 7);
	var1->wtimer = (DAT_05b9d724 << 8) | DAT_05b9d744;
	CCL_Init(tp, c_info_a, 1, 4);
	SET_COLLI_RANGE(var1->cwp, 50.0f);
	tp->exec = (void (*)(struct task *))0x8b4810;
	tp->disp = (void (*)(struct task *))0x8b47c0;
}

// STUB: SADX 0x008b4940
void CreateUkidoor()
{
}
