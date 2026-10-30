#include "decls.h"

// GLOBAL: SADX 0x0270aab8
static struct CCL_INFO ccinfo[10];

static void KasyaMain(struct task *tp);
static void KasyaDisplay(struct task *tp);
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern int DAT_060b9138;

#pragma optimize("", off)
// STUB: SADX 0x006b4290
static void KasyaDisplay(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x006b45e0
static void KasyaMain(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006b4640
void KasyaInit(struct task *tp)
{
	struct obj *var1;
	struct taskwk *var2;

	var2 = tp->twp;
	var1 = GetMobileLandObject();
	var2->counter.ptr = var1;
	var1->scl[0] = 1.0f;
	var1->scl[1] = 1.0f;
	var1->evalflags = 0x10;
	var1->scl[2] = 1.0f;
	var1->ang[0] = var2->ang.x;
	var1->ang[1] = var2->ang.y;
	var1->ang[2] = var2->ang.z;
	var1->pos[0] = var2->pos.x;
	var1->pos[1] = var2->pos.y;
	var1->pos[2] = var2->pos.z;
	var1->model = *(struct NJS_MODEL **)((char *)*(void **)((char *)DAT_060eea9c + 0x1c) + 4);
	var1->child = *(struct obj **)((char *)*(void **)((char *)DAT_060eea9c + 0x1c) + 0x2c);
	var1->sibling = *(struct obj **)((char *)*(void **)((char *)DAT_060eea9c + 0x1c) + 0x30);
	RegisterCollisionEntry(0x48001001, tp, var1);
	tp->dest = KasyaDestruct;
	CCL_Init(tp, ccinfo, 0xa, 4);
	tp->exec = KasyaMain;
	tp->disp = KasyaDisplay;
}

// FUNCTION: SADX 0x006b4a70
void mrtrain_adxdestruct(struct task *tp)
{
	DAT_060b9138 = 0;
}

// FUNCTION: SADX 0x006b4a80
void mrtrain_adxprove(struct task *tp)
{
	if ((((int)DAT_05b9d724 << 8) | (int)DAT_05b9d744) != 0x2100)
	{
		DestroyTask(tp);
		return;
	}
}

// FUNCTION: SADX 0x00855000
void KasyaDestruct(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
	ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
}
