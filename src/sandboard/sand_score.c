#include "decls.h"
static void dispScore(struct task *task_p);

// STUB: SADX 0x007e85a0
void SandScoreAddGateScore()
{
}

// STUB: SADX 0x007e85f0
void initScore(struct task *task_p, const void *param_p)
{
}

// STUB: SADX 0x007e8610
void destScore(struct task *task_p)
{
}

// STUB: SADX 0x007e8630
float drawLetter(float xPos, float yPos, float prio, enum TexId_e102time texId)
{
	return (float)0;
}

#pragma optimize("", off)
// STUB: SADX 0x007e8860
static void dispScore(struct task *task_p)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007e88e0
void execScore(struct task *task_p)
{
	short *var1 = (short *)task_p->mwp;

	if (*var1 > 0)
	{
		*var1 -= 1;
	}
	else
	{
		var1[1] = 0;
	}
	dispScore(task_p);
}

// STUB: SADX 0x007e8910
struct task *SandScoreSetScoreTask()
{
	return (struct task *)0;
}
