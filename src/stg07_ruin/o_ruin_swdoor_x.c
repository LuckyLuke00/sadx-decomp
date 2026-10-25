#include "decls.h"
void ___njSetTexture(struct NJS_TEXLIST *texlist);
extern struct NJS_TEXLIST texlist_sw_panel;
extern struct obj object_lwobj_lwdoor_lwdoor[];
extern int DAT_05b9d838;
void njPushMatrix(float *);
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
void njRotateY(float *, unsigned short);
void ds_DrawObjectClip(struct obj *obj, float clipScl);
void njPopMatrix(int param_1);
