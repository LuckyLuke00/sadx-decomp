#include "decls.h"

// FUNCTION: SADX 0x00495100
void SummaryBgDestrutor(struct task *tp)
{
	struct anywk *var1 = tp->awp;
	if (var1->work.ptr[1])
	{
		late_ReleaseTexture((struct NJS_TEXLIST *)var1->work.ptr[1]);
		var1->work.ptr[1] = 0;
	}
}
