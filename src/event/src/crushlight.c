#include "decls.h"
extern struct task *DAT_060cc134;
void FUN_007d6940(struct task *param_1);

// FUNCTION: SADX 0x007d2c50
void FUN_007d2c50()
{
	if (DAT_060cc134)
	{
		FreeTask(DAT_060cc134);
		DAT_060cc134 = 0;
	}
}

// STUB: SADX 0x007d2c70
void execCrushLightTask(struct task *p_task)
{
}

// FUNCTION: SADX 0x007d2cb0
void initCrushLightTask(struct task *p_task)
{
	p_task->exec = execCrushLightTask;
	p_task->disp = 0;
	p_task->dest = FUN_007d6940;
}

// STUB: SADX 0x007d2cd0
void crushLightOn(float pos_x, float pos_y, float pos_z, int crushLightNum, int life, float start_width, float end_width, unsigned long start_col, unsigned long end_col)
{
}
