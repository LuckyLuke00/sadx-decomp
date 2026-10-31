#include "decls.h"

// GLOBAL: SADX 0x026dac20
static struct CCL_INFO ccinfo[9];

static void ObjectMain(struct task *tp);
static void ObjectDisplay(struct task *tp);
extern void ObjectClosed(struct task *tp);
extern struct obj object_sscasinosikake_hnakagen_hnakagen[];
extern struct obj object_sscasinosikake_hnakagen_2_hnakagen[];
extern struct NJS_ACTION action_sscasinosikake_hnakagen[];
extern short DAT_05b9d744;
extern int DAT_05b9d838;
extern unsigned char DAT_05bafb86;
extern unsigned char DAT_05bafbc2;
extern unsigned char DAT_05bafc02;
extern unsigned char DAT_05bafc41;
extern unsigned char DAT_05bafcc1;
extern unsigned char DAT_05bafb81;
extern unsigned char DAT_05bafbc1;
extern unsigned char DAT_05bafc01;
extern unsigned char DAT_05bafc40;
extern unsigned char DAT_05bafc80;
extern unsigned char DAT_05bafcc0;
extern int DAT_060b56a0;

// FUNCTION: SADX 0x00681150
int getSsHotelPoolDoorMode()
{
	return DAT_060b56a0;
}

// FUNCTION: SADX 0x00681160
long SeqCheckFront()
{
	long var1 = GetPlayerCharacterName(0);
	switch (var1)
	{
		case 0:
			return DAT_05bafb81;
		case 2:
			return DAT_05bafbc1;
		case 3:
			return DAT_05bafc01;
		case 5:
			return DAT_05bafc40;
		case 6:
			return DAT_05bafc80;
		case 7:
			return DAT_05bafcc0;
		default:
			return 0;
	}
}

// FUNCTION: SADX 0x006811d0
long SeqCheckBack()
{
	long var1;

	var1 = GetPlayerCharacterName(0);
	switch (var1)
	{
		case 0:
			return DAT_05bafb86;
		case 2:
			return DAT_05bafbc2;
		case 3:
			return DAT_05bafc02;
		case 5:
			return DAT_05bafc41;
		case 7:
			return DAT_05bafcc1;
		default:
			return 0;
	}
}

// STUB: SADX 0x00681240
long SeqCheckPool()
{
	return (long)0;
}

// FUNCTION: SADX 0x00681290
static void ObjectDisplay(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		if (DAT_05b9d744 == 1 || DAT_05b9d744 == 3)
		{
			action_sscasinosikake_hnakagen[0].object = &object_sscasinosikake_hnakagen_2_hnakagen[0];
		}
		else
		{
			if (var1->timer.l == (long)SeqCheckPool && checkInSsHodel() == 0)
			{
				action_sscasinosikake_hnakagen[0].object = &object_sscasinosikake_hnakagen_2_hnakagen[0];
			}
			else
			{
				action_sscasinosikake_hnakagen[0].object = &object_sscasinosikake_hnakagen_hnakagen[0];
			}
		}
		SetObjectTexture();
		if (var1->timer.l == (long)SeqCheckPool && checkInSsHodel() == 0)
		{
			late_ActionClipEx(&action_sscasinosikake_hnakagen[0], var1->counter.f, 0, 1.0f);
			njPopMatrix(1);
		}
		else
		{
			SaveConstantAttr();
			OnConstantAttr(0, 0x2000000);
			late_ActionClipEx(&action_sscasinosikake_hnakagen[0], var1->counter.f, 0, 1.0f);
			LoadConstantAttr();
			njPopMatrix(1);
		}
	}
}

// STUB: SADX 0x006814b0
void ObjectColliSet2(struct taskwk *twp)
{
}

// STUB: SADX 0x006816d0
static void ObjectMain(struct task *tp)
{
}

// STUB: SADX 0x00681770
void ObjectClosed(struct task *tp)
{
}

// STUB: SADX 0x006817d0
void ObjectWaitKeyblock(struct task *tp)
{
}

// FUNCTION: SADX 0x00681880
void ObjectSSHotelfront(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &ccinfo[0], 9, 4);
		}
		var1->btimer = 0;
		var1->counter.f = 0.0f;
		var1->timer.ptr = (void *)SeqCheckFront;
		if (SeqCheckFront() != 0)
		{
			tp->exec = ObjectMain;
		}
		else
		{
			tp->exec = ObjectClosed;
		}
		tp->disp = ObjectDisplay;
		tp->dest = ExplosionRockDestructor;
	}
}

// STUB: SADX 0x00681900
void ObjectSSHotelback(struct task *tp)
{
}
