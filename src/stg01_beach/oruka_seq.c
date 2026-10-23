#include "decls.h"
extern int DAT_060cea0c;
extern float DAT_060cea10;
extern float DAT_060cea14;
extern float DAT_060cea18;
extern int DAT_060cea1c;
extern struct task *DAT_060ce9f8;
extern int DAT_060ce9fc;

// FUNCTION: SADX 0x007f75f0
void orInitOrukaSequence()
{
	DAT_060cea1c = 0;
	DAT_060cea10 = 0.0f;
	DAT_060cea14 = 0.0f;
	DAT_060cea18 = 0.0f;
	CreateYurehasi();
	DAT_060ce9f8 = CreateElementalTask(6, 6, ObjectBeachWave25);
	DAT_060ce9fc = 0;
}

// FUNCTION: SADX 0x007f7640
void orDestructOrukaSequence()
{
	DestructYurehasi();
	if ((*(struct task *(*))&DAT_060cea1c) != 0)
	{
		FreeTask((*(struct task *(*))&DAT_060cea1c));
	}
	if (DAT_060ce9f8 != 0)
	{
		FreeTask(DAT_060ce9f8);
	}
}

// FUNCTION: SADX 0x007f7670
long orCreateAttackOruka(float pos_x, float pos_y, float pos_z, long ang_y)
{
	struct task *var1;
	struct taskwk *var2;
	if (DAT_060cea1c != 0)
	{
		FreeTask((struct task *)DAT_060cea1c);
	}
	DAT_060cea0c = 0;
	var1 = CreateElementalTask(3, 3, ObjectBeachAttackoruka);
	DAT_060cea1c = (int)var1;
	var2 = var1->twp;
	var2->pos.x = pos_x;
	var2->ang.y = ang_y;
	var2->pos.y = pos_y;
	var2->pos.z = pos_z;
	return 1;
}

// FUNCTION: SADX 0x007f76d0
long orDeleteAttackOruka()
{
	if (DAT_060cea1c == 0)
		return 0;
	DAT_060cea0c = 1;
	return 1;
}

// FUNCTION: SADX 0x007f76f0
void orFreeAttackOruka(struct task *o_tp)
{
	if (DAT_060cea1c == (int)o_tp)
	{
		DAT_060cea10 = 0.0f;
		DAT_060cea14 = 0.0f;
		DAT_060cea18 = 0.0f;
		DAT_060cea1c = 0;
	}
}

// FUNCTION: SADX 0x007f7720
long orCreatePathOruka()
{
	if (DAT_060cea1c != 0)
	{
		return 0;
	}
	DAT_060cea0c = 0;
	DAT_060cea1c = (int)CreateElementalTask(3, 3, ObjectBeachPathoruka);
	return 1;
}

// FUNCTION: SADX 0x007f7760
void orFreePathOruka(struct task *o_tp)
{
	if (DAT_060cea1c == (int)o_tp)
	{
		DAT_060cea1c = 0;
	}
}

// FUNCTION: SADX 0x007f7780
long orCreateRippleSource(float pos_x, float pos_z, float start_rad, float end_rad, float scl)
{
	CreateRippleSource25(DAT_060ce9f8, pos_x, pos_z, start_rad, end_rad, scl);
	return 1;
}

// FUNCTION: SADX 0x007f77c0
float orGetWaveHeight(float pos_x, float pos_z)
{
	float local_8;
	local_8 = 0.0;
	if (DAT_060ce9f8 != NULL)
	{
		local_8 = (float)GetWaveHeight25(DAT_060ce9f8, pos_x, pos_z);
	}
	return local_8;
}
