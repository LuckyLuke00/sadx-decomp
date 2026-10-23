#include "decls.h"
extern "C" int rand(void);

// STUB: SADX 0x004662c0
long ALBHV_JumpToPond(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00466390
long ALBHV_GoToWater(struct task *tp)
{
	AL_GetRandomAttrPos((enum eLANDMARK_ATTR)9, (struct NJS_POINT3 *)((char *)tp->mwp + 0x54));
	rand();
	AL_WalkSelect(tp);
	return 0;
}
