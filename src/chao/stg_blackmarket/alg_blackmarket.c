#include "decls.h"
extern unsigned char DAT_05ad95e1;
extern struct task *DAT_05b32e54;
extern char objLandTableChaoBlackMarket[36];
void FUN_0044db20(struct task *param_1);

// FUNCTION: SADX 0x0046def0
void AL_BlackmarketMasterDest(struct task *tp)
{
	BGM_Stop();
	Serif_Stop();
	AL_MinimalExit();
	AL_ReleaseTex(1);
	AlgKinderAdExit();
	FUN_0044db20(tp);
}

// FUNCTION: SADX 0x0046df20
void AL_BlackmarketMasterExec(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		DAT_05ad95e1 = 1;
		tp->disp = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->dest = AL_BlackmarketMasterDest;
		AL_PlayerDisable();
		FUN_0044daf0();
		AlgKinderAdInit();
		AL_BlackmarketCamera();
		AL_LoadTex("AL_TEX_COMMON", &texlist_al_tex_common, 1);
		AL_LoadTex("AL_OBJECT", &texlist_al_object, 1);
		AL_LoadTex("AL_DX_OBJ_CMN", &texlist_al_dx_obj_cmn, 1);
		AL_LoadTex("ChaoBlackmarketObj", &texlist_ChaoBlackmarketObj, 1);
		AL_MinimalInit();
		DAT_05b32e54 = AL_BlackmarketMenuCreate(tp);
		ALO_BlackmarketLampCreate(tp);
		ALO_BlackmarketBuyerCreate(tp);
		ALO_BlackmarketHangyoCreate(tp);
		ADXTaskInit();
		BGM_Play(0x7c);
		var1->mode = 1;
		DAT_05ad95e1 = 0;
		break;
	case 1:
		if (AL_BlackmarketMenuOver(DAT_05b32e54) != 0)
		{
			AL_ChangeStage((enum eCHAO_STAGE_NUMBER)4);
			var1->mode = 2;
		}
		break;
	}
	tp->disp(tp);
	LoopTaskC(tp);
	PauseDisable();
}

// FUNCTION: SADX 0x0046e020
void _alg_blackmarket_prolog()
{
	___OutputDebugString("ChaoStgBlackmarket Prolog begin\n");
	CreateElementalTask(2, 2, AL_BlackmarketMasterExec);
	LandChangeLandTable((struct _OBJ_LANDTABLE *)&objLandTableChaoBlackMarket);
	SetObjEditTable(0);
	___OutputDebugString("ChaoStgBlackmarket Prolog end\n");
}

// FUNCTION: SADX 0x0046e060
void _alg_blackmarket_epilog()
{
	___OutputDebugString("ChaoStgBlackmarket Epilog begin\n");
	___OutputDebugString("ChaoStgBlackmarket Epilog end\n");
}
