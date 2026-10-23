#include "decls.h"
extern unsigned char DAT_060ce44c;
extern unsigned char DAT_060ce44d;
extern float DAT_060ce450;

// FUNCTION: SADX 0x007eb620
void SetTornadeLifeGauge(int xpos, int ypos, int max)
{
	struct task *var1 = CreateElementalTask(2, 6, TornadeLifeGauge);
	struct taskwk *var2 = var1->twp;
	if (xpos > 0)
	{
		var2->pos.x = (float)xpos;
		var2->pos.y = (float)ypos;
	}
	else
	{
		var2->pos.x = 323.0f;
		var2->pos.y = 410.0f;
	}
	DAT_060ce44c = (unsigned char)max;
	DAT_060ce44d = (unsigned char)max;
	DAT_060ce450 = (float)max;
}
