#include "decls.h"
extern struct NJS_MODEL *model_name[6];
extern int DAT_05b9d838;
void SetObjectTexture2(long No);
void njPushMatrix(float *);
void njTranslateV(float *, struct NJS_POINT3 *);
void njRotateY(float *, unsigned short);
void ds_DrawModelClip(struct NJS_MODEL *mdl, float clipScl);
void njPopMatrix(int param_1);
