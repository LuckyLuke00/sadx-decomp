#include "decls.h"

// FUNCTION: SADX 0x00833b30
void ObjectMountainLightB(struct task *tp)
{
	tp->twp->counter.ptr = object_sotolight_light_light;
	CCL_Init(tp, (struct CCL_INFO *)&object_c2_info, 1, 4);
	ObjectCCollision_setMeshNWZ(tp);
	ObjectCCollision(tp);
}
