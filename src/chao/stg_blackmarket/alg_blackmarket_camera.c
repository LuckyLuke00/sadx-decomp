#include "decls.h"

// FUNCTION: SADX 0x00471b40
void AL_BlackmarketCamera()
{
	CameraSetCollisionCameraFunc(AL_BlackmarketCameraFunc, 1, 2);
}
