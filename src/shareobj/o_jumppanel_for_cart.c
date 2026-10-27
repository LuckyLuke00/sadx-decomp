#include "decls.h"
extern struct NJS_TEXLIST texlist_obj_shareobj;
extern struct obj object_tpobj_jumpdai_jumpdai[1];

// FUNCTION: SADX 0x008d4f20
void jumppanel_for_cartDisplay(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if ((texlist_obj_shareobj.textures == 0) || ((struct NJS_TEXNAME *)texlist_obj_shareobj.textures)->texaddr == 0)
		return;
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.z != 0)
		njRotateZ(0, (unsigned short)local_8->ang.z);
	if (local_8->ang.x != 0)
		njRotateX(0, local_8->ang.x);
	if (local_8->ang.y != 0)
		njRotateY(0, local_8->ang.y);
	___njSetTexture(&texlist_obj_shareobj);
	___dsDrawObject(&object_tpobj_jumpdai_jumpdai[0]);
	njPopMatrix(1);
}
