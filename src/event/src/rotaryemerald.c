#include "decls.h"

// FUNCTION: SADX 0x007d4670
void CreateRotaryEmerald(float pos_x, float pos_y, float pos_z, float r, long rot_spd, struct task *eme1_task_p, struct task *eme2_task_p, struct task *eme3_task_p, struct task *eme4_task_p, struct task *eme5_task_p, struct task *eme6_task_p, struct task *eme7_task_p)
{
	struct NJS_POINT3 pos;
	struct task *eme_task_p[7];
	pos.x = pos_x;
	pos.y = pos_y;
	pos.z = pos_z;
	g_EmeraldRotSpd = rot_spd;
	g_RotaryCircleR = r;
	eme_task_p[0] = eme1_task_p;
	eme_task_p[1] = eme2_task_p;
	eme_task_p[2] = eme3_task_p;
	eme_task_p[3] = eme4_task_p;
	eme_task_p[4] = eme5_task_p;
	eme_task_p[5] = eme6_task_p;
	eme_task_p[6] = eme7_task_p;
	createRotaryEmeraldTask(pos, eme_task_p);
}
