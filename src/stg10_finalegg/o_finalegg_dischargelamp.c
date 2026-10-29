#include "decls.h"
extern struct THahenInfo HahenInfo[4];

// FUNCTION: SADX 0x0089e140
void DispAllHahens(struct TMyWork *MyWork)
{
	SetObjectTexture();
	struct TMyWork *var1 = MyWork;
	struct THahenInfo *var2 = HahenInfo;
	int var3;
	var1 = (struct TMyWork *)((char *)var1 + 0x20);
	for (var3 = 4; var3 != 0; var3--)
	{
		njPushMatrix(NULL);
		njTranslateV(NULL, (struct NJS_POINT3 *)var1);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateY(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateX(NULL, (unsigned short)*(short *)((char *)var1 + 0x18));
		}
		if (*(int *)((char *)var1 + 0x20) != 0)
		{
			njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x20));
		}
		ds_DrawModelClip(var2->Obj->model, 1.0f);
		njPopMatrix(1);
		var1 = (struct TMyWork *)((char *)var1 + 0x30);
		var2++;
	}
}
