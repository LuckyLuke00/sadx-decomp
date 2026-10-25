#include "decls.h"
extern int DAT_05b3df4c;
extern struct NJS_TEXLIST texlist_chaos7_0breath;
extern void ADX_Close();
extern void le_loadLight(int stg, int act);
extern void late_ReleaseTexture(struct NJS_TEXLIST *tl);
extern void texLoadTexturePvmFile(char *fname, struct NJS_TEXLIST *ptlo);
extern struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
extern void chaos_gdcontrol(struct task *tp);

// STUB: SADX 0x006fb120
void SetTableBg_chaos7(int c_level)
{
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
void chaos_gdcontrol(struct task *tp)
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
