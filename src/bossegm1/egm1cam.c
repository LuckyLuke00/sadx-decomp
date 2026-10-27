#include "decls.h"
extern float DAT_060b99e0;
extern float DAT_060b99e4;
extern float DAT_060b99e8;
extern float DAT_060b99ec;

// FUNCTION: SADX 0x006c3eb0
void SetCamEgm1Flying()
{
	DAT_060b99e4 = 0.0;
	DAT_060b99e8 = 10.0;
	DAT_060b99ec = 40.0;
	DAT_060b99e0 = 4.0;
}

// FUNCTION: SADX 0x006c3ee0
void SetCamEgm1Attack()
{
	DAT_060b99e4 = 0.0f;
	DAT_060b99e8 = 40.0f;
	DAT_060b99ec = 100.0f;
	DAT_060b99e0 = 1.0f;
}

// FUNCTION: SADX 0x006c3f10
void SetCamEgm1SpdSlowFlying()
{
	DAT_060b99e4 = 0.0f;
	DAT_060b99e8 = 10.0f;
	DAT_060b99ec = 40.0f;
	DAT_060b99e0 = 1.0f;
}

// FUNCTION: SADX 0x006c3f40
void SetCamEgm1SpdFastFlying()
{
	DAT_060b99e4 = 0.0;
	DAT_060b99e8 = 10.0;
	DAT_060b99ec = 40.0;
	DAT_060b99e0 = 100.0;
}

// STUB: SADX 0x006c3f70
void SetCamPrmAlways(struct task *tp)
{
}
