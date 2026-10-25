#include "decls.h"
static void Normal2(struct task *tp);
static void Disp2(struct task *tp);
extern float ScreenRaitoY;
extern struct NJS_SPRITE sprite_black;

#pragma optimize("", off)
// STUB: SADX 0x00881cc0
static void Disp2(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00881e00
static void Normal2(struct task *tp)
{
	Disp2(tp);
}

// FUNCTION: SADX 0x00881e10
void ObjectCardDisp(struct task *tp)
{
	sprite_black.sy = ScreenRaitoY * 60.0;
	sprite_black.p.y = 0.0f;
	tp->exec = Normal2;
	tp->disp = Disp2;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
