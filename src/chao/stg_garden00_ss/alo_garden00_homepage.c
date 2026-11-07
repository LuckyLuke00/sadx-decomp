#include "decls.h"
extern struct SAlgKinderOrthoQuad kQuad[];
extern struct NJS_TEXLIST texlist_al_garden00ss_2d;

// FUNCTION: SADX 0x004777a0
void FDisp(struct task *tp)
{
	struct anywk *var1;

	if (DAT_05b9d838 != 0)
	{
		return;
	}
	var1 = tp->awp;
	if (*(int *)var1 != 1)
	{
		return;
	}
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	___njSetTexture(&texlist_al_garden00ss_2d);
	AlgKinderOrthoBegin();
	___njSetTextureNum(0);
	AlgKinderOrthoQuadDrawArrayOffset((const struct SAlgKinderOrthoQuad *)&kQuad, 0x12, -1, 0x54, 0x38);
	AlgKinderOrthoEnd();
	AlMsgWinDisp((struct SAlMsgWin *)var1->work.ptr[1]);
}
