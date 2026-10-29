#include "decls.h"
void FUN_007d21b0(...);

// STUB: SADX 0x00811460
void setTPFog(unsigned char mode)
{
}

// STUB: SADX 0x008117a0
void FUN_008117a0(struct taskwk *param_1)
{
}

// STUB: SADX 0x00811df0
void execBgTwinkle(struct task *tp)
{
}

// FUNCTION: SADX 0x00811e70
void Bg_Twinkle(struct task *tp)
{
	tp->exec = execBgTwinkle;
	tp->disp = dispBgTwinkle;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
