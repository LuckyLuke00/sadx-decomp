#include "decls.h"
extern char DAT_035af7e0[1];
extern void *DAT_035af79c;
// GLOBAL: SADX 0x00a0ee64
static struct TaskInfo ObjectTaskInfo;

// FUNCTION: SADX 0x007e8ec0
struct task *SetWorm01Task()
{
	return SandObjSetChildTask(&ObjectTaskInfo, (void *)0x35af714);
}

// FUNCTION: SADX 0x007e8f00
struct task *SetWorm03Task()
{
	return SandObjSetChildTask(&ObjectTaskInfo, &DAT_035af79c);
}

// FUNCTION: SADX 0x007e8f20
struct task *SetSmallWorm01Task()
{
	return SandObjSetChildTask(&ObjectTaskInfo, &DAT_035af7e0);
}
