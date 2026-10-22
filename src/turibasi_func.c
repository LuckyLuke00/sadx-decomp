#include "decls.h"
void FUN_008dcb90(struct taskwk *param_1, struct NJS_POINT3 *param_2);
unsigned char FUN_008dcc50(struct taskwk *param_1, struct NJS_POINT3 *param_2);
void BridgeDraw(struct taskwk *twp);
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

// STUB: SADX 0x008db560
void BridgeNormal(struct task *tp)
{
}

// STUB: SADX 0x008db620
void BridgeNormal2(struct task *tp)
{
}

// FUNCTION: SADX 0x008db6e0
void ObjectBridgeShitaDisplayer(struct task *tp)
{
	struct taskwk *local_cg;
	float local_8g;

	local_cg = tp->twp;
	local_8g = local_cg->scl.x;
	___njSetTexture((struct NJS_TEXLIST *)local_cg->value.ptr);
	njPushMatrix(0);
	njTranslateV(0, &local_cg->pos);
	if (local_cg->ang.y != 0)
		njRotateY(0, local_cg->ang.y);
	if (local_cg->ang.x != 0)
		njRotateX(0, local_cg->ang.x);
	FUN_0067d2d0(0, local_8g, local_8g, local_8g);
	ds_DrawModelClip((struct NJS_MODEL *)local_cg->counter.ptr, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x008db7a0
void ObjectBridgeShita(struct task *tp)
{
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

// STUB: SADX 0x008dbd70
void ObjectTuribasiExecutor(struct task *tp)
{
}

// STUB: SADX 0x008dc120
void FUN_008dc120(struct task *tp)
{
}

// STUB: SADX 0x008dcaf0
void BridgeCheckCollision(struct taskwk *twp)
{
}

// STUB: SADX 0x008dcb90
void FUN_008dcb90(struct taskwk *twp, struct NJS_POINT3 *out)
{
}

// STUB: SADX 0x008dcc50
unsigned char FUN_008dcc50(struct taskwk *twp, struct NJS_POINT3 *pnt)
{
	return (unsigned char)0;
}

// STUB: SADX 0x008dcd10
void BridgeSetForce(struct taskwk *twp, float xpos, float zpos)
{
}

// STUB: SADX 0x008dd0f0
void BridgeDeform(struct taskwk *twp)
{
}

// STUB: SADX 0x008dd2e0
void ObjectTuribasiDestructor(struct task *tp)
{
}
