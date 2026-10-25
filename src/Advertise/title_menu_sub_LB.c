#include "decls.h"
void FUN_005fa3a0(struct DDlgType *param_1);
void FUN_005fa060();
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

// STUB: SADX 0x005fa060
void FUN_005fa060(void)
{
}

// STUB: SADX 0x005fa160
struct task *SetAdvaTitleMenuTask_LB(struct ModeSelPrmType *prmp)
{
	return (struct task *)0;
}

// STUB: SADX 0x005fa3a0
void FUN_005fa3a0(struct DDlgType *dlgp)
{
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
