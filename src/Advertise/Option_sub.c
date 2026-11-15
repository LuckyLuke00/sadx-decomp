#include "decls.h"
#include <string>
#include <vector>
#include "../advertise.h"
extern unsigned char DAT_05edd821;
extern unsigned char DAT_05edd820;
extern float DAT_05edd854;
extern float DAT_05edd858;
extern unsigned char DAT_0267aa45;
extern unsigned char DAT_0267aa44;
extern int DAT_0267aa40;
extern int DAT_05edd830;
extern unsigned int DAT_01c6e42c;
std::wstring trim2(const std::wstring& param_1);
std::vector<std::wstring, std::allocator<std::wstring> > FUN_005ebc40(const std::wstring& param_1, const std::wstring& param_2, bool param_3);
void DestroyControl();
static void title_menu_disp(struct task *tp);
static void title_menu_exec(struct task *tp);
static void DisplayTitleNew(float basez);

// GLOBAL: SADX 0x05edd840
std::vector<std::wstring>::iterator DAT_05edd840;

// GLOBAL: SADX 0x05edd844
std::vector<std::wstring> DAT_05edd844;

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

// FUNCTION: SADX 0x005ebea0
int InitStaff()
{
	SOCFile* local_3c0v = new SOCFile;
	int local_3b8q = 0;
	if (local_3c0v->Open(".\\system\\SonicADV_Socstaff.bin", 1))
	{
		local_3b8q = local_3c0v->FUN_009285c0();
		local_3c0v->FUN_00928630(0, 0);
	}
	else
	{
		delete local_3c0v;
		local_3c0v = 0;
		return 0;
	}
	wchar_t* local_3c8w = new wchar_t[(local_3b8q + 2) / 2];
	wchar_t* local_3bch = 0;
	local_3bch = local_3c8w;
	unsigned long local_3b4g = 0;
	bool local_3c1m = local_3c0v->FUN_009286c0(local_3bch, local_3b8q, &local_3b4g);
	if (!local_3c1m)
	{
		delete local_3c0v;
		local_3c0v = 0;
		delete[] local_3c8w;
		return 0;
	}
	UnknowTochar((char*)local_3c8w, local_3b8q);
	local_3c8w[local_3b8q / 2] = 0;
	DAT_05edd844 = FUN_005ebc40(local_3c8w + 1, L"\n", true);
	delete local_3c0v;
	delete[] local_3c8w;
	unsigned int local_3ccy;
	for (local_3ccy = 0; local_3ccy < DAT_05edd844.size(); local_3ccy = local_3ccy + 1)
	{
		DAT_05edd844[local_3ccy] = trim2(DAT_05edd844[local_3ccy]);
	}
	DAT_05edd840 = DAT_05edd844.begin() + 426;
	int local_3d0n = 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"Patch"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L""), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"LITTLE STONE SOFTWARE"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L""), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"Jeff Astor"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"Peter Bratcher"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"Adam Hooley"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"Ben Watson"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"Sean Workman"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L""), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"SEGA OF EUROPE"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L""), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"*ASSOCIATE PRODUCER"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"Jessica Padkin"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L""), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"*PROJECT LEAD"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"Andrew Sparks"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L""), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"*FUNCTIONALITY QA LEAD"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"Christopher Dadswell"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L""), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"*SENIOR TESTER"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"Wing-Pui Chung"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L""), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"*TESTER"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L"Finlay Milligan"), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L""), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L""), local_3d0n = local_3d0n + 1;
	DAT_05edd844.insert(DAT_05edd840 + local_3d0n, 1, L""), local_3d0n = local_3d0n + 1;
	DAT_05edd854 = DAT_01c6e42c;
	DAT_05edd858 = DAT_01c6e42c;
	DAT_0267aa45 = 1;
	DAT_0267aa44 = 1;
	DAT_0267aa40 = -1;
	DAT_05edd830 = 0;
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
