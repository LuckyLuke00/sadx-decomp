#include "decls.h"

// STUB: SADX 0x00471ac0
void AL_BlackmarketCameraFunc(struct _OBJ_CAMERAPARAM *pParam)
{
}

// FUNCTION: SADX 0x00471b40
void AL_BlackmarketCamera()
{
	CameraSetCollisionCameraFunc(AL_BlackmarketCameraFunc, 1, 2);
}
