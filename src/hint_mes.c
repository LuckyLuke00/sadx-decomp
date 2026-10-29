#include "decls.h"
void FUN_0056dc40(struct MSGC *param_1);
void FUN_0056db40(struct MSGC *param_1, long param_2, long param_3);
extern void disp_message_get(struct MSGC *msgc_p, char *message_p);
extern void disp_message_after(struct MSGC *msgc_p);
void FUN_0056dc40(struct MSGC *param_1);
void FUN_0056db40(struct MSGC *param_1, long param_2, long param_3);
extern int DAT_05b9d838;
void FUN_0056dc40(struct MSGC *param_1);
void FUN_0056db40(struct MSGC *param_1, long param_2, long param_3);
void *field_message_init(struct HintMessageMemory *data_p, const short *code_p, const void *message_p, enum mesdata_type mes_data_type);
void disp_message_get(struct MSGC *msgc_p, char *message_p);
void disp_message_after(struct MSGC *msgc_p);
void FUN_0056dc40(struct MSGC *param_1);
void FUN_0056db40(struct MSGC *param_1, long param_2, long param_3);
extern int DAT_05ccde24;
extern int DAT_05ccde30;
extern int DAT_05ccde84;
void FUN_0056dc40(struct MSGC *param_1);
void FUN_0056db40(struct MSGC *param_1, long param_2, long param_3);
extern unsigned char DAT_05bafb00[];
void FUN_0056d4a0(long param_1);
extern const struct HintMessageTable *DAT_05ccde7c;
extern const struct NpcMessageTable *DAT_05ccde80;
extern int DAT_05ccde78;
extern int DAT_05ccde20;
extern int DAT_05ccde88;
extern signed char *DAT_05ccde2c;
extern long DAT_05ccde28;

// FUNCTION: SADX 0x0056d170
void HintMainMessages(const char * *message)
{
	field_msg_create_man((void (*)(void *))disp_main_message, (void *)message, 0);
}

// FUNCTION: SADX 0x0056d190
void HintMainMessagesTime(const char * *message, long time)
{
	DAT_05ccde28 = time;
	field_msg_create_man((void (*)(void *))disp_main_messageTime, (void *)message, 0);
	return;
}

// FUNCTION: SADX 0x0056d1b0
void HintRegistStatusPointer(signed char *status_p)
{
	DAT_05ccde2c = status_p;
}

// FUNCTION: SADX 0x0056d1c0
void NpcMessageDataInit(const struct NpcMessageTable *table)
{
	DAT_05ccde80 = table;
	DAT_05ccde78 = 0;
	DAT_05ccde20 = 0;
	DAT_05ccde88 = 0;
}

// FUNCTION: SADX 0x0056d1f0
void HintMessageDataInit(const struct HintMessageTable *table)
{
	DAT_05ccde7c = table;
	DAT_05ccde78 = 0;
	DAT_05ccde20 = 0;
	DAT_05ccde88 = 0;
}

// STUB: SADX 0x0056d220
long HintMessageInit(const long number, struct HintMessageMemory *data_p)
{
	return (long)0;
}

// FUNCTION: SADX 0x0056d3a0
void HintMessageStart(const struct HintMessageMemory *data_p)
{
	long local_8;

	if (data_p->adx_index > -1)
	{
		Serif_Play(data_p->adx_index);
		local_8 = 1;
	}
	else
	{
		local_8 = 0;
	}
	if (data_p->message_p != 0)
	{
		field_msg_create_man((void (*)(void *))disp_message_wait, (void *)data_p->message_p, local_8);
	}
	FUN_0056d4a0(data_p->flag_index);
}

// FUNCTION: SADX 0x0056d400
void NpcMessageStart(const struct NpcMessageMemory *data_p)
{
	if (*(int *)((char *)data_p + 0) != 0)
	{
		field_msg_create_man((void (*)(void *))disp_npc_message_wait, *(void **)((char *)data_p + 0), 0);
	}
	FUN_0056d4a0(*(long *)((char *)data_p + 4));
}

// FUNCTION: SADX 0x0056d440
long HintMessageCheck()
{
	int iVar1;
	iVar1 = FUN_004f6400();
	if (iVar1 == 5)
	{
		Serif_Stop();
		return DAT_05ccde78;
	}
	if (iVar1 == 0)
	{
		return DAT_05ccde78;
	}
	return 1;
}

// FUNCTION: SADX 0x0056d480
void HintMessageStop()
{
	DAT_05ccde88 = 1;
	Serif_Stop();
}

// FUNCTION: SADX 0x0056d4a0
void FUN_0056d4a0(long param_1)
{
	if (param_1 > -1)
	{
		if ((param_1 & 0x4000) != 0)
		{
			DAT_05bafb00[param_1 & 0xffffbfff] = 1;
		}
		else
		{
			DAT_05bafb00[param_1] = 0;
		}
	}
}

// STUB: SADX 0x0056d4e0
void *field_message_init(struct HintMessageMemory *data_p, const short *code_p, const void *message_p, enum mesdata_type mes_data_type)
{
	return (void *)0;
}

// STUB: SADX 0x0056d680
int FUN_0056d680(int param_1, int *param_2, int *param_3, int param_4)
{
	return (int)0;
}

// FUNCTION: SADX 0x0056d700
int FUN_0056d700(short *param_1)
{
	int local_8;

	do
	{
		local_8 = (short)*param_1;
		if ((local_8 & 0x4000) != 0)
		{
			if (EV_CheckExec(local_8 & 0xffffbfff) != 0)
			{
				return 1;
			}
		}
		else
		{
			if (EV_CheckExec(local_8) == 0)
			{
				return 1;
			}
		}
		param_1++;
	}
	while ((short)*param_1 >= 0);
	return 0;
}

// FUNCTION: SADX 0x0056d770
int FUN_0056d770(short *param_1)
{
	int local_8;
	do
	{
		local_8 = *param_1;
		if (local_8 & 0x4000)
		{
			if (DAT_05bafb00[local_8 & 0xffffbfff])
			{
				return 1;
			}
		}
		else
		{
			if (!DAT_05bafb00[local_8])
			{
				return 1;
			}
		}
		param_1++;
	} while (*param_1 >= 0);
	return 0;
}

// FUNCTION: SADX 0x0056d7e0
int FUN_0056d7e0(short param_1)
{
	int local_8;
	local_8 = 1 << GetPlayerNumber();
	return (int)param_1 & local_8;
}

// FUNCTION: SADX 0x0056d800
short * FUN_0056d800(short *param_1)
{
	while (*param_1 != -1)
	{
		if (*param_1 == -2)
		{
			return param_1;
		}
		param_1 = param_1 + 1;
	}
	return 0;
}

// STUB: SADX 0x0056d830
int * FUN_0056d830(int *param_1, int param_2)
{
	return (int *)0;
}

// STUB: SADX 0x0056d8b0
void disp_message_wait(const struct HintMessageString *message_p)
{
}

// STUB: SADX 0x0056d970
void disp_message_get(struct MSGC *msgc_p, char *message_p)
{
}

#pragma optimize("", off)
// STUB: SADX 0x0056da30
void field_msg_front_fade(struct MSGC *msgc_p, long time, long rate)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0056daf0
void field_msg_back_fade(struct MSGC *msgc_p, long time, long rate)
{
	*(unsigned char *)((char *)msgc_p + 0x23) = 0;
	*(unsigned char *)((char *)msgc_p + 0x1f) = 0;
	FUN_0056db40(msgc_p, 0xa, 0xc);
	*(unsigned char *)((char *)msgc_p + 0x23) = 0x80;
	field_msg_front_fade(msgc_p, 0xa, 0x18);
	*(unsigned char *)((char *)msgc_p + 0x1f) = 0xff;
}

// FUNCTION: SADX 0x0056dc20
void disp_message_after(struct MSGC *msgc_p)
{
	if (DAT_05ccde84 != 0)
	{
		FUN_0056dc40(msgc_p);
	}
	PauseEnable();
}

#pragma optimize("", off)
// STUB: SADX 0x0056dc40
void FUN_0056dc40(struct MSGC *param_1)
{
}
#pragma optimize("", on)

// STUB: SADX 0x0056dcc0
void disp_message_draw_wait_button(struct MSGC *msgc_p)
{
}

// STUB: SADX 0x0056e0d0
void disp_main_message(char * *message)
{
}

// STUB: SADX 0x0056e170
void disp_main_messageTime(char * *message)
{
}

#pragma optimize("", off)
// STUB: SADX 0x0056e210
void field_msg_create_man(void (*thread_func)(void *), void *arg_p, long adx_use)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0056e2b0
void field_msg_wait_message_loop(struct task *task_p)
{
	struct anywk *local_8g;
	struct thread *local_cg;

	local_8g = task_p->awp;
	if ((local_8g->work.ul[3] != 0) && (DAT_05b9d838 == 0))
	{
		DAT_05ccde88 = 0;
		local_cg = TH_Create(local_8g->work.ptr[1], local_8g->work.ptr[2], 0);
		TH_SetDest(local_cg, field_msg_thread_end);
		DestroyTask(task_p);
	}
	if (DAT_05ccde78 == 0)
	{
		if (local_8g->work.ptr[0] != 0)
		{
			DAT_05ccde24 = (int)local_8g->work.ptr[0];
		}
		DAT_05ccde20 = (int)local_8g->work.ptr[4];
		DAT_05ccde78 = 1;
		local_8g->work.ul[3] = 1;
	}
}

// FUNCTION: SADX 0x0056e360
void field_msg_thread_end()
{
	if (DAT_05ccde84 != 0)
	{
		FUN_004c3310((int *)&DAT_05ccde30);
		DAT_05ccde84 = 0;
	}
	DAT_05ccde78 = 0;
	if (DAT_05ccde24 != 0)
	{
		*(char *)DAT_05ccde24 = 0;
		DAT_05ccde24 = 0;
	}
}
