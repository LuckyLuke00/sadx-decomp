#include "decls.h"
void FUN_005abbc0(struct task *param_1);
void FUN_005ac3c0(struct task *param_1);
void FUN_005ac3c0(struct task *param_1);
extern struct NJS_MODEL DAT_05a7fd5c;
void FUN_005ac3c0(struct task *param_1);
extern int DAT_05b9d838;
extern struct NJS_MODEL DAT_05a8005c;
extern struct NJS_MODEL DAT_05a80684;
extern struct CCL_INFO relbox_switch_colli_info[1];
extern void relbox_switch_exec(struct task *task_p);
extern void relbox_switch_draw(struct task *task_p);
extern void relbox_switch_end(struct task *task_p);
extern long CCL_Init(struct task *tp, struct CCL_INFO *info, long nbInfo, unsigned char id);
void FUN_005ac3c0(struct task *param_1);
extern int DAT_05edbde4;
extern int DAT_05edbde0;
extern void (*DAT_0099613c[4])(struct task *);

// FUNCTION: SADX 0x005aba60
long GetReleaseBoxOpenID()
{
	long local_8;

	if (DAT_05edbde4 != 0)
	{
		local_8 = *(int *)((char *)DAT_05edbde4 + 0x20);
		return (long)*(char *)((char *)local_8 + 3);
	}
	else
	{
		return -2;
	}
}

// FUNCTION: SADX 0x005aba90
void InitReleaseBox()
{
	DAT_05edbde4 = 0;
	DAT_05edbde0 = 0;
}

// STUB: SADX 0x005abab0
void ObjectReleaseBox(struct task *task_p)
{
}

// FUNCTION: SADX 0x005abbb0
struct task *IsReleaseBoxActive()
{
	return (struct task *)DAT_05edbde4;
}

// FUNCTION: SADX 0x005abbc0
void FUN_005abbc0(struct task *param_1)
{
	struct taskwk *local_8;
	local_8 = param_1->twp;
	if (FUN_004c39c0(param_1) == 0)
	{
		LoopTaskC(param_1);
	}
	DAT_0099613c[local_8->mode](param_1);
	relbox_end(param_1);
	EntryColliList(local_8);
}

// FUNCTION: SADX 0x005abc20
void relbox_exec_normal(struct task *task_p)
{
	CheckRangeOut(task_p);
}

// FUNCTION: SADX 0x005abd70
void relbox_end(struct task *task_p)
{
	struct taskwk *local_8;
	local_8 = task_p->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	SetRegularTexture();
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.y != 0)
	{
		njRotateY(0, (Uint16)local_8->ang.y);
	}
	if (local_8->mode == 0)
	{
		___dsDrawModel(&DAT_05a8005c);
	}
	else
	{
		if (local_8->counter.l != 0)
		{
			relbox_crush_draw(task_p);
		}
	}
	___dsDrawModel(&DAT_05a80684);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x005abe10
void relbox_exec(struct task *task_p)
{
	FUN_005ac3c0(task_p);
	DAT_05edbde4 = 0;
}

// FUNCTION: SADX 0x005abe30
void relbox_switch_init(struct task *task_p)
{
	struct taskwk *local_8;
	local_8 = task_p->twp;
	local_8->mode = 0;
	CCL_Init(task_p, relbox_switch_colli_info, 1, 4);
	task_p->disp = relbox_switch_draw;
	task_p->dest = relbox_switch_end;
	task_p->exec = relbox_switch_exec;
}

// STUB: SADX 0x005ac000
void relbox_player_hold(long player_id, struct NJS_POINT3 *pos_p)
{
}

// FUNCTION: SADX 0x005ac0e0
void relbox_switch_draw(struct task *task_p)
{
	struct taskwk *local_8;

	local_8 = task_p->twp;
	SetRegularTexture();
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	ds_DrawModelClip(&DAT_05a7fd5c, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x005ac130
void relbox_switch_end(struct task *task_p)
{
	struct taskwk *local_8;

	local_8 = task_p->ptp->twp;
	*(int *)((char *)local_8 + 0x30) = 0;
}

// FUNCTION: SADX 0x005ac150
void FUN_005ac150(int param_1)
{
	struct taskwk *local_8;
	local_8 = *(struct taskwk **)((char *)param_1 + 0x20);
	*(void **)((char *)local_8 + 8) = FUN_005ac400((int)&DAT_05a8005c);
	*(float *)((char *)local_8 + 0xc) = 255.0f;
	*(unsigned char *)((char *)local_8 + 1) = 1;
	*(unsigned short *)((char *)local_8 + 6) = 0x78;
}

// STUB: SADX 0x005ac1a0
void FUN_005ac1a0(struct task *param_1)
{
}

#pragma optimize("", off)
// STUB: SADX 0x005ac270
void relbox_crush_draw(struct task *task_p)
{
}
#pragma optimize("", on)
