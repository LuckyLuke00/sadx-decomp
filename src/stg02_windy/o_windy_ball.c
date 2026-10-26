#include "decls.h"

// FUNCTION: SADX 0x00808620
void DrawBall(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct anywk *var2 = tp->awp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	if ((int)((var2->work.f[2] + var1->wtimer) * 65536.0 / 360.0))
	{
		njRotateX(0, (short)(int)((var2->work.f[2] + var1->wtimer) * 65536.0 / 360.0));
	}
	late_DrawModelClip(model_wvobj_wara_wara, 1, 1.0f);
	njPopMatrix(1);
}
