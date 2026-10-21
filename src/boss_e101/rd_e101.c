#include "decls.h"

// GLOBAL: SADX 0x02bc0a18
struct NJS_POINT3 *DAT_02bc0a18[1];
// GLOBAL: SADX 0x02bc0a1c
struct NJS_POINT2 *DAT_02bc0a1c[1];
// GLOBAL: SADX 0x02bc0a20
struct NJS_POINT2 *DAT_02bc0a20[1];
// GLOBAL: SADX 0x02bc0a24
struct NJS_ARGB *DAT_02bc0a24[1];
extern struct NJS_ARGB DAT_05b3e040;
extern struct NJS_POINT2 DAT_05b3e050;
extern struct NJS_POINT3 DAT_05b3e074;
extern struct NJS_POINT2 DAT_05b3e080;
extern int DAT_05b3e0d0;
void SetFreeCameraMode(long sw);
void SetE101(void);
struct task *ADXTaskInit(void);
void BGM_Play(int no);
int EV_CheckCansel(void);

// FUNCTION: SADX 0x0067fa10
static void RdBossEnd(struct task *tp)
{
	___njFogDisable();
}

// FUNCTION: SADX 0x00705160
static void RdBossInit(struct task *tp)
{
	unsigned int local_8 = (unsigned char)DAT_05b9d744 * 4;
	DAT_05b3e040 = (*(struct NJS_ARGB **)((char *)DAT_02bc0a24 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080 = (*(struct NJS_POINT2 **)((char *)DAT_02bc0a1c + local_8))[DAT_05b3e0d0];
	DAT_05b3e080.y -= 1000.0;
	DAT_05b3e050 = (*(struct NJS_POINT2 **)((char *)DAT_02bc0a20 + local_8))[DAT_05b3e0d0];
	DAT_05b3e074 = (*(struct NJS_POINT3 **)((char *)DAT_02bc0a18 + local_8))[DAT_05b3e0d0];
}

// FUNCTION: SADX 0x00705210
void Rd_E101(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	SetFreeCameraMode(0);
	switch (local_8->mode)
	{
	case 0:
		tp->dest = RdBossEnd;
		++local_8->mode;
	case 1:
		if (EV_CheckCansel() != 1)
			++local_8->mode;
		break;
	case 2:
		RdBossInit(tp);
		SetE101();
		ADXTaskInit();
		BGM_Play(11);
		++local_8->mode;
		break;
	}
}
