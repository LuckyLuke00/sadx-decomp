#include "decls.h"

// STUB: SADX 0x006f0e80
long Chaos4PlayerFlyingCheck()
{
	return (long)0;
}

// STUB: SADX 0x006f0ec0
void Dsp_Chaos4WaterTube(struct task *pTask)
{
}

// STUB: SADX 0x006f10d0
void FUN_006f10d0(struct taskwk *twp)
{
}

// STUB: SADX 0x006f1150
void Exe_Chaos4Wave(struct task *pTask)
{
}

// FUNCTION: SADX 0x006f13b0
void Chaos4WaveSet(struct NJS_POINT3 *base_pos, struct Angle3 *base_ang)
{
	struct task *var1;
	struct taskwk *var2;

	if (HamonCountGet() > 0x14)
		return;
	var1 = CreateElementalTask(2, 3, Exe_Chaos4Wave);
	if (var1 == 0)
		return;
	var2 = var1->twp;
	EnemyInitialize(var1, var2);
	var2->pos.x = base_pos->x;
	var2->pos.y = base_pos->y;
	var2->pos.z = base_pos->z;
	var2->pos.y = 20.0f;
	var2->ang.x = base_ang->x;
	var2->ang.y = base_ang->y;
	var2->ang.z = base_ang->z;
	var1->exec = Exe_Chaos4Wave;
	var1->disp = Dsp_Chaos4Wave;
	var1->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
