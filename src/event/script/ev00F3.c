#include "decls.h"
extern struct task *DAT_060cb654;
extern struct task *DAT_060cb658;
extern unsigned char DAT_05bafb25;
extern struct NJS_TEXLIST DAT_05a9238c;
extern struct NJS_ACTION DAT_060cc220;
extern struct NJS_ACTION DAT_060cc840;
extern struct NJS_ACTION DAT_060cc848;
extern struct NJS_ACTION DAT_060cc850;
extern struct NJS_ACTION DAT_060cc858;
extern struct NJS_ACTION DAT_060cc860;
extern struct NJS_ACTION DAT_060cc878;
extern struct NJS_ACTION DAT_060cc890;
extern struct TEX_PVMTABLE evpvm[];
void FUN_0056a2a0();
void FUN_0056a2b0();
void FUN_0056a2c0();
void FUN_0056b370(struct task *param_1, float param_2, float param_3, float param_4);
void FUN_0056b3e0(struct task *param_1, long param_2, long param_3, long param_4);
void FUN_0056b650(struct task *param_1, struct NJS_ACTION *param_2, struct NJS_TEXLIST *param_3, float param_4, int param_5, int param_6);
void FUN_0056b6d0(struct task *param_1);
void FUN_0056bb50(struct task *param_1);
void FUN_0056bb90();
void FUN_0056d0b0(struct task *param_1, char *param_2);
void FUN_00717f90(int param_1);
void FUN_00717fc0();
void FUN_00718010(int param_1, int param_2, int param_3);
void FUN_00718050(int param_1);
void FUN_00718120(int param_1, int param_2, int param_3, int param_4);
void FUN_00731880();
void FUN_007d1cf0(int param_1);
void FUN_007d2030(float param_1, float param_2, float param_3, long param_4, long param_5, long param_6, float param_7, float param_8, float param_9, struct obj *param_10, struct NJS_TEXLIST *param_11, int param_12);
struct task *FUN_007d4c80(float param_1, float param_2, float param_3, float param_4, float param_5);
void FUN_007d4cd0(struct task *param_1, float param_2);
void FUN_007d6280(float param_1, float param_2, float param_3, long param_4, long param_5, long param_6);
void FUN_007d6940(struct task *param_1);

// FUNCTION: SADX 0x007318d0
static void dispChaos0Task(struct task *p_task)
{
	struct taskwk *var1 = DAT_060cb654->twp;

	*((unsigned char *)&object_c0_manju_c0_manju->model->mats->diffuse + 3) = *((unsigned char *)var1->value.ptr + 0x1c);
	SetParamDispChaosWater(&var1->pos, &var1->scl);
}

// FUNCTION: SADX 0x00731900
static void execChaos0Task(struct task *p_task)
{
	struct taskwk *var1 = p_task->twp;
	char *var2 = (char *)var1->value.ptr;

	switch (var1->mode)
	{
	case 0:
		var1->scl.x = njCos((int)((var1->counter.f += 6.0) * 65536.0 / 360.0)) * 0.125 + 1.0;
		var1->scl.y = njCos((int)(var1->counter.f * 65536.0 / 360.0)) * 0.125 + 1.0;
		var1->scl.z = njSin((int)(var1->counter.f * 65536.0 / 360.0)) * 0.125 + 1.0;
		break;
	case 1:
		var1->pos.x = *(float *)(var2 + 4) + var1->pos.x;
		var1->pos.y = *(float *)(var2 + 8) + var1->pos.y;
		var1->pos.z = *(float *)(var2 + 0xc) + var1->pos.z;
		var1->timer.l++;
		if (var1->timer.l > *(long *)(var2 + 0x10))
		{
			var1->mode = 0;
		}
		var1->scl.y = njCos((int)((var1->counter.f += 6.0) * 65536.0 / 360.0)) * 0.5 + 1.5;
		break;
	case 2:
		var1->counter.f += 18.0;
		*(float *)(var2 + 0x14) -= *(float *)(var2 + 0x18);
		var1->timer.l++;
		if (var1->timer.l > *(long *)(var2 + 0x10))
		{
			var1->mode = 3;
		}
		var1->scl.x = njCos((int)(var1->counter.f * 65536.0 / 360.0)) * 0.125 + 1.0;
		var1->scl.y = njCos((int)(var1->counter.f * 65536.0 / 360.0)) * 0.125 + 1.0;
		var1->scl.z = njSin((int)(var1->counter.f * 65536.0 / 360.0)) * 0.125 + 1.0;
		var1->scl.x = *(float *)(var2 + 0x14) * var1->scl.x;
		var1->scl.y = var1->scl.y * *(float *)(var2 + 0x14);
		var1->scl.z = var1->scl.z * *(float *)(var2 + 0x14);
		*(unsigned char *)(var2 + 0x1c) -= *(unsigned char *)(var2 + 0x1d);
		break;
	case 3:
		return;
	}
	dispChaos0Task(p_task);
}

// FUNCTION: SADX 0x00731b20
static void initChaos0Task(struct task *p_task)
{
	p_task->exec = execChaos0Task;
	p_task->disp = dispChaos0Task;
	p_task->dest = FUN_007d6940;
}

// FUNCTION: SADX 0x00731b40
static void createChaos0(float pos_x, float pos_y, float pos_z, long ang)
{
	struct taskwk *var1;
	char *var2;
	struct task *var3;

	DAT_060cb654 = CreateElementalTask(2, 5, initChaos0Task);
	var2 = (char *)MAlloc(0x20);
	var1 = DAT_060cb654->twp;
	var1->pos.x = pos_x;
	var1->value.ptr = var2;
	var1->pos.y = pos_y;
	var1->mode = 0;
	var1->ang.y = ang;
	var1->pos.z = pos_z;
	var1->scl.x = 0.8f;
	var1->scl.y = 0.8f;
	var1->scl.z = 0.8f;
	var1->counter.f = 0.0f;
	var3 = SetTaskDispChaosWater(ang);
	*(struct task **)var2 = var3;
	*(unsigned char *)(var2 + 0x1c) = 0x99;
	initialChaos(var3->twp, (struct chaoswk *)var3->awp, 5);
}

// FUNCTION: SADX 0x00731bd0
static void evmain(int code)
{
	if (code == 1)
	{
		DAT_060cb654 = 0;
		DAT_060cb658 = 0;
	}
	switch (code)
	{
	case 1:
		EV_InitPlayer(0);
		SetBankDir(0x71);
		FUN_00717f90(5);
		FUN_0056bb90();
		FUN_0056a2b0();
		FUN_0056a2c0();
		EV_CameraPos(1, 0, -28.67f, 14.19f, 2386.76f);
		EV_CameraAng(1,0,0x700,0xfc00,0);
		EV_CameraAng(0,0x78,0xe600,0xfc00,0);
		FUN_007d2030(-5.7f, -152.58f, 2169.71f, 0x1900, 0x3000, 0x1000, 1.0f, 1.0f, 1.0f, object_m_em_blue_m_em_blue, &texlist_m_em_blue, 0);
		FUN_007d2030(-11.3f, -152.58f, 2168.5f, 0x700, 0x7000, 0xe00, 1.0f, 1.0f, 1.0f, object_m_em_green_m_em_green, &texlist_m_em_green, 1);
		FUN_007d2030(-15.2f, -152.58f, 2166.4f, 0x1200, 0x5000, 0xd00, 1.0f, 1.0f, 1.0f, object_m_em_purple_m_em_purple, &texlist_m_em_purple, 2);
		FUN_007d2030(0.8f, -152.58f, 2169.73f, 0x1000, 0xb000, 0x1000, 1.0f, 1.0f, 1.0f, object_m_em_sky_m_em_sky, &texlist_m_em_sky, 3);
		FUN_007d2030(6.0f, -152.58f, 2168.63f, 0x1200, 0x9000, 0x300, 1.0f, 1.0f, 1.0f, object_m_em_white_m_em_white, &texlist_m_em_white, 4);
		FUN_007d2030(10.8f, -152.58f, 2165.63f, 0xef00, 0xb000, 0x600, 1.0f, 1.0f, 1.0f, object_m_em_yellow_m_em_yellow, &texlist_m_em_yellow, 5);
		FUN_0056b370(FUN_0056b1f0(0), 151.09f, -179.73f, 2154.86f);
		EV_CreatePlayer(2, KnucklesTheEchidna, -2.96f, -157.08f, 2208.78f, 0, 0, 0);
		EV_CreatePlayer(5, Eggman, -38.05f, -262.58f, 2623.56f, 0x884, 0x8000, 0x44);
		EV_SetMode(FUN_0056b1f0(5),0);
		FUN_007d6280(-22.02f, -258.52f, 2651.15f, 0x884, 0xa000, 0x6000);
		FUN_0056aea0(2);
		DAT_05bafb25 = 3;
		FUN_0056b650(FUN_0056b1f0(5), action_g_g0023_eggman, &DAT_05a9238c, 1.0f, 1, 0);
		FUN_0056aea0(1);
		BGM_Play(0x5c);
		ChgEggMobleMod(5);
		FUN_0056aea0(0x76);
		EV_CameraPos(0, 0xb4, -17.73f, -68.6f, 2275.62f);
		FUN_0056d0b0(FUN_0056b1f0(2),"FAFB");
		EV_Msg(strtbl[DAT_05b3ebbc][0]);
		EV_SerifPlay(0x574);
		FUN_0056aea0(1);
		EV_CameraOff();
		EV_MsgCls();
		EV_ClrFace(FUN_0056b1f0(2));
		FUN_0056aea0(0x1e);
		FUN_0056b650(FUN_0056b1f0(2), &DAT_060cc860, &texlist_knuckles, 0.3f, 0, 0);
		FUN_0056b650(FUN_0056b1f0(2), &DAT_060cc220, &texlist_knuckles, 1.0f, 1, 0);
		EV_CameraPos(1, 0, -6.23f, -154.14f, 2215.12f);
		EV_CameraAng(1,0,0xf100,64000,0);
		EV_CameraPerspective(1,1,0x1c72);
		FUN_0056aea0(1);
		FUN_0056d0b0(FUN_0056b1f0(2),"CAFAFB");
		EV_Msg(strtbl[DAT_05b3ebbc][1]);
		EV_SerifPlay(0x575);
		FUN_0056aea0(0x3c);
		EV_CameraPos(0, 100, -3.39f, -150.72f, 2223.22f);
		EV_CameraAng(0,100,0,0xfe00,0);
		EV_CameraPerspective(1,100,0x3111);
		EV_CameraOff();
		EV_MsgCls();
		EV_ClrFace(FUN_0056b1f0(2));
		FUN_0056aea0(0x1e);
		FUN_0056d0b0(FUN_0056b1f0(2),"CDEB");
		EV_SerifPlay(0x576);
		EV_Msg(strtbl[DAT_05b3ebbc][2]);
		FUN_0056aea0(1);
		EV_CameraOff();
		EV_MsgCls();
		EV_ClrFace(FUN_0056b1f0(2));
		FUN_0056aea0(0x1e);
		FUN_0056b650(FUN_0056b1f0(2), &DAT_060cc878, &texlist_knuckles, 1.0f, 0, 0);
		FUN_0056b650(FUN_0056b1f0(2), &DAT_060cc890, &texlist_knuckles, 1.0f, 1, 0);
		FUN_0056aea0(10);
		FUN_0056d0b0(FUN_0056b1f0(2),"AAED");
		EV_Msg(strtbl[DAT_05b3ebbc][3]);
		EV_SerifPlay(0x577);
		FUN_0056aea0(1);
		EV_CameraOff();
		EV_ClrFace(FUN_0056b1f0(2));
		EV_MsgCls();
		FUN_0056aea0(0x1e);
		EV_CameraPos(0, 0, -9.38f, -149.77f, 2179.65f);
		EV_CameraAng(0,0,0,0,0);
		EV_CameraPos(0, 0x78, 7.61f, -149.77f, 2179.65f);
		FUN_0056b6d0(FUN_0056b1f0(2));
		EV_MovePoint2(FUN_0056b1f0(2), -1.52f, -157.08f, 2180.37f, 0.3f, 0.0f);
		FUN_0056aea0(10);
		EV_Msg(strtbl[DAT_05b3ebbc][4]);
		EV_SerifPlay(0x578);
		FUN_0056aea0(1);
		EV_CameraOff();
		EV_MsgCls();
		FUN_0056bb50(FUN_0056b1f0(2));
		FUN_0056aea0(10);
		FUN_0056b650(FUN_0056b1f0(2), &DAT_060cc858, &texlist_knuckles, 1.0f, 1, 0);
		EV_CameraPos(0, 0x78, 20.08f, -149.77f, 2189.74f);
		EV_CameraAng(0,0x78,0,0x2000,0);
		FUN_0056d0b0(FUN_0056b1f0(2),"ED");
		EV_Msg(strtbl[DAT_05b3ebbc][5]);
		EV_SerifPlay(0x579);
		FUN_0056aea0(1);
		EV_CameraOff();
		EV_ClrFace(FUN_0056b1f0(2));
		EV_MsgCls();
		FUN_0056aea0(0x1e);
		FUN_0056d0b0(FUN_0056b1f0(2),"EADC");
		EV_Msg(strtbl[DAT_05b3ebbc][6]);
		EV_SerifPlay(0x57a);
		FUN_0056aea0(0x3c);
		EV_MsgCls();
		FUN_0056aea0(0x32);
		EV_ClrFace(FUN_0056b1f0(2));
		FUN_0056b650(FUN_0056b1f0(2), &DAT_060cc848, &texlist_knuckles, 1.0f, 0, 0x10);
		FUN_0056b650(FUN_0056b1f0(2), &DAT_060cc850, &texlist_knuckles, 1.0f, 1, 0);
		FUN_0056aea0(0x3c);
		EV_CameraPos(0, 0, -20.23f, -124.58f, 2273.54f);
		EV_CameraAng(0,0,0xf100,0x7e00,0);
		EV_CameraPerspective(1,0x3c,0x222);
		FUN_0056aea0(0x3c);
		FUN_0056b370(FUN_0056b1f0(2), -4.35f, -157.08f, 2246.73f);
		FUN_0056b3e0(FUN_0056b1f0(2),0,0,0);
		FUN_0056aea0(1);
		FUN_0056b6d0(FUN_0056b1f0(2));
		FUN_0056b650(FUN_0056b1f0(2), &DAT_060cc858, &texlist_knuckles, 1.0f, 1, 0);
		FUN_0056aea0(0x28);
		EV_CameraPos(0, 0, -5.82f, -143.55f, 2277.51f);
		EV_CameraAng(0,0,0xf000,0xfd00,0);
		EV_CameraPerspective(1,1,0x31c7);
		FUN_0056aea0(1);
		FUN_0056b650(FUN_0056b1f0(2), &DAT_060cc858, &texlist_knuckles, 1.0f, 1, 0);
		FUN_0056d0b0(FUN_0056b1f0(2),"H");
		EV_Msg(strtbl[DAT_05b3ebbc][7]);
		EV_SerifPlay(0x57b);
		FUN_0056aea0(1);
		EV_CameraOff();
		EV_MsgClose();
		FUN_0056b6d0(FUN_0056b1f0(2));
		EV_MovePoint2(FUN_0056b1f0(2), -1.06f, -239.57f, 2398.72f, 3.0f, 3.0f);
		FUN_0056aea0(0x14);
		EV_MoveFree(FUN_0056b1f0(2));
		FUN_0056aea0(0x28);
		EV_CameraPerspective(1,1,0x3111);
		EV_CameraPos(0, 0, -16.915f, -256.77f, 2638.145f);
		EV_CameraAng(0,0,0xfe00,0x2200,0);
		FUN_0056b370(FUN_0056b1f0(2), -19.96f, -257.14f, 2606.0f);
		FUN_0056b3e0(FUN_0056b1f0(2),0,0xd000,0);
		FUN_0056b650(FUN_0056b1f0(2), *(struct NJS_ACTION **)(DAT_06274afc + 0x14c), &texlist_knuckles, 0.8f, 1, 0);
		createChaos0(12.58f, -264.7f, 2644.47f, 0);
		FUN_0056aea0(1);
		EV_MovePoint2(FUN_0056b1f0(2), -29.0f, -260.6f, 2614.18f, 0.03f, 1.0f);
		FUN_0056bb50(FUN_0056b1f0(2));
		FUN_0056b6d0(FUN_0056b1f0(2));
		FUN_0056b650(FUN_0056b1f0(2), &DAT_060cc858, &texlist_knuckles, 1.0f, 1, 8);
		FUN_0056aea0(0x3c);
		EV_Msg(strtbl[DAT_05b3ebbc][8]);
		EV_SerifPlay(0x57c);
		FUN_0056aea0(1);
		EV_CameraOff();
		EV_MsgCls();
		FUN_0056aea0(10);
		FUN_0056b650(FUN_0056b1f0(2), &DAT_060cc840, &texlist_knuckles, 1.0f, 1, 0x10);
		FUN_0056d0b0(FUN_0056b1f0(2),"F");
		EV_Msg(strtbl[DAT_05b3ebbc][9]);
		EV_SerifPlay(0x57d);
		FUN_0056aea0(1);
		EV_CameraOff();
		EV_MsgCls();
		FUN_00718010(0,0x537,0x708);
		EV_CameraPos(0, 0x5a, 26.59f, -261.28f, 2653.96f);
		EV_CameraAng(0,0x5a,0x100,0x2900,0);
		EV_CameraPerspective(0,0x5a,0x1d28);
		FUN_0056aea0(0x6e);
		EV_MsgClose();
		FUN_00718050(0);
		DAT_060cb658 = FUN_007d4c80(0.016666668f, 0.0f, 0.0f, 0.0f, 0.0f);
		FUN_0056aea0(0x5a);
		FUN_00718120(0x536,0,0,0);
		if ((DAT_060cb658 != 0) && (FUN_007d4cd0(DAT_060cb658, -1.0f), DAT_060cb658 != 0))
		{
			FUN_007d4cd0(DAT_060cb658, 1.0f);
		}
		FUN_0056aea0(0x3c);
		FUN_00718120(0x535,0,0,0);
		FUN_0056aea0(10);
		if (DAT_060cb658 != 0)
		{
			FreeTask(DAT_060cb658);
			DAT_060cb658 = 0;
		}
		break;
	case 2:
		FUN_00717fc0();
		FUN_007d62e0();
		if (DAT_060cb658 != 0)
		{
			FreeTask(DAT_060cb658);
			DAT_060cb658 = 0;
		}
		FUN_00731880();
		FUN_007d1cf0(0);
		FUN_007d1cf0(1);
		FUN_007d1cf0(2);
		FUN_007d1cf0(3);
		FUN_007d1cf0(4);
		FUN_007d1cf0(5);
		EV_InitPlayer(0);
		FUN_0056b510(2);
		FUN_0056b510(5);
		FUN_0056bcd0();
		FUN_0056a2a0();
		return;
	}
}

// GLOBAL: SADX 0x02c22c98
struct EVTABLE2 __ev00f3 = {evmain, evpvm};
