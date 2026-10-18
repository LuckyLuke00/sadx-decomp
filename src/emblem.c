#include <math.h>
#include "decls.h"

#define FUN_004c38e0 PadReadOn

extern int DAT_05b3e05c;
extern int DAT_05cc3574;
extern char DAT_05cc3631;
extern unsigned char DAT_05bb00a9;
extern unsigned long DAT_05cccf84;
extern int DAT_05b9d838;
extern short *DAT_05baf368;
extern struct taskwk *DAT_05b42a7c;
extern char DAT_05ccca18;
extern char emblem_num[0x20];

void FUN_0055de60(struct _SC_NUMBERS *);
void Exec(struct task *);
void Disp(struct task *);

// FUNCTION: SADX 0x0049e0a0
void GetEmblem(struct SAVE_DATA *savedata, long num)
{
	long index = num / 8;
	long bit = 1 << (num % 8);

	*((char *)savedata + index + 0x240) |= bit;
	if (DAT_05b3e05c == 5 || DAT_05b3e05c == 10)
	{
		if (DAT_05cc3574 == 0)
		{
			DAT_05cc3631 = 1;
		}
		else
		{
			CreateSaveData();
		}
	}
	CheckEmbleAchievement(savedata);
}

// FUNCTION: SADX 0x0049e130
int FUN_0049e130(struct SAVE_DATA *savedata)
{
	int total = 0;
	unsigned char *ptr = (unsigned char *)savedata + 0x240;
	int i;
	unsigned char bits;

	for (i = 0x11; i > 0; i--)
	{
		bits = *ptr;
		while (bits)
		{
			if (bits & 1)
			{
				total++;
			}
			bits = bits >> 1;
		}
		ptr++;
	}
	return total;
}

// FUNCTION: SADX 0x0049e1a0
int FUN_0049e1a0(int num)
{
	if (num >= 5)
	{
		num--;
	}
	if (num >= 2)
	{
		num--;
	}
	return num + 0x6f;
}

// FUNCTION: SADX 0x0049e1d0
long GetEmblemNumberofStageClear(long a, long b, long c)
{
	long result = 0;
	long i;
	unsigned short bits;

	if (b == 0)
	{
		result = 100;
		result += c * 5;
	}
	else if (b <= 14)
	{
		for (i = 0; i < a + 1; i++)
		{
			if (a == i)
			{
				bits = 0xffff >> (15 - b);
				bits &= em_stage_table[i];
			}
			else
			{
				bits = em_stage_table[i];
			}
			while (bits)
			{
				if (bits & 1)
				{
					result++;
				}
				bits = bits >> 1;
			}
		}
		result--;
		result += c * 32;
	}
	else if (b > 0x22 && b <= 0x26)
	{
		result = b + 0x3d;
		result += c * 5;
	}
	else if (b == 0x27 || b == 0x28 || b == 0x29)
	{
		result = 0x6a;
		result += c;
	}
	return result;
}

// FUNCTION: SADX 0x0049e2f0
void GetEmblemofEnding(struct SAVE_DATA *savedata, long num)
{
	GetEmblem(savedata, FUN_0049e1a0(num));
}

// FUNCTION: SADX 0x0049e310
long CheckEmblemofEnding(struct SAVE_DATA *savedata, long num)
{
	return FUN_0049d410((int)savedata, FUN_0049e1a0(num));
}

// FUNCTION: SADX 0x0049e330
long CheckEmblemofStageClear(struct SAVE_DATA *savedata, long a, long b, long c)
{
	if (!DAT_05bb00a9)
	{
		return FUN_0049d410((int)savedata, GetEmblemNumberofStageClear(a, b, c));
	}
	else
	{
		return 1 << FUN_0049f2a0(b, c) & DAT_05cccf84;
	}
}

// FUNCTION: SADX 0x0049e830
void dispEmblem(struct task *tp)
{
	struct taskwk *twp = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_emblem);
	njPushMatrix(0);
	njTranslateV(0, &twp->pos);
	if (twp->ang.y)
	{
		njRotateY(0, twp->ang.y);
	}
	late_DrawObjectMesh((struct obj *)twp->counter.ptr, 0);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0049e8b0
void FUN_0049e8b0(struct task *tp)
{
	FreeTask(tp);
}

// FUNCTION: SADX 0x0049e8d0
struct task *FUN_0049e8d0(struct NJS_POINT3 *pos)
{
	struct task *tp = CreateElementalTask(2, 3, ObjectGetEmblem);

	if (tp)
	{
		tp->twp->mode = 0;
		tp->twp->pos.x = pos->x;
		tp->twp->pos.y = pos->y;
		tp->twp->pos.z = pos->z;
		if (DAT_05baf368[2] & 1)
		{
			PadReadOff();
		}
		return tp;
	}
	return 0;
}

// FUNCTION: SADX 0x0049e950
void ObjectGetEmblem(struct task *tp)
{
	struct taskwk *twp = tp->twp;

	twp->ang.x = 0;
	twp->ang.z = 0;
	twp->mode = 0;
	twp->counter.f = 0.0f;
	twp->wtimer = 0;
	twp->value.l = 0;
	twp->timer.f = 0.0f;
	twp->scl.x = 1.0f;
	if (DAT_05baf368[2] & 1)
	{
		PadReadOff();
	}
	*(float *)(emblem_num + 0xc) = ScreenRaitoX * 320.0;
	*(float *)(emblem_num + 0x10) = ScreenRaitoY * 370.0;
	*(float *)(emblem_num + 0x18) = ScreenRaitoX * 2.5;
	tp->exec = Exec;
	tp->disp = Disp;
}

// FUNCTION: SADX 0x0049ea10
void Exec(struct task *tp)
{
	struct taskwk *twp = tp->twp;
	float dx1;
	float zd;
	float dx;
	float dz1;

	if (CheckRangeOut(tp))
	{
		return;
	}
	if (DAT_05baf368[2] & 1)
	{
		PadReadOff();
	}
	switch (twp->mode)
	{
	case 0:
		twp->mode = 1;
		twp->wtimer = 0;
		twp->value.l = FUN_0049e130((struct SAVE_DATA *)&DAT_05ccca18);
		dsPlay_oneshot(12, 0, 0, 0);
		break;
	case 1:
		twp->wtimer++;
		if (twp->wtimer > 0x2d)
		{
			twp->wtimer = 0;
			twp->mode = 2;
		}
		dx1 = DAT_05b42a7c->pos.x - twp->pos.x;
		zd = DAT_05b42a7c->pos.z - twp->pos.z;
		twp->ang.y = (long)(atan2((double)dx1, (double)zd) * 65536.0 / 6.283184);
		*(long *)(emblem_num + 8) = twp->value.l;
		FUN_0055de60((struct _SC_NUMBERS *)emblem_num);
		break;
	case 2:
		twp->wtimer++;
		if (twp->wtimer == 12)
		{
			twp->wtimer = 0;
			*(long *)(emblem_num + 0x1c) = -1;
		}
		else if (twp->wtimer == 6)
		{
			*(long *)(emblem_num + 0x1c) = 0x3fffffff;
		}
		FUN_0055de60((struct _SC_NUMBERS *)emblem_num);
		twp->counter.f -= 0.02f;
		if (twp->counter.f <= -1.0)
		{
			twp->counter.f = -1.0f;
			twp->mode = 3;
			if (isCheckGGApper_Emblem())
			{
				InitGGMessage();
			}
			else
			{
				PadReadOn();
				FreeTask(tp);
			}
		}
		else
		{
			dx = DAT_05b42a7c->pos.x - twp->pos.x;
			dz1 = DAT_05b42a7c->pos.z - twp->pos.z;
			twp->ang.y = (long)(atan2((double)dx, (double)dz1) * 65536.0 / 6.283184);
			twp->scl.x += 0.08f;
		}
		break;
	case 3:
		if (!isGGMessageEnable())
		{
			PadReadOn();
			FreeTask(tp);
		}
		break;
	}
	Disp(tp);
}

// FUNCTION: SADX 0x0049ec90
void Disp(struct task *tp)
{
	struct taskwk *twp = tp->twp;
	float scale = twp->scl.x;

	___njSetTexture(&texlist_emblem);
	SaveConstantAttr();
	OnConstantAttr(0, 0x100000);
	SetMaterial(twp->counter.f, 0.0f, 0.0f, 0.0f);
	njPushMatrix(0);
	njTranslateV(0, &twp->pos);
	if (twp->ang.y)
	{
		njRotateY(0, twp->ang.y);
	}
	FUN_0067d2d0(0, scale, scale, scale);
	late_DrawObjectMesh(object_o_emblm_emblm, 0);
	njPopMatrix(1);
	ResetMaterial();
	LoadConstantAttr();
}
