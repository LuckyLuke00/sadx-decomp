#include "decls.h"
void DestroyTask(struct task *tp);
void late_ReleaseTexture(struct NJS_TEXLIST *tl);
extern short DAT_05b9d744;
void DisplayBg(struct task *tp);
extern struct NJS_TEXLIST texlist_highway_car;
static void ExecuteBg(struct task *tp);
static void DisplayBg(struct task *tp);
static void DestructBg(struct task *tp);

// FUNCTION: SADX 0x00819ca0
void Rd_HighwayE(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (var1->counter.ptr != 0)
	{
		struct task *var2 = (struct task *)var1->counter.ptr;

		if (var2->twp != 0)
		{
			var2->twp->counter.ptr = 0;
			DestroyTask(var2);
		}
	}

	if (var1->mode == 3)
	{
		late_ReleaseTexture(&texlist_highway_car);
	}
}

// FUNCTION: SADX 0x00819ce0
void subRd_Destruct(struct task *tp)
{
	if (tp->twp->counter.ptr != NULL)
	{
		*(int *)((char *)*(void **)((char *)tp->twp->counter.ptr + 0x20) + 8) = 0;
	}
}

// STUB: SADX 0x00819d00
void FUN_00819d00(struct task *tp)
{
}

// STUB: SADX 0x00819f30
void FUN_00819f30()
{
}

// STUB: SADX 0x0081a250
static void DestructBg(struct task *tp)
{
}

// STUB: SADX 0x0081a3b0
static void DisplayBg(struct task *tp)
{
}

// FUNCTION: SADX 0x0081a840
void Rd_Highway(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->counter.l == 0)
	{
		struct task *var2 = CreateElementalTask(2, 0, subRd_Highway);
		var1->counter.l = (long)var2;
		var2->twp->counter.l = (long)tp;
		tp->dest = Rd_HighwayE;
	}
	if ((char)DAT_05b9d744 == 2 && var1->mode != 3)
	{
		var1->mode = 3;
		ADX_Close();
		texLoadTexturePvmFile("HIGHWAY_CAR", &texlist_highway_car);
	}
}

// STUB: SADX 0x0081a8a0
static void ExecuteBg(struct task *tp)
{
}

// FUNCTION: SADX 0x0081a920
void Bg_Highway(struct task *tp)
{
	tp->exec = ExecuteBg;
	tp->disp = DisplayBg;
	tp->dest = DestructBg;
}
