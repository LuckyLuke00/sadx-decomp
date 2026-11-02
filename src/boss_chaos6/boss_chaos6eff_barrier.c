#include "decls.h"
extern struct obj object_c0_balia_a_balia_a[1];
extern "C" double atan2(double v, double u);
static void objDisplay(struct task *tp);
static void objNormal(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x006fae40
static void objDisplay(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006faf30
static void objNormal(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		var1->counter.f += 0.05000000074505806;
		if (var1->counter.f >= 1.0f)
		{
			var1->mode = 1;
		}
		break;
	case 1:
		var1->timer.b[0]++;
		if (var1->timer.b[0] < 2)
		{
			break;
		}
		var1->timer.b[1]++;
		if (var1->timer.b[1] < 0xb)
		{
			break;
		}
		var1->mode = 2;
		break;
	case 2:
		var1->counter.f -= 0.05000000074505806;
		if (var1->counter.f <= 0.0f)
		{
			FreeTask(tp);
			return;
		}
		break;
	}
	var1->pos.x = njCos(*(int *)((char *)var1 + 0x18)) * 38.0 + *(float *)((char *)DAT_05edd128 + 0x20);
	var1->pos.z = njSin(*(int *)((char *)var1 + 0x18)) * 38.0 + *(float *)((char *)DAT_05edd128 + 0x28);
	objDisplay(tp);
}

// FUNCTION: SADX 0x006fb000
void Chaos6Barrier(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	float var2 = var1->pos.z - *(float *)((char *)DAT_05edd128 + 0x28);
	float var3 = var1->pos.x - *(float *)((char *)DAT_05edd128 + 0x20);
	*(int *)((char *)var1 + 0x18) = (int)(atan2(var2, var3) * 65536.0f / 6.283184);
	var1->counter.f = 0.0f;
	*(int *)((char *)object_c0_balia_a_balia_a[0].model->mats + 0x10) |= 0x100000;
	tp->exec = objNormal;
	tp->disp = objDisplay;
}
