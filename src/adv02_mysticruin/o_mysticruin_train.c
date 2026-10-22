#include "decls.h"
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern int DAT_060b9138;

// FUNCTION: SADX 0x006b4a70
void mrtrain_adxdestruct(struct task *tp)
{
	DAT_060b9138 = 0;
}

// FUNCTION: SADX 0x006b4a80
void mrtrain_adxprove(struct task *tp)
{
	if ((((int)DAT_05b9d724 << 8) | (int)DAT_05b9d744) != 0x2100)
	{
		DestroyTask(tp);
		return;
	}
}
