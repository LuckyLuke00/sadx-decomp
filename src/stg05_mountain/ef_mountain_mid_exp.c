#include "decls.h"
extern int DAT_05b9d838;
extern struct NJS_TEXLIST texlist_mexplosion_mountain;
extern struct obj object_mexplosion_mountain[1];

// FUNCTION: SADX 0x00838100
void dispBigBomb(struct task *pTask)
{
	struct anywk *var1 = pTask->awp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_mexplosion_mountain);
	float var2 = *(float *)((char *)var1 + 0x1c) / 63.0;
	njPushMatrix(0);
	SaveControl3D();
	SaveConstantAttr();
	njControl3D(0x14);
	SetMaterial(*(float *)((char *)var1 + 0x24), *(float *)((char *)var1 + 0x24), *(float *)((char *)var1 + 0x24), *(float *)((char *)var1 + 0x24));
	OnConstantAttr(0, 0x2000000);
	njTranslateV(0, (struct NJS_POINT3 *)(*(int *)((char *)var1 + 0x28)));
	FUN_0067d2d0(0, var2, var2, var2);
	late_DrawObject((struct obj *)&object_mexplosion_mountain, 4);
	FUN_0067d2d0(0, 1.0, -1.0f, 1.0);
	late_DrawObject((struct obj *)&object_mexplosion_mountain, 4);
	LoadConstantAttr();
	LoadControl3D();
	njPopMatrix(1);
}
