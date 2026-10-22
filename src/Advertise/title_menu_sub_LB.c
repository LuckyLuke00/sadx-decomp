#include "decls.h"
static void DisplayTitleNew(float basez);

// FUNCTION: SADX 0x005f4e40
void DrawMainMenuDlgSub_LB(struct DDlgType *dlgp)
{
	___njSetTexture(&texlist_ava_lb_menu);
	ghSetPvrTexMaterial(0xffffffff);
}

// STUB: SADX 0x005f4e60
int FUN_005f4e60()
{
	return (int)0;
}

// FUNCTION: SADX 0x005fb390
void FUN_005fb390(struct task *param_1)
{
	DisplayTitleNew(*(float *)((char *)param_1 + 0x10));
}

// STUB: SADX 0x005fb3b0
static void DisplayTitleNew(float basez)
{
}
