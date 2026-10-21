#include "decls.h"
extern long DAT_05edbe78;

// STUB: SADX 0x005b5ab0
int Playable(long playerno)
{
	return (int)0;
}

// STUB: SADX 0x005b5b20
struct task *FUN_005b5b20(void *param_1)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x005b5bb0
void CPlayable_Dest(struct task *tp)
{
	SeqSave();
	DAT_05edbe78 = 0;
}

// FUNCTION: SADX 0x005b5de0
int PlayableWait()
{
	return DAT_05edbe78;
}
