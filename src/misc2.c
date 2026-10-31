#include "decls.h"
struct NJS_SPHERE
{
	struct NJS_POINT3 c;
	float r;
};

// FUNCTION: SADX 0x005d8d20
void DrawCustomObject(struct obj *top_object, struct CUSTOM_OBJ *custom)
{
	int local_8;

	njPushMatrix(0);
	if (top_object->model)
	{
		local_8 = 0;
		while (custom[local_8].obj)
		{
			if (custom[local_8].obj == top_object)
			{
				break;
			}
			local_8++;
		}
		if (!custom[local_8].obj)
		{
			if (!DAT_05b9d838)
			{
				njTranslateV(0, (struct NJS_POINT3 *)top_object->pos);
				if (top_object->ang[2])
				{
					njRotateZ(0, (unsigned short)top_object->ang[2]);
				}
				if (top_object->ang[0])
				{
					njRotateX(0, (unsigned short)top_object->ang[0]);
				}
				if (top_object->ang[1])
				{
					njRotateY(0, (unsigned short)top_object->ang[1]);
				}
				njScaleV(0, (struct NJS_POINT3 *)top_object->scl);
				___dsDrawModel(top_object->model);
			}
		}
		else if (custom[local_8].exad)
		{
			custom[local_8].exad(top_object);
		}
	}
	else
	{
		njTranslateV(0, (struct NJS_POINT3 *)top_object->pos);
		if (top_object->ang[2])
		{
			njRotateZ(0, (unsigned short)top_object->ang[2]);
		}
		if (top_object->ang[0])
		{
			njRotateX(0, (unsigned short)top_object->ang[0]);
		}
		if (top_object->ang[1])
		{
			njRotateY(0, (unsigned short)top_object->ang[1]);
		}
		njScaleV(0, (struct NJS_POINT3 *)top_object->scl);
	}
	if (top_object->child)
	{
		njPushMatrix(0);
		DrawCustomObject(top_object->child, custom);
		njPopMatrix(1);
	}
	njPopMatrix(1);
	if (top_object->sibling)
	{
		DrawCustomObject(top_object->sibling, custom);
	}
}

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
