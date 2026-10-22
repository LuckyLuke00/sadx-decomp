#include "decls.h"

// FUNCTION: SADX 0x006a4360
void BlockDisplayer(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (((var1->flag & 0x200) != 0) && (DAT_05b9d838 == 0))
	{
		SetObjectTexture();
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(0, (unsigned short)var1->ang.y);
		}
		njPopMatrix(1);
	}
}
