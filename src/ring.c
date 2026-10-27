#include "decls.h"
void RingNumRunning(float xpos, float ypos, float zpos, int num);
extern struct NJS_TEXLIST texlist_ring;
extern struct NJS_TEXANIM anim_ring[1];
extern int DAT_05b9d838;
extern float DAT_05b3df40;
extern int DAT_05b3df4c;
extern struct NJS_MODEL DAT_05a7b20c;
extern unsigned long DAT_05edbcfc;

// FUNCTION: SADX 0x005a6b00
void InitRing()
{
	DAT_05edbcfc = 0;
}

// FUNCTION: SADX 0x005a7030
void RingDraw(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (dsCheckViewV(&local_8->pos, 20.0f) == 0)
	{
		return;
	}
	if (local_8->btimer < 0x32)
	{
		if (*(float *)((char *)local_8 + 0x30) != -1000000.0f)
		{
			StaticShadow(local_8, *(float *)((char *)local_8 + 0x30));
		}
	}
	SaveConstantAttr();
	OffConstantAttr(0, 0x80000);
	SetRegularTexture();
	njPushMatrix(0);
	FUN_0067d830(0, local_8->pos.x, local_8->pos.y, local_8->pos.z);
	if (*(int *)((char *)local_8 + 0x18) != 0)
	{
		njRotateY(0, *(unsigned short *)((char *)local_8 + 0x18));
	}
	if (DAT_05b3df4c != 0)
	{
		DAT_05b3df40 = 32.0f;
		late_DrawModel(&DAT_05a7b20c, 1);
		DAT_05b3df40 = 0.0f;
	}
	else
	{
		___dsDrawModel(&DAT_05a7b20c);
	}
	njPopMatrix(1);
	LoadConstantAttr();
}

// FUNCTION: SADX 0x005a7160
void RingDoneDisplayer(struct task *tp)
{
	RingDone(tp->twp);
}

// STUB: SADX 0x005a73c0
void DamegeRingScatter(unsigned char pno)
{
}

// FUNCTION: SADX 0x005a7d60
void dispTobitiri0(struct task *tp)
{
	struct NJS_POINT3 v;
	struct anywk *local_18;
	local_18 = tp->awp;
	v.x = 0.0;
	v.y = 3.44;
	v.z = 0.0;
	njCalcVector(0, &v, &v);
	RingDrawShadow(tp, *(float *)local_18, v.x, v.z);
}

// STUB: SADX 0x005a7dd0
void dispTobitiri1(struct task *tp)
{
}

// FUNCTION: SADX 0x005a7e10
void FUN_005a7e10(struct NJS_TEXLIST *param_1, int param_2)
{
	*(struct NJS_TEXLIST **)((char *)param_2 + 0x18) = &texlist_ring;
	*(struct NJS_TEXANIM **)((char *)param_2 + 0x1c) = (struct NJS_TEXANIM *)&anim_ring;
	*(float *)((char *)param_2 + 0xc) = 1.0f;
	*(float *)((char *)param_2 + 0x10) = 1.0f;
	*(float *)((char *)param_2 + 8) = 0.0f;
	*(float *)((char *)param_2 + 4) = 0.0f;
	*(float *)param_2 = 0.0f;
}

#pragma optimize("", off)
// STUB: SADX 0x005a7e50
void RingDrawShadow(struct task *tp, float tempy, float pushx, float pushz)
{
}
#pragma optimize("", on)

// STUB: SADX 0x005a82d0
void RingNumRunning(float xpos, float ypos, float zpos, int num)
{
}
