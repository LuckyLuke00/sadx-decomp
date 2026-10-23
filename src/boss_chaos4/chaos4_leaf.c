#include "decls.h"
extern int DAT_05b9d838;
extern int DAT_05b3df4c;
extern int DAT_05b3df40;

// FUNCTION: SADX 0x006f14f0
void Dsp_Leaf(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	struct anywk *var2 = pTask->awp;
	if (DAT_05b9d838 == 0)
	{
		Tmit_MaterialInit();
		___njSetTexture(&texlist_chaos4_object);
		njPushMatrix((float *)0);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX((float *)0, (unsigned short)*(short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY((float *)0, (unsigned short)*(short *)((char *)var1 + 0x18));
		}
		if (DAT_05b3df4c != 0)
		{
			if (*(short *)((char *)var2 + 0xe) > 0)
			{
				*(float *)&DAT_05b3df40 = -17952.0f;
			}
		}
		late_DrawObjectClipMS((struct obj *)&object_c4_nc_s_asiba_nc_s_asiba, 1, 1.0f);
		njPopMatrix(1);
	}
}
