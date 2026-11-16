#include <list>
#include "decls.h"
#include <string.h>
#include "../advertise.h"
struct DAT_05edd970_1
{
	wchar_t field_0x0[21];
	wchar_t field_0x2a[16];
	wchar_t field_0x4a[16];
};
// GLOBAL: SADX 0x05edd970
std::list<DAT_05edd970_1> DAT_05edd970;
// GLOBAL: SADX 0x05edd980
std::list<DAT_05edd970_1>::iterator DAT_05edd980;
static void title_menu_exec(struct task *tp);
static void title_menu_disp(struct task *tp);
extern unsigned char DAT_05edd940;
extern unsigned char DAT_05edd941;
extern unsigned char DAT_05edd942;
extern unsigned char DAT_05edd92c;
extern float DAT_05edd928;
extern int DAT_05edd930;
extern int DAT_05edd934;
extern int DAT_05edd938;
extern int DAT_05edd958;
extern int DAT_05edd95c;
extern int DAT_05edd964;
extern int DAT_05edd968;
extern int DAT_05edd96c;
extern unsigned char DAT_05edd92e;
extern bool DAT_05edd92f;
extern unsigned char DAT_05edd943;
extern int DAT_05edd93c;
extern int DAT_05b3ebbc;
extern Magic::RenderCore::Texture *DAT_05edd948;
extern Magic::RenderCore::Texture *DAT_05edd94c;
extern Magic::RenderCore::Texture *DAT_05edd950;
extern Magic::RenderCore::Texture *DAT_05edd954;
extern struct ButtonInfo DAT_0267b980[17];
extern struct ButtonInfo DAT_0267ba90[17];
extern struct ButtonInfo DAT_0267bba0[17];
extern struct ButtonInfo DAT_0267b870[17];
extern struct ButtonInfo DAT_0267b760[17];
extern struct ButtonInfo texinfo_I[];
extern struct ButtonInfo texinfo_G[];
extern struct ButtonInfo texinfo_S[];
extern struct ButtonInfo texinfo_F[];
extern struct ButtonInfo texinfo_J[];
extern struct ButtonInfo texinfo_E[];
extern struct SAVE_DATA DAT_05cd0f30;
void FUN_005fa3a0(struct DDlgType *param_1);
void FUN_005fa060();
static void DisplayTitleNew(float basez);

// FUNCTION: SADX 0x005f4e40
void DrawMainMenuDlgSub_LB(struct DDlgType *dlgp)
{
	___njSetTexture(&texlist_ava_lb_menu);
	ghSetPvrTexMaterial(0xffffffff);
}

// FUNCTION: SADX 0x005f4e60
int FUN_005f4e60()
{
	switch ((unsigned char)DAT_05edd940)
	{
		case 0:
			return 0;
		case 1:
			if (InitLB() == 0)
			{
				DAT_05edd940 = 0;
				return 0;
			}
			DAT_05edd940 = 2;
			break;
		case 2:
			DrawLB();
			break;
		case 3:
			FUN_005fa060();
			DAT_05edd940 = 0;
			return 2;
	}
	return 1;
}

// FUNCTION: SADX 0x005f4ee0
int InitLB()
{
	SOCFileStream fileStream;

	if (fileStream.ReadFile("system\\LeaderBoards\\BG.dds"))
	{
		DAT_05edd948 = new Magic::RenderCore::Texture;
		DAT_05edd948->Load(fileStream.FUN_00424960(), 1, fileStream.FUN_0040b8a0(), 0, 1, 0);
	}
	switch (DAT_05b3ebbc)
	{
		case 0:
			if (fileStream.ReadFile("system\\LeaderBoards\\Text1.dds"))
			{
				DAT_05edd94c = new Magic::RenderCore::Texture;
				DAT_05edd94c->Load(fileStream.FUN_00424960(), 1, fileStream.FUN_0040b8a0(), 0, 1, 0);
			}
			if (fileStream.ReadFile("system\\LeaderBoards\\Text2.dds"))
			{
				DAT_05edd950 = new Magic::RenderCore::Texture;
				DAT_05edd950->Load(fileStream.FUN_00424960(), 1, fileStream.FUN_0040b8a0(), 0, 1, 0);
			}
			break;
		case 4:
			if (fileStream.ReadFile("system\\LeaderBoards\\Text1_de.dds"))
			{
				DAT_05edd94c = new Magic::RenderCore::Texture;
				DAT_05edd94c->Load(fileStream.FUN_00424960(), 1, fileStream.FUN_0040b8a0(), 0, 1, 0);
			}
			if (fileStream.ReadFile("system\\LeaderBoards\\Text2_de.dds"))
			{
				DAT_05edd950 = new Magic::RenderCore::Texture;
				DAT_05edd950->Load(fileStream.FUN_00424960(), 1, fileStream.FUN_0040b8a0(), 0, 1, 0);
			}
			break;
		case 3:
			if (fileStream.ReadFile("system\\LeaderBoards\\Text1_es.dds"))
			{
				DAT_05edd94c = new Magic::RenderCore::Texture;
				DAT_05edd94c->Load(fileStream.FUN_00424960(), 1, fileStream.FUN_0040b8a0(), 0, 1, 0);
			}
			if (fileStream.ReadFile("system\\LeaderBoards\\Text2_es.dds"))
			{
				DAT_05edd950 = new Magic::RenderCore::Texture;
				DAT_05edd950->Load(fileStream.FUN_00424960(), 1, fileStream.FUN_0040b8a0(), 0, 1, 0);
			}
			break;
		case 2:
			if (fileStream.ReadFile("system\\LeaderBoards\\Text1_fr.dds"))
			{
				DAT_05edd94c = new Magic::RenderCore::Texture;
				DAT_05edd94c->Load(fileStream.FUN_00424960(), 1, fileStream.FUN_0040b8a0(), 0, 1, 0);
			}
			if (fileStream.ReadFile("system\\LeaderBoards\\Text2_fr.dds"))
			{
				DAT_05edd950 = new Magic::RenderCore::Texture;
				DAT_05edd950->Load(fileStream.FUN_00424960(), 1, fileStream.FUN_0040b8a0(), 0, 1, 0);
			}
			break;
		default:
			if (fileStream.ReadFile("system\\LeaderBoards\\Text1.dds"))
			{
				DAT_05edd94c = new Magic::RenderCore::Texture;
				DAT_05edd94c->Load(fileStream.FUN_00424960(), 1, fileStream.FUN_0040b8a0(), 0, 1, 0);
			}
			if (fileStream.ReadFile("system\\LeaderBoards\\Text2.dds"))
			{
				DAT_05edd950 = new Magic::RenderCore::Texture;
				DAT_05edd950->Load(fileStream.FUN_00424960(), 1, fileStream.FUN_0040b8a0(), 0, 1, 0);
			}
			break;
	}
	DAT_05edd968 = 0;
	DAT_05edd96c = 0;
	DAT_05edd970.clear();
	DAT_05edd930 = 0;
	DAT_05edd958 = 0;
	LBChange = 2;
	DAT_05edd941 = 0;
	if (DAT_05edd92e == 0)
	{
		FUN_005f5940(DAT_05edd942, LBChange, DAT_05edd941, 2);
	}
	DAT_05edd92f = 1;
	DAT_05edd93c = FUN_0041a800()->FUN_004caf80();
	DAT_05edd943 = 0;
	LbPage = 1;
	return 1;
}

// FUNCTION: SADX 0x005f5940
void FUN_005f5940(unsigned char param_1, unsigned char param_2, unsigned char param_3, int param_4)
{
	DAT_05edd970_1 local_7c;

	DAT_05edd970.clear();
	for (int local_80 = 0; local_80 < 0xc; local_80 = local_80 + 1)
	{
		swprintf(local_7c.field_0x0, 5, L"%05d", local_80);
		swprintf(local_7c.field_0x2a, 0x10, L"%02d:%02d:%02d", local_80 + 1, local_80 + 1, local_80 + 1);
		swprintf(local_7c.field_0x4a, 0x10, L"%06d", 0);
		DAT_05edd970.push_back(local_7c);
	}
	DAT_05edd980 = DAT_05edd970.begin();
}

// FUNCTION: SADX 0x005f5a70
void DrawLB()
{
	float local_70l = 0.0f;
	float local_34g = -18.0f;
	float local_6c = DAT_01c6e428 / 920.0;
	float local_68i = DAT_01c6e42c / 690.0;
	struct ButtonInfo *local_50t;
	if (FUN_0041a800()->FUN_004caf80() - DAT_05edd93c >= 500)
	{
		DAT_05edd92f = !DAT_05edd92f;
		DAT_05edd93c = FUN_0041a800()->FUN_004caf80();
	}
	DrawTexture(0, 0, 640, 480, 0.9f, DAT_05edd948, 0.0f, 0.0f, 0.8984375f, 0.673828125f, -1);
	int local_30h = 0;
	local_50t = 0;
	float local_44s = 0.0f;
	float local_40u = 0.0f;
	float local_3ch = 0.0f;
	float local_4c = 0.0f;
	float local_54g = 0.0f;
	float local_64s = 0.0f;
	float local_48q = 0.0f;
	float local_60o = 0.0f;
	switch (DAT_05b42a90)
	{
	case 5: local_50t = texinfo_I; break;
	case 4: local_50t = texinfo_G; break;
	case 3: local_50t = texinfo_S; break;
	case 2: local_50t = texinfo_F; break;
	case 0: local_50t = texinfo_J; break;
	default: local_50t = texinfo_E; break;
	}
	if (DAT_05edd942 == 0)
	{
		DrawTexture((int)(local_6c * 43.0), (int)(local_68i * 22.0 - local_68i * 12.0 + local_68i * 10.0), (int)(local_50t[1].Windth * local_6c), (int)(local_50t[1].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[1].PosX / 1024.0), (float)(local_50t[1].PosY / 1024.0), (float)((local_50t[1].PosX + local_50t[1].Windth) / 1024.0), (float)((local_50t[1].PosY + local_50t[1].Height) / 1024.0), -1);
		switch (LBChange)
		{
			case 0:
				DrawTexture((int)(local_50t[1].Windth * local_6c + 13.0 + 26.0), (int)(local_68i * 36.0 - local_68i * -5.0), (int)(local_50t[20].Windth * local_6c), (int)(local_50t[20].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[20].PosX / 1024.0), (float)(local_50t[20].PosY / 1024.0), (float)((local_50t[20].PosX + local_50t[20].Windth) / 1024.0), (float)((local_50t[20].PosY + local_50t[20].Height) / 1024.0), -1);
				break;
			case 1:
				DrawTexture((int)(local_50t[1].Windth * local_6c + 13.0 + 26.0), (int)(local_68i * 36.0 - local_68i * -5.0), (int)(local_50t[21].Windth * local_6c), (int)(local_50t[21].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[21].PosX / 1024.0), (float)(local_50t[21].PosY / 1024.0), (float)((local_50t[21].PosX + local_50t[21].Windth) / 1024.0), (float)((local_50t[21].PosY + local_50t[21].Height) / 1024.0), -1);
				break;
			case 2:
				DrawTexture((int)(local_50t[1].Windth * local_6c + 13.0 + 26.0), (int)(local_68i * 36.0 - local_68i * -5.0), (int)(local_50t[22].Windth * local_6c), (int)(local_50t[22].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[22].PosX / 1024.0), (float)(local_50t[22].PosY / 1024.0), (float)((local_50t[22].PosX + local_50t[22].Windth) / 1024.0), (float)((local_50t[22].PosY + local_50t[22].Height) / 1024.0), -1);
				break;
		}
	}
	else
	{
		DrawTexture((int)(local_6c * 43.0), (int)(local_68i * 22.0 - local_68i * 12.0 + local_68i * 10.0), (int)(local_50t[0].Windth * local_6c), (int)(local_50t[0].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[0].PosX / 1024.0), (float)(local_50t[0].PosY / 1024.0), (float)((local_50t[0].PosX + local_50t[0].Windth) / 1024.0), (float)((local_50t[0].PosY + local_50t[0].Height) / 1024.0), -1);
		switch (LBChange)
		{
			case 0:
				DrawTexture((int)(local_50t[0].Windth * local_6c + 13.0 + 26.0), (int)(local_68i * 36.0 - local_68i * -5.0), (int)(local_50t[20].Windth * local_6c), (int)(local_50t[20].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[20].PosX / 1024.0), (float)(local_50t[20].PosY / 1024.0), (float)((local_50t[20].PosX + local_50t[20].Windth) / 1024.0), (float)((local_50t[20].PosY + local_50t[20].Height) / 1024.0), -1);
				break;
			case 1:
				DrawTexture((int)(local_50t[0].Windth * local_6c + 13.0 + 26.0), (int)(local_68i * 36.0 - local_68i * -5.0), (int)(local_50t[21].Windth * local_6c), (int)(local_50t[21].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[21].PosX / 1024.0), (float)(local_50t[21].PosY / 1024.0), (float)((local_50t[21].PosX + local_50t[21].Windth) / 1024.0), (float)((local_50t[21].PosY + local_50t[21].Height) / 1024.0), -1);
				break;
			case 2:
				DrawTexture((int)(local_50t[0].Windth * local_6c + 13.0 + 26.0), (int)(local_68i * 36.0 - local_68i * -5.0), (int)(local_50t[22].Windth * local_6c), (int)(local_50t[22].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[22].PosX / 1024.0), (float)(local_50t[22].PosY / 1024.0), (float)((local_50t[22].PosX + local_50t[22].Windth) / 1024.0), (float)((local_50t[22].PosY + local_50t[22].Height) / 1024.0), -1);
				break;
		}
	}
	if (DAT_05edd92f != 0)
	{
		DrawTexture((int)(local_6c * 79.0), (int)(local_68i * 109.0), (int)(local_50t[30].Windth * local_6c), (int)(local_50t[30].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[30].PosX / 1024.0), (float)(local_50t[30].PosY / 1024.0), (float)((local_50t[30].PosX + local_50t[30].Windth) / 1024.0), (float)((local_50t[30].PosY + local_50t[30].Height) / 1024.0), -1);
		DrawTexture((int)(local_6c * 800.0), (int)(local_68i * 109.0), (int)(local_50t[31].Windth * local_6c), (int)(local_50t[31].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[31].PosX / 1024.0), (float)(local_50t[31].PosY / 1024.0), (float)((local_50t[31].PosX + local_50t[31].Windth) / 1024.0), (float)((local_50t[31].PosY + local_50t[31].Height) / 1024.0), -1);
	}
	switch (DAT_05edd941)
	{
		case 0:
			DrawTexture((int)((DAT_01c6e428 - local_50t[2].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[2].Windth * local_6c), (int)(local_50t[2].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[2].PosX / 1024.0), (float)(local_50t[2].PosY / 1024.0), (float)((local_50t[2].PosX + local_50t[2].Windth) / 1024.0), (float)((local_50t[2].PosY + local_50t[2].Height) / 1024.0), -1);
			break;
		case 1:
			DrawTexture((int)((920.0 - local_50t[3].Windth) / 2.0 * local_6c), (int)(local_68i * 104.0), (int)(local_50t[3].Windth * local_6c), (int)(local_50t[3].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[3].PosX / 1024.0), (float)(local_50t[3].PosY / 1024.0), (float)((local_50t[3].PosX + local_50t[3].Windth) / 1024.0), (float)((local_50t[3].PosY + local_50t[3].Height) / 1024.0), -1);
			break;
		case 15:
			DrawTexture((int)((DAT_01c6e428 - local_50t[4].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[4].Windth * local_6c), (int)(local_50t[4].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[4].PosX / 1024.0), (float)(local_50t[4].PosY / 1024.0), (float)((local_50t[4].PosX + local_50t[4].Windth) / 1024.0), (float)((local_50t[4].PosY + local_50t[4].Height) / 1024.0), -1);
			break;
		case 5:
			DrawTexture((int)((DAT_01c6e428 - local_50t[5].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[5].Windth * local_6c), (int)(local_50t[5].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[5].PosX / 1024.0), (float)(local_50t[5].PosY / 1024.0), (float)((local_50t[5].PosX + local_50t[5].Windth) / 1024.0), (float)((local_50t[5].PosY + local_50t[5].Height) / 1024.0), -1);
			break;
		case 12:
			DrawTexture((int)((DAT_01c6e428 - local_50t[6].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[6].Windth * local_6c), (int)(local_50t[6].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[6].PosX / 1024.0), (float)(local_50t[6].PosY / 1024.0), (float)((local_50t[6].PosX + local_50t[6].Windth) / 1024.0), (float)((local_50t[6].PosY + local_50t[6].Height) / 1024.0), -1);
			break;
		case 7:
			DrawTexture((int)((DAT_01c6e428 - local_50t[7].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[7].Windth * local_6c), (int)(local_50t[7].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[7].PosX / 1024.0), (float)(local_50t[7].PosY / 1024.0), (float)((local_50t[7].PosX + local_50t[7].Windth) / 1024.0), (float)((local_50t[7].PosY + local_50t[7].Height) / 1024.0), -1);
			break;
		case 9:
			DrawTexture((int)((DAT_01c6e428 - local_50t[9].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[9].Windth * local_6c), (int)(local_50t[9].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[9].PosX / 1024.0), (float)(local_50t[9].PosY / 1024.0), (float)((local_50t[9].PosX + local_50t[9].Windth) / 1024.0), (float)((local_50t[9].PosY + local_50t[9].Height) / 1024.0), -1);
			break;
		case 16:
			DrawTexture((int)((DAT_01c6e428 - local_50t[10].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[10].Windth * local_6c), (int)(local_50t[10].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[10].PosX / 1024.0), (float)(local_50t[10].PosY / 1024.0), (float)((local_50t[10].PosX + local_50t[10].Windth) / 1024.0), (float)((local_50t[10].PosY + local_50t[10].Height) / 1024.0), -1);
			break;
		case 13:
			DrawTexture((int)((DAT_01c6e428 - local_50t[11].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[11].Windth * local_6c), (int)(local_50t[11].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[11].PosX / 1024.0), (float)(local_50t[11].PosY / 1024.0), (float)((local_50t[11].PosX + local_50t[11].Windth) / 1024.0), (float)((local_50t[11].PosY + local_50t[11].Height) / 1024.0), -1);
			break;
		case 4:
			DrawTexture((int)((DAT_01c6e428 - local_50t[12].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[12].Windth * local_6c), (int)(local_50t[12].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[12].PosX / 1024.0), (float)(local_50t[12].PosY / 1024.0), (float)((local_50t[12].PosX + local_50t[12].Windth) / 1024.0), (float)((local_50t[12].PosY + local_50t[12].Height) / 1024.0), -1);
			break;
		case 14:
			DrawTexture((int)((DAT_01c6e428 - local_50t[13].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[13].Windth * local_6c), (int)(local_50t[13].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[13].PosX / 1024.0), (float)(local_50t[13].PosY / 1024.0), (float)((local_50t[13].PosX + local_50t[13].Windth) / 1024.0), (float)((local_50t[13].PosY + local_50t[13].Height) / 1024.0), -1);
			break;
		case 8:
			DrawTexture((int)((DAT_01c6e428 - local_50t[14].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[14].Windth * local_6c), (int)(local_50t[14].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[14].PosX / 1024.0), (float)(local_50t[14].PosY / 1024.0), (float)((local_50t[14].PosX + local_50t[14].Windth) / 1024.0), (float)((local_50t[14].PosY + local_50t[14].Height) / 1024.0), -1);
			break;
		case 6:
			DrawTexture((int)((DAT_01c6e428 - local_50t[15].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[15].Windth * local_6c), (int)(local_50t[15].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[15].PosX / 1024.0), (float)(local_50t[15].PosY / 1024.0), (float)((local_50t[15].PosX + local_50t[15].Windth) / 1024.0), (float)((local_50t[15].PosY + local_50t[15].Height) / 1024.0), -1);
			break;
		case 11:
			DrawTexture((int)((DAT_01c6e428 - local_50t[16].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[16].Windth * local_6c + 15.0), (int)(local_50t[16].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[16].PosX / 1024.0), (float)(local_50t[16].PosY / 1024.0), (float)((local_50t[16].PosX + local_50t[16].Windth + 15.0) / 1024.0), (float)((local_50t[16].PosY + local_50t[16].Height) / 1024.0), -1);
			break;
		case 3:
			DrawTexture((int)((DAT_01c6e428 - local_50t[17].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[17].Windth * local_6c), (int)(local_50t[17].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[17].PosX / 1024.0), (float)(local_50t[17].PosY / 1024.0), (float)((local_50t[17].PosX + local_50t[17].Windth) / 1024.0), (float)((local_50t[17].PosY + local_50t[17].Height) / 1024.0), -1);
			break;
		case 17:
			DrawTexture((int)((DAT_01c6e428 - local_50t[18].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[18].Windth * local_6c), (int)(local_50t[18].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[18].PosX / 1024.0), (float)(local_50t[18].PosY / 1024.0), (float)((local_50t[18].PosX + local_50t[18].Windth) / 1024.0), (float)((local_50t[18].PosY + local_50t[18].Height) / 1024.0), -1);
			break;
		case 10:
			DrawTexture((int)((DAT_01c6e428 - local_50t[19].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[19].Windth * local_6c), (int)(local_50t[19].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[19].PosX / 1024.0), (float)(local_50t[19].PosY / 1024.0), (float)((local_50t[19].PosX + local_50t[19].Windth) / 1024.0), (float)((local_50t[19].PosY + local_50t[19].Height) / 1024.0), -1);
			break;
		case 2:
			DrawTexture((int)((DAT_01c6e428 - local_50t[8].Windth * local_6c) / 2.0), (int)(local_68i * 104.0), (int)(local_50t[8].Windth * local_6c), (int)(local_50t[8].Height * local_68i), 0.01f, DAT_05edd94c, (float)(local_50t[8].PosX / 1024.0), (float)(local_50t[8].PosY / 1024.0), (float)((local_50t[8].PosX + local_50t[8].Windth) / 1024.0), (float)((local_50t[8].PosY + local_50t[8].Height) / 1024.0), -1);
			break;
	}
	DrawTexture((int)(local_6c * 50.0 + local_6c * 10.0 + local_44s * local_6c), (int)(local_68i * 188.0 - 5.0 - 5.0 - local_68i * 5.0), (int)(local_50t[26].Windth * local_6c), (int)(local_50t[26].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[26].PosX / 1024.0), (float)(local_50t[26].PosY / 1024.0), (float)((local_50t[26].PosX + local_50t[26].Windth + 3.0) / 1024.0), (float)((local_50t[26].PosY + local_50t[26].Height) / 1024.0), -1);
	DrawTexture((int)(local_6c * 233.0 - 25.0 + 8.0 + local_40u * local_6c), (int)(local_68i * 188.0 - 5.0 - 5.0 - local_68i * 5.0), (int)(local_50t[24].Windth * local_6c), (int)(local_50t[24].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[24].PosX / 1024.0), (float)(local_50t[24].PosY / 1024.0), (float)((local_50t[24].PosX + local_50t[24].Windth) / 1024.0), (float)((local_50t[24].PosY + local_50t[24].Height) / 1024.0), -1);
	if (DAT_05edd941 == 11 || DAT_05edd941 == 12)
	{
		DrawTexture((int)(local_6c * 561.0 + 10.0 + 2.0 - 8.0 + 4.0 + local_54g * local_6c), (int)(local_68i * 188.0 - 5.0 - 5.0 - local_68i * 5.0), (int)(local_50t[28].Windth * local_6c), (int)(local_50t[28].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[28].PosX / 1024.0), (float)(local_50t[28].PosY / 1024.0), (float)((local_50t[28].PosX + local_50t[28].Windth + 5.0) / 1024.0), (float)((local_50t[28].PosY + local_50t[28].Height) / 1024.0), -1);
		DrawTexture((int)(local_6c * 772.0 - 16.0 + local_48q * local_6c), (int)(local_68i * 188.0 - 5.0 - 5.0 - local_68i * 5.0), (int)(local_50t[25].Windth * local_6c), (int)(local_50t[25].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[25].PosX / 1024.0), (float)(local_50t[25].PosY / 1024.0), (float)((local_50t[25].PosX + local_50t[25].Windth) / 1024.0), (float)((local_50t[25].PosY + local_50t[25].Height) / 1024.0), -1);
	}
	else if (DAT_05edd941 == 15 || DAT_05edd941 == 17 || DAT_05edd941 == 16 || DAT_05edd941 == 14)
	{
		DrawTexture((int)(local_6c * 561.0 + 10.0 + 2.0 + local_64s * local_6c), (int)(local_68i * 188.0 - 5.0 - 5.0 - local_68i * 5.0), (int)(local_50t[25].Windth * local_6c), (int)(local_50t[25].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[25].PosX / 1024.0), (float)(local_50t[25].PosY / 1024.0), (float)((local_50t[25].PosX + local_50t[25].Windth) / 1024.0), (float)((local_50t[25].PosY + local_50t[25].Height) / 1024.0), -1);
	}
	else if (DAT_05edd941 == 13)
	{
		DrawTexture((int)(local_6c * 561.0 + 10.0 + 2.0 + 13.0 - 4.0 + local_3ch * local_6c), (int)(local_68i * 188.0 - 5.0 - 5.0 - local_68i * 5.0), (int)(local_50t[27].Windth * local_6c), (int)(local_50t[27].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[27].PosX / 1024.0), (float)(local_50t[27].PosY / 1024.0), (float)((local_50t[27].PosX + local_50t[27].Windth + 5.0) / 1024.0), (float)((local_50t[27].PosY + local_50t[27].Height) / 1024.0), -1);
	}
	else
	{
		DrawTexture((int)(local_6c * 561.0 + 10.0 + 2.0 + 13.0 - 4.0 + local_4c * local_6c), (int)(local_68i * 188.0 - 5.0 - 5.0 - local_68i * 5.0), (int)(local_50t[27].Windth * local_6c), (int)(local_50t[27].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[27].PosX / 1024.0), (float)(local_50t[27].PosY / 1024.0), (float)((local_50t[27].PosX + local_50t[27].Windth + 5.0) / 1024.0), (float)((local_50t[27].PosY + local_50t[27].Height) / 1024.0), -1);
		DrawTexture((int)(local_6c * 772.0 - 16.0 + local_48q * local_6c), (int)(local_68i * 188.0 - 5.0 - 5.0 - local_68i * 5.0), (int)(local_50t[25].Windth * local_6c), (int)(local_50t[25].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[25].PosX / 1024.0), (float)(local_50t[25].PosY / 1024.0), (float)((local_50t[25].PosX + local_50t[25].Windth) / 1024.0), (float)((local_50t[25].PosY + local_50t[25].Height) / 1024.0), -1);
	}
	wchar_t num[16] = {0};
	if (LBChange == 1)
		swprintf(num, 16, L"%d", DAT_05edd930);
	else if (LBChange == 0)
		swprintf(num, 16, L"%d", DAT_05edd934);
	else
		swprintf(num, 16, L"%d", DAT_05edd930);
	wchar_t *local_58aq = num;
	int Widthv = 0;
	int Heightr = 0;
	GetTextSize(local_58aq, Widthv, Heightr);
	DrawStringW((int)(local_6c * 603.0 - Widthv - local_6c * 170.0), (int)(local_68i * 610.0 + 6.0 - 12.0 + 1.0 + 2.0 * local_68i), local_58aq, -1, 1.0f);
	DrawTexture((int)(local_6c * 461.0 + DAT_05edd928 * local_6c), (int)(local_68i * 624.0 - 15.0 + 1.0 - local_68i * 11.0 + 2.0 * local_68i), (int)(local_50t[23].Windth * local_6c), (int)(local_50t[23].Height * local_68i), 0.01f, DAT_05edd950, (float)(local_50t[23].PosX / 1024.0), (float)(local_50t[23].PosY / 1024.0), (float)((local_50t[23].PosX + local_50t[23].Windth) / 1024.0), (float)((local_50t[23].PosY + local_50t[23].Height) / 1024.0), -1);
	struct ButtonInfo *local_7cz = 0;
	float local_88 = 0.0f;
	float local_78 = 0.0f;
	float local_8co = 0.0f;
	float local_80u = 0.0f;
	float local_84 = 0.0f;
	float local_74 = 0.0f;
	switch (DAT_05b3ebbc)
	{
	case 4: local_7cz = DAT_0267b980; break;
	case 3: local_7cz = DAT_0267ba90; break;
	case 2: local_7cz = DAT_0267bba0; break;
	case 0: local_7cz = DAT_0267b870; break;
	default: local_7cz = DAT_0267b760; break;
	}
	DrawTexture((int)(local_6c * 218.0 - local_6c * 45.0 + local_88 * local_6c), (int)(local_68i * 653.0 - 20.0 + 3.0 + 4.0), (int)(local_7cz[0].Windth * local_6c), (int)(local_7cz[0].Height * local_68i), 0.01f, DAT_05b3e36c, (float)(local_7cz[0].PosX / 512.0), (float)(local_7cz[0].PosY / 512.0), (float)((local_7cz[0].PosX + local_7cz[0].Windth) / 512.0), (float)((local_7cz[0].PosY + local_7cz[0].Height) / 512.0), -1);
	DrawTexture((int)(local_6c * 254.0 - local_6c * 45.0 + local_78 * local_6c), (int)(local_68i * 653.0 - 20.0 + 3.0 + 4.0), (int)(local_7cz[12].Windth * local_6c), (int)(local_7cz[12].Height * local_68i), 0.01f, DAT_05b3e36c, (float)(local_7cz[12].PosX / 512.0), (float)(local_7cz[12].PosY / 512.0), (float)((local_7cz[12].PosX + local_7cz[12].Windth) / 512.0), (float)((local_7cz[12].PosY + local_7cz[12].Height) / 512.0), -1);
	DrawTexture((int)(local_6c * 422.0 + local_8co * local_6c), (int)(local_68i * 653.0 - 20.0 + 3.0 + 4.0), (int)(local_7cz[3].Windth * local_6c), (int)(local_7cz[3].Height * local_68i), 0.01f, DAT_05b3e36c, (float)(local_7cz[3].PosX / 512.0), (float)(local_7cz[3].PosY / 512.0), (float)((local_7cz[3].PosX + local_7cz[3].Windth) / 512.0), (float)((local_7cz[3].PosY + local_7cz[3].Height) / 512.0), -1);
	DrawTexture((int)(local_6c * 460.0 + local_80u * local_6c), (int)(local_68i * 653.0 - 20.0 + 3.0 + 4.0), (int)(local_7cz[9].Windth * local_6c), (int)(local_7cz[9].Height * local_68i), 0.01f, DAT_05b3e36c, (float)(local_7cz[9].PosX / 512.0), (float)(local_7cz[9].PosY / 512.0), (float)((local_7cz[9].PosX + local_7cz[9].Windth) / 512.0), (float)((local_7cz[9].PosY + local_7cz[9].Height) / 512.0), -1);
	DrawTexture((int)(local_6c * 600.0 + local_6c * 75.0 + local_84 * local_6c), (int)(local_68i * 653.0 - 20.0 + 3.0 + 4.0), (int)(local_7cz[2].Windth * local_6c), (int)(local_7cz[2].Height * local_68i), 0.01f, DAT_05b3e36c, (float)(local_7cz[2].PosX / 512.0), (float)(local_7cz[2].PosY / 512.0), (float)((local_7cz[2].PosX + local_7cz[2].Windth) / 512.0), (float)((local_7cz[2].PosY + local_7cz[2].Height) / 512.0), -1);
	DrawTexture((int)(local_6c * 635.0 + local_6c * 75.0 + local_74 * local_6c), (int)(local_68i * 653.0 - 20.0 + 3.0 + 4.0), (int)(local_7cz[13].Windth * local_6c), (int)(local_7cz[13].Height * local_68i), 0.01f, DAT_05b3e36c, (float)(local_7cz[13].PosX / 512.0), (float)(local_7cz[13].PosY / 512.0), (float)((local_7cz[13].PosX + local_7cz[13].Windth) / 512.0), (float)((local_7cz[13].PosY + local_7cz[13].Height) / 512.0), -1);
	bool local_6 = false;
	bool local_5al = false;
	if (DAT_05edd92c != 1)
	{
		if ((DAT_05b92e44 & 0x10) && (LbPage != 1 || DAT_05edd964 != 0))
		{
			dsPlay_oneshot(1, 0, 0, 0);
			if (--DAT_05edd964 < 0)
			{
				LbPage--;
				DAT_05edd964 = 9;
				if (LbPage <= 0)
					LbPage = 1;
				if (LBChange != 0 && LbPage >= 1)
				{
					DAT_05edd970.clear();
					local_30h = 1;
					DAT_05edd92c = 1;
				}
				else if (LBChange == 0 && LbPage > 1)
					DAT_05edd980--;
			}
			else
				DAT_05edd980--;
		}
		if (DAT_05b92e44 & 0x20)
		{
			int local_90 = 0;
			if (LBChange == 0)
				local_90 = DAT_05edd934;
			else
				local_90 = DAT_05edd930;
			if ((LbPage - 1) * 10 + 1 + DAT_05edd964 <= local_90)
			{
				DAT_05edd964++;
				if (DAT_05edd964 >= DAT_05edd970.size() && DAT_05edd970.size() < 10)
					DAT_05edd964--;
				else if ((LbPage - 1) * 10 + 1 + DAT_05edd964 > local_90)
					DAT_05edd964--;
				else if (DAT_05edd964 > 9 && LBChange != 0)
				{
					dsPlay_oneshot(1, 0, 0, 0);
					DAT_05edd964 = 0;
					DAT_05edd970.clear();
					local_30h = 2;
					DAT_05edd92c = 1;
					LbPage++;
				}
				else if (DAT_05edd980 != DAT_05edd970.end() && LBChange == 0 && DAT_05edd964 > 9)
				{
					dsPlay_oneshot(1, 0, 0, 0);
					LbPage++;
					DAT_05edd980++;
				}
				else
				{
					dsPlay_oneshot(1, 0, 0, 0);
					DAT_05edd980++;
				}
			}
		}
	}
	if (DAT_05edd92c != 0)
	{
		switch (DAT_05b3ebbc)
		{
			case 4:
				DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.34472656f, 0.82128906f, 0.38085938f, -1);
				break;
			case 3:
				DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.51660156f, 0.82128906f, 0.5527344f, -1);
				break;
			case 2:
				DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.0f, 0.82128906f, 0.036132812f, -1);
				break;
			case 0:
				DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.171875f, 0.82128906f, 0.20800781f, -1);
				break;
			default:
				DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.0f, 0.82128906f, 0.038085938f, -1);
		}
	}
	else
	{
		if (DAT_05edd970.empty())
		{
			switch (LBChange)
			{
				case 0:
					switch (DAT_05b3ebbc)
					{
					case 4:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.3876953f, 0.82128906f, 0.42382812f, -1);
						break;
					case 3:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.5595703f, 0.82128906f, 0.5957031f, -1);
						break;
					case 2:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.04296875f, 0.82128906f, 0.07910156f, -1);
						break;
					case 0:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.21484375f, 0.82128906f, 0.25097656f, -1);
						break;
					default:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.04296875f, 0.82128906f, 0.07910156f, -1);
					}
					break;
				case 1:
					switch (DAT_05b3ebbc)
					{
					case 4:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.4736328f, 0.82128906f, 0.5097656f, -1);
						break;
					case 3:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.6455078f, 0.82128906f, 0.6816406f, -1);
						break;
					case 2:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.12890625f, 0.82128906f, 0.16503906f, -1);
						break;
					case 0:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.30078125f, 0.82128906f, 0.33691406f, -1);
						break;
					default:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.12890625f, 0.82128906f, 0.16503906f, -1);
					}
					break;
				case 2:
					switch (DAT_05b3ebbc)
					{
					case 4:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.43066406f, 0.82128906f, 0.46679688f, -1);
						break;
					case 3:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.60253906f, 0.82128906f, 0.6386719f, -1);
						break;
					case 2:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.0859375f, 0.82128906f, 0.12207031f, -1);
						break;
					case 0:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.2578125f, 0.82128906f, 0.2939453f, -1);
						break;
					default:
						DrawTexture((int)(local_6c * 42.0), (int)(local_68i * 242.0 - 9.0), (int)(local_6c * 841.0), (int)(local_68i * 37.0), 0.01f, DAT_05edd954, 0.0f, 0.0859375f, 0.82128906f, 0.12207031f, -1);
					}
					break;
			}
		}
		else
		{
			std::list<DAT_05edd970_1>::iterator local_94 = DAT_05edd970.begin();
			int local_98g = 0;
			for (; local_98g < 10; local_94++, local_98g++)
			{
				if (local_94 == DAT_05edd970.end())
					break;
				int WidthEntries = 0;
				int HeightEntries = 0;
				wchar_t *local_9c = (*local_94).field_0x0;
				GetTextSize(local_9c, WidthEntries, HeightEntries);
				DrawStringW((int)(local_6c * 129.0 + (local_6c * 100.0 - WidthEntries * 1.4f) - local_6c * 90.0), (int)((local_98g * 17 + 224.0f + local_98g * 20) * local_68i - 9.0 + 10.3f - 4.0), local_9c, -1, 1.2f);
				DrawStringW((int)(local_6c * 225.0 - 13.0), (int)((local_98g * 17 + 224.0f + local_98g * 20) * local_68i - 9.0 + 10.3f - 4.0), (*local_94).field_0x0 + 5, -1, 1.2f);
				if (DAT_05edd941 == 15 || DAT_05edd941 == 17 || DAT_05edd941 == 16 || DAT_05edd941 == 14 || DAT_05edd941 == 12 || DAT_05edd941 == 11)
				{
					int WidthData = 0;
					int HeightData = 0;
					wchar_t *local_a8g = (*local_94).field_0x2a;
					GetTextSize(local_a8g, WidthData, HeightData);
					DrawStringW((int)(local_6c * 580.0 - local_6c * 20.0 + (local_6c * 120.0 - WidthData * 1.4f)), (int)((local_98g * 17 + 224.0f + local_98g * 20) * local_68i - 9.0 + 10.3f - 4.0), local_a8g, -1, 1.2f);
				}
				else
					DrawStringW((int)(local_6c * 580.0 - local_6c * 20.0), (int)((local_98g * 17 + 224.0f + local_98g * 20) * local_68i - 9.0 + 10.3f - 4.0), (*local_94).field_0x2a, -1, 1.2f);
				if (DAT_05edd941 != 13 && DAT_05edd941 != 15 && DAT_05edd941 != 17 && DAT_05edd941 != 16 && DAT_05edd941 != 14)
				{
					wchar_t *local_b8 = (*local_94).field_0x4a;
					int WidthScore = 0;
					int HeightScore = 0;
					GetTextSize(local_b8, WidthScore, HeightScore);
					DrawStringW((int)(local_6c * 760.0 - local_6c * 10.0 + (local_6c * 120.0 - WidthScore * 1.4f) - local_6c * 20.0), (int)((local_98g * 17 + 224.0f + local_98g * 20) * local_68i - 9.0 + 10.3f - 4.0), local_b8, -1, 1.2f);
				}
			}
			DrawTexture((int)(local_6c * 42.0), (int)((DAT_05edd964 * 17 + DAT_05edd964 * 20 + 242) * local_68i - 9.0 - 4.0), (int)(local_6c * 838.0), (int)(local_68i * 34.0), 0.01f, DAT_05edd948, 0.0f, 0.68359375f, 0.818359375f, 0.71875f, -1);
		}
	}
	if (local_30h == 1 && LBChange != 0)
		FUN_005f5940(DAT_05edd942, LBChange, DAT_05edd941, (unsigned char)local_30h);
	if (local_30h == 2 && LBChange != 0)
		FUN_005f5940(DAT_05edd942, LBChange, DAT_05edd941, (unsigned char)local_30h);
}

// STUB: SADX 0x005fa060
void FUN_005fa060(void)
{
}

// FUNCTION: SADX 0x005fa160
struct task *SetAdvaTitleMenuTask_LB(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, title_menu_exec);
	DAT_05edd91c = local_8g;
	if (DAT_05edd91c)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, prmp);
		local_8g->exec = title_menu_exec;
		local_8g->disp = title_menu_disp;
	}
	DAT_05edd940 = 0;
	return local_8g;
}

// STUB: SADX 0x005fa1e0
static void title_menu_exec(struct task *tp)
{
}

// STUB: SADX 0x005fa3a0
void FUN_005fa3a0(struct DDlgType *param_1)
{
}

// FUNCTION: SADX 0x005fa460
void title_menu_sub_lb_exec(struct TitleMenuWk *wkp)
{
	signed char local_5kt;
	signed char local_ci[3];
	signed char cs[5];
	float local_20 = DAT_01c6e428 / 920.0;
	float local_1c = DAT_01c6e42c / 690.0;

	local_5kt = 0;
	cs[local_5kt] = -1;
	switch (wkp->SubMode)
	{
		case 0:
			AdvaOpenDialogQuick((enum DiaTypeEnum)0x1c, (signed char)wkp->SelMenu, cs);
			wkp->SubMode = (enum TitleMenuSbMdEnum)1;
			DAT_05edd940 = 0;
		case 1:
			___njSetTexture(&texlist_ava_lb_menu);
			ghSetPvrTexMaterial(0xffffffff);
			if (GetDialogStat() >= 0 && DAT_05b40a48 == 1)
			{
				wkp->SelMenu = (enum TitleMenuEnum)GetDialogStat();
				switch (wkp->SelMenu)
				{
					case 0:
						DAT_05edd940 = 1;
						DAT_05edd942 = 0;
						LBChange = 2;
						DAT_05edd941 = 0;
						DAT_05edd964 = 0;
						wkp->SubMode = (enum TitleMenuSbMdEnum)7;
						break;
					case 1:
						DAT_05edd940 = 1;
						DAT_05edd942 = 1;
						LBChange = 2;
						DAT_05edd941 = 0;
						DAT_05edd964 = 0;
						wkp->SubMode = (enum TitleMenuSbMdEnum)7;
						break;
					default:
						CmnAdvaModeProcedure(ADVA_MODE_TITLE_MENU_SUB);
						DAT_05ccca18.lastPlayer = 0;
						AvaExtractFile();
						DAT_05cd0f30 = DAT_05ccca18;
						wkp->SubMode = TITLEMENU_SMD_NWAIT;
						break;
				}
			}
			else
			{
				if (GetStatAdvaBGM() == 5)
				{
					if (GetDialogNoKeyTime() >= 0x1e0)
					{
						DAT_05ccca18.lastPlayer = 0;
						AvaExtractFile();
						DAT_05cd0f30 = DAT_05ccca18;
						wkp->SubMode = TITLEMENU_SMD_TO_DEMO;
					}
				}
				else
				{
					SetDialogNoKeyTime(0);
				}
			}
			break;
		case 2:
		{
			signed char local_21 = GetDialogStat();
			if (local_21 >= 0)
			{
				switch (local_21)
				{
					case 0:
						CharSelAdvaModeProcedure(ADVA_MODE_TRIALACT_SEL);
						DAT_05cd14e1 = 0;
						wkp->SubMode = TITLEMENU_SMD_NWAIT;
						break;
					case 1:
						CharSelAdvaModeProcedure(ADVA_MODE_MINIGAME_SEL);
						DAT_05cd14e1 = 1;
						wkp->SubMode = TITLEMENU_SMD_NWAIT;
						break;
					case 2:
						CmnAdvaModeProcedure(wkp->NextModeSub);
						wkp->SubMode = TITLEMENU_SMD_NWAIT;
						break;
					default:
						wkp->SubMode = TITLEMENU_SMD_TO_MAINMENU;
						break;
				}
			}
			else
			{
				if (GetStatAdvaBGM() == 5)
				{
					if (GetDialogNoKeyTime() >= 0x1e0)
					{
						wkp->SubMode = TITLEMENU_SMD_TO_DEMO;
					}
				}
				else
				{
					SetDialogNoKeyTime(0);
				}
			}
			break;
		}
		case 3:
			if (CloseDialog() != 0)
			{
				wkp->Cnt = 0;
				wkp->SubMode = TITLEMENU_SMD_TO_DEMO2;
			}
			break;
		case 4:
			if (wkp->Cnt++ >= 0x14)
			{
				*(int *)((char *)DAT_05cda18c->awp + 0x10) = 0x6b;
				CmnAdvaModeProcedure(ADVA_MODE_NONE);
				wkp->SubMode = TITLEMENU_SMD_NWAIT;
			}
			break;
		case 5:
			if (AvaGetPutiEnable() != 0)
			{
				AdvaOpenDialogCsrLet((enum DiaTypeEnum)3, (signed char)wkp->SelMenu, cs);
			}
			else
			{
				AdvaOpenDialogCsrLet((enum DiaTypeEnum)3, (signed char)wkp->SelMenu, cs);
			}
			wkp->SubMode = TITLEMENU_SMD_DECIDE;
			break;
		case 7:
		{
			int local_28;
			if (DAT_05edd92c != 1)
			{
				bool local_29 = false;
				if ((DAT_05b92e44 & 0x40) != 0 && !local_29)
				{
					DAT_05edd928 = 0;
					dsPlay_oneshot(1, 0, 0, 0);
					DAT_05edd964 = 0;
					DAT_05edd941--;
					DAT_05edd970.clear();
					DAT_05edd968 = 0;
					DAT_05edd96c = 0;
					DAT_05edd930 = 0;
					DAT_05edd934 = 0;
					DAT_05edd938 = 0;
					LbPage = 1;
					if (DAT_05edd941 >= 0xff)
					{
						DAT_05edd941 = 0x11;
					}
					if (LBChange == 2)
					{
						DAT_05edd958 = 0;
					}
					if (LBChange == 0)
					{
						DAT_05edd95c = 0;
						FUN_005f5940(DAT_05edd942, LBChange, DAT_05edd941, 2);
					}
					else if (LBChange != 0)
					{
						FUN_005f5940(DAT_05edd942, LBChange, DAT_05edd941, 2);
					}
					local_29 = true;
					DAT_05edd980 = DAT_05edd970.begin();
				}
				if ((DAT_05b92e44 & 0x80) != 0 && !local_29)
				{
					DAT_05edd928 = 0;
					dsPlay_oneshot(1, 0, 0, 0);
					DAT_05edd964 = 0;
					DAT_05edd930 = 0;
					DAT_05edd934 = 0;
					DAT_05edd938 = 0;
					DAT_05edd941++;
					LbPage = 1;
					DAT_05edd970.clear();
					DAT_05edd968 = 0;
					DAT_05edd96c = 0;
					if (DAT_05edd941 >= 0x12)
					{
						DAT_05edd941 = 0;
					}
					if (LBChange == 2)
					{
						DAT_05edd958 = 0;
					}
					if (LBChange == 0)
					{
						DAT_05edd95c = 0;
						FUN_005f5940(DAT_05edd942, LBChange, DAT_05edd941, 2);
					}
					else if (LBChange != 0)
					{
						FUN_005f5940(DAT_05edd942, LBChange, DAT_05edd941, 2);
					}
					local_29 = true;
					DAT_05edd980 = DAT_05edd970.begin();
				}
				if ((DAT_05b92e44 & 0x400) != 0 && !local_29)
				{
					dsPlay_oneshot(3, 0, 0, 0);
					DAT_05edd964 = 0;
					DAT_05edd930 = 0;
					DAT_05edd934 = 0;
					DAT_05edd938 = 0;
					LBChange++;
					LbPage = 1;
					DAT_05edd970.clear();
					DAT_05edd968 = 0;
					DAT_05edd96c = 0;
					if (LBChange > 2)
					{
						LBChange = 0;
					}
					else if (LBChange == 2)
					{
						DAT_05edd958 = 0;
					}
					if (LBChange == 0)
					{
						DAT_05edd95c = 0;
						FUN_005f5940(DAT_05edd942, LBChange, DAT_05edd941, 2);
					}
					else if (LBChange != 0)
					{
						FUN_005f5940(DAT_05edd942, LBChange, DAT_05edd941, 2);
					}
					local_29 = true;
					DAT_05edd980 = DAT_05edd970.begin();
				}
				if ((DAT_05b92e44 & 4) != 0 && !local_29)
				{
					local_29 = true;
				}
			}
			if (DAT_05edd940 == 2 && (DAT_05b92e44 & 2) != 0)
			{
				dsPlay_oneshot(3, 0, 0, 0);
				DAT_05edd940 = 3;
			}
			local_28 = FUN_005f4e60();
			if (local_28 == 0 || local_28 == 2)
			{
				wkp->SubMode = TITLEMENU_SMD_STAY;
				DAT_05edd940 = 0;
				DAT_05edd964 = 0;
				DAT_05edd930 = 0;
				LbPage = 1;
				DAT_05edd968 = 0;
				DAT_05edd96c = 0;
			}
			break;
		}
	}
}

// STUB: SADX 0x005fac40
static void title_menu_disp(struct task *tp)
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
