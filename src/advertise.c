#include "decls.h"
#include <math.h>
#include <new>
#include <windows.h>
#include "advertise.h"
void *FUN_0058a5d0(unsigned int param_1);
extern float ScreenRaitoY;
void late_DrawMap(void *arg);
void FUN_0057cd30();
long InitMap();
void FUN_0057cf20();
void late_SetFunc(void (*fnc)(void *), void *arg, float zprio, int flgs);
extern void FUN_00589a70(char *param_1, int param_2, int param_3);
extern void __fastcall FUN_00589c10(void *param_1, int param_2, char param_3);
void FUN_0041c2d0(void *param_1);
int dsPlay_oneshot(int tone, int id, int pri, int volofs);
int InitLBOn();
void DrawLBOn();
void DestroyLBOn();
void split2(void *param_1, void *param_2);
extern struct NJS_TEXLIST DAT_05cd2664;
void FUN_00588890(int param_1);
extern unsigned char DAT_05cd2786;

#pragma optimize("", off)
// STUB: SADX 0x00579ab0
void late_displayMission(struct task *tp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x00579e00
void InitDisplayStart()
{
}

// FUNCTION: SADX 0x0057a4e0
void displayMission(struct task *tp)
{
	___njFogDisable();
	late_SetFunc((void (*)(void *))late_displayMission, tp, 22047.998046875f, 1);
	___njFogEnable();
}

// FUNCTION: SADX 0x0057a510
void endDisplayMission(struct task *tp)
{
	late_ReleaseTexture(&DAT_05cd2664);
}

// STUB: SADX 0x0057a530
void InitDisplayResult()
{
}

// FUNCTION: SADX 0x0057a660
void InitDisplayGoal()
{
	pdVibMxStop(0);
}

// FUNCTION: SADX 0x0057a670
void DisplayPress(struct task *tp)
{
	late_SetFunc((void (*)(void *))late_DisplayPress, tp, 22047.998f, 1);
}

#pragma optimize("", off)
// STUB: SADX 0x0057a6a0
void late_DisplayPress(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x0057a860
void printPauseTexture(enum PAUSE_TEXTURE_ID id, struct NJS_POINT3 *pos, struct NJS_POINT2 *scl)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x0057a920
void printPause(float ofsy)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0057aa00
void FUN_0057aa00(enum PAUSE_TEXTURE_ID param_1, long param_2, long param_3, long param_4)
{
	printMenu2(param_1, 0xf0, param_2 + 0xf0, param_3);
}

#pragma optimize("", off)
// STUB: SADX 0x0057aa30
void printMenu2(enum PAUSE_TEXTURE_ID id, long pos_x, long pos_y, long flag)
{
}
#pragma optimize("", on)

// STUB: SADX 0x0057ae10
signed char PausePrev(signed char sel)
{
	return (signed char)0;
}

// STUB: SADX 0x0057cc20
int FUN_0057cc20()
{
	return (int)0;
}

// FUNCTION: SADX 0x0057cd00
void MapDispOn()
{
	if (DAT_05cd2786 == 0)
	{
		DAT_05cd2786 = 1;
	}
}

// FUNCTION: SADX 0x0057cd20
void FUN_0057cd20()
{
	DAT_05cd2786 = 0;
}

extern short DAT_00956b1c[13];
extern int DAT_0098fa18[17];
extern int DAT_0098fa5c[7];
extern struct DialogPrmType DAT_0098fa78;
extern unsigned int DAT_01c6e428;
extern unsigned int DAT_01c6e42c;
extern short DAT_01c6e868[13];
extern struct NJS_TEXLIST DAT_025ddb78;
extern unsigned int DAT_026054e8[4];
extern int DAT_02605538;
extern unsigned char DAT_0260553c;
extern unsigned char DAT_0260553d;
extern unsigned char DAT_0260553e;
extern unsigned char DAT_0260553f;
extern int DAT_02605a24;
extern unsigned char DAT_02606b18;
extern char* DAT_02606b1c[6];
extern char* DAT_02606b34[6];
extern char* DAT_02606b4c[6];
extern char* DAT_02606b64[5];
extern char* DAT_02606b78[5];
extern char* DAT_02606b8c[5];
extern char* DAT_02606ba0[5];
extern void* DAT_05ab39ac;
extern struct NJS_ARGB DAT_05ad9654;
extern int DAT_05b3e05c;
extern Magic::RenderCore::Texture* DAT_05b3e36c;
extern int DAT_05b3e388;
extern int DAT_05b3ebbc;
extern int DAT_05b42a90;
extern char DAT_05b42c1c;
extern int DAT_05b92e44;
extern unsigned int DAT_05cd26f0[4];
extern Magic::RenderCore::Texture* DAT_05cd2700;
extern Magic::RenderCore::Texture* DAT_05cd2704;
extern Magic::RenderCore::Texture* DAT_05cd2708;
extern Magic::RenderCore::Texture* DAT_05cd2710;
extern Magic::RenderCore::Texture* DAT_05cd2714;
extern Magic::RenderCore::Texture* DAT_05cd2718;
extern Magic::RenderCore::Texture* DAT_05cd271c;
extern Magic::RenderCore::Texture* DAT_05cd2720;
extern Magic::RenderCore::Texture* DAT_05cd2724;
extern Magic::RenderCore::Texture* DAT_05cd2728;
extern Magic::RenderCore::Texture* DAT_05cd272c;
extern Magic::RenderCore::Texture* DAT_05cd2730;
extern struct ButtonInfo* DAT_05cd273c;
extern Magic::RenderCore::Texture* DAT_05cd2740;
extern Magic::RenderCore::Texture* DAT_05cd2744;
extern Magic::RenderCore::Texture* DAT_05cd2748;
extern Magic::RenderCore::Texture* DAT_05cd274c;
extern Magic::RenderCore::Texture* DAT_05cd2750;
extern Magic::RenderCore::Texture* DAT_05cd2754;
extern Magic::RenderCore::Texture* DAT_05cd2758;
extern unsigned char DAT_05cd2767;
extern int DAT_05cd2768;
extern int DAT_05cd276c;
extern int DAT_05cd2770;
extern int DAT_05cd2774;
extern int DAT_05cd2780;
extern unsigned char DAT_05cd2784;
extern unsigned char DAT_05cd2785;
extern int DAT_05cd2790;
extern int DAT_05cd2794;
extern int DAT_05cd2798;
extern int DAT_05cd279c;
extern unsigned char DAT_05cd27e8;
extern int DAT_05cd27ec;
extern int DAT_05cd27f0;
// GLOBAL: SADX 0x05cd27f4
std::vector<std::wstring> DAT_05cd27f4;
// GLOBAL: SADX 0x05cd2820
std::list<LBOnData>::iterator DAT_05cd2820;
extern float DAT_05cd2824;
// GLOBAL: SADX 0x05cd2828
std::list<LBOnData> DAT_05cd2828;
extern float DAT_05cd2854;
extern int DAT_05cd2864;
extern int DAT_05cd2868;
extern struct task* DAT_05cd2878;
extern int DAT_05cd287c;
extern int DAT_05cd2880[13];
extern struct MSGC DAT_05cd28b8;
extern int DAT_05cd2900;
extern int DAT_05cd2904;
extern int DAT_05cd2908;

bool FUN_0040ae00();
int FUN_0040b010(const void*, const void*);
void FUN_004208c0(int, int, const wchar_t*, int, float, float);
void* FUN_00424960();
int FUN_0040b8a0();
void FUN_004b23e0(void*, void*, int, const char*, int);
void FUN_004f3470();
void FUN_00579960(struct MSGC*, int*, int*);
int FUN_00583720();
void DrawTexture(int, int, int, int, float, Magic::RenderCore::Texture*, float, float, float, float, int);
void RenderTexture(int, int, int, int, float, Magic::RenderCore::Texture*, float, float, float, float, int);

// STUB: SADX 0x0057cd30
void FUN_0057cd30()
{
}

// STUB: SADX 0x0057cd40
int FUN_0057cd40()
{
	return (int)0;
}

// STUB: SADX 0x0057ce00
long InitMap()
{
	return (long)0;
}

// STUB: SADX 0x0057cf20
void FUN_0057cf20()
{
}

// STUB: SADX 0x0057d000
void late_DrawMap(void *arg)
{
}

#pragma optimize("", off)
// STUB: SADX 0x0057d220
int cameramodechange(int sw)
{
	return (int)0;
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0057d490
int padconfig(int sw)
{
	int local_22ci;
	void *local_230;
	NJS_POINT3 local_23cv;
	unsigned long local_240g;
	NJS_POINT2 local_248j;
	unsigned long local_24cp;
	char local_26cj[32];
	float local_270k;
	int local_274u;
	int local_2f8w[32];
	float local_2fcj;
	int local_300l;
	char local_320j[32];
	local_2fcj = (float)(DAT_01c6e428 / 920.0);
	local_270k = (float)(DAT_01c6e42c / 690.0);
	switch (sw)
	{
	case 0:
		if (DAT_05cd2908 == 0)
			break;
		switch (DAT_05cd2904)
		{
		case 0:
			___njColorBlendingMode(0, 8);
			___njColorBlendingMode(1, 6);
			SetMaterial(0.5f, 0.0f, 0.0f, 1.0f);
			local_23cv.x = 220.0f;
			local_23cv.y = 54.0f;
			local_248j.x = 12.5f;
			local_248j.y = 21.5f;
			printPauseTexture((PAUSE_TEXTURE_ID)8, &local_23cv, &local_248j);
			for (local_22ci = 0; local_22ci < 7; ++local_22ci)
				printMenu2((PAUSE_TEXTURE_ID)(local_22ci + 45), 236, (long)(local_22ci * 40.0 + 70.0), DAT_05cd2900 == local_22ci);
			printMenu2((PAUSE_TEXTURE_ID)(local_22ci + 46), 236, (long)(local_22ci * 40.0 + 70.0), DAT_05cd2900 == local_22ci);
			if (IsSOCAVAPress(0, 4) || IsSOCAVAPress(0, 8))
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3, 0, 0, 0);
				if (DAT_05cd2900 == 7)
					DAT_05cd2904 = 9;
				else
					DAT_05cd2904 = 1;
				DisplayTask();
				SpLoopOnlyDisplay();
				break;
			}
			else
			{
				if (IsSOCAVAPress(0, 2))
				{
					MSG_Close(&DAT_05cd28b8);
					FUN_004c1c20();
					dsPlay_oneshot(3, 0, 0, 0);
					DAT_05cd2908 = 0;
					DisplayTask();
					SpLoopOnlyDisplay();
					break;
				}
				else
					MSG_Disp(&DAT_05cd28b8);
			}
			if (DAT_05b92e44 & 0x20)
			{
				dsPlay_oneshot(1, 0, 0, 0);
				++DAT_05cd2900;
				if (DAT_05cd2900 + 45 > 52)
					DAT_05cd2900 = 0;
			}
			if (DAT_05b92e44 & 0x10)
			{
				dsPlay_oneshot(1, 0, 0, 0);
				--DAT_05cd2900;
				if (DAT_05cd2900 + 45 < 45)
					DAT_05cd2900 = 7;
			}
			DisplayTask();
			SpLoopOnlyDisplay();
			break;
		case 1:
			MSG_Open(&DAT_05cd28b8, 64, 220, 512, 56, 0xd0000020);
			DAT_05cd28b8.bc.argb.a = 0x80;
			MSG_Puts(&DAT_05cd28b8, DAT_02606ba0[DAT_05b3ebbc]);
			MSG_LoadTexture2(&DAT_05cd28b8);
			DAT_05cd2904 = 2;
			for (local_22ci = 0; local_22ci < 13; ++local_22ci)
				DAT_05cd2880[local_22ci] = DAT_01c6e868[local_22ci];
			DAT_05cd287c = -2;
		case 2:
			MSG_Disp(&DAT_05cd28b8);
			DisplayTask();
			SpLoopOnlyDisplay();
			if (KeyGetPress(41))
				break;
			local_230 = pdGetPeripheral(0);
			if (DAT_05cd287c == -2)
			{
				if (*(unsigned int *)((char *)local_230 + 8) != 0)
					break;
				else
					DAT_05cd287c = -1;
			}
			local_240g = 0;
			local_24cp = 0;
			if (local_240g == 0)
				local_240g = local_24cp;
			if (local_240g > 0)
			{
				DAT_05cd287c = local_240g - 1;
				DAT_05cd2904 = 3;
			}
			break;
		case 3:
			MSG_Cls(&DAT_05cd28b8);
			MSG_Puts(&DAT_05cd28b8, DAT_02606b8c[DAT_05b3ebbc]);
			MSG_LoadTexture(&DAT_05cd28b8);
		case 10:
			if (DAT_05b3ebbc == 0)
				texLoadTexturePvmFile("ava_dlg", &DAT_025ddb78);
			else
				texLoadTexturePvmFile("ava_dlg_e", &DAT_025ddb78);
			texLoadTexturePvmFile("adv_window", &texlist_adv_window);
			texLoadTexturePvmFile("ava_csr", &texlist_ava_csr);
			DAT_05cd2878 = SetDialogTask();
			OpenDialog(&DAT_0098fa78, 0);
			DAT_05b3e388 = 1;
			DAT_05cd2904 = 4;
		case 4:
			MSG_Disp(&DAT_05cd28b8);
			DialogExec();
			DisplayTask();
			SpLoopOnlyDisplay();
			switch (GetDialogStat())
			{
			case 0:
				DAT_05cd2904 = 5;
				break;
			case 1:
				DAT_05cd2904 = 6;
				break;
			}
			break;
		case 5:
    if (DAT_05cd2900 == 7) {
        for (local_22ci = 0; local_22ci < 13; ++local_22ci)
            DAT_05cd2880[local_22ci] = DAT_00956b1c[local_22ci];
    } else {
        for (local_22ci = 0; local_22ci < 13; ++local_22ci) {
            if (DAT_05cd2880[local_22ci] == DAT_05cd287c)
                DAT_05cd2880[local_22ci] = -1;
        }
        DAT_05cd2880[DAT_0098fa5c[DAT_05cd2900]] = DAT_05cd287c;
    }
    for (local_22ci = 0; local_22ci < 13; ++local_22ci)
        DAT_01c6e868[local_22ci] = (short)DAT_05cd2880[local_22ci];
    for (local_22ci = 0; local_22ci < 32; ++local_22ci)
        local_2f8w[local_22ci] = -1;
    for (local_22ci = 0; local_22ci < 13; ++local_22ci) {
        if (DAT_05cd2880[local_22ci] >= 0) {
            for (local_300l = 0; local_300l < 17; ++local_300l) {
                if (DAT_0098fa18[local_300l] == local_22ci) {
                    local_2f8w[DAT_05cd2880[local_22ci]] = local_300l + 1;
                    break;
                }
            }
        }
    }
    {
        SOCIniFile local_354;
        local_354.FUN_0067edf0(".\\sonicDX.ini");
        local_354.FUN_0092b1b0("sonicDX", "padconfig", "pad_user");
        local_274u = 32;
        for (local_22ci = 31; local_22ci >= 0; --local_22ci) {
            if (local_2f8w[local_22ci] != -1)
                break;
            --local_274u;
        }
        wsprintfA(local_320j, "%d", local_274u);
        local_354.FUN_0092b1b0("pad_user", "buttons", local_320j);
        for (local_22ci = 0; local_22ci < local_274u; ++local_22ci) {
            wsprintfA(local_320j, "pad%d", local_22ci);
            wsprintfA(local_26cj, "%d", local_2f8w[local_22ci]);
            local_354.FUN_0092b1b0("pad_user", local_320j, local_26cj);
        }
    }
		case 6:
			MSG_Disp(&DAT_05cd28b8);
			DialogExec();
			DisplayTask();
			SpLoopOnlyDisplay();
			DAT_05cd2904 = 7;
			break;
		case 7:
			FreeDialogTask();
			MSG_Close(&DAT_05cd28b8);
			MSG_Disp(0);
			FUN_004c1c20();
			DAT_05b3e388 = 0;
			late_ReleaseTexture(&DAT_025ddb78);
			late_ReleaseTexture(&texlist_adv_window);
			late_ReleaseTexture(&texlist_ava_csr);
			DAT_05cd2904 = 0;
			MSG_Open(&DAT_05cd28b8, 64, 420, 512, 56, 0xd0000020);
			DAT_05cd28b8.bc.argb.a = 0x80;
			MSG_Puts(&DAT_05cd28b8, DAT_02606b78[DAT_05b3ebbc]);
			MSG_LoadTexture2(&DAT_05cd28b8);
			DisplayTask();
			SpLoopOnlyDisplay();
			break;
		case 8:
			MSG_Close(&DAT_05cd28b8);
			MSG_Disp(0);
			FUN_004c1c20();
			MSG_Open(&DAT_05cd28b8, 64, 420, 512, 56, 0xd0000020);
			DAT_05cd28b8.bc.argb.a = 0x80;
			MSG_Puts(&DAT_05cd28b8, DAT_02606b78[DAT_05b3ebbc]);
			MSG_LoadTexture2(&DAT_05cd28b8);
			DAT_05cd2904 = 0;
			DisplayTask();
			SpLoopOnlyDisplay();
			break;
		case 9:
			MSG_Open(&DAT_05cd28b8, 64, 220, 512, 56, 0xd0000020);
			DAT_05cd28b8.bc.argb.a = 0x80;
			DAT_05cd28b8.sx = 0;
			MSG_Puts(&DAT_05cd28b8, DAT_02606b64[DAT_05b3ebbc]);
			MSG_LoadTexture(&DAT_05cd28b8);
			DAT_05cd2904 = 10;
			DisplayTask();
			SpLoopOnlyDisplay();
			break;
		case 11:
			DAT_05cd2904 = 25;
			break;
		case 0xc:
{
	int local_358r;
	float local_35cr;
	bool local_35dh;
	bool local_35es;
	float local_364m;
	float local_368i;
	float local_36c;
	bool local_36du;
    if (DAT_05cd2767 != 1) {
        local_35es = false;
        local_35dh = false;
        local_35cr = FUN_00405f00()->FUN_00424b40()->GetValue(SOCController::AXIS_LX);
        local_364m = FUN_00405f00()->FUN_00424b40()->GetValue(SOCController::AXIS_LY);
        if (local_35cr != 0.0f) {
            if (local_35cr < -0.5 || local_35cr > 0.5) {
                local_368i = Magic::MATH::Math::AngleUniform<float>(atanf(local_364m / local_35cr));
                local_36c = DAT_0098fa14 * local_368i;
                if (local_36c <= 10.0 || local_36c >= 350.0) {
                    local_35es = true;
                } else if (local_36c >= 170.0 || local_36c <= 190.0) {
                    local_35dh = true;
                }
            }
        } else {
            if (local_35cr < -0.5) {
                local_35es = true;
            } else if (local_35cr > 0.5) {
                local_35dh = true;
            }
        }
        if (DAT_05cd2767 != 1) {
            local_36du = false;
            if ((DAT_05b92e44 & 0x40) && !local_36du) {
                dsPlay_oneshot(1, 0, 0, 0);
                DAT_05cd2790 = 0;
                --DAT_05cd2785;
                DAT_05cd2768 = 0;
                DAT_05cd276c = 0;
                DAT_05cd2770 = 0;
                DAT_02605538 = 1;
                if (DAT_05cd2785 >= 0xff)
                    DAT_05cd2785 = 17;
                if (DAT_0260553e == 2)
                    DAT_05cd2774 = 0;
                DAT_05cd2828.clear();
                DAT_05cd2794 = 0;
                DAT_05cd2798 = 0;
                if (DAT_0260553e == 0) {
                    DAT_05cd279c = 0;
                    FUN_005b5aa0(DAT_0260553f, DAT_0260553e, DAT_05cd2785, 2);
                } else if (DAT_0260553e != 0) {
                    FUN_005b5aa0(DAT_0260553f, DAT_0260553e, DAT_05cd2785, 2);
                }
                local_36du = true;
                DAT_05cd2820 = DAT_05cd2828.begin();
            }
            if ((DAT_05b92e44 & 0x80) && !local_36du) {
                dsPlay_oneshot(1, 0, 0, 0);
                DAT_05cd2790 = 0;
                ++DAT_05cd2785;
                DAT_05cd2768 = 0;
                DAT_05cd276c = 0;
                DAT_05cd2770 = 0;
                DAT_02605538 = 1;
                if (DAT_05cd2785 >= 18)
                    DAT_05cd2785 = 0;
                if (DAT_0260553e == 2)
                    DAT_05cd2774 = 0;
                DAT_05cd2828.clear();
                DAT_05cd2794 = 0;
                DAT_05cd2798 = 0;
                if (DAT_0260553e == 0) {
                    DAT_05cd279c = 0;
                    FUN_005b5aa0(DAT_0260553f, DAT_0260553e, DAT_05cd2785, 2);
                } else if (DAT_0260553e != 0) {
                    FUN_005b5aa0(DAT_0260553f, DAT_0260553e, DAT_05cd2785, 2);
                }
                local_36du = true;
                DAT_05cd2820 = DAT_05cd2828.begin();
            }
            if ((DAT_05b92e44 & 0x400) && !local_36du) {
                dsPlay_oneshot(3, 0, 0, 0);
                DAT_05cd2790 = 0;
                ++DAT_0260553e;
                DAT_05cd2768 = 0;
                DAT_05cd276c = 0;
                DAT_05cd2770 = 0;
                DAT_02605538 = 1;
                if (DAT_0260553e > 2) {
                    DAT_0260553e = 0;
                } else if (DAT_0260553e == 2) {
                    DAT_05cd2774 = 0;
                }
                DAT_05cd2828.clear();
                DAT_05cd2794 = 0;
                DAT_05cd2798 = 0;
                if (DAT_0260553e == 0) {
                    DAT_05cd279c = 0;
                    FUN_005b5aa0(DAT_0260553f, DAT_0260553e, DAT_05cd2785, 2);
                } else if (DAT_0260553e != 0) {
                    FUN_005b5aa0(DAT_0260553f, DAT_0260553e, DAT_05cd2785, 2);
                }
                local_36du = true;
                DAT_05cd2820 = DAT_05cd2828.begin();
            }
            if ((DAT_05b92e44 & 4) && !local_36du)
                local_36du = true;
        }
    }
    local_358r = FUN_00583720();
    if (local_358r == 0 || local_358r == 2) {
        DAT_05cd2784 = 0;
        DAT_05cd2790 = 0;
        DAT_05cd2768 = 0;
        DAT_02605538 = 1;
        DAT_05cd2794 = 0;
        DAT_05cd2798 = 0;
        DAT_05cd2904 = 11;
    }
    break;
}
		case 0xd:
    if (!FUN_0040ae00()) {
        SOCFileStream local_374;
        switch (DAT_05b42a90) {
        case 5: {
            if (local_374.ReadFile("system\\Unlock\\TrialGame2_it.dds")) {
                DAT_05cd2758 = new Magic::RenderCore::Texture;
                DAT_05cd2758->Load(local_374.FUN_00424960(), 1,
                    local_374.FUN_0040b8a0(), 0, 1, 0);
            }
            break;
        }
        case 4: {
            if (local_374.ReadFile("system\\Unlock\\TrialGame2_de.dds")) {
                DAT_05cd2758 = new Magic::RenderCore::Texture;
                DAT_05cd2758->Load(local_374.FUN_00424960(), 1,
                    local_374.FUN_0040b8a0(), 0, 1, 0);
            }
            break;
        }
        case 3: {
            if (local_374.ReadFile("system\\Unlock\\TrialGame2_es.dds")) {
                DAT_05cd2758 = new Magic::RenderCore::Texture;
                DAT_05cd2758->Load(local_374.FUN_00424960(), 1,
                    local_374.FUN_0040b8a0(), 0, 1, 0);
            }
            break;
        }
        case 2: {
            if (local_374.ReadFile("system\\Unlock\\TrialGame2_fr.dds")) {
                DAT_05cd2758 = new Magic::RenderCore::Texture;
                DAT_05cd2758->Load(local_374.FUN_00424960(), 1,
                    local_374.FUN_0040b8a0(), 0, 1, 0);
            }
            break;
        }
        case 0: {
            if (local_374.ReadFile("system\\Unlock\\TrialGame2_J.dds")) {
                DAT_05cd2758 = new Magic::RenderCore::Texture;
                DAT_05cd2758->Load(local_374.FUN_00424960(), 1,
                    local_374.FUN_0040b8a0(), 0, 1, 0);
            }
            break;
        }
        default: {
            if (local_374.ReadFile("system\\Unlock\\TrialGame2.dds")) {
                DAT_05cd2758 = new Magic::RenderCore::Texture;
                DAT_05cd2758->Load(local_374.FUN_00424960(), 1,
                    local_374.FUN_0040b8a0(), 0, 1, 0);
            }
            break;
        }
        }
        DAT_05cd2904 = 0x18;
        DAT_05cd2900 = 0;
    } else {
        DAT_05cd2908 = 0;
    }
    DisplayTask();
    SpLoopOnlyDisplay();
    break;

		case 0xe:
			___njColorBlendingMode(0,8);
			___njColorBlendingMode(1,6);
			SetMaterial(0.5f,0.0f,0.0f,1.0f);
			local_23cv.x = 208.0f;
			local_23cv.y = 85.0f;
			local_248j.x = 14.0f;
			local_248j.y = 16.0f;
			printPauseTexture((PAUSE_TEXTURE_ID)8,&local_23cv,&local_248j);
			SetMaterial(1.0f,1.0f,1.0f,1.0f);
			printPause(0.0f);
			local_22ci = 0;
			printMenu2((PAUSE_TEXTURE_ID)((GetFreeCamera() != 0) + 11),0xf0,0x62,DAT_05cd2900 == 0);
			for (local_22ci = 1; local_22ci < 4; local_22ci = local_22ci + 1)
			{
				printMenu2((PAUSE_TEXTURE_ID)(local_22ci + 0x15),0xf0,(long)(50.0 * local_22ci + 70.0 - 7.0 + 42.0 - 7.0),DAT_05cd2900 == local_22ci);
			}
			printMenu2((PAUSE_TEXTURE_ID)0x15,0xf0,(long)(50.0 * local_22ci + 70.0 - 7.0 + 42.0 - 7.0),DAT_05cd2900 == local_22ci);
			DrawButtonACBB();
			switch(DAT_05cd2900)
			{
			case 0:
			DrawTexture(0, (int)(local_270k * 500.0), (int)(local_2fcj * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2740, 0.0f, 0.109375f, 0.8984375f, 0.16015625f, -1);
				break;
			case 1:
			DrawTexture(0, (int)(local_270k * 500.0), (int)(local_270k * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2744, 0.0f, 0.0546875f, 0.8984375f, 0.10546875f, -1);
				break;
			case 2:
			DrawTexture(0, (int)(local_270k * 500.0), (int)(local_270k * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2744, 0.0f, 0.109375f, 0.8984375f, 0.16015625f, -1);
				break;
			case 3:
			DrawTexture(0, (int)(local_270k * 500.0), (int)(local_270k * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2744, 0.0f, 0.1640625f, 0.8984375f, 0.21484375f, -1);
				break;
			default:
			DrawTexture(0, (int)(local_270k * 500.0), (int)(local_270k * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2744, 0.0f, 0.21875f, 0.8984375f, 0.26953125f, -1);
			}
			if (IsSOCAVAPress(0,4) != 0 || IsSOCAVAPress(0,8) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3,0,0,0);
				switch(DAT_05cd2900)
				{
				case 0:
					cameramodechange(1);
					DAT_05cd2904 = 0x17;
					break;
				case 1:
					
    {
        SOCFileStream local_37c;
            if (local_37c.ReadFile(DAT_02606b4c[DAT_05b42a90])) {
            void* local_384 = local_37c.FUN_00424960();
            int local_380 = local_37c.FUN_0040b8a0();
            DAT_05cd2700 = new Magic::RenderCore::Texture;
            FUN_004b23e0(&DAT_05cd2700, local_384, local_380,
                DAT_02606b4c[DAT_05b42a90], DAT_05b42a90);
            DAT_05cd2700->Load(local_384, 1, local_380, 0, 1, 0);
        }
            if (local_37c.ReadFile(DAT_02606b34[DAT_05b42a90])) {
            void* local_38cj = local_37c.FUN_00424960();
            int local_388g = local_37c.FUN_0040b8a0();
            DAT_05cd2704 = new Magic::RenderCore::Texture;
            FUN_004b23e0(&DAT_05cd2704, local_38cj, local_388g,
                DAT_02606b34[DAT_05b42a90], DAT_05b42a90);
            DAT_05cd2704->Load(local_38cj, 1, local_388g, 0, 1, 0);
        }
            if (local_37c.ReadFile(DAT_02606b1c[DAT_05b42a90])) {
            void* local_394w = local_37c.FUN_00424960();
            int local_390l = local_37c.FUN_0040b8a0();
            DAT_05cd2708 = new Magic::RenderCore::Texture;
            FUN_004b23e0(&DAT_05cd2708, local_394w, local_390l,
                DAT_02606b1c[DAT_05b42a90], DAT_05b42a90);
            DAT_05cd2708->Load(local_394w, 1, local_390l, 0, 1, 0);
        }
        DAT_05cd2904 = 0x10;
        DAT_05cd2900 = 0;
    }
    break;
				case 2:
					DAT_05cd2904 = 0x11;
					DAT_05cd2900 = 0;
					break;
				case 3:
					InitStaff2();
					DAT_05cd2904 = 0x12;
					DAT_05cd2900 = 0;
					break;
				default:
					MSG_Close(&DAT_05cd28b8);
					FUN_004c1c20();
					DisplayTask();
					SpLoopOnlyDisplay();
					DAT_05cd2908 = 0;
					return 1;
				}
			
			}
			else
			{
				if (IsSOCAVAPress(0,2) != 0)
				{
					dsPlay_oneshot(3,0,0,0);
					DAT_05cd2908 = 0;
					DAT_05cd2900 = 0;
					DisplayTask();
					SpLoopOnlyDisplay();
					break;
				}
				else
				{
				if ((DAT_05b92e44 & 0x20) != 0)
				{
					dsPlay_oneshot(1,0,0,0);
					DAT_05cd2900 = DAT_05cd2900 + 1;
					if (0x1a < DAT_05cd2900 + 0x16)
					{
						DAT_05cd2900 = 0;
					}
				}
			
				}

			}

			if ((DAT_05b92e44 & 0x10) != 0)
			{
				dsPlay_oneshot(1,0,0,0);
				DAT_05cd2900 = DAT_05cd2900 - 1;
				if (DAT_05cd2900 + 0x16 < 0x16)
				{
					DAT_05cd2900 = 4;
				}
			}
			DisplayTask();
			SpLoopOnlyDisplay();
			break;
		case 0xf:
			___njColorBlendingMode(0,8);
			___njColorBlendingMode(1,6);
			SetMaterial(0.5f,0.0f,0.0f,1.0f);
			local_23cv.x = 208.0f;
			local_23cv.y = 85.0f;
			local_248j.x = 14.0f;
			local_248j.y = 18.9f;
			printPauseTexture((PAUSE_TEXTURE_ID)8,&local_23cv,&local_248j);
			SetMaterial(1.0f,1.0f,1.0f,1.0f);
			printPause(21.0f);
			for (local_22ci = 0; local_22ci < 6; local_22ci = local_22ci + 1)
			{
				printMenu2((PAUSE_TEXTURE_ID)(local_22ci + 0x19),0xf0,(long)(40.0 * local_22ci + 70.0 - 7.0 + 42.0 - 7.0),DAT_05cd2900 == local_22ci);
			}
			printMenu2((PAUSE_TEXTURE_ID)0x15,0xf0,(long)(40.0 * local_22ci + 70.0 - 7.0 + 42.0 - 7.0),DAT_05cd2900 == local_22ci);
			DrawButtonACBB();
			switch(DAT_05cd2900)
			{
			case 0:
			DrawTexture(0, 0x182, (int)(local_2fcj * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2740, 0.0f, 0.65625f, 0.8984375f, 0.70703125f, -1);
				break;
			case 1:
			DrawTexture(0, 0x182, (int)(local_270k * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2740, 0.0f, 0.7109375f, 0.8984375f, 0.76171875f, -1);
				break;
			case 2:
			DrawTexture(0, 0x182, (int)(local_2fcj * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2740, 0.0f, 0.765625f, 0.8984375f, 0.81640625f, -1);
				break;
			case 3:
			DrawTexture(0, 0x182, (int)(local_270k * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2740, 0.0f, 0.8203125f, 0.8984375f, 0.87109375f, -1);
				break;
			case 4:
			DrawTexture(0, 0x182, (int)(local_270k * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2740, 0.0f, 0.875f, 0.8984375f, 0.92578125f, -1);
				break;
			case 5:
			DrawTexture(0, 0x182, (int)(local_270k * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2740, 0.0f, 0.9296875f, 0.8984375f, 0.98046875f, -1);
				break;
			default:
			DrawTexture(0, 0x182, (int)(local_270k * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2744, 0.0f, 0.21875f, 0.8984375f, 0.26953125f, -1);
			}
			if (IsSOCAVAPress(0,4) != 0 || IsSOCAVAPress(0,8) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3,0,0,0);
				switch(DAT_05cd2900)
				{
				case 0:
					DAT_05cd2900 = 0;
					DAT_05cd27e8 = 1;
					DAT_05cd27ec = DAT_05b3e05c;
					DAT_05b3e05c = 0x2b;
					DAT_05cd27f0 = 0;
					setBtpToBtp_Pre();
					FUN_004f3470();
					((SOCRender*)DAT_05ab39ac)->FUN_00419cf0(3);
					break;
				case 1:
					DAT_05cd2900 = 1;
					DAT_05cd27e8 = 1;
					DAT_05cd27ec = DAT_05b3e05c;
					DAT_05b3e05c = 0x2b;
					DAT_05cd27f0 = 1;
					setBtpToBtp_Pre();
					FUN_004f3470();
					((SOCRender*)DAT_05ab39ac)->FUN_00419cf0(3);
					break;
				case 2:
					DAT_05cd2900 = 2;
					DAT_05cd27e8 = 1;
					DAT_05cd27ec = DAT_05b3e05c;
					DAT_05b3e05c = 0x2b;
					DAT_05cd27f0 = 2;
					setBtpToBtp_Pre();
					FUN_004f3470();
					((SOCRender*)DAT_05ab39ac)->FUN_00419cf0(3);
					break;
				case 3:
					DAT_05cd2900 = 3;
					DAT_05cd27e8 = 1;
					DAT_05cd27ec = DAT_05b3e05c;
					DAT_05b3e05c = 0x2b;
					DAT_05cd27f0 = 3;
					setBtpToBtp_Pre();
					FUN_004f3470();
					((SOCRender*)DAT_05ab39ac)->FUN_00419cf0(3);
					break;
				case 4:
					DAT_05cd2900 = 4;
					DAT_05cd27e8 = 1;
					DAT_05cd27ec = DAT_05b3e05c;
					DAT_05b3e05c = 0x2b;
					DAT_05cd27f0 = 4;
					setBtpToBtp_Pre();
					FUN_004f3470();
					((SOCRender*)DAT_05ab39ac)->FUN_00419cf0(3);
					break;
				case 5:
					DAT_05cd2900 = 5;
					DAT_05cd27e8 = 1;
					DAT_05cd27ec = DAT_05b3e05c;
					DAT_05b3e05c = 0x2b;
					DAT_05cd27f0 = 5;
					setBtpToBtp_Pre();
					FUN_004f3470();
					((SOCRender*)DAT_05ab39ac)->FUN_00419cf0(3);
					break;
				default:
					MSG_Close(&DAT_05cd28b8);
					FUN_004c1c20();
					DAT_05cd2904 = 0xe;
					DAT_05cd2900 = 1;
				}
				DisplayTask();
				SpLoopOnlyDisplay();
				break;
			}
			else if (IsSOCAVAPress(0,2) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3,0,0,0);
				DAT_05cd2904 = 0xe;
				DAT_05cd2900 = 1;
				DisplayTask();
				SpLoopOnlyDisplay();
				break;
			}
			else
			{
				if ((DAT_05b92e44 & 0x20) != 0)
				{
					dsPlay_oneshot(1,0,0,0);
					DAT_05cd2900 = DAT_05cd2900 + 1;
					if (0x1f < DAT_05cd2900 + 0x19)
					{
						DAT_05cd2900 = 0;
					}
				}
			}
			if ((DAT_05b92e44 & 0x10) != 0)
			{
				dsPlay_oneshot(1,0,0,0);
				DAT_05cd2900 = DAT_05cd2900 - 1;
				if (DAT_05cd2900 + 0x19 < 0x19)
				{
					DAT_05cd2900 = 6;
				}
			}
			DisplayTask();
			SpLoopOnlyDisplay();
			break;
		case 0x10:
{
	Magic::RenderCore::Texture *local_39cj;
	float local_3a0m;
	float local_3a4x;
			local_39cj = DAT_05cd2700;
			if (FUN_0040b010(&DAT_05ad9654,&DAT_05cd26f0) != 0)
			{
				local_39cj = DAT_05cd2708;
			}
			else if (FUN_0040b010(&DAT_05ad9654,&DAT_026054e8) != 0)
			{
				local_39cj = DAT_05cd2700;
			}
			else
			{
				local_39cj = DAT_05cd2704;
			}
			if (local_39cj != 0)
			{
				local_3a0m = (float)((double)DAT_01c6e428 / (double)640.0);
				local_3a4x = (float)((double)DAT_01c6e42c / (double)480.0);
			DrawTexture(0, 0, (int)(local_3a0m * 640.0), (int)(local_3a4x * 480.0), 0.01f, local_39cj, 0.0f, 0.0f, 0.8984375f, 0.673828125f, -1);
			DrawTexture((int)(local_3a0m * 360.0), (int)((460.0 - DAT_05cd273c[2].Height) * local_3a4x), (int)(DAT_05cd273c[2].Windth * local_3a0m), (int)(DAT_05cd273c[2].Height * local_3a4x), 0.01f, DAT_05b3e36c, DAT_05cd273c[2].PosX / 512.0, DAT_05cd273c[2].PosY / 512.0, (DAT_05cd273c[2].PosX + DAT_05cd273c[2].Windth) / 512.0, (DAT_05cd273c[2].PosY + DAT_05cd273c[2].Height) / 512.0, -1);
			DrawTexture((int)((340.0 - DAT_05cd273c[13].Windth) * local_3a0m), (int)((460.0 - DAT_05cd273c[2].Height) * local_3a4x), (int)(DAT_05cd273c[13].Windth * local_3a0m), (int)(DAT_05cd273c[13].Height * local_3a4x), 0.01f, DAT_05b3e36c, DAT_05cd273c[13].PosX / 512.0, DAT_05cd273c[13].PosY / 512.0, (DAT_05cd273c[13].PosX + DAT_05cd273c[13].Windth) / 512.0, (DAT_05cd273c[13].PosY + DAT_05cd273c[13].Height) / 512.0, -1);
			}
			if (IsSOCAVAPress(0,2) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3,0,0,0);
				DAT_05cd2904 = 0xe;
				DAT_05cd2900 = 1;
				DisplayTask();
				SpLoopOnlyDisplay();
				FUN_0041c2d0(DAT_05cd2700);
				FUN_0041c2d0(DAT_05cd2704);
				FUN_0041c2d0(DAT_05cd2708);
				FUN_004b5e70((int)&DAT_05cd2700);
				FUN_004b5e70((int)&DAT_05cd2704);
				FUN_004b5e70((int)&DAT_05cd2708);
				delete DAT_05cd2700;
				DAT_05cd2700 = 0;
				delete DAT_05cd2704;
				DAT_05cd2704 = 0;
				delete DAT_05cd2708;
				DAT_05cd2708 = 0;
				break;
			}
			break;
		}
		case 0x11:
			___njColorBlendingMode(0,8);
			___njColorBlendingMode(1,6);
			SetMaterial(0.5f,0.0f,0.0f,1.0f);
			local_23cv.x = 208.0f;
			local_23cv.y = 85.0f;
			local_248j.x = 14.0f;
			local_248j.y = 9.0f;
			printPauseTexture((PAUSE_TEXTURE_ID)8,&local_23cv,&local_248j);
			SetMaterial(1.0f,1.0f,1.0f,1.0f);
			printPause(0.0f);
			for (local_22ci = 0; local_22ci < 2; local_22ci = local_22ci + 1)
			{
				printMenu2((PAUSE_TEXTURE_ID)(local_22ci + 0x1f),0xf0,(long)(40.0 * local_22ci + 70.0 - 7.0 + 42.0 - 7.0),DAT_05cd2900 == local_22ci);
			}
			printMenu2((PAUSE_TEXTURE_ID)0x15,0xf0,(long)(40.0 * local_22ci + 70.0 - 7.0 + 42.0 - 7.0),DAT_05cd2900 == local_22ci);
			DrawButtonACBB();
			switch (DAT_05cd2900)
			{
			case 0:
				DrawTexture(0, (int)(local_270k * 393.0), (int)(local_2fcj * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2740, 0.0f, 0.546875f, 0.8984375f, 0.59765625f, -1);
				break;
			case 1:
				DrawTexture(0, (int)(local_270k * 393.0), (int)(local_270k * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2740, 0.0f, 0.6015625f, 0.8984375f, 0.65234375f, -1);
				break;
			default:
				DrawTexture(0, (int)(local_270k * 393.0), (int)(local_270k * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2744, 0.0f, 0.21875f, 0.8984375f, 0.26953125f, -1);
				break;
			}
			if (IsSOCAVAPress(0,4) != 0 || IsSOCAVAPress(0,8) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3,0,0,0);
				switch (DAT_05cd2900)
				{
				case 0:
					if (gu8Vibration != '\0')
					{
						DAT_05cd2900 = 0;
					}
					else
					{
						DAT_05cd2900 = 1;
					}
					DAT_05cd2904 = 0x13;
					break;
				case 1:
					if (AvaGetOnseiSettei() == 0)
					{
						DAT_05cd2900 = 0;
					}
					else
					{
						DAT_05cd2900 = 1;
					}
					DAT_05cd2904 = 0x15;
					break;
				default:
					MSG_Close(&DAT_05cd28b8);
					FUN_004c1c20();
					DAT_05cd2904 = 0xe;
					DAT_05cd2900 = 3;
					DisplayTask();
					SpLoopOnlyDisplay();
					break;
				}
				DisplayTask();
				SpLoopOnlyDisplay();
				break;
			}
			else if (IsSOCAVAPress(0,2) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3,0,0,0);
				DAT_05cd2904 = 0xe;
				DAT_05cd2900 = 2;
				DisplayTask();
				SpLoopOnlyDisplay();
				break;
			}
			else
			{
				if ((DAT_05b92e44 & 0x20) != 0)
				{
					dsPlay_oneshot(1,0,0,0);
					DAT_05cd2900 = DAT_05cd2900 + 1;
					if (0x21 < DAT_05cd2900 + 0x1f)
					{
						DAT_05cd2900 = 0;
					}
				}
			}
			if ((DAT_05b92e44 & 0x10) != 0)
			{
				dsPlay_oneshot(1,0,0,0);
				DAT_05cd2900 = DAT_05cd2900 - 1;
				if (DAT_05cd2900 + 0x1f < 0x1f)
				{
					DAT_05cd2900 = 2;
				}
			}
			DisplayTask();
			SpLoopOnlyDisplay();
			break;
		case 0x12:
{

	int local_3a8g;
	float local_3acq;
	float local_3b0o;
	unsigned int local_3b4x;
	const wchar_t *local_3b8n;
	int local_3bcr;
	int local_3c0x;
	float local_3c4;
	float local_3c8o;
			local_3b0o = (float)((double)DAT_01c6e428 / (double)920.0);
			local_3acq = (float)((double)DAT_01c6e42c / (double)690.0);
			RenderTexture(0, 0, (int)((local_3b0o * 920.0) + 1.0f), (int)(local_3acq * 690.0), 0.02f, DAT_05cd274c, 0.0f, 0.0f, 0.89453125f, 0.6728515625f, -1);
			local_3a8g = (int)((DAT_05cd27f4.size() * 52) * (double)local_3acq);
			if (DAT_05cd2824 + 640.0 > -local_3a8g)
			{
				for (local_3b4x = 0; local_3b4x < DAT_05cd27f4.size(); local_3b4x = local_3b4x + 1)
				{
					local_3b8n = (const wchar_t *)DAT_05cd27f4[local_3b4x].c_str();
					local_3bcr = 0;
					local_3c0x = 0;
					if (*local_3b8n == 0x2a)
					{
						GetTextSize(local_3b8n + 1,local_3bcr,local_3c0x);
					}
					else
					{
						GetTextSize(local_3b8n,local_3bcr,local_3c0x);
					}
					local_3c8o = FUN_00582ad0((float)((int)(local_3b4x - 1) * 32.0 + 20.0) * ScreenRaitoY + DAT_05cd2824);
					local_3c4 = FUN_00582ad0((float)((DAT_01c6e428 - local_3bcr) / 2.0));
					if (*local_3b8n == 0)
					{
						DAT_02606b18 = '\0';
						continue;
					}
					else if (DAT_02606b18 == '\0' && local_3b4x != 0)
					{
						if (local_3c8o + 19.0 < 0.0)
						{
							DAT_02606b18 = '\x01';
							continue;
						}
						if (*local_3b8n == 0x2a)
						{
							if (local_3c8o > 0.0 && (double)DAT_01c6e42c > local_3c8o)
							{
								FUN_004208c0((int)local_3c4,(int)local_3c8o,local_3b8n + 1,0xffffff80,1.0f,0.02f);
							}
						}
						else if (local_3c8o > 0.0 && (double)DAT_01c6e42c > local_3c8o)
						{
							FUN_004208c0((int)local_3c4,(int)local_3c8o,local_3b8n,0xffffffff,1.0f,0.02f);
						}
						DAT_02606b18 = '\x01';
					}
					else
					{
						if (local_3c8o + 19.0 < 0.0)
						{
							DAT_02606b18 = '\x01';
							continue;
						}
						if (*local_3b8n == 0x2a)
						{
							if (local_3c8o > 0.0 && (double)DAT_01c6e42c > local_3c8o)
							{
								FUN_004208c0((int)local_3c4,(int)local_3c8o,local_3b8n + 1,0xffffff80,1.0f,0.02f);
							}
						}
						else if (local_3c8o > 0.0 && (double)DAT_01c6e42c > local_3c8o)
						{
							FUN_004208c0((int)local_3c4,(int)local_3c8o,local_3b8n,0xffffffff,1.0f,0.02f);
						}
						DAT_02606b18 = '\x01';
					}
				}
			}
			if (DAT_05cd2824 + 640.0 < -local_3a8g)
			{
				DrawTexture((int)(((double)DAT_01c6e428 - local_3b0o * 415.0) / 2.0), (int)DAT_05cd2854, (int)(local_3b0o * 415.0), (int)(local_3acq * 270.0), 0.02f, DAT_05cd2750, 0.0f, 0.0f, 0.810546875f, 0.52734375f, DAT_02605a24);
				if (DAT_0260553c != '\0')
				{
					if (((double)DAT_01c6e42c - local_3acq * 270.0) / 2.0 < DAT_05cd2854)
					{
						DAT_05cd2854 = DAT_05cd2854 - 2.0;
					}
					if (((double)DAT_01c6e42c - local_3acq * 270.0) / 2.0 > DAT_05cd2854)
					{
						DAT_05cd2854 = ((double)DAT_01c6e42c - local_3acq * 270.0) / 2.0;
					}
				}
				if (((double)DAT_01c6e42c - local_3acq * 270.0) / 2.0 == DAT_05cd2854)
				{
					DAT_0260553c = '\0';
					// GLOBAL: SADX 0x05cd2874
					// $S1
					// GLOBAL: SADX 0x05cd2870
					static int DAT_05cd2870 = FUN_0041a800()->FUN_004caf80();
					// GLOBAL: SADX 0x05cd286c
					static int DAT_05cd286c = FUN_0041a800()->FUN_004caf80();
					if (DAT_0260553d != '\0')
					{
						DAT_05cd2870 = FUN_0041a800()->FUN_004caf80();
						DAT_0260553d = '\0';
						DAT_05cd286c = FUN_0041a800()->FUN_004caf80();
					}
					if (DAT_05cd2870 != 0)
					{
						DAT_05cd2868 = FUN_0041a800()->FUN_004caf80() - DAT_05cd2870;
						if (DAT_05cd2868 >= 5000)
						{
							FUN_00579960(&DAT_05cd28b8,&DAT_05cd2904,&DAT_05cd2900);
							break;
						}
						if (DAT_05cd2868 >= 3000)
						{
							DrawTexture(0, 0, (int)(local_3b0o * 960.0), (int)(local_3acq * 690.0), 0.0f, 0, 0.0f, 0.0f, 1.0f, 1.0f, DAT_05cd2780);
							if (DAT_05cd286c != 0)
							{
								if (FUN_0041a800()->FUN_004caf80() - DAT_05cd286c >= 13)
								{
									if (DAT_02605a24 != 0xffffff)
									{
										DAT_02605a24 = DAT_02605a24 - 0x2000000;
									}
									if (DAT_05cd2780 != -0x1000000)
									{
										DAT_05cd2780 = DAT_05cd2780 + 0x2000000;
									}
									if (DAT_05cd2780 == 0)
									{
										DAT_05cd2780 = -0x1000000;
									}
									if (DAT_02605a24 == -1)
									{
										DAT_02605a24 = 0xffffff;
									}
									DAT_05cd286c = FUN_0041a800()->FUN_004caf80();
								}
							}
						}
					}
				}
			}
			DAT_05cd2824 = FUN_00582ad0((float)(DAT_05cd2824 - 8.0));
			switch(DAT_05b42a90)
			{
			case 5:
			DrawTexture(0, (int)(local_3acq * 629.0), (int)(local_3b0o * 920.0), (int)(local_3acq * 64.0), 0.01f, DAT_05cd2754, 0.0f, 0.373046875f, 0.8984375f, 0.498046875f, -1);
				break;
			case 4:
			DrawTexture(0, (int)(local_3acq * 629.0), (int)(local_3b0o * 920.0), (int)(local_3acq * 64.0), 0.01f, DAT_05cd2754, 0.0f, 0.5f, 0.8984375f, 0.625f, -1);
				break;
			case 3:
			DrawTexture(0, (int)(local_3acq * 629.0), (int)(local_3b0o * 920.0), (int)(local_3acq * 64.0), 0.01f, DAT_05cd2754, 0.0f, 0.625f, 0.8984375f, 0.75f, -1);
				break;
			case 2:
			DrawTexture(0, (int)(local_3acq * 629.0), (int)(local_3b0o * 920.0), (int)(local_3acq * 64.0), 0.01f, DAT_05cd2754, 0.0f, 0.25f, 0.8984375f, 0.375f, -1);
				break;
			case 0:
			DrawTexture(0, (int)(local_3acq * 629.0), (int)(local_3b0o * 920.0), (int)(local_3acq * 65.0), 0.01f, DAT_05cd2754, 0.0f, 0.125f, 0.8984375f, 0.251953125f, -1);
				break;
			default:
			DrawTexture(0, (int)(local_3acq * 629.0), (int)(local_3b0o * 920.0), (int)(local_3acq * 64.0), 0.01f, DAT_05cd2754, 0.0f, 0.0f, 0.8984375f, 0.125f, -1);
				break;
}
			if (IsSOCAVAPress(0,2) != 0)
			{
				FUN_00579960(&DAT_05cd28b8,&DAT_05cd2904,&DAT_05cd2900);
				break;
			}
			break;
		}
		case 0x13:
{
			___njColorBlendingMode(0,8);
			___njColorBlendingMode(1,6);
			local_23cv.x = 112.0f;
			local_23cv.y = 224.0f;
			local_248j.x = 26.0f;
			local_248j.y = 4.0f;
			SetMaterial(0.5f,0.0f,0.0f,1.0f);
			printPauseTexture((PAUSE_TEXTURE_ID)8,&local_23cv,&local_248j);
			SetMaterial(1.0f,1.0f,1.0f,1.0f);
			for (local_22ci = 0; local_22ci < 2; local_22ci = local_22ci + 1)
			{
				switch (local_22ci)
				{
				case 0:
					printMenu2((PAUSE_TEXTURE_ID)0x22,0x90,0xf0,DAT_05cd2900 == local_22ci);
					break;
				case 1:
					printMenu2((PAUSE_TEXTURE_ID)0x23,0x150,0xf0,DAT_05cd2900 == local_22ci);
					break;
				}
			}
			ResetMaterial();
			DrawButtonACBB();
			if (IsSOCAVAPress(0,4) != 0 || IsSOCAVAPress(0,8) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				switch (DAT_05cd2900)
				{
				case 0:
					gu8Vibration = '\x01';
					FUN_00405f00()->FUN_00424b40()->Vib(30000,30000,500.0);
					DAT_05cd2904 = 0x11;
					DAT_05cd2900 = 0;
					dsPlay_oneshot(3,0,0,0);
					break;
				case 1:
					gu8Vibration = '\0';
					DAT_05cd2904 = 0x11;
					DAT_05cd2900 = 0;
					dsPlay_oneshot(3,0,0,0);
					break;
				default:
					MSG_Close(&DAT_05cd28b8);
					FUN_004c1c20();
					dsPlay_oneshot(3,0,0,0);
					DAT_05cd2904 = 0x11;
					DAT_05cd2900 = 0;
					DisplayTask();
					SpLoopOnlyDisplay();
					break;
				}
				DisplayTask();
				SpLoopOnlyDisplay();
				break;
			}
			else if (IsSOCAVAPress(0,2) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3,0,0,0);
				DAT_05cd2904 = 0x11;
				DAT_05cd2900 = 0;
				DisplayTask();
				SpLoopOnlyDisplay();
				break;
			}
			else
			{
				if ((DAT_05b92e44 & 0x80) != 0)
				{
					dsPlay_oneshot(1,0,0,0);
					DAT_05cd2900 = DAT_05cd2900 + 1;
					if (0x23 < DAT_05cd2900 + 0x22)
					{
						DAT_05cd2900 = 0;
					}
				}
			}
			if ((DAT_05b92e44 & 0x40) != 0)
			{
				dsPlay_oneshot(1,0,0,0);
				DAT_05cd2900 = DAT_05cd2900 - 1;
				if (DAT_05cd2900 + 0x22 < 0x22)
				{
					DAT_05cd2900 = 1;
				}
			}
			DisplayTask();
			SpLoopOnlyDisplay();
			break;
		}
		case 0x14:
			___njColorBlendingMode(0,8);
			___njColorBlendingMode(1,6);
			SetMaterial(0.5f,0.0f,0.0f,1.0f);
			local_23cv.x = 207.0f;
			local_23cv.y = 54.0f;
			local_248j.x = 14.0f;
			local_248j.y = 21.5f;
			for (local_22ci = 0; local_22ci < 4; local_22ci = local_22ci + 1)
			{
				printMenu2((PAUSE_TEXTURE_ID)(local_22ci + 0x24),0xf0,(long)(40.0 * local_22ci + 70.0 + 100.0),DAT_05cd2900 == local_22ci);
			}
			printMenu2((PAUSE_TEXTURE_ID)0x15,0xf0,(long)(40.0 * local_22ci + 70.0 + 100.0),DAT_05cd2900 == local_22ci);
			DrawButtonACBB();
			if (IsSOCAVAPress(0,4) != 0 || IsSOCAVAPress(0,8) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3,0,0,0);
				switch(DAT_05cd2900)
				{
				case 0:
					AvaSetTextSettei(1);
					DAT_05cd2908 = 0;
					break;
				case 1:
					AvaSetTextSettei(2);
					DAT_05cd2908 = 0;
					break;
				case 2:
					AvaSetTextSettei(4);
					DAT_05cd2908 = 0;
					break;
				case 3:
					AvaSetTextSettei(3);
					DAT_05cd2908 = 0;
					break;
				case 4:
					AvaSetTextSettei(0);
					DAT_05cd2908 = 0;
					break;
				default:
					MSG_Close(&DAT_05cd28b8);
					FUN_004c1c20();
					DAT_05cd2908 = 0;
					DisplayTask();
					SpLoopOnlyDisplay();
				}
				DisplayTask();
				SpLoopOnlyDisplay();
				break;
			}
			else if (IsSOCAVAPress(0,2) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3,0,0,0);
				DAT_05cd2908 = 0;
				DAT_05cd2900 = 0;
				DisplayTask();
				SpLoopOnlyDisplay();
				break;
			}
			else
			{
				if ((DAT_05b92e44 & 0x20) != 0)
				{
					dsPlay_oneshot(1,0,0,0);
					DAT_05cd2900 = DAT_05cd2900 + 1;
					if (0x29 < DAT_05cd2900 + 0x24)
					{
						DAT_05cd2900 = 0;
					}
				}
			}
			if ((DAT_05b92e44 & 0x10) != 0)
			{
				dsPlay_oneshot(1,0,0,0);
				DAT_05cd2900 = DAT_05cd2900 - 1;
				if (DAT_05cd2900 + 0x24 < 0x24)
				{
					DAT_05cd2900 = 4;
				}
			}
			DisplayTask();
			SpLoopOnlyDisplay();
			break;
		case 0x15:
			___njColorBlendingMode(0,8);
			___njColorBlendingMode(1,6);
			local_23cv.x = 112.0f;
			local_23cv.y = 224.0f;
			local_248j.x = 26.0f;
			local_248j.y = 4.0f;
			SetMaterial(0.5f,0.0f,0.0f,1.0f);
			printPauseTexture((PAUSE_TEXTURE_ID)8,&local_23cv,&local_248j);
			SetMaterial(1.0f,1.0f,1.0f,1.0f);
			for (local_22ci = 0; local_22ci < 2; local_22ci = local_22ci + 1)
			{
				switch (local_22ci)
				{
				case 0:
					printMenu2((PAUSE_TEXTURE_ID)0x29,0x90,0xf0,DAT_05cd2900 == local_22ci);
					break;
				case 1:
					printMenu2((PAUSE_TEXTURE_ID)0x2a,0x150,0xf0,DAT_05cd2900 == local_22ci);
					break;
				}
			}
			ResetMaterial();
			DrawButtonACBB();
			if (IsSOCAVAPress(0,4) != 0 || IsSOCAVAPress(0,8) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3,0,0,0);
				switch (DAT_05cd2900)
				{
				case 0:
					AvaSetOnseiSettei(0);
					DAT_05b42c1c = AvaGetOnseiSettei() ? 0 : 1;
					DAT_05cd2904 = 0x11;
					DAT_05cd2900 = 1;
					break;
				case 1:
					AvaSetOnseiSettei(1);
					DAT_05b42c1c = AvaGetOnseiSettei() ? 0 : 1;
					DAT_05cd2904 = 0x11;
					DAT_05cd2900 = 1;
					break;
				default:
					MSG_Close(&DAT_05cd28b8);
					FUN_004c1c20();
					DAT_05cd2904 = 0x11;
					DAT_05cd2900 = 1;
					DisplayTask();
					SpLoopOnlyDisplay();
					break;
				}
				DisplayTask();
				SpLoopOnlyDisplay();
				break;
			}
			else if (IsSOCAVAPress(0,2) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3,0,0,0);
				DAT_05cd2904 = 0x11;
				DAT_05cd2900 = 1;
				DisplayTask();
				SpLoopOnlyDisplay();
				break;
			}
			else
			{
				if ((DAT_05b92e44 & 0x80) != 0)
				{
					dsPlay_oneshot(1,0,0,0);
					DAT_05cd2900 = DAT_05cd2900 + 1;
					if (0x2a < DAT_05cd2900 + 0x29)
					{
						DAT_05cd2900 = 0;
					}
				}
			}
			if ((DAT_05b92e44 & 0x40) != 0)
			{
				dsPlay_oneshot(1,0,0,0);
				DAT_05cd2900 = DAT_05cd2900 - 1;
				if (DAT_05cd2900 + 0x29 < 0x29)
				{
					DAT_05cd2900 = 1;
				}
			}
			DisplayTask();
			SpLoopOnlyDisplay();
			break;
		case 0x16:
{
	int local_3ccg;
	float local_3d0i;
	float local_3d4y;
			local_3d4y = (float)((double)DAT_01c6e428 / (double)920.0);
			local_3d0i = (float)((double)DAT_01c6e42c / (double)690.0);
			local_3ccg = 2;
			if (IsSOCAVAPress(0,2) != 0)
			{
				if (DAT_05cd2864 <= 0)
				{
					MSG_Close(&DAT_05cd28b8);
					FUN_004c1c20();
					dsPlay_oneshot(3,0,0,0);
					DAT_05cd2904 = 0xf;
					DisplayTask();
					SpLoopOnlyDisplay();
					FUN_0041c2d0(DAT_05cd2710);
					delete DAT_05cd2710;
					DAT_05cd2710 = 0;
					FUN_0041c2d0(DAT_05cd2714);
					delete DAT_05cd2714;
					DAT_05cd2714 = 0;
					FUN_0041c2d0(DAT_05cd2718);
					delete DAT_05cd2718;
					DAT_05cd2718 = 0;
					FUN_0041c2d0(DAT_05cd271c);
					delete DAT_05cd271c;
					DAT_05cd271c = 0;
					FUN_0041c2d0(DAT_05cd2720);
					delete DAT_05cd2720;
					DAT_05cd2720 = 0;
					FUN_0041c2d0(DAT_05cd2724);
					delete DAT_05cd2724;
					DAT_05cd2724 = 0;
					FUN_0041c2d0(DAT_05cd2728);
					delete DAT_05cd2728;
					DAT_05cd2728 = 0;
					if (DAT_05cd272c != 0)
					{
						FUN_0041c2d0(DAT_05cd272c);
						delete DAT_05cd272c;
						DAT_05cd272c = 0;
					}
					if (DAT_05cd2730 != 0)
					{
						FUN_0041c2d0(DAT_05cd2730);
						delete DAT_05cd2730;
						DAT_05cd2730 = 0;
					}
					DAT_05cd2864 = 0;
				}
				else
				{
					dsPlay_oneshot(3,0,0,0);
					DAT_05cd2864 = DAT_05cd2864 + -1;
				}
			}
			break;
		}
		case 0x17:
			if (cameramodechange(0) != 1)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				DAT_05cd2904 = 0xe;
				DisplayTask();
				SpLoopOnlyDisplay();
			}
			break;
		case 0x18:
{
			if (DAT_05cd2758 != 0)
			{
				DrawTexture(0, 0, 0x280, 0x1e0, 0.01f, DAT_05cd2758, 0.0f, 0.0f, 0.8984375f, 0.673828125f, -1);
				DrawButtonXUBB();
			}
			if (IsSOCAVAPress(0,2) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3,0,0,0);
				DAT_05cd2908 = 0;
				DAT_05cd2900 = 0;
				DisplayTask();
				SpLoopOnlyDisplay();
				FUN_0041c2d0(DAT_05cd2758);
				delete DAT_05cd2758;
				DAT_05cd2758 = 0;
				break;
			}
			if (FUN_00405f00()->FUN_00424b40()->IsPress((SOCController::ControllerButton)7))
			{
			}
			break;
		}
		case 0x19:
			___njColorBlendingMode(0,8);
			___njColorBlendingMode(1,6);
			SetMaterial(0.5f,0.0f,0.0f,1.0f);
			local_23cv.x = 208.0f;
			local_23cv.y = 85.0f;
			local_248j.x = 14.0f;
			local_248j.y = 9.0f;
			printPauseTexture((PAUSE_TEXTURE_ID)8,&local_23cv,&local_248j);
			SetMaterial(1.0f,1.0f,1.0f,1.0f);
			printPause(21.0f);
			for (local_22ci = 0; local_22ci < 3; local_22ci = local_22ci + 1)
			{
				printMenu2((PAUSE_TEXTURE_ID)(local_22ci + 0x13),0xf0,(long)(40.0 * local_22ci + 70.0 - 7.0 + 42.0 - 7.0),DAT_05cd2900 == local_22ci);
			}
			DrawButtonACBB();
			switch (DAT_05cd2900)
			{
			case 0:
				DrawTexture(0, 0x182, (int)(local_2fcj * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2748, 0.0f, 0.0f, 0.8984375f, 0.05078125f, -1);
				break;
			case 1:
				DrawTexture(0, 0x182, (int)(local_270k * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2748, 0.0f, 0.0546875f, 0.8984375f, 0.10546875f, -1);
				break;
			default:
				DrawTexture(0, 0x182, (int)(local_270k * 920.0), (int)(local_270k * 52.0), 0.01f, DAT_05cd2744, 0.0f, 0.21875f, 0.8984375f, 0.26953125f, -1);
				break;
			}
			if (IsSOCAVAPress(0,4) != 0 || IsSOCAVAPress(0,8) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3,0,0,0);
				switch (DAT_05cd2900)
				{
				case 0:
					DAT_05cd2784 = 1;
					DAT_0260553f = 1;
					DAT_0260553e = 2;
					DAT_05cd2785 = 0;
					DAT_05cd2790 = 0;
					DAT_05cd2794 = 0;
					DAT_05cd2798 = 0;
					DAT_05cd2904 = 0xc;
					break;
				case 1:
					DAT_05cd2784 = 1;
					DAT_0260553f = 0;
					DAT_0260553e = 2;
					DAT_05cd2785 = 0;
					DAT_05cd2794 = 0;
					DAT_05cd2798 = 0;
					DAT_05cd2790 = 0;
					DAT_05cd2904 = 0xc;
					break;
				default:
					MSG_Close(&DAT_05cd28b8);
					FUN_004c1c20();
					DAT_05cd2908 = 0;
					break;
				}
				DisplayTask();
				SpLoopOnlyDisplay();
				break;
			}
			else if (IsSOCAVAPress(0,2) != 0)
			{
				MSG_Close(&DAT_05cd28b8);
				FUN_004c1c20();
				dsPlay_oneshot(3,0,0,0);
				DAT_05cd2908 = 0;
				DAT_05cd2900 = 0;
				DisplayTask();
				SpLoopOnlyDisplay();
				break;
			}
			else
			{
				if ((DAT_05b92e44 & 0x20) != 0)
				{
					dsPlay_oneshot(1,0,0,0);
					DAT_05cd2900 = DAT_05cd2900 + 1;
					if (0x15 < DAT_05cd2900 + 0x13)
					{
						DAT_05cd2900 = 0;
					}
				}
			}
			if ((DAT_05b92e44 & 0x10) != 0)
			{
				dsPlay_oneshot(1,0,0,0);
				DAT_05cd2900 = DAT_05cd2900 - 1;
				if (DAT_05cd2900 + 0x13 < 0x13)
				{
					DAT_05cd2900 = 2;
				}
			}
			DisplayTask();
			SpLoopOnlyDisplay();
			break;
		}
		return 1;
		break;
	case 1:
		if (DAT_05cd2908 == 0)
		{
			DAT_05cd2908 = 1;
			DAT_05cd2904 = 0;
			DAT_05cd2900 = 0;
			MSG_Open(&DAT_05cd28b8, 64, 420, 512, 56, 0xd0000020);
			DAT_05cd28b8.bc.argb.a = 0x80;
			MSG_Puts(&DAT_05cd28b8, DAT_02606b78[DAT_05b3ebbc]);
			MSG_LoadTexture2(&DAT_05cd28b8);
		}
		break;
	case 2:
		DAT_05cd2908 = 0;
		break;
	case 3:
		if (DAT_05cd2908 == 0)
		{
			DAT_05cd2908 = 1;
			DAT_05cd2904 = 11;
			DAT_05cd2900 = 0;
		}
		break;
	case 4:
		if (DAT_05cd2908 == 0)
		{
			DAT_05cd2908 = 1;
			DAT_05cd2904 = 13;
			DAT_05cd2900 = 0;
		}
		break;
	case 5:
		if (DAT_05cd2908 == 0)
		{
			DAT_05cd2908 = 1;
			DAT_05cd2904 = 14;
			DAT_05cd2900 = 0;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x00582ad0
float FUN_00582ad0(float param_1)
{
	float local_8;
	local_8 = (float)floor((double)param_1);
	return local_8;
}

// STUB: SADX 0x00582af0
void __fastcall FUN_00582af0(int param_1)
{
}

// FUNCTION: SADX 0x00583720
int FUN_00583720()
{
	if (DAT_05cd2784 == 2 && (DAT_05b92e44 & 2) != 0)
	{
		dsPlay_oneshot(3, 0, 0, 0);
		DAT_05cd2784 = 3;
	}
	switch (DAT_05cd2784)
	{
	case 0:
		return 0;
	case 1:
		if (InitLBOn() == 0)
		{
			DAT_05cd2784 = 0;
			return 0;
		}
		DAT_05cd2784 = 2;
		break;
	case 2:
		DrawLBOn();
		break;
	case 3:
		DestroyLBOn();
		DAT_05cd2784 = 0;
		return 2;
	}
	return 1;
}

// STUB: SADX 0x00587710
void DestroyLBOn()
{
}

// STUB: SADX 0x00588800
void FUN_00588800(void *param_1, wchar_t *param_2)
{
}

// STUB: SADX 0x00588890
void FUN_00588890(int param_1)
{
}

// STUB: SADX 0x00588920
int FUN_00588920(struct NJS_POINT3 *param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x005889a0
void FUN_005889a0(int param_1)
{
}

// STUB: SADX 0x00588a30
void FUN_00588a30(int param_1)
{
}

// STUB: SADX 0x00588c90
char * FUN_00588c90(char *param_1, char *param_2, int param_3, int param_4)
{
	return (char *)0;
}

// STUB: SADX 0x00588db0
void FUN_00588db0(struct obj *param_1, int param_2)
{
}

// STUB: SADX 0x00588e00
void __fastcall FUN_00588e00(void *param_1, char param_2, int param_3, int param_4)
{
}

// STUB: SADX 0x00588ea0
void split2(void *param_1, void *param_2)
{
}

// STUB: SADX 0x00589930
void FUN_00589930()
{
}

// STUB: SADX 0x00589a70
void FUN_00589a70(char *param_1, int param_2, int param_3)
{
}

// STUB: SADX 0x00589b70
void FUN_00589b70(void *param_1, int param_2, int param_3, short param_4)
{
}

// STUB: SADX 0x00589c10
void __fastcall FUN_00589c10(void *param_1, int param_2, char param_3)
{
}

// STUB: SADX 0x0058a010
int FUN_0058a010(int *param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x0058a090
void FUN_0058a090(void *param_1, int param_2, int param_3)
{
}

// STUB: SADX 0x0058a490
void FUN_0058a490(int param_1, int param_2, int param_3)
{
}

// STUB: SADX 0x0058a4b0
void FUN_0058a4b0(int param_1, int param_2, int param_3)
{
}

// FUNCTION: SADX 0x0058a560
void *FUN_0058a560(unsigned int param_1)
{
	void *local_8 = 0;
	if (param_1 <= 0)
	{
		param_1 = 0;
	}
	else if (param_1 > 0x9249249 || (local_8 = operator new(param_1 * 0x1c)) == 0)
	{
		throw std::bad_alloc(0);
	}
	return local_8;
}

// FUNCTION: SADX 0x0058a5d0
void *FUN_0058a5d0(unsigned int param_1)
{
	void *local_8 = 0;
	if (param_1 <= 0)
	{
		param_1 = 0;
	}
	else if (param_1 > 0x7fffffff || (local_8 = operator new(param_1 * 2)) == 0)
	{
		throw std::bad_alloc(0);
	}
	return local_8;
}

// FUNCTION: SADX 0x0058a640
unsigned short * FUN_0058a640(unsigned short *param_1, unsigned short *param_2, unsigned short *param_3)
{
	for (; param_1 != param_2; param_1 = param_1 + 1)
	{
		if (*param_1 == *param_3)
			break;
	}
	return param_1;
}

// STUB: SADX 0x0058a670
void FUN_0058a670(void *param_1, void *param_2)
{
}

// STUB: SADX 0x0058a710
void FUN_0058a710(void *param_1, int param_2, void *param_3, void *param_4)
{
}

// STUB: SADX 0x0058a7d0
void FUN_0058a7d0(void *param_1, void *param_2)
{
}
