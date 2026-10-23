#include "decls.h"
extern float DAT_05b3ec0c;
extern float DAT_05b3ec10;
extern float DAT_05b3ec14;
extern int DAT_05edbd0c;
extern int DAT_05edbd7c;

// FUNCTION: SADX 0x005a88c0
void FUN_005a88c0(struct sMobleCtrl *param_1, struct taskwk *param_2, struct taskwk *param_3)
{
	*(char *)param_1 = 1;
	param_2->ang = param_3->ang;
	DAT_05b3ec0c = 0.0;
	DAT_05b3ec10 = 1.0;
	DAT_05b3ec14 = 10.0;
	PConvertVector_P2G(param_3, (struct NJS_POINT3 *)&DAT_05b3ec0c);
	FUN_005a8990((float *)&param_3->pos, &DAT_05b3ec0c, (float *)&param_2->pos);
	*(short *)((char *)param_1 + 0xc) = GetNearestPath(&param_3->pos, (struct sMRacePath *)DAT_05edbd7c, *(short *)((char *)param_1 + 8));
	*(short *)((char *)param_1 + 0xe) = GetNearestPath(&param_2->pos, (struct sMRacePath *)DAT_05edbd0c, *(short *)((char *)param_1 + 0xa));
	FUN_005a9060(*(short *)((char *)param_1 + 0xc));
}
