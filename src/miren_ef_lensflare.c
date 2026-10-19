#include "decls.h"
extern int DAT_05b9d838;
void DrawLensFlare(struct NJS_POINT3 *);
struct task;
struct LensFlareParam;

// FUNCTION: SADX 0x00570850
struct task *MirenCreateLensFlare(const struct NJS_POINT3 *pos_p)
{
	struct NJS_POINT3 local_14h;
	struct task *local_18;

	local_14h.x = pos_p->x;
	local_14h.y = pos_p->y;
	local_14h.z = pos_p->z;
	local_18 = MirenSetTask((enum tasklevel)4, &MirenEfLensFlareTaskInfo, &local_14h);
	return local_18;
}

// FUNCTION: SADX 0x005708a0
void initLensFlare(struct task *task_p, const struct LensFlareParam *param_p)
{
	if (param_p != NULL)
	{
		*(int *)((char *)param_p + 0x00) = *(int *)((char *)task_p + 0x20);
		*(int *)((char *)param_p + 0x04) = *(int *)((char *)task_p + 0x24);
		*(int *)((char *)param_p + 0x08) = *(int *)((char *)task_p + 0x28);
	}
	return;
}

// FUNCTION: SADX 0x005708d0
void dispLensFlare(struct task *task_p)
{
	if (DAT_05b9d838 == 0)
	{
		DrawLensFlare((struct NJS_POINT3 *)((int)(*(int **)((char *)task_p + 0x20)) + 0x20));
	}
	return;
}
