#include "decls.h"
extern "C" int rand(void);

// FUNCTION: SADX 0x00466390
long ALBHV_GoToWater(struct task *tp)
{
	AL_GetRandomAttrPos((enum eLANDMARK_ATTR)9, (struct NJS_POINT3 *)((char *)tp->mwp + 0x54));
	rand();
	AL_WalkSelect(tp);
	return 0;
}
