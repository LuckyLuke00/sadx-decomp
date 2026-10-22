#include "decls.h"
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
