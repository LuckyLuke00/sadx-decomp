#include "decls.h"
static void Exec(struct task *tp);
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern int DAT_060dd394;
extern float DAT_060dd390;
extern int DAT_060dd398;
extern float DAT_060dd39c;
void ObjShelterMizubashira(struct task *tp);

// FUNCTION: SADX 0x008a2800
static void Exec(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (var1->wtimer != ((DAT_05b9d724 << 8) | (short)DAT_05b9d744))
	{
		FreeTask(tp);
		return;
	}
	switch (var1->mode)
	{
	case 0:
		if ((DAT_060dd394 & 1) != 0 && DAT_060dd398 == 2)
		{
			var1->mode = 1;
			CreateChildTask(2, ObjShelterMizubashira, tp);
		}
		LoopTaskC(tp);
		break;
	case 1:
		DAT_060dd390 -= 0.15000000596046448;
		if (DAT_060dd390 <= 82.5f)
		{
			DAT_060dd390 = 82.5f;
			DAT_060dd398 = 4;
			var1->mode = 2;
		}
		else
		{
			DAT_060dd39c += 0.12848275899887085;
		}
		LoopTaskC(tp);
		break;
	case 2:
		LoopTaskC(tp);
		break;
	}
}

// FUNCTION: SADX 0x008a28e0
void ObjShelterSenmanager(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->mode = 0;
	var1->wtimer = (short)(DAT_05b9d724 << 8 | DAT_05b9d744);
	var1->pos.x = 750.0f;
	var1->pos.y = 65.0f;
	var1->pos.z = -650.0f;
	DAT_060dd394 = 0;
	CreateChildTask(3, ObjShelterSen, tp);
	CreateChildTask(2, ObjShelterSensoko, tp);
	DAT_060dd390 = 155.0f;
	CreateChildTask(6, ObjShelterSensuimen, tp);
	tp->exec = Exec;
	tp->dest = ExplosionRockDestructor;
}
