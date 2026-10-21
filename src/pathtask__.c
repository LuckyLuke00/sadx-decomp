#include "decls.h"

// STUB: SADX 0x005de820
float FUN_005de820(float *param_1, float *param_2)
{
	return (float)0;
}

// FUNCTION: SADX 0x005df800
void PathworkCameraTube(struct task *tp)
{
	tp->twp->smode = 0;
	InitPathworkCamera(tp);
}

// FUNCTION: SADX 0x005e0010
void PathworkCameraYamacamera1(struct task *tp)
{
	tp->twp->smode = 1;
	InitPathworkCamera(tp);
}

// FUNCTION: SADX 0x005e0030
void PathworkCameraYamacamera2(struct task *tp)
{
	tp->twp->smode = 2;
	InitPathworkCamera(tp);
}

// FUNCTION: SADX 0x005e0050
void PathworkCameraYamacamera3(struct task *tp)
{
	tp->twp->smode = 3;
	InitPathworkCamera(tp);
}

// FUNCTION: SADX 0x005e0070
void PathworkCameraYamacamera4(struct task *tp)
{
	tp->twp->smode = 4;
	InitPathworkCamera(tp);
}

// FUNCTION: SADX 0x005e0090
void PathworkCameraYamacamera5(struct task *tp)
{
	tp->twp->smode = 5;
	InitPathworkCamera(tp);
}

// FUNCTION: SADX 0x005e00b0
void PathworkCameraYamacamera6(struct task *tp)
{
	tp->twp->smode = 6;
	InitPathworkCamera(tp);
}

// FUNCTION: SADX 0x005e00d0
void PathworkCameraYE3(struct task *tp)
{
	tp->twp->smode = 9;
	InitPathworkCamera(tp);
}
