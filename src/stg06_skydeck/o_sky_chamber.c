#include "decls.h"

// STUB: SADX 0x008436e0
void dispSkyFallingWMotion(struct task *tp)
{
}

// STUB: SADX 0x00843d40
void ObjectSkyFalling(struct task *tp)
{
}

// FUNCTION: SADX 0x00843d70
void dispSkyChamber(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 100.0f))
	{
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		SetObjectTexture();
		njEasyDrawObject((struct obj *)(*(int *)&var1->timer));
		njPopMatrix(1);
	}
}
