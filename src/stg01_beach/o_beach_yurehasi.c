#include "decls.h"
extern int DAT_05b9d838;
extern struct obj object_seaobj_hasi_b_hasi_b[];
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

// FUNCTION: SADX 0x00802460
void B_Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838 == 0)
	{
		if (var1->smode == 0)
		{
			SetObjectTexture();
			njPushMatrix(0);
			njTranslateV(0, &var1->pos);
			if (*(int *)((char *)var1 + 0x1c) != 0)
			{
				njRotateZ(0, *(unsigned short *)((char *)var1 + 0x1c));
			}
			if (*(int *)((char *)var1 + 0x1c) != 0)
			{
				njRotateX(0, *(unsigned short *)((char *)var1 + 0x1c));
			}
			ds_DrawObjectClip(object_seaobj_hasi_b_hasi_b, 1.0f);
			njPopMatrix(1);
		}
	}
}

// STUB: SADX 0x008028c0
void A_Exec(struct task *tp)
{
}

// STUB: SADX 0x00802900
void B_Exec(struct task *tp)
{
}

// STUB: SADX 0x00802950
void A_Init(struct task *tp)
{
}

// STUB: SADX 0x00802a30
void B_Init(struct task *tp)
{
}

// FUNCTION: SADX 0x00802bf0
void CreateYurehasi(void)
{
	struct task *var1 = CreateElementalTask(2, 3, ObjectBeachYurehasi);
	DAT_060cee5c = var1;
	struct taskwk *var2 = var1->twp;
	var2->pos.x = 2803.0f;
	var2->pos.y = -1.0f;
	var2->pos.z = 365.0f;
}
