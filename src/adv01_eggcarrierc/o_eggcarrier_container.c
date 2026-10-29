#include "decls.h"
void ___dsDrawObject(struct obj *obj);
long SetObjectTexture();
extern int DAT_05b9d838;
extern struct obj *DAT_060eea98;

// FUNCTION: SADX 0x0069f1f0
void ContainerDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	SetObjectTexture();
	___dsDrawObject(*(struct obj **)((char *)DAT_060eea98 + 0x50));
	njPopMatrix(1);
}

// STUB: SADX 0x0069f240
void ObjectECBoosterContainer(struct task *tp)
{
}
