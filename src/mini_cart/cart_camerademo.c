#include "decls.h"
extern int DAT_05ccdbe0;
void CartRacePrepareRace();

// FUNCTION: SADX 0x007e4f80
void cartCameraDemoCheckrer(struct task *tp)
{
	if (DAT_05ccdbe0 == 0)
	{
		FreeTask(tp);
		CartRacePrepareRace();
	}
}

// STUB: SADX 0x007e4fa0
void SetCartCameraDemo()
{
}
