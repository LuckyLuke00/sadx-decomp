#include "decls.h"

// FUNCTION: SADX 0x0044bdb0
void KillChao(struct task *tp)
{
	AL_ClearChaoParam((struct CHAO_PARAM_GC *)(*(int **)((char *)tp->twp + 0x6c)));
	FreeTask(tp);
}
