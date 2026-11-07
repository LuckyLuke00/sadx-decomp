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
	awp->face.mouse1_request_num = mouse_tex_num[num][0];
	awp->face.mouse2_request_num = mouse_tex_num[num][1];
	awp->face.mouse_keep_timer = timer;
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
	awp->face.eyelid_request_close_ang = close_ang;
	awp->face.eyelid_request_express_ang = express_ang;
	awp->face.eyelid_keep_timer = timer;
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
