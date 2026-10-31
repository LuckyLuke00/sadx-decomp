#include "decls.h"
void E102EggLiftCollisionDest(struct task *tp);
extern struct obj object_ecb_bosscl_bosscl[1];
void WithdrawCollisionEntry(struct task *pTask, struct obj *pObject);

// FUNCTION: SADX 0x0061bf50
void E102EggLiftCollisionInit(struct task *tp)
{
	struct taskwk *local_8g;
	struct obj *local_cj;
	struct obj *local_10;

	local_8g = tp->twp;
	local_10 = &object_ecb_bosscl_bosscl[0];
	local_cj = GetMobileLandObject();
	*(struct obj **)((char *)local_8g + 8) = local_cj;
	local_cj->evalflags = 0x10;
	local_cj->scl[0] = 1.0f;
	local_cj->scl[1] = 1.0f;
	local_cj->scl[2] = 1.0f;
	local_cj->ang[2] = 0;
	local_cj->ang[1] = 0;
	local_cj->ang[0] = 0;
	local_cj->pos[0] = object_ecb_bosscl_bosscl[0].pos[0];
	local_cj->pos[1] = object_ecb_bosscl_bosscl[0].pos[1];
	local_cj->pos[2] = object_ecb_bosscl_bosscl[0].pos[2];
	local_cj->model = local_10->model;
	local_cj->child = local_10->child;
	local_cj->sibling = local_10->sibling;
	RegisterCollisionEntry(0x18000001, tp, local_cj);
	tp->exec = (void (__cdecl *)(struct task *))FUN_005b5aa0;
	tp->dest = E102EggLiftCollisionDest;
}

// FUNCTION: SADX 0x0061c030
void E102EggLiftCollisionDest(struct task *tp)
{
	WithdrawCollisionEntry(tp, &object_ecb_bosscl_bosscl[0]);
}
