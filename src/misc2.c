#include "decls.h"
struct NJS_SPHERE
{
	struct NJS_POINT3 c;
	float r;
};

// FUNCTION: SADX 0x005d91c0
long CheckBallColli(struct NJS_POINT3 *point1, float r1, struct NJS_POINT3 *point2, float r2)
{
	struct NJS_SPHERE tmp_point[2];
	tmp_point[0].c.x = point1->x;
	tmp_point[0].c.y = point1->y;
	tmp_point[0].c.z = point1->z;
	tmp_point[0].r = r1;
	tmp_point[1].c.x = point2->x;
	tmp_point[1].c.y = point2->y;
	tmp_point[1].c.z = point2->z;
	tmp_point[1].r = r2;
	return njCollisionCheckSS(&tmp_point[0], &tmp_point[1]);
}
