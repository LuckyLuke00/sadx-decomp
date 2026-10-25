#include "decls.h"
extern struct obj object_windobj_bridge_a1_bridge_a1[1];

// FUNCTION: SADX 0x0080d6a0
void DrawTest(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix((float *)0);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX((float *)0, *(unsigned short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
	}
	___dsDrawObject(&object_windobj_bridge_a1_bridge_a1[0]);
	njPopMatrix(1);
}

// STUB: SADX 0x0080dca0
void BrokenBridgePos(struct NJS_POINT3 *pos, int flag, struct task *tp)
{
}

// STUB: SADX 0x0080e1a0
void ObjectWindyBridge(struct task *tp)
{
}
