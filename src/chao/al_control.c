#include "decls.h"
extern int DAT_05aeb68c;

// FUNCTION: SADX 0x0043ec80
void AL_EnableMove()
{
	DAT_05aeb68c = 1;
}

// FUNCTION: SADX 0x0043ec90
void AL_DisableMove()
{
	DAT_05aeb68c = 0;
}

// FUNCTION: SADX 0x0043eca0
long AL_IsMovable()
{
	return DAT_05aeb68c;
}

// FUNCTION: SADX 0x0043ecb0
void AL_EnablePushout(struct task *tp)
{
	struct CCL_INFO *var1;

	var1 = CCL_GetInfo(tp->twp, 1);
	var1->push |= 7;
}

// FUNCTION: SADX 0x0043ecd0
void AL_FixPosition(struct task *tp)
{
	CCL_GetInfo(tp->twp, 1L)->push |= 0x70;
}

// FUNCTION: SADX 0x0043ecf0
void AL_ReleasePosition(struct task *tp)
{
	struct CCL_INFO *var1 = CCL_GetInfo(tp->twp, 1);
	var1->push &= 0x8f;
}

// FUNCTION: SADX 0x0043ed10
void AL_EnableTouch(struct task *tp)
{
	tp->twp->flag |= 0x240;
	CCL_Enable(tp->twp, 0);
	CCL_Enable(tp->twp, 2);
}

// FUNCTION: SADX 0x0043ed40
void AL_DisableTouch(struct task *tp)
{
	tp->twp->flag &= 0xfdbf;
	CCL_Disable(tp->twp, 0);
	CCL_Disable(tp->twp, 2);
}

// FUNCTION: SADX 0x0043ed70
void AL_DisableNade(struct task *tp)
{
	CCL_Disable(tp->twp, 2);
}
