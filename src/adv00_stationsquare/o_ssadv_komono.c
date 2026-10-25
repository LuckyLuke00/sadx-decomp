#include "decls.h"
extern struct obj object_bin_bin_bin;
extern struct CCL_INFO object_komono_bin_info;
extern struct obj object_ssobj_isub_isub[1];
extern struct CCL_INFO object_komono_isub_info[1];
extern struct obj object_ssobj_isua_isua[1];
extern struct CCL_INFO object_komono_isua_info[1];
extern struct obj object_ssobj_exit_exit[1];
extern struct CCL_INFO object_komono_exit_info[1];

// STUB: SADX 0x0068dd30
void ObjectSsadvKomonoKeikoto(struct task *tp)
{
}

// STUB: SADX 0x0068dd60
void ObjectSsadvKomonoRoomlight(struct task *tp)
{
}

// FUNCTION: SADX 0x0068dd90
void Object_Ssadv_KomonoExec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			EntryColliList(var1);
		}
		Object_Ssadv_KomonoDraw(tp);
	}
}

// STUB: SADX 0x0068ddd0
void ObjectSsadvKomonoBin(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		tp->twp->counter.l = (long)&(*(struct obj (*)[1])&object_bin_bin_bin)[0];
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &(*(struct CCL_INFO (*)[1])&object_komono_bin_info)[0], 1, 4);
		}
		tp->disp = Object_Ssadv_KomonoDraw;
		tp->exec = Object_Ssadv_KomonoExec;
	}
}

// FUNCTION: SADX 0x0068de20
void ObjectSsadvKomonoExit(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		tp->twp->counter.l = (long)&object_ssobj_exit_exit[0];
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &object_komono_exit_info[0], 1, 4);
		}
		tp->disp = Object_Ssadv_KomonoDraw;
		tp->exec = Object_Ssadv_KomonoExec;
	}
}

// FUNCTION: SADX 0x0068de70
void ObjectSsadvKomonoIsua(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		*(int *)((char *)tp->twp + 8) = (int)object_ssobj_isua_isua;
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, object_komono_isua_info, 2, 4);
		}
		tp->disp = Object_Ssadv_KomonoDraw;
		tp->exec = Object_Ssadv_KomonoExec;
	}
}

// FUNCTION: SADX 0x0068dec0
void ObjectSsadvKomonoIsub(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		*(int *)((char *)tp->twp + 8) = (int)object_ssobj_isub_isub;
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, object_komono_isub_info, 2, 4);
		}
		tp->disp = Object_Ssadv_KomonoDraw;
		tp->exec = Object_Ssadv_KomonoExec;
	}
}
