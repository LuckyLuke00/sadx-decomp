#include "decls.h"
extern char DAT_060bb3e4[8];
extern char DAT_060bb3ec[8];
extern int DAT_060bb3e0;
extern int DAT_060bb3f4;
extern int DAT_05b9d838;
extern struct NJS_TEXLIST *egm3_texlist_list[4];
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x006d5890
void UkisimaDraw(struct task *tp)
{
	struct taskwk *var1;
	struct anywk *var2;
	float *var3;

	var1 = tp->twp;
	var2 = tp->awp;
	if (DAT_05b9d838 == 0)
	{
		SaveConstantAttr();
		___njSetTexture(egm3_texlist_list[0]);
		SaveControl3D();
		njControl3D(0x10);
		SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
		var3 = (float *)0;
		njPushMatrix(var3);
		FUN_0067d830(var3, var1->pos.x, var1->pos.y, var1->pos.z);
		if (var1->ang.y != 0)
		{
			njRotateY(var3, (unsigned short)var1->ang.y);
		}
		ds_DrawObjectClip((struct obj *)var2->work.ptr[0], 1.0f);
		njPopMatrix(1);
		ResetMaterial();
		LoadControl3D();
		LoadConstantAttr();
	}
}

// FUNCTION: SADX 0x006d5950
void UkisimaExit(struct task *tp)
{
	struct anywk *var1 = tp->awp;

	if (var1->work.ptr[1] != 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->work.ptr[1]);
		ReleaseMobileLandObject((struct obj *)var1->work.ptr[1]);
		var1->work.ptr[1] = 0;
	}
}

// FUNCTION: SADX 0x006d5980
void KowareUkisimaDraw(struct task *tp)
{
	struct taskwk *var1;
	struct anywk *var2;

	var1 = tp->twp;
	var2 = tp->awp;
	if (DAT_05b9d838 == 0)
	{
		SaveConstantAttr();
		njPushMatrix(NULL);
		FUN_0067d830(NULL, var1->pos.x, var1->pos.y, var1->pos.z);
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)var1->ang.z);
		}
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)var1->ang.x);
		}
		if ((*((unsigned char *)var2 + 0x20) & 0x10) == 0)
		{
			___njSetTexture(egm3_texlist_list[2]);
			ds_DrawModelClip(model_koware[*(unsigned long *)((char *)var2 + 0x20) & 0xf], 1.0f);
		}
		else
		{
			___njSetTexture(egm3_texlist_list[3]);
			ds_DrawModelClip(model_koware_side[*(unsigned long *)((char *)var2 + 0x20) & 0xf], 1.0f);
		}
		njPopMatrix(1);
		LoadConstantAttr();
	}
}

// FUNCTION: SADX 0x006d5a60
long UkisimaExist(float x, float z)
{
	long var1 = ((long)((z + 480.0f) / 120.0f));
	if ((unsigned long)var1 <= 7)
	{
		if ((x > -320.0f) && (x < -200.0f))
		{
			DAT_060bb3f4 = 0;
			DAT_060bb3e0 = (int)var1;
			return (long)(signed char)DAT_060bb3e4[var1];
		}
		if ((x > 200.0f) && (x < 320.0f))
		{
			DAT_060bb3f4 = 1;
			DAT_060bb3e0 = (int)var1;
			return (long)(signed char)DAT_060bb3ec[var1];
		}
	}
	return 0;
}

// STUB: SADX 0x006d5c40
void UkisimaBreak(float x, float z)
{
}
