#include "decls.h"
extern int DAT_060b9ffc;
extern int DAT_060ba000;
extern int DAT_060b9ff4;
extern int DAT_060b9fec;

// FUNCTION: SADX 0x006ccad0
void egm3CamInit()
{
	DAT_060b9ffc = 0;
	DAT_060ba000 = 0;
	DAT_060b9ff4 = 0;
	DAT_060b9fec = 0;
}

// FUNCTION: SADX 0x006ccea0
void egm3EarthQuakeReq()
{
	DAT_060b9fec = 1;
}

// STUB: SADX 0x006cceb0
void camEarthQuake()
{
}

// STUB: SADX 0x006cd550
void camWait(struct taskwk *ptwp, struct taskwk *etwp)
{
}

// STUB: SADX 0x006cd650
void camLaser1(struct taskwk *ptwp, struct taskwk *etwp)
{
}

// STUB: SADX 0x006cdc70
void CameraEgm3(struct _OBJ_CAMERAPARAM *pParam)
{
}
