#include "decls.h"
extern struct task *DAT_060cee5c;

// FUNCTION: SADX 0x00802290
void DestructYurehasi(void)
{
	if (DAT_060cee5c != NULL)
	{
		FreeTask(DAT_060cee5c);
	}
}

// FUNCTION: SADX 0x00802400
void A_Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SetObjectTexture();
	if (var1->smode)
	{
		return;
	}
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	___dsDrawObject((struct obj *)var1->value.ptr);
	njPopMatrix(1);
}

// STUB: SADX 0x00802460
void B_Disp(struct task *tp)
{
}

// STUB: SADX 0x008028c0
void A_Exec(struct task *tp)
{
}

// STUB: SADX 0x00802900
void B_Exec(struct task *tp)
{
}

// STUB: SADX 0x00802bf0
void CreateYurehasi()
{
}
