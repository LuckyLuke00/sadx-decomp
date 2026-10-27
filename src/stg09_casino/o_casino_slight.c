#include "decls.h"
void DispMot3(struct task *tp);
void ExecCM(struct task *tp);
int FUN_004c39c0(...);
long CCL_Init(struct task *tp, struct CCL_INFO *info, long nbInfo, unsigned char id);
long CheckRangeOutWithR(struct task *tp, float fRange);
extern struct CCL_INFO coll_sl[1];
extern struct NJS_ACTION action_cas_obj_s_light_b[1];
extern struct NJS_ACTION action_cas_obj_s_light_g[1];

// FUNCTION: SADX 0x008783b0
void DispMot3(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 640010.0f) == 0)
	{
		if (dsCheckViewV(&var1->pos, 220.0f))
		{
			SetObjectTexture2(0xc);
			njPushMatrix(0);
			njTranslateV(0, &var1->pos);
			if (*(int *)((char *)var1 + 0x1c) != 0)
			{
				njRotateZ(0, (unsigned short)*(short *)((char *)var1 + 0x1c));
			}
			if (*(int *)((char *)var1 + 0x14) != 0)
			{
				njRotateX(0, (unsigned short)*(short *)((char *)var1 + 0x14));
			}
			if (*(int *)((char *)var1 + 0x18) != 0)
			{
				njRotateY(0, (unsigned short)*(short *)((char *)var1 + 0x18));
			}
			late_ActionClip((struct NJS_ACTION *)var1->timer.ptr, *(float *)((char *)var1 + 8), 4, 1.0f);
			njPopMatrix(1);
		}
	}
}

#pragma optimize("", off)
// STUB: SADX 0x00878480
void ExecCM(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00878510
void FUN_00878510(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	if (CheckRangeOutWithR(param_1, 640010.0f) == 0)
	{
		if (FUN_004c39c0(param_1) == 0)
		{
			CCL_Init(param_1, &coll_sl[0], 1, 4);
		}
		param_1->disp = DispMot3;
		param_1->exec = ExecCM;
		var1->counter.f = 0.0f;
		var1->timer.ptr = &action_cas_obj_s_light_b[0];
	}
}

// FUNCTION: SADX 0x00878570
void FUN_00878570(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	if (CheckRangeOutWithR(param_1, 640010.0f) == 0)
	{
		if (FUN_004c39c0(param_1) == 0)
		{
			CCL_Init(param_1, &coll_sl[0], 1, 4);
		}
		param_1->disp = DispMot3;
		param_1->exec = ExecCM;
		var1->counter.f = 0.0f;
		var1->timer.ptr = &action_cas_obj_s_light_g[0];
	}
}

// FUNCTION: SADX 0x008785d0
void FUN_008785d0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	if (CheckRangeOutWithR(param_1, 640010.0f) == 0)
	{
		if (FUN_004c39c0(param_1) == 0)
		{
			CCL_Init(param_1, &coll_sl[0], 1, 4);
		}
		param_1->disp = DispMot3;
		param_1->exec = ExecCM;
		var1->counter.f = 0.0f;
		var1->timer.ptr = &action_cas_obj_s_light_r[0];
	}
}

// FUNCTION: SADX 0x00878630
void FUN_00878630(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	if (CheckRangeOutWithR(param_1, 640010.0f) == 0)
	{
		if (FUN_004c39c0(param_1) == 0)
		{
			CCL_Init(param_1, &coll_sl[0], 1, 4);
		}
		param_1->disp = DispMot3;
		param_1->exec = ExecCM;
		var1->counter.f = 0.0f;
		var1->timer.ptr = &action_cas_obj_s_light_y[0];
	}
}
