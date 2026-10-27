#include "decls.h"
extern struct NJS_MODEL model_glass_cube_1_cube_1[];

// FUNCTION: SADX 0x00824330
void DrawGlass(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct NJS_MODEL *var2 = (struct NJS_MODEL *)var1->timer.ptr;

	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	njRotateXYZ(0, var1->ang.x, var1->ang.y, var1->ang.z);
	late_DrawModel((struct NJS_MODEL *)var2->normals, 4);
	njPopMatrix(1);
}

// STUB: SADX 0x008244f0
void GlassBroken(struct task *tp)
{
}

// STUB: SADX 0x008246e0
void ObjectHighwayGlassAct2(struct task *tp)
{
}
