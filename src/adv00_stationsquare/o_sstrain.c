#include "decls.h"
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern int DAT_060b5fe0;

// FUNCTION: SADX 0x00691150
void sstrain_adxdestruct(struct task *tp)
{
	DAT_060b5fe0 = 0;
}

// FUNCTION: SADX 0x00691160
void sstrain_adxprove(struct task *tp)
{
	if ((((int)DAT_05b9d724 << 8) | (int)DAT_05b9d744) != 0x1a01)
	{
		DestroyTask(tp);
		return;
	}
}
