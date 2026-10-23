#include "decls.h"
void FUN_00492b00(int param_1, int param_2);
void FUN_00492b20(int param_1, int param_2);
void FUN_00492b80(int param_1, int param_2, int param_3);
extern unsigned char mouse_tex_num[7][2];
extern unsigned char eye_tex_num[];

// STUB: SADX 0x00492a90
void ADV1_AL_SetEyeNum(struct alifewk *awp, long num, long timer)
{
}

// FUNCTION: SADX 0x00492ac0
void ADV1_AL_SetMouseNum(struct alifewk *awp, long num, long timer)
{
	*(unsigned short *)((char *)awp + 0x80c) = mouse_tex_num[num][0];
	*(unsigned short *)((char *)awp + 0x80e) = mouse_tex_num[num][1];
	*(long *)((char *)awp + 0x7d4) = timer;
}

// FUNCTION: SADX 0x00492b00
void FUN_00492b00(int param_1, int param_2)
{
	*(short *)(param_1 + 0x804) = (short)eye_tex_num[param_2];
}

// STUB: SADX 0x00492b20
void FUN_00492b20(int param_1, int param_2)
{
}

// FUNCTION: SADX 0x00492b50
void ADV1_AL_SetEyelidAng(struct alifewk *awp, long close_ang, long express_ang, long timer)
{
	*(long *)((char *)awp + 0x7ec) = close_ang;
	*(long *)((char *)awp + 0x7fc) = express_ang;
	*(long *)((char *)awp + 0x7d8) = timer;
}

// FUNCTION: SADX 0x00492b80
void FUN_00492b80(int param_1, int param_2, int param_3)
{
	*(int *)(param_1 + 0x7f0) = param_2;
	*(int *)(param_1 + 0x800) = param_3;
}

// STUB: SADX 0x00492ba0
void ADV1_AL_FaceInit(struct taskwk *twp, struct alifewk *awp)
{
}
