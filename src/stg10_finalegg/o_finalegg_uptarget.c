#include "decls.h"
void dummytarget_make_crushdata(struct dummy_crushwk **crushwk_pp, struct obj *obj);
extern void dummytarget_init(struct task *task_p);
extern void FUN_007d21b0(void *param_1);
extern long CCL_Init(struct task *tp, struct CCL_INFO *info, long nbInfo, unsigned char id);
extern int FUN_00551570(int param_1);
extern struct task *CreateChildTask(unsigned short im, void (*exec)(struct task *), struct task *tp);
extern struct CCL_INFO uptarget_colli_info[1];
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x00894790
void target_silenang_set(struct task *task_p)
{
	task_p->twp->value.l = (task_p->twp->value.l + 0x400) & 0xffff;
}

// FUNCTION: SADX 0x00894900
void target_man_exec_nop(struct task *task_p)
{
	struct taskwk *var1 = task_p->twp;
	if (CheckRangeOut(task_p) == 0)
	{
		if (isMissionClearDisp() == 0)
		{
			if ((short)var1->wtimer > 0)
			{
				var1->wtimer--;
				if (var1->wtimer == 0)
				{
					SetFinishAction();
				}
			}
		}
		LoopTaskC(task_p);
	}
}

// FUNCTION: SADX 0x00894950
void target_man_end(struct task *task_p)
{
	dsStop_num(0x11c);
}

// STUB: SADX 0x00894960
void target_draw_wheel(struct task *task_p)
{
}

// STUB: SADX 0x00894980
void target_end(struct task *task_p)
{
}

// STUB: SADX 0x008949a0
void uptarget_exec_wait(struct task *task_p)
{
}

// STUB: SADX 0x00894a20
void uptarget_exec_open(struct task *task_p)
{
}

// STUB: SADX 0x00894a60
void uptarget_exec_up(struct task *task_p)
{
}

// FUNCTION: SADX 0x00894a80
void uptarget_draw_scale_set(struct task *task_p)
{
	FUN_0067d2d0(0, 1.0, 1.0, task_p->twp->scl.z);
}

// STUB: SADX 0x00894ab0
void uptarget_draw_trans_set(struct task *task_p)
{
}

// STUB: SADX 0x00894b60
void dummytarget_exec_crush(struct task *task_p)
{
}

// STUB: SADX 0x00894e90
void dummytarget_draw_crush(struct task *task_p)
{
}

// FUNCTION: SADX 0x00894ef0
void dummytarget_end(struct task *task_p)
{
	struct taskwk *var1 = task_p->ptp->twp;
	struct taskwk *var2 = task_p->twp;

	if (var2->counter.ptr != 0)
	{
		Free(var2->counter.ptr);
	}

	var1->timer.ptr = 0;
}

// STUB: SADX 0x00894f20
void dummytarget_make_crushdata(struct dummy_crushwk **crushwk_pp, struct obj *obj)
{
}

// FUNCTION: SADX 0x008950f0
void ObjectFinalEggUptargetSonic(struct task *task_p)
{
	CCL_Init(task_p, (struct CCL_INFO *)&uptarget_colli_info, 1, 4);
	task_p->exec = uptarget_sonic_draw;
	task_p->disp = uptarget_sonic_draw;
	task_p->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// STUB: SADX 0x008952a0
void FUN_008952a0(struct obj *param_1, struct obj *param_2, int param_3, int param_4)
{
}

// STUB: SADX 0x00895430
void target_draw_object(struct task *task_p, struct obj *obj, int *index)
{
}

// FUNCTION: SADX 0x00895750
void target_exec(struct task *task_p)
{
	task_p->twp->value.l = (task_p->twp->value.l + 0x400) & 0xffff;
	LoopTaskC(task_p);
	target_draw(task_p);
}

// STUB: SADX 0x00895890
void ObjectFinalEggUptarget(struct task *task_p)
{
}

// FUNCTION: SADX 0x00895990
void target_init(struct task *task_p)
{
	struct taskwk *var1;
	int local_8;
	var1 = task_p->twp;
	var1->smode = 0;
	var1->btimer = 1;
	local_8 = FUN_00551570((int)task_p->ptp);
	if (local_8 != 0)
	{
		var1->mode = 4;
	}
	else
	{
		var1->mode = 5;
		var1->timer.l = (int)CreateChildTask(2, dummytarget_init, task_p);
	}
	task_p->exec = target_exec;
	task_p->disp = target_draw;
	task_p->dest = target_end;
}

// STUB: SADX 0x008959f0
void ObjectFinalEggTarget(struct task *task_p)
{
}
