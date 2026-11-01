#include "decls.h"
static void Disp(struct task *tp);
static void Exec(struct task *tp);
extern float ScreenRaitoX;
extern float ScreenRaitoY;
extern struct NJS_SPRITE sprite_fade;

// FUNCTION: SADX 0x008b56e0
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
		SetMaterial(var1->counter.f, 0.0f, 0.0f, 0.0f);
		sprite_fade.sx = ScreenRaitoX * 640.0 * 0.015625;
		sprite_fade.sy = ScreenRaitoY * 480.0 * 0.015625;
		sprite_fade.p.x = ScreenRaitoX * 320.0;
		sprite_fade.p.y = ScreenRaitoY * 240.0;
		late_DrawSprite2D(&sprite_fade, 0, 22047.0f, 0x22, 4);
		ResetMaterial();
	}
}

// STUB: SADX 0x008b57a0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x008b5890
void ObjShelterFade(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = 0.0f;
	var1->mode = 0;
	tp->exec = Exec;
	tp->disp = Disp;
}
