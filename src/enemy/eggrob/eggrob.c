#include "decls.h"
extern short DAT_05edecee;
extern short DAT_05edece8;
extern float DAT_05edeec8;
extern int DAT_05eded70;
extern int DAT_05eded74;
extern int DAT_05eded04;
extern int DAT_05eded08;
extern int DAT_05edeed8;
extern char DAT_05eded6c;
extern struct NJS_TEXLIST texlist_eggrob;
extern int DAT_05eded7c;
extern struct obj object_eggrob_a_er_ra4[1];
extern struct obj object_eggrob_a_er_ra5[1];
extern struct obj object_eggrob_a_er_ra6[1];
extern struct obj object_eggrob_a_er_ra7[1];
extern struct obj object_eggrob_a_j_er_head[1];
extern struct obj object_eggrob_a_chn9_1[1];
extern short DAT_05edecec;
extern float DAT_05eded78;
extern float DAT_05edecfc;
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern float DAT_05edecd4;
void FUN_00610a30(struct task *param_1);
extern int DAT_05eded84;
extern int DAT_05eded88;
extern int DAT_05eded8c;
extern int DAT_05eded80;

// FUNCTION: SADX 0x00610640
void Eggrob_Infl_BlindToAmy()
{
	DAT_05eded80 = 1;
}

// STUB: SADX 0x00610650
void FUN_00610650(int *param_1)
{
}

// FUNCTION: SADX 0x006109b0
void Eggrob_Init(struct task *tp)
{
	CCL_Init(tp, (struct CCL_INFO *)&eggrob_ci_info, 2, 3);
	tp->dest = Eggrob_Destruct;
	tp->disp = Eggrob_Display;
	if (((DAT_05b9d724 << 8) | DAT_05b9d744) == 0x302)
	{
		createMirrorTask(tp);
	}
	tp->exec = Eggrob;
	DAT_05edecd4 = 0.0f;
	FUN_00610a30(tp);
	Eggrob_BeamInit();
}

// FUNCTION: SADX 0x00610af0
void FUN_00610af0()
{
	DAT_05eded80 = 0;
	*(float *)&DAT_05eded84 = 0.0f;
	*(float *)&DAT_05eded88 = 0.0f;
	*(float *)&DAT_05eded8c = 0.0f;
}

// FUNCTION: SADX 0x00610b20
void Eggrob_Destruct(struct task *tp)
{
	Eggrob_ResetStatus(tp->twp);
}

// FUNCTION: SADX 0x00610b40
void Eggrob_ResetStatus(struct taskwk *twp)
{
	twp->btimer = 0;
	twp->value.f = 1.0f;
	*(unsigned long *)((char *)twp->cwp->info + 0x34) |= 0x10;
	DAT_05eded7c = 0;
	object_eggrob_a_chn9_1[0].ang[1] = 0;
	object_eggrob_a_j_er_head[0].ang[2] = 0x8000;
	object_eggrob_a_er_ra4[0].evalflags &= 0xfffffff7;
	object_eggrob_a_er_ra5[0].evalflags &= 0xfffffff7;
	object_eggrob_a_er_ra6[0].evalflags &= 0xfffffff7;
	object_eggrob_a_er_ra7[0].evalflags &= 0xfffffff7;
}

// FUNCTION: SADX 0x00612b50
void FUN_00612b50(short param_1, float param_2)
{
	DAT_05edecec = param_1;
	DAT_05eded78 = param_2;
	DAT_05edecfc = param_2;
}

// STUB: SADX 0x00613680
void FUN_00613680(float *param_1)
{
}

// STUB: SADX 0x00613a80
void Eggrob_BeamInit()
{
}

// STUB: SADX 0x00615570
void FUN_00615570()
{
}

// STUB: SADX 0x006155e0
void FUN_006155e0(struct NJS_POINT3 *param_1, struct NJS_POINT3 *param_2)
{
}

// STUB: SADX 0x00615a00
void FUN_00615a00(struct NJS_POINT3 *pos, float rad)
{
}

// STUB: SADX 0x00615f90
void Eggrob_RPunchShadow(struct task *tp)
{
}

// STUB: SADX 0x006160a0
void DisplayerEggrob_FindDisplay(struct task *tp)
{
}

// STUB: SADX 0x00616150
void Eggrob_FindDisplay(struct task *tp)
{
}

// STUB: SADX 0x00616210
void DisplayerEggrob_HatenaDisplay(struct task *tp)
{
}

// STUB: SADX 0x006162c0
void Eggrob_HatenaDisplay(struct task *tp)
{
}

// STUB: SADX 0x00616560
void DisplayerEggrob_ShindohaWave(struct task *tp)
{
}

// STUB: SADX 0x00616650
int FUN_00616650(int *param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x006166a0
void EggrobForEvent0(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	CCL_Init(tp, (struct CCL_INFO *)&eggrob_ci_info, 2, 2);
	SetEventWork(local_8);
	PInitialize(local_8->counter.b[0], tp);
	texLoadTexturePvmFile("EGGROB", &texlist_eggrob);
	*(float *)((char *)local_8 + 0x34) = 0.0f;
	*(float *)((char *)local_8 + 0x30) = 0.0f;
	*(float *)((char *)local_8 + 0x2c) = 0.0f;
	DAT_05edecd4 = 0.0f;
	DAT_05edece8 = 0;
	DAT_05eded08 = (int)eggrob_action;
	DAT_05edecee = 0x14;
	DAT_05edecec = DAT_05edecee;
	DAT_05eded04 = (int)&DAT_05eded6c;
	object_eggrob_a_chn9_1[0].ang[1] = 0;
	object_eggrob_a_j_er_head[0].ang[2] = 0x8000;
	DAT_05edeed8 = 0;
	DAT_05eded74 = 0;
	*(unsigned long *)((char *)local_8->cwp->info + 0x34) |= 0x10;
	DAT_05edeec8 = 0.0f;
	local_8->timer.l = 0xb4;
	local_8->mode = 5;
	Eggrob_BeamInit();
	DAT_05eded70 = 0;
	tp->dest = EggrobForEvent0_Destruct;
	tp->exec = EggrobForEvent0_Exe;
}

// FUNCTION: SADX 0x006167d0
void EggrobForEvent0_Destruct(struct task *tp)
{
	object_eggrob_a_chn9_1[0].ang[1] = 0;
	object_eggrob_a_j_er_head[0].ang[2] = 0x8000;
	object_eggrob_a_er_ra4[0].evalflags &= 0xfffffff7;
	object_eggrob_a_er_ra5[0].evalflags &= 0xfffffff7;
	object_eggrob_a_er_ra6[0].evalflags &= 0xfffffff7;
	object_eggrob_a_er_ra7[0].evalflags &= 0xfffffff7;
	PDestruct(tp->twp->counter.b[0]);
}

// STUB: SADX 0x00617040
void EggrobForEvent0_RP_1(struct task *tp)
{
}
