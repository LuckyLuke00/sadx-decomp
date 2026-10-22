#include "decls.h"

// FUNCTION: SADX 0x005ba3f0
void ObjectEmeraldTriangleDisplay(struct NJS_POINT3 *pos)
{
	njPushMatrix(0);
	njTranslateV(0, pos);
	late_DrawPolygon3D((struct NJS_POINT3COL *)&tridai, 3, 0x20, 1);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x005bad70
void CallObjectEmeraldDisplay(struct task *tp)
{
	ObjectEmeraldDisplay(&tp->twp->pos, &tp->twp->ang.y);
}
