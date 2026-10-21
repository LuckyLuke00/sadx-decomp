#include "decls.h"
extern struct ActionParam DAT_035af6d8;

// FUNCTION: SADX 0x007e8920
struct task *SetRockyHead01Task()
{
	static struct ActionParam var1;
	return SandObjSetChildTask(&ObjectTaskInfo, (void *)0x35af6bc);
}

// FUNCTION: SADX 0x007e8940
struct task *SetRockyHead02Task()
{
	return SandObjSetChildTask(&ObjectTaskInfo, &DAT_035af6d8);
}

// FUNCTION: SADX 0x007e8960
struct task *SetRockyHead03Task()
{
	return SandObjSetChildTask(&ObjectTaskInfo, (void *)0x35af6f4);
}

// STUB: SADX 0x007e8ac0
void destObject(struct task *task_p)
{
}

// STUB: SADX 0x007e8ad0
void dispRockyHead(struct task *task_p)
{
}

// STUB: SADX 0x007e8b80
void FUN_007e8b80(float *param_1, float *param_2, float *param_3)
{
}
