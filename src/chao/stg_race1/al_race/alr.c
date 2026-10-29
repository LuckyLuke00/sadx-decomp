#include "decls.h"
#include <stdlib.h>
void FUN_00486bc0(struct Alr *param_1, struct NJS_POINT3 *param_2);
void FUN_00486bc0(struct Alr *param_1, struct NJS_POINT3 *param_2);
void FUN_00486bc0(struct Alr *param_1, struct NJS_POINT3 *param_2);
void FUN_00486bc0(struct Alr *param_1, struct NJS_POINT3 *param_2);
void FUN_00486bc0(struct Alr *param_1, struct NJS_POINT3 *param_2);

// FUNCTION: SADX 0x00486880
void Alr_SetWorkData(struct Alr *___this, struct taskwk *twp, struct alifewk *awp)
{
	___this->flag |= 2;
	___this->awp = awp;
	___this->twp = twp;
	if (___this->flag & 1)
	{
		___this->flag |= 4;
	}
}

// FUNCTION: SADX 0x004868c0
void Alr_Close(struct Alr *___this)
{
	___this->flag &= 0xfff8;
	___this->awp = 0;
	___this->twp = 0;
}

// FUNCTION: SADX 0x004868e0
void Alr_Kill(struct Alr *___this)
{
	if (___this->awp)
	{
		DestroyTask(*(struct task **)((char *)___this->awp + 0x8cc));
		___this->flag = 0;
	}
}

// FUNCTION: SADX 0x00486910
int Alr_CheckOpen(struct Alr *___this)
{
	return *(unsigned char *)(&___this->flag) >> 2 & 1;
}

// FUNCTION: SADX 0x00486930
struct alifewk *Alr_GetAwp(struct Alr *___this)
{
	if ((___this->flag & 4) != 0)
	{
		return ___this->awp;
	}
	return 0;
}

// FUNCTION: SADX 0x00486950
struct taskwk *Alr_GetTwp(struct Alr *___this)
{
	if (___this->flag & 4)
		return ___this->twp;
	return 0;
}

// FUNCTION: SADX 0x00486970
void Alr_ExeWaterEff(struct Alr *___this, struct NJS_POINT3 *trans, struct NJS_POINT3 *velo)
{
	___this->flag |= 0x20;
	AlrEff_SetFlag(&___this->eff, 0x10);
	AlrEff_Exe(&___this->eff, trans, velo);
}

// FUNCTION: SADX 0x004869a0
int Alr_CheckRace(const struct Alr *___this)
{
	if (___this->mode >= 4 && (___this->mode <= 9 || ___this->mode == 16))
	{
		return 1;
	}
	return 0;
}

// STUB: SADX 0x004869c0
int Alr_CheckGoal(const struct Alr *___this)
{
	return (int)0;
}

// STUB: SADX 0x004869e0
int Alr_CheckCommendation(const struct Alr *___this)
{
	return (int)0;
}

// FUNCTION: SADX 0x00486a00
int Alr_GetCommand(struct Alr *___this, int command)
{
	if (___this->command == command)
	{
		___this->command = 0;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00486a30
int Alr_CheckLookAtMe(struct Alr *___this)
{
	int id;
	if (GetIdLookChao(&id) && id == ___this->id)
	{
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00486a60
void Alr_EndEx(struct Alr *___this)
{
	if (___this->ex_mode != 0)
	{
		___this->command = 4;
		___this->ex_mode = 0;
		___this->ex_cnt = 0;
	}
}

// FUNCTION: SADX 0x00486a90
void FUN_00486a90(struct Alr *param_1)
{
	int var1;
	float var2;
	int var3;

	var1 = rand();
	var2 = (float)var1 * 3.0517578125e-05;
	var2 = var2 * 3.0 + 0.0;
	var3 = (int)var2;
	param_1->ex_mode = (unsigned char)var3;
}

// FUNCTION: SADX 0x00486bb0
int FUN_00486bb0(struct Alr *param_1)
{
	return param_1->rank;
}

// STUB: SADX 0x00486bc0
void FUN_00486bc0(struct Alr *param_1, struct NJS_POINT3 *param_2)
{
}

// STUB: SADX 0x00486c00
void Alr_ConstraintLookAt(struct Alr *___this, const struct NJS_POINT3 *pos)
{
}

// STUB: SADX 0x00486c40
void Alr_checkCamera(struct Alr *___this)
{
}

// STUB: SADX 0x00486cd0
void FUN_00486cd0(struct Alr *param_1)
{
}

// FUNCTION: SADX 0x00486d50
void Alr_StopAim(struct Alr *___this)
{
	___this->flag |= 0x10;
}

// FUNCTION: SADX 0x00486e50
int FUN_00486e50(struct Alr *param_1)
{
	return param_1->use_path;
}

// FUNCTION: SADX 0x00486e60
int AlrEvent_Set(struct AlrEvent *___this, void (*func)(struct Alr *), int level)
{
	if (___this->level < level)
	{
		___this->level = level;
		___this->cnt = 0;
		___this->timer = 0;
		___this->event = func;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00486e90
void AlrEvent_SetForce(struct AlrEvent *___this, void (*func)(struct Alr *))
{
	___this->level++;
	___this->cnt = 0;
	___this->timer = 0;
	___this->event = func;
}

// STUB: SADX 0x00486eb0
int Alr_EventGoToAim(struct Alr *___this, const struct NJS_POINT3 *aim, float radius, int time)
{
	return (int)0;
}

// STUB: SADX 0x00486f90
int Alr_EventFaceToAim(struct Alr *___this, const struct NJS_POINT3 *aim, int time)
{
	return (int)0;
}

// STUB: SADX 0x00487050
int Alr_EventWithCommand(struct Alr *___this, int time, int command)
{
	return (int)0;
}

// STUB: SADX 0x00487110
long Alr_SetTaskCommunication(struct Alr *___this, signed char command, struct task *obj_tp, signed char obj_kind)
{
	return (long)0;
}

// FUNCTION: SADX 0x004873a0
void FUN_004873a0(void *param_1)
{
	*(int *)param_1 = 0;
	*(int *)((char *)param_1 + 4) = (int)FUN_007d21b0;
}

// FUNCTION: SADX 0x00487aa0
void *Alr_SetId(struct Alr *___this, int id)
{
	___this->flag |= 1;
	if (___this->flag & 2)
	{
		___this->flag = (___this->flag & 0xfffd) | 4;
	}
	else
	{
		___this->awp = NULL;
		___this->twp = NULL;
	}
	Alr_Clear(___this, id);
	return ___this;
}

// FUNCTION: SADX 0x00487b00
enum Event_Id Alr_GetCurrentEvent(struct Alr *___this)
{
	if (___this->event.event == Alr_useToy)
	{
		return (enum Event_Id)1;
	}
	if (___this->event.event == Alr_eatCoCo)
	{
		return (enum Event_Id)2;
	}
	if (___this->event.event == Alr_swing)
	{
		return (enum Event_Id)3;
	}
	if (___this->event.event == Alr_goCoCo)
	{
		return (enum Event_Id)4;
	}
	if (___this->event.event == Alr_pushBall)
	{
		return (enum Event_Id)5;
	}
	return (enum Event_Id)0;
}
