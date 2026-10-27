#include "decls.h"
extern struct obj object_tpobj7_dpaneru_dpaneru[];
extern struct NJS_TEXLIST texlist_obj_shareobj;
extern struct obj object_tpobj7_dpaneru_dpaneru[1];
void FUN_00422560(int param_1);
void npSetZCompare();

// FUNCTION: SADX 0x008d4a90
void dashpanel_for_cartDisplay(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if ((texlist_obj_shareobj.textures == 0) || (texlist_obj_shareobj.textures->texaddr == 0))
		return;
	FUN_00422560(3);
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.z != 0)
		njRotateZ(0, (unsigned short)local_8->ang.z);
	if (local_8->ang.x != 0)
		njRotateX(0, (unsigned short)local_8->ang.x);
	if (local_8->ang.y != 0)
		njRotateY(0, (unsigned short)local_8->ang.y);
	___njSetTexture(&texlist_obj_shareobj);
	___dsDrawObject(&object_tpobj7_dpaneru_dpaneru[0]);
	njPopMatrix(1);
	npSetZCompare();
}

// STUB: SADX 0x008d4b60
void dashpanel_for_cartTextureAnimation(struct task *tp)
{
}
