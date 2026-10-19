#include "decls.h"

extern unsigned char DAT_05cd14ed;
extern int DAT_05cd14f4;
extern int DAT_05cd14fc;

// FUNCTION: SADX 0x00573d20
int GetAdvertisePlayerNumber(unsigned char)
{
	int local_8 = DAT_05cd14ed;
	return local_8;
}

// FUNCTION: SADX 0x00573d40
long EV_FreeNpcMilesPlayerTask()
{
	return FreeNpcMilesPlayerTask();
}

// FUNCTION: SADX 0x00573d50
struct task *EV_CreateNpcMilesPlayerTask()
{
	return CreateNpcMilesPlayerTask();
}

// FUNCTION: SADX 0x00573d60
void EV_NpcMilesStandByOn()
{
	DAT_05cd14f4 = 1;
}

// FUNCTION: SADX 0x00573d70
void EV_NpcMilesStandByOff()
{
	DAT_05cd14f4 = 0;
}

// FUNCTION: SADX 0x00573d80
struct task *EV_CreateBossController(struct BOSSPLAYER_CREATE_PARAM *Param)
{
	return CreateBossPlayer(Param);
}

// FUNCTION: SADX 0x00573da0
struct task *EV_CreateBossPlayerTask(struct BOSSPLAYER_CREATE_PARAM *Param)
{
	return CreateBossPlayerTask(Param);
}

// FUNCTION: SADX 0x00573dc0
void EV_FreeBossPlayerTask(struct BOSSPLAYER_CREATE_PARAM *Param)
{
	FreeBossPlayerTask(Param);
}

// FUNCTION: SADX 0x00573de0
void SetBossPlayerResult(int flag)
{
	DAT_05cd14fc = flag;
}

// FUNCTION: SADX 0x00573df0
int GetBossPlayerResult()
{
	return DAT_05cd14fc;
}

// FUNCTION: SADX 0x00573e00
long GameStageNameModeInit(long time)
{
	return StageNameModeInit(time);
}

// FUNCTION: SADX 0x00573e20
long GameStageNameMode(void *Param)
{
	return StageNameMode(Param);
}
