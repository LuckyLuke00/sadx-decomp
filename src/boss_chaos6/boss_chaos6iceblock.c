#include "decls.h"
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void njPushMatrix(float *param_1);
void njTranslateV(float *param_1, struct NJS_POINT3 *param_2);
void njRotateZ(float *param_1, int param_2);
void njRotateX(float *param_1, unsigned short param_2);
void njRotateY(float *param_1, unsigned short param_2);
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
void late_DrawObjectMesh(struct obj *obj, int flgs);
void njPopMatrix(int param_1);
extern struct NJS_TEXLIST texlist_chaos6;
extern struct obj *iceobj_tbl[7];

// STUB: SADX 0x006f8eb0
void SetChaos6IceBlock(int id, int num)
{
}
