#include "decls.h"
extern "C" int rand(void);

// FUNCTION: SADX 0x006edb00
void SetBallBubble(struct task *chaos_tp, int num, float size)
{
	int var3;
	struct task *var4;
	struct anywk *var5;
	float var2;
	int var1;

	var2 = (float)rand() * 3.0517578125e-05;
	var1 = (int)((var2 * 0.5f + 0.5f) * num + 0.10000000149011612f);
	if (var1 > 0)
	{
		for (var3 = var1; var3 != 0; var3--)
		{
			var4 = CreateChildTask(2, BallBubble, chaos_tp);
			if (var4 != 0)
			{
				var5 = (struct anywk *)MAlloc(0x1c);
				var4->awp = var5;
				var2 = (float)rand() * 3.0517578125e-05;
				*(float *)var5 = (var2 * 0.5f + 1.0f) * size;
			}
		}
	}
}
