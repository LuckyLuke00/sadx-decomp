#include "decls.h"

// FUNCTION: SADX 0x00489650
int AlrRoot_GetGoal(struct AlrRoot *___this, struct NJS_POINT3 *answer)
{
	if (___this->goal_info.goal.x == -10000.0f)
	{
		answer->z = answer->y = answer->x = 0.0f;
		return 0;
	}
	answer->x = ___this->goal_info.goal.x;
	answer->y = ___this->goal_info.goal.y;
	answer->z = ___this->goal_info.goal.z;
	return 1;
}

// STUB: SADX 0x00489690
int AlrRoot_CheckGoal(struct AlrRoot *___this, struct NJS_POINT3 *trans)
{
	return (int)0;
}

// FUNCTION: SADX 0x004896f0
void AlrRoot_Del(struct AlrRoot *___this)
{
	if (___this->subpath)
	{
		Free(___this->subpath);
	}
	___this->subpath = 0;
}

// FUNCTION: SADX 0x00489710
void AlrRoot_Clear(struct AlrRoot *___this, float goal_pathpos)
{
	if (AlrRoot_GetPosOnMainPath(___this, goal_pathpos, (struct NJS_POINT3 *)___this) == 0)
	{
		___this->goal_info.goal.x = -10000.0f;
		___this->goal_info.goal.y = 0.0f;
		___this->goal_info.goal.z = 0.0f;
	}
}
