#include "decls.h"
void SaveControl3D();
void SaveConstantAttr();
void LoadConstantAttr();
void LoadControl3D();
extern int DAT_060c462c;

// FUNCTION: SADX 0x00710630
void dispMidBomb(struct task *pTask)
{
	struct anywk *var1 = pTask->awp;
	___njSetTexture(&_texlist_e101r);
	float var2 = *(float *)((char *)var1 + 0x1c) / 63.0;
	if (DAT_05b9d838 == 0)
	{
		njPushMatrix(0);
		SaveControl3D();
		SaveConstantAttr();
		njControl3D(0x14);
		SetMaterial(1.0, *(float *)((char *)var1 + 0x24), *(float *)((char *)var1 + 0x24), *(float *)((char *)var1 + 0x24));
		njSetConstantAttr(-1, 0x2000000);
		njTranslateV(0, (struct NJS_POINT3 *)(*(int *)((char *)var1 + 0x28)));
		FUN_0067d2d0(0, var2, var2, var2);
		late_DrawObject((struct obj *)(DAT_060c462c + 0xaacc), 4);
		FUN_0067d2d0(0, 1.0, -1.0f, 1.0);
		late_DrawObject((struct obj *)(DAT_060c462c + 0xaacc), 4);
		LoadConstantAttr();
		LoadControl3D();
		njPopMatrix(1);
	}
	ResetMaterial();
}
