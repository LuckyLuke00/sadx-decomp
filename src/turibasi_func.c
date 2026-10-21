#include "decls.h"
extern int DAT_05b9d838;

// FUNCTION: SADX 0x008db4c0
void BridgeEditMode(struct taskwk *twp)
{
	if (DAT_05b9d838 != 0)
		return;
	njPushMatrix(0);
	njTranslateV(0, &twp->pos);
	if (twp->ang.y != 0)
		njRotateY(0, twp->ang.y);
	___dsDrawModel(*(struct NJS_MODEL **)((int)twp->value.ptr + 0x4c));
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008db530
void ObjectTuribasi(struct task *tp)
{
	BridgeInit(tp);
	tp->exec = ObjectTuribasiExecutor;
	tp->dest = ObjectTuribasiDestructor;
	tp->disp = ObjectTuribasiDisplayer;
}

// FUNCTION: SADX 0x008dbd30
void ObjectTuribasiDisplayer(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	BridgeDraw(local_8);
}

// FUNCTION: SADX 0x008dbd50
void ObjectTuribasiDisplayer2(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	BridgeDraw2(local_8);
}
