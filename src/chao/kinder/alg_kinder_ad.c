#include "decls.h"
extern struct NJS_TEXLIST gsAdTexlist;
void FUN_004b6520(int param_1);

// FUNCTION: SADX 0x007108c0
void AlgKinderAdInit()
{
	texLoadTexturePvmFile((char *)gsAdTexFilename, &gsAdTexlist);
	FUN_004b6460(&gsAdTexlist, "gsAdTexlist");
}

// FUNCTION: SADX 0x007108f0
void AlgKinderAdExit()
{
	FUN_004b6520((int)&gsAdTexlist);
	late_ReleaseTexture(&gsAdTexlist);
}

// FUNCTION: SADX 0x00710910
void AlgKinderAdSetTexture()
{
	___njSetTexture(&gsAdTexlist);
}

// FUNCTION: SADX 0x00710920
struct NJS_TEXLIST *AlgKinderAdGetTexlist()
{
	return &gsAdTexlist;
}
