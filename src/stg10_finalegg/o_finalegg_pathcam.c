#include "decls.h"

// FUNCTION: SADX 0x008a1160
void ObjectCamPathCam_End(struct task *tp)
{
	Free(*(void **)((char *)tp->twp + 0x2c));
}
