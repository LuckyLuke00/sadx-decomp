#include "decls.h"
void FUN_00472030(struct task *param_1);
static void FDisp(struct task *tp);
static void FDest(struct task *tp);
void njDirectUpdateObject(struct obj *);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
void FUN_00422560(int param_1);
void npSetZCompare();
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void FUN_004a7cb0(struct obj *param_1, struct NJS_MOTION *param_2, float param_3);
extern struct NJS_TEXLIST texlist_chao_entrance;
extern struct obj object_crch_nc_door_all_nc_door_all[];
extern struct NJS_MOTION motion_crch_nc_door_all[];
extern int DAT_05b9d838;
extern int DAT_05b33014;

// FUNCTION: SADX 0x00471fb0
static void FDest(struct task *tp)
{
	njDirectReleaseObject((struct obj *)&object_crch_nc_door_all_nc_door_all);
	Free(tp->awp);
	tp->awp = 0;
}

// FUNCTION: SADX 0x00471fe0
static void FDisp(struct task *tp)
{
	struct anywk *var1;

	if (DAT_05b9d838 == 0)
	{
		var1 = tp->awp;
		___njSetTexture(&texlist_chao_entrance);
		FUN_00422560(3);
		FUN_004a7cb0((struct obj *)&object_crch_nc_door_all_nc_door_all, (struct NJS_MOTION *)&motion_crch_nc_door_all, *(float *)var1);
		npSetZCompare();
	}
}

// FUNCTION: SADX 0x00472090
struct task *FUN_00472090()
{
	struct task *var1;
	var1 = CreateElementalTask(8, 2, FUN_00472030);
	var1->dest = FDest;
	var1->disp = FDisp;
	DAT_05b33014 = (int)var1;
	njDirectUpdateObject((struct obj *)&object_crch_nc_door_all_nc_door_all);
	return var1;
}

// FUNCTION: SADX 0x004720d0
void ALO_EntDoorOpen()
{
	*(char *)((char *)*(int *)((char *)DAT_05b33014 + 0x2c) + 0xf) = 1;
}
