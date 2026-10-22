#include "decls.h"
extern int DAT_05b9d838;
extern struct NJS_TEXLIST texlist_egm2_common;
extern struct obj object_egman_body_body[1];
extern struct NJS_POINT3 DAT_009bfd58;

// FUNCTION: SADX 0x006c9eb0
void Egm2EggmanDisp(struct task *tp)
{
	if (!DAT_05b9d838)
	{
		___njSetTexture(&texlist_egm2_common);
		njPushMatrix(0);
		njTranslateV(0, &DAT_009bfd58);
		ds_DrawObjectClip((struct obj *)&object_egman_body_body, 1);
		njPopMatrix(1);
	}
}
