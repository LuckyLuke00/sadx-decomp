#include "decls.h"

// FUNCTION: SADX 0x004861e0
void AlrCam_ConstraintAroundAng(struct AlrCam *___this, long angle)
{
	___this->flag |= 4;
	___this->aim_angle = angle;
}
