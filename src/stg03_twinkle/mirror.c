#include "decls.h"
extern int DAT_060cef38;

// FUNCTION: SADX 0x00812880
long initMirror()
{
	DAT_060cef38 = 0;
	return 1;
}

// STUB: SADX 0x00812890
long setMirror(long num, struct MirrorPlane *mp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00812d00
struct task *createMirrorTask(struct task *tp)
{
	struct task *var1;
	var1 = CreateChildTask(8, execMirrorTask, tp);
	if (var1 != 0)
	{
		var1->awp->work.ul[0] = 0;
		return var1;
	}
	return 0;
}

// FUNCTION: SADX 0x00812d30
struct task *createMirrorTaskP(struct task *tp)
{
	struct task *var1;
	var1 = CreateElementalTask(8, 1, execMirrorTaskP);
	if (var1 != 0)
	{
		var1->awp->work.ul[0] = 0;
		return var1;
	}
	return 0;
}
