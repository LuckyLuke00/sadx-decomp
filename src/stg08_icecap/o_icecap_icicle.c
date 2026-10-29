#include "decls.h"

// FUNCTION: SADX 0x00866ec0
void ObjectIcicleDisplay(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, (unsigned short)*(short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		late_DrawObjectClipMesh((struct obj *)var1->counter.ptr, 0, 1.0f);
		njPopMatrix(1);
	}
}
