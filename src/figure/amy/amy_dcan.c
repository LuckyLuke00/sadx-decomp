#include "decls.h"
void ADC_Displayer(struct task *tp);
static void ADC_DrumCanExe(struct task *tp);
extern int DAT_05b9d838;
extern struct NJS_MODEL **DAT_060eeab4;
extern struct CCL_INFO colliinfo_dcan[1];
extern unsigned long DAT_05edc458;

// FUNCTION: SADX 0x005d5270
long ADC_PutDrumCan(struct NJS_POINT3 *pos)
{
	struct task *local_8;
	local_8 = CreateElementalTask(2, 6, ADC_DrumCanIni);
	if (local_8 != NULL)
	{
		local_8->twp->pos = *pos;
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x005d52c0
void ADC_DrumCanIni(struct task *tp)
{
	CCL_Init(tp, (struct CCL_INFO *)&colliinfo_dcan, 2, 4);
	tp->exec = ADC_DrumCanExe;
	tp->disp = ADC_Displayer;
}

// FUNCTION: SADX 0x005d52f0
void ADC_Displayer(struct task *tp)
{
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_amy);
		njPushMatrix(0);
		njTranslateV(0, (struct NJS_POINT3 *)((char *)tp->twp + 0x20));
		___dsDrawModel(*DAT_060eeab4);
		njPopMatrix(1);
	}
}

#pragma optimize("", off)
// STUB: SADX 0x005d5350
static void ADC_DrumCanExe(struct task *tp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x005d5510
long ADC_SetDrumCan()
{
	return (long)0;
}

// FUNCTION: SADX 0x005d55d0
struct task *ADC_DrumCanTouchCheck()
{
	return (struct task *)DAT_05edc458;
}

// FUNCTION: SADX 0x005d55e0
void ADC_ResetDrumCanTouchCheck()
{
	DAT_05edc458 = 0;
}
