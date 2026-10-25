#include "decls.h"
void FUN_00422560(int param_1);
void npSetZCompare();
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void FUN_004a7cb0(struct obj *param_1, struct NJS_MOTION *param_2, float param_3);
extern struct NJS_TEXLIST texlist_chao_entrance;
extern struct obj object_crch_nc_door_all_nc_door_all[];
extern struct NJS_MOTION motion_crch_nc_door_all[];
extern int DAT_05b9d838;
extern int DAT_05b33014;

// FUNCTION: SADX 0x004720d0
void ALO_EntDoorOpen()
{
	*(char *)((char *)*(int *)((char *)DAT_05b33014 + 0x2c) + 0xf) = 1;
}
