#include "decls.h"
extern const struct NJS_MOTION *kBuyerMotionTable[3];
extern struct obj object_kin_bl_buyer_buyer[];

// FUNCTION: SADX 0x0046e080
void FBuyerDest(struct task *tp)
{
	if (tp->awp != NULL)
	{
		Free(tp->awp);
		tp->awp = NULL;
	}
}

// FUNCTION: SADX 0x0046e300
void FBuyerDisp(struct task *tp)
{
	struct anywk *var1;

	var1 = tp->awp;
	___njSetTexture(&texlist_ChaoBlackmarketObj);
	njPushMatrixEx();
	FUN_0067d830((float *)0, 0.0f, 0.0f, -11.9f);
	FUN_004a7cb0((struct obj *)&object_kin_bl_buyer_buyer, (struct NJS_MOTION *)kBuyerMotionTable[*(int *)((char *)var1 + 8)], *(float *)((char *)var1 + 0xc));
	njPopMatrixEx();
}

// FUNCTION: SADX 0x0046e4b0
struct task *ALO_BlackmarketBuyerCreate(struct task *ptp)
{
	struct task *var1 = CreateChildTask(2, FBuyerExec, ptp);
	if (var1 != NULL)
	{
		var1->twp->mode = 0;
	}
	return var1;
}
