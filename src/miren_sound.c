#include "decls.h"
struct StartBgmParam;
extern struct task *DAT_05ccdeb0;

// STUB: SADX 0x0056efd0
struct task *MirenSoundSetStartBgmTask(int bgmId, int time)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x0056f020
void MirenSoundInitBgm(int bgmId)
{
	ADXTaskInit();
	MirenSoundStartBgm(bgmId);
	if (DAT_05ccdeb0 != NULL)
	{
		DestroyTask(DAT_05ccdeb0);
	}
}

// FUNCTION: SADX 0x0056f050
void MirenSoundFinishBgm()
{
	ADX_Close();
	if (DAT_05ccdeb0 != 0)
	{
		DestroyTask(DAT_05ccdeb0);
	}
}

// FUNCTION: SADX 0x0056f080
void MirenSoundStartBgm(int bgmId)
{
	RoundBGM_Play(bgmId);
}

// STUB: SADX 0x0056f0a0
void MirenSoundPlayOneShotSE(int se, const struct NJS_POINT3 *pos_p, const struct VolumeInfo *info_p)
{
}

// FUNCTION: SADX 0x0056f120
void MirenSoundPlayLoopSE(int se, const struct task *task_p, const struct NJS_POINT3 *pos_p, const struct VolumeInfo *info_p)
{
	struct NJS_POINT3 *local_cg;
	int local_8g;

	if (task_p != NULL)
	{
		local_8g = MirenSoundGetVolumeOffset(pos_p, info_p);
		if (DAT_05b42a7c == NULL)
		{
			dsPlay_timer(se, (int)task_p, 1, 0, 2);
			if (local_8g != 0)
			{
				dsVolume_id((int)task_p, local_8g);
			}
		}
		else
		{
			local_cg = (struct NJS_POINT3 *)((char *)DAT_05b42a7c + 0x20);
			dsPlay_timer_v(se, (int)task_p, 1, local_8g, 2, local_cg->x, local_cg->y, local_cg->z);
		}
	}
}

// STUB: SADX 0x0056f1c0
void MirenSoundStopLoopSE(const struct task *task_p)
{
}

// STUB: SADX 0x0056f1e0
int MirenSoundGetVolumeOffset(const struct NJS_POINT3 *pos_p, const struct VolumeInfo *info_p)
{
	return (int)0;
}

// FUNCTION: SADX 0x0056f3c0
void initStartBgm(struct task *task_p, const struct StartBgmParam *param_p)
{
	struct motionwk *local_8;

	local_8 = task_p->mwp;
	*(int *)local_8 = *(int *)param_p;
	*(int *)((char *)local_8 + 4) = *(int *)((char *)param_p + 4);
}

// STUB: SADX 0x0056f3f0
void execStartBgm(struct task *task_p)
{
}

// FUNCTION: SADX 0x0056f440
void destStartBgm(struct task *task_p)
{
	DAT_05ccdeb0 = 0;
}
