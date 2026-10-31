#include "decls.h"
extern void chaos_gdcontrol(struct task *tp);
extern int DAT_05b3df4c;
extern struct NJS_TEXLIST texlist_chaos7_0breath;
extern void ADX_Close();
extern void le_loadLight(int stg, int act);
extern void late_ReleaseTexture(struct NJS_TEXLIST *tl);
extern void texLoadTexturePvmFile(char *fname, struct NJS_TEXLIST *ptlo);
extern struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
static void chaos_gdcontrol(struct task *tp);

// FUNCTION: SADX 0x006fb120
void SetTableBg_chaos7(int c_level)
{
	unsigned int local_8 = (unsigned char)DAT_05b9d744 * 4;
	DAT_05b3e040 = (*(struct NJS_ARGB **)((char *)pFogTable_Chaos07 + local_8))[c_level];
	DAT_05b3e080 = (*(struct NJS_POINT2 **)((char *)pClipSky_Chaos07 + local_8))[c_level];
	DAT_05b3e080.y -= 1000.0;
	DAT_05b3e050 = (*(struct NJS_POINT2 **)((char *)pClipMap_Chaos07 + local_8))[c_level];
	DAT_05b3e074 = (*(struct NJS_POINT3 **)((char *)pScale_Chaos07 + local_8))[c_level];
}

// FUNCTION: SADX 0x006fb1d0
void ChangeSuperSonic(struct task *tp)
{
	if (++tp->twp->timer.l > 1)
	{
		SetInputP(0, 0x2e);
		DestroyTask(tp);
	}
}

// STUB: SADX 0x006fb200
static void chaos_gdcontrol(struct task *tp)
{
}

// FUNCTION: SADX 0x006fb370
void rdChaos7ChangeBgm()
{
	struct task *var1;

	ADX_Close();
	le_loadLight(0x13, 1);
	late_ReleaseTexture(&texlist_chaos7_0breath);
	texLoadTexturePvmFile("CHAOS7_0BREATH2ND", &texlist_chaos7_0breath);
	var1 = CreateElementalTask(2, 0, chaos_gdcontrol);
	var1->twp->mode = 0x17;
	var1->twp->wtimer = 0x3c;
}

// FUNCTION: SADX 0x006fb3c0
void rdChaos7ChangeLight1st()
{
	ADX_Close();
	le_loadLight(0x13, 0);
}

// FUNCTION: SADX 0x006fb6e0
void DstrBg_Chaos7(struct task *tp)
{
	ADX_Close();
	___njFogDisable();
	CHAOS_SetChaosNo(0);
	DAT_05b3df4c = 0;
}
