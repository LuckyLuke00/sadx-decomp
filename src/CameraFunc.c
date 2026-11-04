#include "decls.h"
void sonicCameraAvoidObstacle();
extern int DAT_05ccdbd8;
extern int DAT_05ccdafc;
extern "C" double atan2(double v, double u);
extern struct PDS_PERIPHERAL *DAT_05b93268;
extern char DAT_05ccdad0;
extern int DAT_05ccdb08;
extern float DAT_05ccdb30;
extern float DAT_05ccdb40;
extern int DAT_05ccdb6c;
extern int DAT_05ccdbcc;
extern float DAT_05ccdbb4;
extern float DAT_05ccdbb8;
extern float DAT_05ccdbbc;
extern float DAT_05ccdc0c;

// GLOBAL: SADX 0x02603650
static struct Angle3 chaoscam_angacc_lim_def;

// GLOBAL: SADX 0x0260365c
static struct Angle3 chaoscam_angspd_lim_def;

extern float DAT_05ccdb04;
extern float DAT_05ccdb34;
extern float DAT_05ccdb38;
extern float DAT_05ccdb3c;
extern int DAT_05ccdc10;
extern int DAT_05ccdc14;
extern int DAT_05ccdc18;
struct _OBJ_CAMERAPARAM;
struct pathinfo {
};
struct NJS_POINT3;
struct pathtag;
void CameraReleaseEventCamera(void);
void CameraSetEventCameraFunc(void (*fnCamera)(struct _OBJ_CAMERAPARAM *), unsigned char ucAdjustType, signed char scCameraDirect);
long DiffAngle(long ang0, long ang1);
long AdjustAngle(long ang0, long ang1, long dang);
extern long DAT_05ccdb9c;
extern long DAT_05ccdba0;
extern long DAT_05ccdb54;
extern long DAT_05ccdb58;
extern struct taskwk *DAT_05baf368[8];
extern struct strCamCartData camCartData[1];
extern struct Angle3 DAT_05b42920;
float FUN_005642f0(float *param_1, float *param_2);
void CCSI_CalcTargetPos(float dist, struct NJS_POINT3 *ans);
extern struct NJS_POINT3 chaoscam_camspd_lim_def;
extern struct Angle3 DAT_05ccdb8c;
extern struct Angle3 DAT_05ccdb7c;
extern struct NJS_POINT3 DAT_05ccdb18;
extern struct taskwk *DAT_05ccdbdc;
extern struct NJS_POINT3 *DAT_05ccdbc0;
extern struct NJS_POINT3 DAT_05ccdb44;
extern int DAT_05ccdb64;
extern float DAT_05ccdb68;
extern float DAT_05ccdaec;
extern float DAT_05ccdc08;
extern float DAT_05ccdb14;
extern int DAT_05ccdc04;
extern int DAT_05ccdbe4;
extern struct NJS_POINT3 *DAT_05b4292c;
extern struct NJS_POINT3 *DAT_05b42930;
void cameraDebugMake(struct _OBJ_CAMERAPARAM *pParam, struct NJS_POINT3 *_pos, struct NJS_POINT3 *_tgt);
extern float DAT_05b42914;
extern float DAT_05ccdb24;
extern float DAT_05ccdad4;
extern float DAT_05ccdad8;
extern float DAT_05ccdadc;
extern float DAT_05ccdbe8;
extern float DAT_05ccdbec;
extern float DAT_05ccdbf0;
extern float _nj_unit_matrix_[16];
extern char DAT_05ccdc28;
extern float DAT_05ccdbf8;
extern float DAT_05ccdbfc;
extern float DAT_05ccdc00;
extern struct _OBJ_CAMERAPARAM *DAT_05edd128;
extern struct _camcontwk *camcont_wp;
extern struct taskwk *DAT_05b42a7c;

// STUB: SADX 0x0055fce0
void CameraFollow(struct _OBJ_CAMERAPARAM *pParam)
{
}

// FUNCTION: SADX 0x0055feb0
void CameraAdvertise(struct _OBJ_CAMERAPARAM *pParam)
{
	*(float *)((char *)camcont_wp + 0x18) = 0.0f;
	*(float *)((char *)camcont_wp + 0x1c) = 0.0f;
	*(float *)((char *)camcont_wp + 0x20) = 0.0f;
	*(float *)((char *)camcont_wp + 8) = 50.0f;
	*(int *)((char *)camcont_wp + 0x24) = 0;
	*(int *)((char *)camcont_wp + 0x2c) = 0;
	*(int *)((char *)camcont_wp + 0x28) = 0;
}

// STUB: SADX 0x0055ff10
void CameraModeEditor(struct _OBJ_CAMERAPARAM *pParam)
{
}

// FUNCTION: SADX 0x005600c0
void CameraModeEditorLOOKAT(struct _OBJ_CAMERAPARAM *pParam)
{
	*(float *)((char *)camcont_wp + 0x18) = *(float *)((char *)pParam + 0x10);
	*(float *)((char *)camcont_wp + 0x1c) = *(float *)((char *)pParam + 0x14);
	*(float *)((char *)camcont_wp + 0x20) = *(float *)((char *)pParam + 0x18);
	*(float *)((char *)camcont_wp + 0x0c) = *(float *)((char *)pParam + 0x04);
	*(float *)((char *)camcont_wp + 0x10) = *(float *)((char *)pParam + 0x08);
	*(float *)((char *)camcont_wp + 0x14) = *(float *)((char *)pParam + 0x0c);
	*(int *)((char *)camcont_wp + 0x2c) = 0;
	CamcontSetCameraLOOKAT(DAT_05b42a7c);
}

// STUB: SADX 0x00560140
void CameraGuriGuri(struct _OBJ_CAMERAPARAM *pParam)
{
}

// STUB: SADX 0x00560a30
void CameraTornadeInside(struct _OBJ_CAMERAPARAM *pParam)
{
}

// STUB: SADX 0x00560f10
void CameraBuilding(struct _OBJ_CAMERAPARAM *pParam)
{
}

// STUB: SADX 0x00561680
void CameraSnowSlide(struct _OBJ_CAMERAPARAM *pParam)
{
}

// STUB: SADX 0x005618c0
void CameraSnowboardSpecial1(struct _OBJ_CAMERAPARAM *pParam)
{
}

// STUB: SADX 0x00561a90
void CameraSnowboardSpecial2(struct _OBJ_CAMERAPARAM *pParam)
{
}

// STUB: SADX 0x00562100
long cameraLRSupport(void)
{
	return (long)0;
}

// STUB: SADX 0x00562930
void calcCamTargetPos(int flag)
{
}

// STUB: SADX 0x00562cc0
void CameraChaos(struct _OBJ_CAMERAPARAM *pParam)
{
}

// FUNCTION: SADX 0x00562ec0
void CameraChaosPole(struct _OBJ_CAMERAPARAM *pParam)
{
	*(float *)((char *)camcont_wp + 0x18) = *(float *)((char *)DAT_05edd128 + 0x20);
	*(float *)((char *)camcont_wp + 0x1c) = *(float *)((char *)DAT_05edd128 + 0x24);
	*(float *)((char *)camcont_wp + 0x20) = *(float *)((char *)DAT_05edd128 + 0x28);
	calcAddAngle(0);
	calcCamTargetPos(0);
	calcCameraPos(0);
}

// FUNCTION: SADX 0x00562f20
void CameraChaosWall(struct _OBJ_CAMERAPARAM *pParam)
{
	CameraChaos7_0Normal(pParam);
}

// FUNCTION: SADX 0x00562f40
void CameraChaosStd(struct _OBJ_CAMERAPARAM *pParam)
{
	*(float *)((char *)camcont_wp + 0x18) = *(float *)((char *)DAT_05edd128 + 0x20) + DAT_05ccdbf8;
	*(float *)((char *)camcont_wp + 0x1c) = *(float *)((char *)DAT_05edd128 + 0x24) + DAT_05ccdbfc;
	*(float *)((char *)camcont_wp + 0x20) = *(float *)((char *)DAT_05edd128 + 0x28) + DAT_05ccdc00;
	calcAddAngle(0);
	calcCamTargetPos(1);
	calcCameraPos(0);
}

// STUB: SADX 0x00562fb0
void SetCameraChaosStdParam(struct NJS_POINT3 *tgtpos_ofs, struct NJS_POINT3 *campos_ofs)
{
}

// FUNCTION: SADX 0x00563020
void SetCameraChaosStdSpeed(struct Angle3 *angacc, struct Angle3 *angspd, struct NJS_POINT3 *camspd)
{
	if (angacc == 0)
	{
		angacc = &chaoscam_angacc_lim_def;
	}
	if (angspd == 0)
	{
		angspd = &chaoscam_angspd_lim_def;
	}
	if (camspd == 0)
	{
		camspd = &chaoscam_camspd_lim_def;
	}
	DAT_05ccdb8c = *angacc;
	DAT_05ccdb7c = *angspd;
	DAT_05ccdb18 = *camspd;
}

// FUNCTION: SADX 0x005630a0
void CCSI_CalcTargetPos(float dist, struct NJS_POINT3 *ans)
{
	struct NJS_POINT3 vs;
	vs.x = 0.0f;
	vs.y = 0.0f;
	vs.z = dist;
	njPushMatrix(&_nj_unit_matrix_);
	if (*(int *)((char *)camcont_wp + 0x28) != 0)
	{
		njRotateY(0, *(unsigned short *)((char *)camcont_wp + 0x28));
	}
	njCalcPoint(0, &vs, ans);
	njPopMatrix(1);
	njAddVector(ans, (struct NJS_POINT3 *)((char *)camcont_wp + 0x18));
}

// FUNCTION: SADX 0x00563130
void CameraChaosStageInit(struct _OBJ_CAMERAPARAM *pParam)
{
	switch (DAT_05ccdad0)
	{
		case 0:
			DAT_05ccdb30 += DAT_05ccdc0c;
			if (DAT_05ccdb30 <= DAT_05ccdb40)
			{
				DAT_05ccdad0 = 1;
			}
			break;
		case 1:
			DAT_05ccdb08 += DAT_05ccdbcc;
			DAT_05ccdb6c += DAT_05ccdbcc;
			if (DAT_05ccdb6c >= 0x4000)
			{
				DAT_05ccdad0 = 2;
				DAT_05ccdad1 = 1;
				PadReadOn();
			}
			break;
		case 2:
			return;
	}
	*(int *)((char *)camcont_wp + 0x28) = DAT_05ccdb08;
	*(float *)((char *)camcont_wp + 0x18) = DAT_05ccdbb4;
	*(float *)((char *)camcont_wp + 0x1c) = DAT_05ccdbb8;
	*(float *)((char *)camcont_wp + 0x20) = DAT_05ccdbbc;
	CCSI_CalcTargetPos(DAT_05ccdb30, (struct NJS_POINT3 *)((char *)camcont_wp + 0xc));
}

// STUB: SADX 0x00563230
void SetParamCameraChaosStageInit(struct taskwk *ttwp, float height, float dist, int time)
{
}

// STUB: SADX 0x00563380
void CameraLine(struct _OBJ_CAMERAPARAM *pParam)
{
}

// STUB: SADX 0x005637a0
void CameraAshland(struct _OBJ_CAMERAPARAM *pParam)
{
}

// FUNCTION: SADX 0x00563900
void CameraEventCamera(struct _OBJ_CAMERAPARAM *pParam)
{
	CalcEventCamera();
	*(float *)((char *)camcont_wp + 0xc) = DAT_05b42a7c->pos.x;
	*(float *)((char *)camcont_wp + 0x10) = DAT_05b42a7c->pos.y;
	*(float *)((char *)camcont_wp + 0x14) = DAT_05b42a7c->pos.z;
	*(long *)((char *)camcont_wp + 0x24) = DAT_05b42a7c->ang.x;
	*(long *)((char *)camcont_wp + 0x28) = DAT_05b42a7c->ang.y;
	*(long *)((char *)camcont_wp + 0x2c) = DAT_05b42a7c->ang.z;
}

// STUB: SADX 0x00563980
void CameraEventPoint(struct _OBJ_CAMERAPARAM *pParam)
{
}

// FUNCTION: SADX 0x00563aa0
void CameraEventPointToPoint(struct _OBJ_CAMERAPARAM *pParam)
{
	*(float *)((char *)camcont_wp + 0xc) = *(float *)((char *)pParam + 4);
	*(float *)((char *)camcont_wp + 0x10) = *(float *)((char *)pParam + 8);
	*(float *)((char *)camcont_wp + 0x14) = *(float *)((char *)pParam + 0xc);
	*(float *)((char *)camcont_wp + 0x18) = *(float *)((char *)pParam + 0x10);
	*(float *)((char *)camcont_wp + 0x1c) = *(float *)((char *)pParam + 0x14);
	*(float *)((char *)camcont_wp + 0x20) = *(float *)((char *)pParam + 0x18);
}

// FUNCTION: SADX 0x00563b00
void SetLocalPathCamera(struct pathtag *ptp, long mode, long timer)
{
	CameraSetEventCameraFunc(CameraLocalPath, 0, 2);
	DAT_05b42a7c->value.ptr = ptp;
	DAT_05b42a7c->counter.b[0] = (char)mode;
	DAT_05b42a7c->timer.l = timer;
	DAT_05b42a7c->counter.w[1] = 0;
}

// FUNCTION: SADX 0x00563b50
void FUN_00563b50(void)
{
	if (DAT_05ccdc28 == 1)
	{
		CameraReleaseEventCamera();
		DAT_05ccdc28 = 0;
	}
}

// STUB: SADX 0x00563b70
void CameraLocalPath(struct _OBJ_CAMERAPARAM *pParam)
{
}

// STUB: SADX 0x00563e90
void CameraStay(struct _OBJ_CAMERAPARAM *pParam)
{
}

// FUNCTION: SADX 0x00564040
int FUN_00564040(int param_1, int param_2, int param_3)
{
	int iVar4;

	iVar4 = *(unsigned short *)((char *)(*(int *)(param_3 + 4) + 2)) - 1;
	if (param_1 >= iVar4 - 2)
	{
		return 1;
	}
	if (param_1 == 0)
	{
		return 1;
	}
	return 0;
}

// STUB: SADX 0x005642f0
float FUN_005642f0(float *param_1, float *param_2)
{
	return (float)0;
}

// STUB: SADX 0x00564370
int PC1_SearchNearPath(struct NJS_POINT3 *postgt, struct PATHCAMERA1WORK *pPathCamera1Work)
{
	return (int)0;
}

// FUNCTION: SADX 0x005652e0
void PathCamera2Core(struct _OBJ_CAMERAPARAM *pParam)
{
	struct Angle3 local_14;
	struct NJS_POINT3 local_20;
	*(float *)((char *)camcont_wp + 0x0c) = *(float *)((char *)DAT_05b42a7c + 0x20);
	*(float *)((char *)camcont_wp + 0x10) = *(float *)((char *)DAT_05b42a7c + 0x24);
	*(float *)((char *)camcont_wp + 0x14) = *(float *)((char *)DAT_05b42a7c + 0x28);
	*(int *)((char *)camcont_wp + 0x24) = *(int *)((char *)DAT_05b42a7c + 0x14);
	*(int *)((char *)camcont_wp + 0x28) = *(int *)((char *)DAT_05b42a7c + 0x18);
	*(int *)((char *)camcont_wp + 0x2c) = *(int *)((char *)DAT_05b42a7c + 0x1c);
	local_20.x = *(float *)((char *)camcont_wp + 0x0c);
	local_20.y = *(float *)((char *)camcont_wp + 0x10);
	local_20.z = *(float *)((char *)camcont_wp + 0x14);
	local_14.x = *(int *)((char *)camcont_wp + 0x24);
	local_14.y = *(int *)((char *)camcont_wp + 0x28);
	local_14.z = *(int *)((char *)camcont_wp + 0x2c);
	*(float *)((char *)camcont_wp + 0x0c) = DAT_05ccdb34;
	*(float *)((char *)camcont_wp + 0x10) = DAT_05ccdb38;
	*(float *)((char *)camcont_wp + 0x14) = DAT_05ccdb3c;
	*(int *)((char *)camcont_wp + 0x24) = DAT_05ccdc10;
	*(int *)((char *)camcont_wp + 0x28) = DAT_05ccdc14;
	*(int *)((char *)camcont_wp + 0x2c) = DAT_05ccdc18;
	DAT_05ccdbd0 = 1;
	CamcontSetCameraCAMSTATUS(DAT_05b42a7c);
}

// FUNCTION: SADX 0x005656f0
void calcModerateVector(struct Angle3 *ang, struct NJS_POINT3 *vec)
{
	njPushMatrix(&_nj_unit_matrix_);
	if (ang->z != 0)
	{
		njRotateZ(0, (unsigned short)ang->z);
	}
	if (ang->x != 0)
	{
		njRotateX(0, (unsigned short)ang->x);
	}
	if (ang->y != 0)
	{
		njRotateY(0, (unsigned short)ang->y);
	}
	njCalcVector(0, vec, vec);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00566070
void FUN_00566070(float param_1)
{
	*(float *)((char *)camcont_wp + 0xc) = DAT_05b42908;
	*(float *)((char *)camcont_wp + 0x10) = DAT_05b4290c + param_1 + DAT_05ccdb24;
	*(float *)((char *)camcont_wp + 0x14) = DAT_05b42910;
	*(float *)((char *)camcont_wp + 0x18) = DAT_05b42908;
	*(float *)((char *)camcont_wp + 0x1c) = DAT_05b4290c;
	*(float *)((char *)camcont_wp + 0x20) = DAT_05b42910;
}

// FUNCTION: SADX 0x005660e0
void calcCartCamPos()
{
	struct NJS_POINT3 _vec;
	if (*(unsigned char *)camcont_wp == 0 && GetPlayerNumber() == 7)
	{
		_vec.x = 0.0f;
		_vec.y = 20.0f;
		_vec.z = 15.0f;
	}
	else
	{
		_vec = camCartData[*(unsigned char *)camcont_wp].transCam;
	}
	calcModerateVector(&DAT_05b42920, &_vec);
	*(float *)((char *)camcont_wp + 0xc) += _vec.x;
	*(float *)((char *)camcont_wp + 0x10) += _vec.y;
	*(float *)((char *)camcont_wp + 0x14) += _vec.z;
}

// FUNCTION: SADX 0x005661a0
void calcCartCamTgt()
{
	struct NJS_POINT3 _vec;
	_vec = camCartData[*(unsigned char *)camcont_wp].transTgt;
	calcModerateVector(&DAT_05b42920, &_vec);
	*(float *)((char *)camcont_wp + 0x18) += _vec.x;
	*(float *)((char *)camcont_wp + 0x1c) += _vec.y;
	*(float *)((char *)camcont_wp + 0x20) += _vec.z;
}

// FUNCTION: SADX 0x00566230
void FUN_00566230(void)
{
	*(float *)((char *)camcont_wp + 0xc) = *(float *)((char *)camcont_wp + 0xc);
	*(float *)((char *)camcont_wp + 0x10) = *(float *)((char *)camcont_wp + 0x10);
	*(float *)((char *)camcont_wp + 0x14) = *(float *)((char *)camcont_wp + 0x14);
	*(float *)((char *)camcont_wp + 0x18) = (*(float *)((char *)camcont_wp + 0x18) - DAT_05ccdbe8) * 0.2f + DAT_05ccdbe8;
	*(float *)((char *)camcont_wp + 0x1c) = (*(float *)((char *)camcont_wp + 0x1c) - DAT_05ccdbec) * 0.2f + DAT_05ccdbec;
	*(float *)((char *)camcont_wp + 0x20) = (*(float *)((char *)camcont_wp + 0x20) - DAT_05ccdbf0) * 0.2f + DAT_05ccdbf0;
}

// FUNCTION: SADX 0x005662e0
void FUN_005662e0(void)
{
	*(float *)((char *)camcont_wp + 0x0c) = (*(float *)((char *)camcont_wp + 0x0c) - DAT_05ccdad4) * 0.20000000298023224 + DAT_05ccdad4;
	*(float *)((char *)camcont_wp + 0x10) = (*(float *)((char *)camcont_wp + 0x10) - DAT_05ccdad8) * 0.20000000298023224 + DAT_05ccdad8;
	*(float *)((char *)camcont_wp + 0x14) = (*(float *)((char *)camcont_wp + 0x14) - DAT_05ccdadc) * 0.20000000298023224 + DAT_05ccdadc;
	*(float *)((char *)camcont_wp + 0x18) = (*(float *)((char *)camcont_wp + 0x18) - DAT_05ccdbe8) * 0.20000000298023224 + DAT_05ccdbe8;
	*(float *)((char *)camcont_wp + 0x1c) = (*(float *)((char *)camcont_wp + 0x1c) - DAT_05ccdbec) * 0.20000000298023224 + DAT_05ccdbec;
	*(float *)((char *)camcont_wp + 0x20) = (*(float *)((char *)camcont_wp + 0x20) - DAT_05ccdbf0) * 0.20000000298023224 + DAT_05ccdbf0;
}

// FUNCTION: SADX 0x005663c0
void calcCartCamAdjForFollow()
{
	DAT_05ccdad4 = *(float *)((char *)camcont_wp + 0xc);
	DAT_05ccdad8 = *(float *)((char *)camcont_wp + 0x10);
	DAT_05ccdadc = *(float *)((char *)camcont_wp + 0x14);
	DAT_05ccdbe8 = *(float *)((char *)camcont_wp + 0x18);
	DAT_05ccdbec = *(float *)((char *)camcont_wp + 0x1c);
	DAT_05ccdbf0 = *(float *)((char *)camcont_wp + 0x20);
}

// FUNCTION: SADX 0x00566420
void FUN_00566420(void)
{
	if (DAT_05b42914 != 0.0f)
	{
		DAT_05ccdb24 = DAT_05ccdb24 + 0.5f;
	}
	else
	{
		DAT_05ccdb24 = 0.0f;
	}
}

// FUNCTION: SADX 0x00566760
void FUN_00566760(struct _OBJ_CAMERAPARAM *param_1)
{
	struct NJS_POINT3 *local_cg;
	struct NJS_POINT3 *local_8g;
	local_cg = DAT_05b4292c;
	local_8g = DAT_05b42930;
	cameraDebugMake(param_1, local_cg, local_8g);
}

// FUNCTION: SADX 0x00566790
void cameraDebugMake(struct _OBJ_CAMERAPARAM *pParam, struct NJS_POINT3 *_pos, struct NJS_POINT3 *_tgt)
{
	short local_ci;
	short local_10m;
	short local_14;
	short local_8g;
	*(float *)((char *)camcont_wp + 0x18) = _tgt->x;
	*(float *)((char *)camcont_wp + 0x1c) = _tgt->y;
	*(float *)((char *)camcont_wp + 0x20) = _tgt->z;
	*(int *)((char *)camcont_wp + 0x2c) = 0;
	if ((DAT_05b932e8[1].on & 8) != 0)
	{
		local_ci = (short)(DAT_05b93268->x1 << 8);
		local_10m = (short)(DAT_05b93268->y1 << 8);
		if (local_ci > -5000 && local_ci < 0x1388)
		{
			local_ci = 0;
		}
		if (local_10m > -5000 && local_10m < 0x1388)
		{
			local_10m = 0;
		}
		local_14 = (short)(((unsigned short)DAT_05b93268->r << 8) - 0x8000);
		local_8g = (short)(((unsigned short)DAT_05b93268->l << 8) - 0x8000);
		*(int *)((char *)camcont_wp + 0x28) += (int)local_ci / 64;
		*(int *)((char *)camcont_wp + 0x24) += (int)local_10m / 64;
		if ((DAT_05b932e8[1].on & 0x20000) != 0)
		{
			*(float *)((char *)camcont_wp + 8) += 2.0;
		}
		else
		{
			if ((DAT_05b932e8[1].on & 0x10000) != 0)
			{
				*(float *)((char *)camcont_wp + 8) -= 2.0;
			}
		}
	}
	if (*(float *)((char *)camcont_wp + 8) < 5.0)
	{
		*(float *)((char *)camcont_wp + 8) = 5.0f;
	}
	CamcontSetCameraTGTOFST(DAT_05b42a7c);
	*_pos = DAT_05b42a7c->pos;
}

// FUNCTION: SADX 0x00567060
void adjustChange()
{
	switch (GetAdjustMode())
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 8:
		case 9:
		case 10:
		case 0xb:
		case 0xc:
		case 0xd:
		case 0xe:
		case 0xf:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x15:
		case 0x16:
		case 0x17:
		case 0x18:
		case 0x19:
		case 0x1a:
			SetAdjustMode(0x11);
			break;
	}
}

// STUB: SADX 0x005670c0
void CameraFishing(struct _OBJ_CAMERAPARAM *pParam)
{
}

// STUB: SADX 0x00567230
void CameraTwoHares(struct _OBJ_CAMERAPARAM *pParam)
{
}

// FUNCTION: SADX 0x00567390
void FUN_00567390(struct _OBJ_CAMERAPARAM *param_1)
{
	if (*(int *)((char *)param_1 + 0x20) == 0)
	{
		DAT_05ccdb64 = 0;
	}
	DAT_05ccdb68 = *(float *)((char *)param_1 + 0x10);
	DAT_05ccdaec = *(float *)((char *)param_1 + 0x14);
	DAT_05ccdc08 = *(float *)((char *)param_1 + 0x18);
	DAT_05ccdb14 = *(float *)((char *)param_1 + 0x1c);
	DAT_05ccdc04 = *(unsigned short *)((char *)param_1 + 0);
	DAT_05ccdbe4 = *(unsigned short *)((char *)param_1 + 2);
	cameraSonicMain(param_1);
}

// FUNCTION: SADX 0x00567400
void FUN_00567400(struct _OBJ_CAMERAPARAM *param_1)
{
	if (*(int *)((char *)param_1 + 0x20) == 0)
	{
		DAT_05ccdb64 = 0;
	}
	DAT_05ccdb68 = 60.0f;
	DAT_05ccdaec = 35.0f;
	DAT_05ccdc08 = 90.0f;
	DAT_05ccdb14 = 20.0f;
	DAT_05ccdc04 = 0xfffff1c8;
	DAT_05ccdbe4 = 0;
	cameraSonicMain(param_1);
}

// STUB: SADX 0x00567470
void cameraSonicMain(struct _OBJ_CAMERAPARAM *pParam)
{
}

// FUNCTION: SADX 0x005675c0
void FUN_005675c0(void)
{
	DAT_05ccdb44 = DAT_05b42a7c->pos;
}

// STUB: SADX 0x005675f0
void FUN_005675f0(void)
{
}

// STUB: SADX 0x005676f0
void sonicCameraAdjustXangle()
{
}

// STUB: SADX 0x005677c0
void sonicCameraLR(void)
{
}

// FUNCTION: SADX 0x00567bd0
void sonicCameraAvoidObstacle()
{
	struct NJS_POINT3 _spdv0;
	struct NJS_POINT3 _spdv1;
	struct NJS_POINT3 _escape_pos;

	if (DAT_05ccdbd8 == 0 && DAT_05ccdafc != 0)
	{
		_escape_pos.x = *(float *)((char *)camcont_wp + 0x0c);
		_escape_pos.y = *(float *)((char *)camcont_wp + 0x10);
		_escape_pos.z = *(float *)((char *)camcont_wp + 0x14);
		_spdv0.x = DAT_05baf368[0]->pos.x - *(float *)((char *)camcont_wp + 0x0c);
		_spdv0.y = DAT_05baf368[0]->pos.y + *(float *)((char *)GetPlayerWorkPointer(0) + 0x118) - *(float *)((char *)camcont_wp + 0x10);
		_spdv0.z = DAT_05baf368[0]->pos.z - *(float *)((char *)camcont_wp + 0x14);
		_spdv1 = _spdv0;
		if (MSetPositionNW(&_escape_pos, &_spdv1, 0, 4.0f) != 0)
		{
			if ((SubAngle((long)(atan2(_spdv0.z, _spdv0.x) * 65536.0 / 6.283184), (long)(atan2(_spdv1.z, _spdv1.x) * 65536.0 / 6.283184)) & 0xffff) > 0x8000)
			{
				DAT_05ccdbd8 = -0x1e;
			}
			else
			{
				DAT_05ccdbd8 = 0x1e;
			}
		}
	}
}

// FUNCTION: SADX 0x00567d30
void sonicCameraCalcCollision()
{
	CameraAdditionalCollision((struct NJS_POINT3 *)((char *)camcont_wp + 0xc));
	CameraAdditionalPlane(&DAT_05ccdb44, (struct NJS_POINT3 *)((char *)camcont_wp + 0xc));
	CameraCollisitonCheck(&DAT_05ccdb44, (struct NJS_POINT3 *)((char *)camcont_wp + 0xc));
}

// STUB: SADX 0x00567d80
void sonicCameraFollow()
{
}

// FUNCTION: SADX 0x00567e80
void CameraFixed(struct _OBJ_CAMERAPARAM *pParam)
{
	*(float *)((char *)camcont_wp + 0x18) = *(float *)((char *)pParam + 0x10);
	*(float *)((char *)camcont_wp + 0x1c) = *(float *)((char *)pParam + 0x14);
	*(float *)((char *)camcont_wp + 0x20) = *(float *)((char *)pParam + 0x18);
	*(float *)((char *)camcont_wp + 0xc) = *(float *)((char *)pParam + 4);
	*(float *)((char *)camcont_wp + 0x10) = *(float *)((char *)pParam + 8);
	*(float *)((char *)camcont_wp + 0x14) = *(float *)((char *)pParam + 0xc);
	*(int *)((char *)camcont_wp + 0x2c) = 0;
	gravDispose3(pParam);
}

// FUNCTION: SADX 0x00568080
void CameraLeave(struct _OBJ_CAMERAPARAM *pParam)
{
	*(float *)((char *)camcont_wp + 0x18) = DAT_05baf368[0]->pos.x;
	*(float *)((char *)camcont_wp + 0x1c) = DAT_05baf368[0]->pos.y;
	*(float *)((char *)camcont_wp + 0x20) = DAT_05baf368[0]->pos.z;
}

// FUNCTION: SADX 0x005680c0
void CameraRuinWaka1(struct _OBJ_CAMERAPARAM *pParam)
{
	*(float *)((char *)camcont_wp + 0xc) = DAT_05b42a7c->scl.x;
	*(float *)((char *)camcont_wp + 0x10) = DAT_05b42a7c->scl.y;
	*(float *)((char *)camcont_wp + 0x14) = DAT_05b42a7c->scl.z;
	*(float *)((char *)camcont_wp + 0x18) = DAT_05b42a7c->counter.f;
	*(float *)((char *)camcont_wp + 0x1c) = DAT_05b42a7c->timer.f;
	*(float *)((char *)camcont_wp + 0x20) = DAT_05b42a7c->value.f;
	*(int *)((char *)camcont_wp + 0x2c) = 0;
}

// FUNCTION: SADX 0x00568420
void CameraE103Set(struct taskwk *pTaskWk, struct NJS_POINT3 *pLinePos)
{
	DAT_05ccdbdc = pTaskWk;
	DAT_05ccdbc0 = pLinePos;
}

// STUB: SADX 0x005689b0
void AdjustNone(struct taskwk *pTaskWork, struct taskwk *pOldTaskWork, struct _OBJ_ADJUSTPARAM *pCameraAdjustWork)
{
}

// FUNCTION: SADX 0x005692b0
void AdjustTime(struct taskwk *twp, struct taskwk *ptwp, struct _OBJ_ADJUSTPARAM *adjwp)
{
	float local_8 = (float)(long)*(int *)((char *)adjwp + 0x14) / 120.0;
	if (local_8 >= 1.0)
	{
		local_8 = 1.0;
		SetAdjustMode(0);
	}
	twp->pos.x = (twp->pos.x - ptwp->pos.x) * local_8 + ptwp->pos.x;
	twp->pos.y = (twp->pos.y - ptwp->pos.y) * local_8 + ptwp->pos.y;
	twp->pos.z = (twp->pos.z - ptwp->pos.z) * local_8 + ptwp->pos.z;
	twp->ang.x = AdjustAngle(ptwp->ang.x, twp->ang.x, (long)((float)DiffAngle(twp->ang.x, ptwp->ang.x) * local_8));
	twp->ang.y = AdjustAngle(ptwp->ang.y, twp->ang.y, (long)((float)DiffAngle(twp->ang.y, ptwp->ang.y) * local_8));
	twp->ang.z = AdjustAngle(ptwp->ang.z, twp->ang.z, (long)((float)DiffAngle(twp->ang.z, ptwp->ang.z) * local_8));
	CameraCollisitonCheckAdj(&ptwp->pos, &twp->pos);
}

// STUB: SADX 0x00569670
void FUN_00569670(struct taskwk *param_1, struct taskwk *param_2, struct _OBJ_ADJUSTPARAM *param_3)
{
}

// STUB: SADX 0x00569830
void atpInitParam(struct taskwk *twp, struct taskwk *ptwp, struct _OBJ_ADJUSTPARAM *adjwp)
{
}

// STUB: SADX 0x005698e0
void atpCalcCamera2PlayerAngle(struct taskwk *twp, struct taskwk *ptwp, struct _OBJ_ADJUSTPARAM *adjwp)
{
}

// STUB: SADX 0x005699b0
void atpAdjustCameraPoint(struct taskwk *twp, struct taskwk *ptwp, struct _OBJ_ADJUSTPARAM *adjwp)
{
}

// FUNCTION: SADX 0x00569ba0
void atpAdjustCameraPointWithDistance(struct taskwk *twp, struct taskwk *ptwp, struct _OBJ_ADJUSTPARAM *adjwp)
{
	struct NJS_POINT3 local_14m;
	struct NJS_POINT3 local_2c;
	struct NJS_POINT3 local_20g;

	GetPlayerPosition(0, 1, &local_14m, 0);
	local_2c.x = ptwp->pos.x - local_14m.x;
	local_2c.y = ptwp->pos.y - local_14m.y;
	local_2c.z = ptwp->pos.z - local_14m.z;
	local_20g.x = twp->pos.x - DAT_05baf368[0]->pos.x;
	local_20g.y = twp->pos.y - DAT_05baf368[0]->pos.y;
	local_20g.z = twp->pos.z - DAT_05baf368[0]->pos.z;
	twp->pos.x = (local_20g.x - local_2c.x) * DAT_05ccdb04 + local_2c.x + DAT_05baf368[0]->pos.x;
	twp->pos.y = (local_20g.y - local_2c.y) * DAT_05ccdb04 + local_2c.y + DAT_05baf368[0]->pos.y;
	twp->pos.z = (local_20g.z - local_2c.z) * DAT_05ccdb04 + local_2c.z + DAT_05baf368[0]->pos.z;
}

// FUNCTION: SADX 0x00569c90
void atpAdjustCameraTarget(struct taskwk *twp, struct taskwk *ptwp, struct _OBJ_ADJUSTPARAM *adjwp)
{
	twp->ang.x = AdjustAngle(ptwp->ang.x, twp->ang.x, (long)((float)DiffAngle(twp->ang.x, ptwp->ang.x) * DAT_05ccdb04));
	twp->ang.y = AdjustAngle(ptwp->ang.y, twp->ang.y, (long)((float)DiffAngle(twp->ang.y, ptwp->ang.y) * DAT_05ccdb04));
	twp->ang.z = AdjustAngle(ptwp->ang.z, twp->ang.z, (long)((float)DiffAngle(twp->ang.z, ptwp->ang.z) * DAT_05ccdb04));
}

// FUNCTION: SADX 0x00569d70
void AdjustThreePoint(struct taskwk *twp, struct taskwk *ptwp, struct _OBJ_ADJUSTPARAM *adjwp)
{
	if (DiffAngle(twp->ang.x, DAT_05ccdb54) > DAT_05ccdb9c)
	{
		twp->ang.x = AdjustAngle(DAT_05ccdb54, twp->ang.x, DAT_05ccdb9c);
	}
	if (DiffAngle(twp->ang.y, DAT_05ccdb58) > DAT_05ccdba0)
	{
		twp->ang.y = AdjustAngle(DAT_05ccdb58, twp->ang.y, DAT_05ccdba0);
	}
}
