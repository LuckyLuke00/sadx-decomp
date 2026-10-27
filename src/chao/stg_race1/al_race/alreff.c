#include "decls.h"
extern "C" int rand(void);

// STUB: SADX 0x0048fa50
void AlrEff_Ini(struct AlrEff *___this, struct AlrEffData *data, void (*init)(struct AlrEffUnit *), void (*exec)(struct AlrEffUnit *, struct NJS_POINT3 *, struct NJS_POINT3 *))
{
}

// STUB: SADX 0x0048fad0
void AlrEff_Exe(struct AlrEff *___this, struct NJS_POINT3 *trans, struct NJS_POINT3 *velo)
{
}

// STUB: SADX 0x0048fb70
void AlrEff_Dsp(struct AlrEff *___this)
{
}

// STUB: SADX 0x0048fc60
void AlrEff_SetFlag(struct AlrEff *___this, unsigned char flag)
{
}

// STUB: SADX 0x0048fca0
void FUN_0048fca0(float *param_1, float param_2, float param_3)
{
}

// FUNCTION: SADX 0x0048fd30
void AlrEffUnit_iniWater(struct AlrEffUnit *___this)
{
	int var1;
	float var2;
	unsigned short var3;

	___this->mode = 0;
	___this->frame = 0;
	___this->frame_inc_time = 0;
	var1 = rand();
	var2 = (float)var1 * 3.0517578125e-05;
	var2 = var2 * 15.0 + 0.0;
	var3 = (unsigned short)var2;
	___this->timer = var3;
}
