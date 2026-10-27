#include "decls.h"
void SetPathWork();
struct pathtag;
struct pathinfo;
struct pathtbl;
void CalcPNNPntParam(struct pathtag *tag, struct pathinfo *pi, long pnmb, struct pathtbl *pt);
extern short DAT_05b9d724;
extern short DAT_05b9d744;

// FUNCTION: SADX 0x0056fd90
unsigned long InitPathWork()
{
	struct task *local_8g;
	struct taskwk *local_cg;

	local_8g = CreateElementalTask(2, 2, ManagePathWork);
	if (local_8g != 0)
	{
		local_cg = local_8g->twp;
		*(unsigned short *)((char *)local_cg + 0xc) = (DAT_05b9d724 << 8) | DAT_05b9d744;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x0056fde0
void ManagePathWork(struct task *tp)
{
	struct taskwk *local_8g = tp->twp;
	unsigned short local_cg;
	switch (local_8g->mode)
	{
	case 0:
		SetPathWork();
		local_8g->mode = 1;
		break;
	case 1:
		local_cg = (DAT_05b9d724 << 8) | DAT_05b9d744;
		if (*(short *)((char *)local_8g + 0xc) != local_cg)
		{
			SetPathWork();
			*(short *)((char *)local_8g + 0xc) = local_cg;
		}
		break;
	}
}

// STUB: SADX 0x0056fe50
void SetPathWork()
{
}

// STUB: SADX 0x00570230
void CalcPNNPntParam(struct pathtag *tag, struct pathinfo *pi, long pnmb, struct pathtbl *pt)
{
}

// STUB: SADX 0x00570410
long SCPathOnposToPntnmb(struct pathtag *tag, float onpos, unsigned long *pntnmb)
{
	return (long)0;
}

// STUB: SADX 0x00570480
long SCPathPntnmbToOnpos(struct pathtag *tag, unsigned long pntnmb, float *onpos)
{
	return (long)0;
}
