#include "decls.h"
extern unsigned char DAT_05edd821;
extern unsigned char DAT_05edd820;
void DestroyControl();
static void title_menu_disp(struct task *tp);
static void title_menu_exec(struct task *tp);
static void DisplayTitleNew(float basez);

// FUNCTION: SADX 0x005eb290
void DrawOptionMenuSubDlgSub(struct DDlgType *dlgp)
{
	___njSetTexture(&texlist_ava_help_options);
	ghSetPvrTexMaterial(0xffffffff);
}

// FUNCTION: SADX 0x005eb2b0
int DisplayControl()
{
	if (DAT_05edd820 == 2 && (DAT_05b92e44 & 2) != 0)
	{
		dsPlay_oneshot(3, 0, 0, 0);
		DAT_05edd820 = 3;
	}
	switch (DAT_05edd820)
	{
	case 0:
		return 0;
	case 1:
		if (InitControl() == 0)
		{
			DAT_05edd820 = 0;
			return 0;
		}
		DAT_05edd820 = 2;
		break;
	case 2:
		DrawControl();
		break;
	case 3:
		DestroyControl();
		DAT_05edd820 = 0;
		return 2;
	}
	return 1;
}

// STUB: SADX 0x005eba60
void DestroyControl()
{
}

// FUNCTION: SADX 0x005ebb90
int DisplayStaff()
{
	if ((DAT_05edd821 == 2 || DAT_05edd821 == 3) && (DAT_05b92e44 & 2) != 0)
	{
		dsPlay_oneshot(3, 0, 0, 0);
		DAT_05edd821 = 4;
	}
	switch (DAT_05edd821)
	{
	case 0:
		return 0;
	case 1:
		if (InitStaff() == 0)
		{
			DAT_05edd821 = 0;
			return 0;
		}
		DAT_05edd821 = 2;
		break;
	case 2:
		DrawStaff();
		break;
	case 4:
		DestroyStaff();
		DAT_05edd821 = 0;
		return 2;
	}
	return 1;
}

// FUNCTION: SADX 0x005ee430
struct task *SetAdvaOptionMenuTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, title_menu_exec);
	DAT_05edd7bc = local_8g;
	if (DAT_05edd7bc != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, prmp);
		local_8g->exec = title_menu_exec;
		local_8g->disp = title_menu_disp;
	}
	return local_8g;
}

// STUB: SADX 0x005ee4a0
static void title_menu_exec(struct task *tp)
{
}

// STUB: SADX 0x005ee660
void FUN_005ee660(void *param_1)
{
}

// STUB: SADX 0x005effc0
static void title_menu_disp(struct task *tp)
{
}

// FUNCTION: SADX 0x005f0b00
void FUN_005f0b00(struct task *param_1)
{
	DisplayTitleNew(*(float *)((char *)param_1 + 0x10));
}

// STUB: SADX 0x005f0b20
static void DisplayTitleNew(float basez)
{
}

// STUB: SADX 0x005f0ee0
void FreeAdvaOptionMenuTask()
{
}
