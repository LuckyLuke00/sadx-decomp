#include "decls.h"
extern struct NJS_TEXLIST texlist_shooting1;
extern struct NJS_ACTION action_beam_beam_tr1[1];
extern struct NJS_ACTION action_beamev_laser[1];
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
void FUN_004a8b10(NJS_ACTION *param_1, float param_2, int param_3);
void FUN_004a8a50(NJS_ACTION *param_1, float param_2, int param_3);

// FUNCTION: SADX 0x007eda40
void DeadDisp(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	njPushMatrix(0);
	FUN_0067d830(0, 0.0f, 0.0f, 0.0f);
	___njSetTexture(&texlist_shooting1);
	FUN_004a8b10(&action_beam_beam_tr1[0], var1->counter.f, 4);
	njPopMatrix(1);
	njPushMatrix(0);
	FUN_0067d830(0, 0.0f, 0.0f, 0.0f);
	___njSetTexture(&texlist_shooting1);
	FUN_004a8a50(&action_beamev_laser[0], var1->counter.f, 4);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x007edc80
void TornadeDisp(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	njPushMatrix(NULL);
	FUN_0067d830(NULL, 0.0f, 0.0f, 4001.0f);
	___njSetTexture(&texlist_shooting0);
	FUN_0067d2d0(NULL, 0.5f, 0.5f, 0.5f);
	FUN_004a88c0((struct NJS_ACTION *)&action_shot_bf_s_bodya, 0.0f);
	late_ActionEx((struct NJS_ACTION *)&action_shot_s_ecfire, var1->counter.f, 4, 1.0f);
	njPopMatrix(1);
	njPushMatrix(NULL);
	FUN_0067d830(NULL, 0.0f, 0.0f, 0.0f);
	___njSetTexture(&texlist_shooting2);
	___dsSetPalette(2);
	FUN_004a8b10((struct NJS_ACTION *)&action_tr2henkei_tr2_tf_event_s_tr2rt, var1->counter.f, 4);
	___dsSetPalette(0);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x007edd70
void ShtAct2EventCamera(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		var1->counter.f = 0.0f;
		var1->value.f = 0.0f;
		tp->disp = TornadeDisp;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		var1->mode = 1;
		break;
	case 1:
		CameraCameraAction(&sht_caction_cam_int1[0], var1->counter.f);
		TornadeDisp(tp);
		var1->counter.f += 1.0;
		if ((float)(unsigned int)sht_caction_cam_int1[0].motion->nbFrame <= var1->counter.f)
		{
			FreeTask(tp);
		}
		var1->value.f += 0.5;
		if (var1->value.f >= 30.0)
		{
			var1->value.f = 0.0f;
			return;
		}
		break;
	}
}
