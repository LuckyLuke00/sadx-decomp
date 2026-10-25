#include "decls.h"
extern struct obj *egm3_object_list[];
extern struct anywk *DAT_060ba008;
extern float DAT_060ba100[16];
extern struct NJS_MOTION *egm3_motion_list[8];
extern int DAT_060e3ac8;
extern int DAT_060e3ae0;
extern void (*egm3_exec[5])(struct task *);
extern void egm3CalcObjMatrix(struct obj *object, float *matbuf);
extern void EV_Egm3Draw(struct task *tp);
extern struct obj *egm3_object_list[1];
extern void FUN_0067d830(float *, float, float, float);

// STUB: SADX 0x00903090
void EV_EggViperKesu()
{
}

// FUNCTION: SADX 0x00903100
void EV_EggViperEggmanToujou()
{
	*(char *)DAT_060ba008->work.ptr[8] = 2;
}

// FUNCTION: SADX 0x00903110
void EV_EggViperEggmanShaberu()
{
	DAT_060e3ac8 |= 1;
}

// FUNCTION: SADX 0x00903120
void EV_EggViperEggmanShaberiYame()
{
	DAT_060e3ac8 |= 2;
}

// FUNCTION: SADX 0x00903130
void EV_EggViperEggmanHikkomu()
{
	*(char *)(DAT_060ba008->work.ptr[8]) = 3;
}

// STUB: SADX 0x00903140
void EV_EggViperJoushou()
{
}

// STUB: SADX 0x00903490
void EV_EggmanDraw(struct task *tp)
{
}

// FUNCTION: SADX 0x009035a0
void EV_Egm3(struct task *tp)
{
	struct taskwk *var1;
	int var2;

	var1 = tp->twp;
	var2 = (int)var1->mode;
	if (var2 != DAT_060e3ae0)
	{
		DAT_060e3ae0 = var2;
		var1->smode = 0;
	}
	egm3_exec[var2](tp);
	njPushMatrix(0);
	njUnitMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	if (var1->ang.y != 0)
	{
		njRotateY(0, (unsigned short)var1->ang.y);
	}
	if (var1->ang.x != 0)
	{
		njRotateX(0, (unsigned short)var1->ang.x);
	}
	if (var1->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)var1->ang.z);
	}
	egm3CalcObjMatrix(egm3_object_list[0], DAT_060ba100);
	njPopMatrix(1);
	EV_Egm3Draw(tp);
}

// STUB: SADX 0x00903660
void EV_Egm3Init(struct task *tp)
{
}

// FUNCTION: SADX 0x009036c0
void EV_Egm3EggmanHikkomu(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct anywk *var2 = tp->awp;
	int var3 = var1->smode;
	switch (var3)
	{
		case 0:
			*(void **)((char *)var2 + 0x6c) = egm3_motion_list[2];
			*(int *)((char *)var2 + 0x70) = 0;
			var1->smode = 1;
		case 1:
			DAT_060e3ac8 |= 4;
			var1->smode = 2;
		case 2:
			if ((DAT_060e3ac8 & 8) != 0)
			{
				DAT_060e3ac8 &= ~8;
				var1->smode = 3;
				return;
			}
			break;
		case 3:
			*(float *)((char *)var2 + 0x7c) = 1.0f;
			var1->smode = 4;
		case 4:
			*(float *)((char *)var2 + 0x78) -= *(float *)((char *)var2 + 0x7c);
			if (*(float *)((char *)var2 + 0x78) <= 0.0f)
			{
				DAT_060e3ac8 |= 0x20;
				*(float *)((char *)var2 + 0x78) = 0.0f;
				var1->mode = 1;
				return;
			}
			break;
	}
}

// STUB: SADX 0x00903a20
void EV_Egm3EggmanToujou(struct task *tp)
{
}
