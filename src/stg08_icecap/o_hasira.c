#include "decls.h"
extern int DAT_05b9d838;
extern struct NJS_MODEL model__obj_hasira_c_obj_hasira_c[];

// FUNCTION: SADX 0x00866a50
void Normal1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (DAT_05b9d838 == 0)
		{
			if (FUN_004c39c0(tp) == 0)
			{
				EntryColliList(var1);
				ObjectSetupInput(var1, (struct motionwk *)0);
			}
			SetObjectTexture();
			njPushMatrix(NULL);
			njTranslateV(NULL, &var1->pos);
			if (*(int *)((char *)var1 + 0x1c) != 0)
			{
				njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
			}
			if (*(int *)((char *)var1 + 0x14) != 0)
			{
				njRotateX(NULL, (unsigned short)*(short *)((char *)var1 + 0x14));
			}
			if (*(int *)((char *)var1 + 0x18) != 0)
			{
				njRotateY(NULL, (unsigned short)*(short *)((char *)var1 + 0x18));
			}
			late_DrawModelClipMesh((struct NJS_MODEL *)&model__obj_hasira_c_obj_hasira_c, 0, 1.0f);
			njPopMatrix(1);
		}
	}
}

// STUB: SADX 0x00866b20
void Normal2(struct task *tp)
{
}
