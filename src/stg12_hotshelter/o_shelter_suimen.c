#include "decls.h"
extern struct NJS_TEXLIST texlist_shelter_suimen;
extern struct obj *objs[4];
extern float DAT_05b3df40;
extern int DAT_05b9d838;
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void njPushMatrix(float *param_1);
void njTranslateV(float *param_1, struct NJS_POINT3 *param_2);
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
void njRotateZ(float *param_1, int param_2);
void njRotateX(float *param_1, unsigned short param_2);
void late_DrawObjectClip(struct obj *obj, int flgs, float clipScl);
void njPopMatrix(int param_1);
