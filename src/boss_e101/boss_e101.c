#include "decls.h"
extern struct obj object_e101old_kihon0_e101old_e_head[];
extern struct obj object_e101old_kihon0_e101old_e_head[1];
extern struct NJS_MODEL *DAT_060c451c;

// FUNCTION: SADX 0x00706270
void callbackTgt(struct obj *obj)
{
	if (obj == &object_e101old_kihon0_e101old_e_head[0])
	{
		if (*(int *)((char *)DAT_060c451c + 0x54) != 0)
		{
			njRotateY(0, *(unsigned short *)((char *)DAT_060c451c + 0x54));
		}
	}
}

// STUB: SADX 0x00706930
void SetE101()
{
}
