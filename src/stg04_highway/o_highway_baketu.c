#include "decls.h"

// FUNCTION: SADX 0x00820210
void Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	___dsDrawModel(model_ss_bkt_bkt_bkt_bkt);
	___dsDrawModel(model_ss_bkt_huta_bkt_huta);
	njPopMatrix(1);
}
