#include "decls.h"
#include <string.h>
#include <new>
#include <vector>
#include "../advertise.h"
extern char DAT_05b42418[0x104];
void FUN_004b1cb0(int param_1, int param_2, int param_3, int param_4);
struct FUN_004b6590_0
{
	struct NJS_ARGB field_0x0;
	Magic::RenderCore::Texture *field_0x10;
};
struct FUN_004b2330_0
{
	FUN_004b2330_0();
	char field_0x0[0x104];
	int field_0x104;
	Magic::RenderCore::Texture **field_0x108;
	Magic::RenderCore::Texture *field_0x10c;
	Magic::RenderCore::Texture *field_0x110;
	Magic::RenderCore::Texture *field_0x114;
	Magic::RenderCore::Texture *field_0x118;
	std::vector<FUN_004b6590_0 *> field_0x11c;
};
template class std::vector<FUN_004b6590_0 *>;
template class std::vector<FUN_004b2330_0 *>;
void FUN_004b5e70(Magic::RenderCore::Texture **param_1);
void *FUN_0040efd0();
void FUN_004b38e0(struct FUN_004b2330_0 *param_1);
struct FUN_004b38e0_0
{
	int field_0x0;
	char field_0x4[0x104];
	int field_0x108;
	int field_0x10c;
	int field_0x110;
	char *field_0x114;
	int field_0x118;
	int field_0x11c;
	int field_0x120;
	int field_0x124;
	int field_0x128;
};
char *FUN_00412260(char *param_1);
int FUN_00922d50(int param_1, int param_2);
void FUN_004b2740(Magic::RenderCore::LockedSurface *param_1, char *param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void FUN_004b28d0(Magic::RenderCore::LockedSurface *param_1, char *param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10, int param_11, int param_12);
void FUN_004b2ab0(Magic::RenderCore::LockedSurface *param_1, char *param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void FUN_004b2cd0(Magic::RenderCore::LockedSurface *param_1, char *param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void FUN_004b2e50(Magic::RenderCore::LockedSurface *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void FUN_004b2f10(Magic::RenderCore::LockedSurface *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void FUN_004b3060(Magic::RenderCore::LockedSurface *param_1, char *param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void FUN_004b3260(Magic::RenderCore::LockedSurface *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10, int param_11);
void FUN_004b3390(Magic::RenderCore::LockedSurface *param_1, char *param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void FUN_004b3590(Magic::RenderCore::LockedSurface *param_1, char *param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void FUN_004b3710(Magic::RenderCore::LockedSurface *param_1, char *param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);

// GLOBAL: SADX 0x05b422d8
std::vector<FUN_004b2330_0 *>::iterator DAT_05b422d8;

// GLOBAL: SADX 0x05b422dc
std::vector<FUN_004b2330_0 *> DAT_05b422dc;

extern unsigned int DAT_05b42414;
extern int DAT_05b42400;
extern struct NJS_ARGB DAT_05b42404;
extern struct NJS_ARGB DAT_025adbd8;
extern struct NJS_ARGB DAT_05ad9654;
extern struct NJS_ARGB DAT_05b40a4c;
extern struct NJS_ARGB DAT_025adbf8;
extern unsigned char DAT_025addd8;
extern unsigned char DAT_05b423fc;
extern char DAT_025adde0[0x20e][0x12c];
extern char *DAT_0629948c;
extern char *DAT_06299490;

// FUNCTION: SADX 0x004b1a40
int FUN_004b1a40(int *param_1, int param_2)
{
	int local_8 = 0;

	while (param_1 != 0 && *param_1 != 0x24)
	{
		if (*param_1 == param_2)
		{
			local_8 = 1;
		}
		param_1++;
	}
	return local_8;
}

// FUNCTION: SADX 0x004b1a80
bool FUN_004b1a80(char *param_1, int param_2)
{
	for (unsigned int local_8 = 0; local_8 < DAT_05b422dc.size(); local_8++)
	{
		FUN_004b2330_0 **local_c = &DAT_05b422dc[local_8];
		if (!strcmp((*local_c)->field_0x0, param_1) && DAT_05b422dc[local_8]->field_0x104 == param_2)
		{
			return true;
		}
	}
	return false;
}

// STUB: SADX 0x004b2330
FUN_004b2330_0::FUN_004b2330_0()
{
}

// DIFF: code: the allocation temporaries use different stack offsets and the inner vector call resolves to a different specialization.
// FUNCTION: SADX 0x004b23e0
void FUN_004b23e0(Magic::RenderCore::Texture **param_1, char *param_2, unsigned int param_3, const char *param_4, int param_5)
{
	Magic::RenderCore::Texture **local_c = param_1;
	std::string local_30(param_4);
	int local_8c;
	FUN_004b38e0_0 *local_128;
	FUN_004b2330_0 *local_dc;
	unsigned int local_a0;
	FUN_004b6590_0 *local_9c;

	for (local_8c = 0; local_8c < 0x20e; local_8c++)
	{
		local_128 = (FUN_004b38e0_0 *)DAT_025adde0[local_8c];
		if (strcmp(local_128->field_0x4, param_4) == 0 && local_128->field_0x108 == param_5 && !FUN_004b1a80((char *)param_4, param_5))
		{
			local_dc = new FUN_004b2330_0;
			strcpy_s(local_dc->field_0x0, 0x100, local_128->field_0x4);
			local_dc->field_0x104 = param_5;
			local_dc->field_0x108 = param_1;
			local_dc->field_0x10c = *local_c;
			local_dc->field_0x114 = new Magic::RenderCore::Texture;
			local_dc->field_0x114->Load(param_2, 1, param_3, 2, 1, 0);
			local_dc->field_0x118 = new Magic::RenderCore::Texture;
			local_dc->field_0x118->Load(param_2, 1, param_3, 2, 1, 0);
			for (local_a0 = 0; FUN_0040efd0(), local_a0 < (unsigned int)((DAT_06299490 - DAT_0629948c) / 0x94); local_a0++)
			{
				local_9c = new FUN_004b6590_0;
				FUN_0040efd0();
				local_9c->field_0x0 = *(NJS_ARGB *)(DAT_0629948c + local_a0 * 0x94);
				local_9c->field_0x10 = new Magic::RenderCore::Texture;
				local_9c->field_0x10->Load(param_2, 1, param_3, 2, 1, 0);
				local_dc->field_0x11c.push_back(local_9c);
			}
			FUN_004b38e0(local_dc);
			DAT_05b422dc.push_back(local_dc);
			DAT_025addd8 = 1;
		}
	}
}

// FUNCTION: SADX 0x004b2860
unsigned char FUN_004b2860(unsigned char param_1, unsigned char param_2, unsigned char param_3)
{
	float local_ci = param_3 / 255.0;
	unsigned short local_10 = param_2;
	unsigned short local_8g = param_1;
	return (unsigned char)(local_10 * local_ci + (1.0f - local_ci) * local_8g);
}

// FUNCTION: SADX 0x004b3210
bool FUN_004b3210(int *param_1, int *param_2)
{
	if (param_1[0] < param_2[2] && param_1[2] > param_2[0] && param_1[1] < param_2[3] && param_1[3] > param_2[1])
	{
		return true;
	}
	return false;
}

// FUNCTION: SADX 0x004b38e0
void FUN_004b38e0(struct FUN_004b2330_0 *param_1)
{
	if (param_1)
	{
		std::string local_30(param_1->field_0x0);

		{
			Magic::RenderCore::LockedSurface local_40;

			if (param_1->field_0x114->Lock(0, &local_40, 0, 0))
			{
				for (int local_44 = 0; local_44 < 0x20e; local_44++)
				{
					FUN_004b38e0_0 *local_48 = (FUN_004b38e0_0 *)DAT_025adde0[local_44];

					if (local_30.find(local_48->field_0x4) != std::string::npos && local_48->field_0x108 == param_1->field_0x104)
					{
						FUN_00412290_0 *local_4c = (FUN_00412290_0 *)FUN_00412260(local_48->field_0x114);

						if (local_4c)
						{
							switch (local_48->field_0x0)
							{
							case 0:
								if (local_4c->field_0x10)
								{
									Magic::RenderCore::Texture *local_50g = local_40.FUN_009225a0();
									int local_54 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_50g->FUN_009227f0()), 8);

									FUN_004b2740(&local_40, local_4c->field_0x10, local_48->field_0x10c, local_48->field_0x110, local_4c->field_0x0, local_4c->field_0x4, local_50g->FUN_00922870(), local_50g->FUN_00922850(), local_40.FUN_009225b0(), local_54);
								}
								break;
							case 1:
							{
								Magic::RenderCore::Texture *local_58g = local_40.FUN_009225a0();
								int local_5c = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_58g->FUN_009227f0()), 8);

								FUN_004b2e50(&local_40, local_48->field_0x10c, local_48->field_0x110, local_48->field_0x118, local_48->field_0x11c, local_48->field_0x120, local_58g->FUN_00922870(), local_58g->FUN_00922850(), local_40.FUN_009225b0(), local_5c);
								break;
							}
							case 2:
								if (local_4c->field_0x10)
								{
									Magic::RenderCore::Texture *local_60g = local_40.FUN_009225a0();
									int local_64 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_60g->FUN_009227f0()), 8);

									FUN_004b2cd0(&local_40, local_4c->field_0x10, local_48->field_0x10c, local_48->field_0x110, local_4c->field_0x0, local_4c->field_0x4, local_60g->FUN_00922870(), local_60g->FUN_00922850(), local_40.FUN_009225b0(), local_64);
								}
								break;
							case 3:
							{
								Magic::RenderCore::Texture *local_68g = local_40.FUN_009225a0();
								int local_6c = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_68g->FUN_009227f0()), 8);

								FUN_004b2f10(&local_40, local_48->field_0x10c, local_48->field_0x110, local_48->field_0x118, local_48->field_0x11c, local_48->field_0x120, local_68g->FUN_00922870(), local_68g->FUN_00922850(), local_40.FUN_009225b0(), local_6c);
								break;
							}
							case 4:
								if (local_4c->field_0x10)
								{
									Magic::RenderCore::Texture *local_70g = local_40.FUN_009225a0();
									int local_74 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_70g->FUN_009227f0()), 8);

									FUN_004b3060(&local_40, local_4c->field_0x10, local_48->field_0x10c, local_48->field_0x110, local_4c->field_0x0, local_4c->field_0x4, local_70g->FUN_00922870(), local_70g->FUN_00922850(), local_40.FUN_009225b0(), local_74);
								}
								break;
							case 5:
							{
								Magic::RenderCore::Texture *local_78g = local_40.FUN_009225a0();
								int local_7c = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_78g->FUN_009227f0()), 8);

								FUN_004b3260(&local_40, local_48->field_0x10c, local_48->field_0x110, local_48->field_0x118, local_48->field_0x11c, local_48->field_0x124, local_48->field_0x128, local_78g->FUN_00922870(), local_78g->FUN_00922850(), local_40.FUN_009225b0(), local_7c);
								break;
							}
							case 6:
								if (local_4c->field_0x10)
								{
									Magic::RenderCore::Texture *local_80g = local_40.FUN_009225a0();
									int local_84 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_80g->FUN_009227f0()), 8);

									FUN_004b3590(&local_40, local_4c->field_0x10, local_48->field_0x10c, local_48->field_0x110, local_4c->field_0x0, local_4c->field_0x4, local_80g->FUN_00922870(), local_80g->FUN_00922850(), local_40.FUN_009225b0(), local_84);
								}
								break;
							case 7:
								if (local_4c->field_0x10)
								{
									Magic::RenderCore::Texture *local_88q = local_40.FUN_009225a0();
									int local_8c = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_88q->FUN_009227f0()), 8);

									FUN_004b3390(&local_40, local_4c->field_0x10, local_48->field_0x10c, local_48->field_0x110, local_4c->field_0x0, local_4c->field_0x4, local_88q->FUN_00922870(), local_88q->FUN_00922850(), local_40.FUN_009225b0(), local_8c);
								}
								break;
							case 8:
								if (local_4c->field_0x10)
								{
									Magic::RenderCore::Texture *local_90 = local_40.FUN_009225a0();
									int local_94g = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_90->FUN_009227f0()), 8);

									FUN_004b28d0(&local_40, local_4c->field_0x10, local_48->field_0x10c, local_48->field_0x110, local_4c->field_0x0, local_4c->field_0x4, local_90->FUN_00922870(), local_90->FUN_00922850(), local_40.FUN_009225b0(), local_94g, 0, 0);
								}
								break;
							case 9:
								if (local_4c->field_0x10)
								{
									Magic::RenderCore::Texture *local_98 = local_40.FUN_009225a0();
									int local_9c = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_98->FUN_009227f0()), 8);

									FUN_004b2ab0(&local_40, local_4c->field_0x10, local_48->field_0x10c, local_48->field_0x110, local_4c->field_0x0, local_4c->field_0x4, local_98->FUN_00922870(), local_98->FUN_00922850(), local_40.FUN_009225b0(), local_9c);
								}
								break;
							case 10:
							{
								Magic::RenderCore::Texture *local_a0k = local_40.FUN_009225a0();
								int local_a4 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_a0k->FUN_009227f0()), 8);

								FUN_004b3260(&local_40, local_48->field_0x10c, local_48->field_0x110, local_48->field_0x118, local_48->field_0x11c, local_48->field_0x124, local_48->field_0x128, local_a0k->FUN_00922870(), local_a0k->FUN_00922850(), local_40.FUN_009225b0(), local_a4);
								break;
							}
							case 11:
								if (local_4c->field_0x10)
								{
									Magic::RenderCore::Texture *local_a8g = local_40.FUN_009225a0();
									int local_ac = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_a8g->FUN_009227f0()), 8);

									FUN_004b3710(&local_40, local_4c->field_0x10, local_48->field_0x10c, local_48->field_0x110, local_4c->field_0x0, local_4c->field_0x4, local_a8g->FUN_00922870(), local_a8g->FUN_00922850(), local_40.FUN_009225b0(), local_ac);
								}
								break;
							}
						}
					}
				}
				param_1->field_0x114->Unlock();
			}
		}

		{
			Magic::RenderCore::LockedSurface local_bc;

			if (param_1->field_0x118->Lock(0, &local_bc, 0, 0))
			{
				for (int local_c0 = 0; local_c0 < 0x20e; local_c0++)
				{
					FUN_004b38e0_0 *local_c4 = (FUN_004b38e0_0 *)DAT_025adde0[local_c0];

					if (local_30.find(local_c4->field_0x4) != std::string::npos && local_c4->field_0x108 == param_1->field_0x104)
					{
						FUN_00412290_0 *local_c8 = (FUN_00412290_0 *)FUN_00412260(local_c4->field_0x114);

						if (local_c8)
						{
							switch (local_c4->field_0x0)
							{
							case 0:
								if (local_c8->field_0x18)
								{
									Magic::RenderCore::Texture *local_ccg = local_bc.FUN_009225a0();
									int local_d0 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_ccg->FUN_009227f0()), 8);

									FUN_004b2740(&local_bc, local_c8->field_0x18, local_c4->field_0x10c, local_c4->field_0x110, local_c8->field_0x0, local_c8->field_0x4, local_ccg->FUN_00922870(), local_ccg->FUN_00922850(), local_bc.FUN_009225b0(), local_d0);
								}
								break;
							case 1:
							{
								Magic::RenderCore::Texture *local_d4j = local_bc.FUN_009225a0();
								int local_d8 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_d4j->FUN_009227f0()), 8);

								FUN_004b2e50(&local_bc, local_c4->field_0x10c, local_c4->field_0x110, local_c4->field_0x118, local_c4->field_0x11c, local_c4->field_0x120, local_d4j->FUN_00922870(), local_d4j->FUN_00922850(), local_bc.FUN_009225b0(), local_d8);
								break;
							}
							case 2:
								if (local_c8->field_0x18)
								{
									Magic::RenderCore::Texture *local_dc = local_bc.FUN_009225a0();
									int local_e0 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_dc->FUN_009227f0()), 8);

									FUN_004b2cd0(&local_bc, local_c8->field_0x18, local_c4->field_0x10c, local_c4->field_0x110, local_c8->field_0x0, local_c8->field_0x4, local_dc->FUN_00922870(), local_dc->FUN_00922850(), local_bc.FUN_009225b0(), local_e0);
								}
								break;
							case 3:
							{
								Magic::RenderCore::Texture *local_e4i = local_bc.FUN_009225a0();
								int local_e8 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_e4i->FUN_009227f0()), 8);

								FUN_004b2f10(&local_bc, local_c4->field_0x10c, local_c4->field_0x110, local_c4->field_0x118, local_c4->field_0x11c, local_c4->field_0x120, local_e4i->FUN_00922870(), local_e4i->FUN_00922850(), local_bc.FUN_009225b0(), local_e8);
								break;
							}
							case 4:
								if (local_c8->field_0x18)
								{
									Magic::RenderCore::Texture *local_ec = local_bc.FUN_009225a0();
									int local_f0h = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_ec->FUN_009227f0()), 8);

									FUN_004b3060(&local_bc, local_c8->field_0x18, local_c4->field_0x10c, local_c4->field_0x110, local_c8->field_0x0, local_c8->field_0x4, local_ec->FUN_00922870(), local_ec->FUN_00922850(), local_bc.FUN_009225b0(), local_f0h);
								}
								break;
							case 5:
							{
								Magic::RenderCore::Texture *local_f4o = local_bc.FUN_009225a0();
								int local_f8 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_f4o->FUN_009227f0()), 8);

								FUN_004b3260(&local_bc, local_c4->field_0x10c, local_c4->field_0x110, local_c4->field_0x118, local_c4->field_0x11c, local_c4->field_0x124, local_c4->field_0x128, local_f4o->FUN_00922870(), local_f4o->FUN_00922850(), local_bc.FUN_009225b0(), local_f8);
								break;
							}
							case 6:
								if (local_c8->field_0x18)
								{
									Magic::RenderCore::Texture *local_fcu = local_bc.FUN_009225a0();
									int local_100 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_fcu->FUN_009227f0()), 8);

									FUN_004b3590(&local_bc, local_c8->field_0x18, local_c4->field_0x10c, local_c4->field_0x110, local_c8->field_0x0, local_c8->field_0x4, local_fcu->FUN_00922870(), local_fcu->FUN_00922850(), local_bc.FUN_009225b0(), local_100);
								}
								break;
							case 7:
								if (local_c8->field_0x18)
								{
									Magic::RenderCore::Texture *local_104 = local_bc.FUN_009225a0();
									int local_108 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_104->FUN_009227f0()), 8);

									FUN_004b3390(&local_bc, local_c8->field_0x18, local_c4->field_0x10c, local_c4->field_0x110, local_c8->field_0x0, local_c8->field_0x4, local_104->FUN_00922870(), local_104->FUN_00922850(), local_bc.FUN_009225b0(), local_108);
								}
								break;
							case 8:
								if (local_c8->field_0x18)
								{
									Magic::RenderCore::Texture *local_10c = local_bc.FUN_009225a0();
									int local_110 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_10c->FUN_009227f0()), 8);

									FUN_004b28d0(&local_bc, local_c8->field_0x18, local_c4->field_0x10c, local_c4->field_0x110, local_c8->field_0x0, local_c8->field_0x4, local_10c->FUN_00922870(), local_10c->FUN_00922850(), local_bc.FUN_009225b0(), local_110, 0, 0);
								}
								break;
							case 9:
								if (local_c8->field_0x18)
								{
									Magic::RenderCore::Texture *local_114x = local_bc.FUN_009225a0();
									int local_118 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_114x->FUN_009227f0()), 8);

									FUN_004b2ab0(&local_bc, local_c8->field_0x18, local_c4->field_0x10c, local_c4->field_0x110, local_c8->field_0x0, local_c8->field_0x4, local_114x->FUN_00922870(), local_114x->FUN_00922850(), local_bc.FUN_009225b0(), local_118);
								}
								break;
							case 10:
							{
								Magic::RenderCore::Texture *local_11cg = local_bc.FUN_009225a0();
								int local_120 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_11cg->FUN_009227f0()), 8);

								FUN_004b3260(&local_bc, local_c4->field_0x10c, local_c4->field_0x110, local_c4->field_0x118, local_c4->field_0x11c, local_c4->field_0x124, local_c4->field_0x128, local_11cg->FUN_00922870(), local_11cg->FUN_00922850(), local_bc.FUN_009225b0(), local_120);
								break;
							}
							case 11:
								if (local_c8->field_0x18)
								{
									Magic::RenderCore::Texture *local_124g = local_bc.FUN_009225a0();
									int local_128 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_124g->FUN_009227f0()), 8);

									FUN_004b3710(&local_bc, local_c8->field_0x18, local_c4->field_0x10c, local_c4->field_0x110, local_c8->field_0x0, local_c8->field_0x4, local_124g->FUN_00922870(), local_124g->FUN_00922850(), local_bc.FUN_009225b0(), local_128);
								}
								break;
							}
						}
					}
				}
				param_1->field_0x118->Unlock();
			}
		}

		for (unsigned int local_12c = 0; local_12c < param_1->field_0x11c.size(); local_12c++)
		{
			Magic::RenderCore::LockedSurface local_13c;

			if (param_1->field_0x11c[local_12c]->field_0x10->Lock(0, &local_13c, 0, 0))
			{
				for (int local_140 = 0; local_140 < 0x20e; local_140++)
				{
					FUN_004b38e0_0 *local_144 = (FUN_004b38e0_0 *)DAT_025adde0[local_140];

					if (local_30.find(local_144->field_0x4) != std::string::npos && local_144->field_0x108 == param_1->field_0x104)
					{
						FUN_00412290_0 *local_148 = (FUN_00412290_0 *)FUN_00412260(local_144->field_0x114);

						if (local_148)
						{
							switch (local_144->field_0x0)
							{
							case 0:
							{
								int local_14c = local_148->FUN_00412290(param_1->field_0x11c[local_12c]->field_0x0);

								if (param_1->field_0x11c[local_12c]->field_0x10 && local_14c != -1)
								{
									Magic::RenderCore::Texture *local_150l = local_13c.FUN_009225a0();
									int local_154 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_150l->FUN_009227f0()), 8);

									FUN_004b2740(&local_13c, local_148->field_0x20[local_14c].field_0x0, local_144->field_0x10c, local_144->field_0x110, local_148->field_0x0, local_148->field_0x4, local_150l->FUN_00922870(), local_150l->FUN_00922850(), local_13c.FUN_009225b0(), local_154);
								}
								break;
							}
							case 1:
							{
								Magic::RenderCore::Texture *local_158 = local_13c.FUN_009225a0();
								int local_15c = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_158->FUN_009227f0()), 8);

								FUN_004b2e50(&local_13c, local_144->field_0x10c, local_144->field_0x110, local_144->field_0x118, local_144->field_0x11c, local_144->field_0x120, local_158->FUN_00922870(), local_158->FUN_00922850(), local_13c.FUN_009225b0(), local_15c);
								break;
							}
							case 2:
							{
								int local_160 = local_148->FUN_00412290(param_1->field_0x11c[local_12c]->field_0x0);

								if (param_1->field_0x11c[local_12c]->field_0x10 && local_160 != -1)
								{
									Magic::RenderCore::Texture *local_164 = local_13c.FUN_009225a0();
									int local_168 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_164->FUN_009227f0()), 8);

									FUN_004b2cd0(&local_13c, local_148->field_0x20[local_160].field_0x0, local_144->field_0x10c, local_144->field_0x110, local_148->field_0x0, local_148->field_0x4, local_164->FUN_00922870(), local_164->FUN_00922850(), local_13c.FUN_009225b0(), local_168);
								}
								break;
							}
							case 3:
							{
								Magic::RenderCore::Texture *local_16c = local_13c.FUN_009225a0();
								int local_170g = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_16c->FUN_009227f0()), 8);

								FUN_004b2f10(&local_13c, local_144->field_0x10c, local_144->field_0x110, local_144->field_0x118, local_144->field_0x11c, local_144->field_0x120, local_16c->FUN_00922870(), local_16c->FUN_00922850(), local_13c.FUN_009225b0(), local_170g);
								break;
							}
							case 4:
							{
								int local_174 = local_148->FUN_00412290(param_1->field_0x11c[local_12c]->field_0x0);

								if (param_1->field_0x11c[local_12c]->field_0x10 && local_174 != -1)
								{
									Magic::RenderCore::Texture *local_178t = local_13c.FUN_009225a0();
									int local_17c = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_178t->FUN_009227f0()), 8);

									FUN_004b3060(&local_13c, local_148->field_0x20[local_174].field_0x0, local_144->field_0x10c, local_144->field_0x110, local_148->field_0x0, local_148->field_0x4, local_178t->FUN_00922870(), local_178t->FUN_00922850(), local_13c.FUN_009225b0(), local_17c);
								}
								break;
							}
							case 5:
							{
								Magic::RenderCore::Texture *local_180h = local_13c.FUN_009225a0();
								int local_184 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_180h->FUN_009227f0()), 8);

								FUN_004b3260(&local_13c, local_144->field_0x10c, local_144->field_0x110, local_144->field_0x118, local_144->field_0x11c, local_144->field_0x124, local_144->field_0x128, local_180h->FUN_00922870(), local_180h->FUN_00922850(), local_13c.FUN_009225b0(), local_184);
								break;
							}
							case 6:
							{
								int local_188 = local_148->FUN_00412290(param_1->field_0x11c[local_12c]->field_0x0);

								if (param_1->field_0x11c[local_12c]->field_0x10 && local_188 != -1)
								{
									Magic::RenderCore::Texture *local_18c = local_13c.FUN_009225a0();
									int local_190 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_18c->FUN_009227f0()), 8);

									FUN_004b3590(&local_13c, local_148->field_0x20[local_188].field_0x0, local_144->field_0x10c, local_144->field_0x110, local_148->field_0x0, local_148->field_0x4, local_18c->FUN_00922870(), local_18c->FUN_00922850(), local_13c.FUN_009225b0(), local_190);
								}
								break;
							}
							case 7:
							{
								int local_194 = local_148->FUN_00412290(param_1->field_0x11c[local_12c]->field_0x0);

								if (param_1->field_0x11c[local_12c]->field_0x10 && local_194 != -1)
								{
									Magic::RenderCore::Texture *local_198i = local_13c.FUN_009225a0();
									int local_19c = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_198i->FUN_009227f0()), 8);

									FUN_004b3390(&local_13c, local_148->field_0x20[local_194].field_0x0, local_144->field_0x10c, local_144->field_0x110, local_148->field_0x0, local_148->field_0x4, local_198i->FUN_00922870(), local_198i->FUN_00922850(), local_13c.FUN_009225b0(), local_19c);
								}
								break;
							}
							case 8:
							{
								int local_1a0 = local_148->FUN_00412290(param_1->field_0x11c[local_12c]->field_0x0);

								if (param_1->field_0x11c[local_12c]->field_0x10 && local_1a0 != -1)
								{
									Magic::RenderCore::Texture *local_1a4 = local_13c.FUN_009225a0();
									int local_1a8 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_1a4->FUN_009227f0()), 8);

									FUN_004b28d0(&local_13c, local_148->field_0x20[local_1a0].field_0x0, local_144->field_0x10c, local_144->field_0x110, local_148->field_0x0, local_148->field_0x4, local_1a4->FUN_00922870(), local_1a4->FUN_00922850(), local_13c.FUN_009225b0(), local_1a8, 0, 0);
								}
								break;
							}
							case 9:
							{
								int local_1ac = local_148->FUN_00412290(param_1->field_0x11c[local_12c]->field_0x0);

								if (param_1->field_0x11c[local_12c]->field_0x10 && local_1ac != -1)
								{
									Magic::RenderCore::Texture *local_1b0g = local_13c.FUN_009225a0();
									int local_1b4 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_1b0g->FUN_009227f0()), 8);

									FUN_004b2ab0(&local_13c, local_148->field_0x20[local_1ac].field_0x0, local_144->field_0x10c, local_144->field_0x110, local_148->field_0x0, local_148->field_0x4, local_1b0g->FUN_00922870(), local_1b0g->FUN_00922850(), local_13c.FUN_009225b0(), local_1b4);
								}
								break;
							}
							case 10:
							{
								Magic::RenderCore::Texture *local_1b8j = local_13c.FUN_009225a0();
								int local_1bcg = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_1b8j->FUN_009227f0()), 8);

								FUN_004b3260(&local_13c, local_144->field_0x10c, local_144->field_0x110, local_144->field_0x118, local_144->field_0x11c, local_144->field_0x124, local_144->field_0x128, local_1b8j->FUN_00922870(), local_1b8j->FUN_00922850(), local_13c.FUN_009225b0(), local_1bcg);
								break;
							}
							case 11:
							{
								int local_1c0 = local_148->FUN_00412290(param_1->field_0x11c[local_12c]->field_0x0);

								if (param_1->field_0x11c[local_12c]->field_0x10 && local_1c0 != -1)
								{
									Magic::RenderCore::Texture *local_1c4 = local_13c.FUN_009225a0();
									int local_1c8 = FUN_00922d50(Magic::RenderCore::DeviceUtility::GetSizeByPixelFormatInBit(local_1c4->FUN_009227f0()), 8);

									FUN_004b3710(&local_13c, local_148->field_0x20[local_1c0].field_0x0, local_144->field_0x10c, local_144->field_0x110, local_148->field_0x0, local_148->field_0x4, local_1c4->FUN_00922870(), local_1c4->FUN_00922850(), local_13c.FUN_009225b0(), local_1c8);
								}
								break;
							}
							}
						}
					}
				}
				param_1->field_0x11c[local_12c]->field_0x10->Unlock();
			}
		}
	}
}

// DIFF: code: the original puts the stack slot of the size test before the two element locals; the source that gives this order is unknown.
// FUNCTION: SADX 0x004b5ad0
void FUN_004b5ad0(void)
{
	unsigned int local_8gk;
	unsigned int local_ci;
	FUN_004b2330_0 *local_10hk;
	unsigned int local_14k;
	unsigned int local_18go;
	FUN_004b2330_0 *local_1co;
	unsigned int local_20go;
	FUN_004b2330_0 *local_24gl;
	unsigned int local_28g;
	FUN_004b2330_0 *local_2cgm;

	if (!(DAT_05b42414 & 1))
	{
		DAT_05b42414 |= 1;
		DAT_05b42404 = DAT_025adbd8;
	}
	if (((int)!(int)!memcmp(&DAT_05b42404, &DAT_05ad9654, 0x10) || DAT_05b42400 != DAT_05b422dc.size()) && DAT_025addd8)
	{
		if (DAT_05b423fc)
		{
			DAT_05b42404 = DAT_05ad9654;
			DAT_05b42400 = DAT_05b422dc.size();
		}
		if ((int)!(int)!memcmp(&DAT_05ad9654, &DAT_05b40a4c, 0x10) && (int)!(int)!memcmp(&DAT_05ad9654, &DAT_025adbf8, 0x10))
		{
			local_8gk = 0;
			for (local_ci = 0; local_ci < DAT_05b422dc.size(); local_ci++)
			{
				local_10hk = DAT_05b422dc[local_ci];
				for (local_14k = 0; local_14k < local_10hk->field_0x11c.size(); local_14k++)
				{
					FUN_004b6590_0 **local_30 = &local_10hk->field_0x11c[local_14k];
					FUN_004b6590_0 *local_34g = *local_30;
					if ((int)!memcmp(local_34g, &DAT_05ad9654, 0x10))
					{
						local_8gk = local_14k;
					}
				}
			}
			for (local_18go = 0; local_18go < DAT_05b422dc.size(); local_18go++)
			{
				local_1co = DAT_05b422dc[local_18go];
				if (local_1co)
				{
					if (local_1co->field_0x11c.size() > 0 && local_1co && local_1co->field_0x11c[local_8gk]->field_0x10 && local_1co->field_0x108)
					{
						*(Magic::RenderCore::Texture **)local_1co->field_0x108 = local_1co->field_0x11c[local_8gk]->field_0x10;
						DAT_05b423fc = 1;
					}
				}
			}
		}
		else
		{
			if ((int)!memcmp(&DAT_05ad9654, &DAT_025adbf8, 0x10))
			{
				for (local_20go = 0; local_20go < DAT_05b422dc.size(); local_20go++)
				{
					local_24gl = DAT_05b422dc[local_20go];
					if (local_24gl && local_24gl->field_0x118 && local_24gl->field_0x108)
					{
						*(Magic::RenderCore::Texture **)local_24gl->field_0x108 = local_24gl->field_0x118;
						DAT_05b423fc = 1;
					}
				}
			}
			else
			{
				for (local_28g = 0; local_28g < DAT_05b422dc.size(); local_28g++)
				{
					local_2cgm = DAT_05b422dc[local_28g];
					if (local_2cgm && local_2cgm->field_0x114 && local_2cgm->field_0x108)
					{
						*(Magic::RenderCore::Texture **)local_2cgm->field_0x108 = local_2cgm->field_0x114;
						DAT_05b423fc = 1;
					}
				}
			}
		}
	}
}

// DIFF: code: an always false loop test precedes the iterator dereference in the original.
// FUNCTION: SADX 0x004b5e70
void FUN_004b5e70(Magic::RenderCore::Texture **param_1)
{
	bool local_5i;
	unsigned int local_cj;
	FUN_004b2330_0 *local_10m;
	FUN_004b2330_0 *local_14;
	unsigned int local_18i;
	FUN_004b6590_0 *local_1c;

	if (param_1 != 0)
	{
		local_5i = false;
		DAT_05b422d8 = DAT_05b422dc.begin();
		for (local_cj = 0; local_cj < DAT_05b422dc.size(); local_cj++, DAT_05b422d8++)
		{
			local_10m = DAT_05b422dc[local_cj];
			if (local_10m != 0 && local_10m->field_0x108 == param_1)
			{
				local_5i = true;
				break;
			}
		}
		if (local_5i)
		{
			local_14 = *DAT_05b422d8;
			*local_14->field_0x108 = local_14->field_0x10c;
			if (local_14->field_0x114 != 0)
			{
				(local_14->field_0x114)->FUN_00922750();
				delete local_14->field_0x114;
				local_14->field_0x114 = 0;
			}
			if (local_14->field_0x118 != 0)
			{
				(local_14->field_0x118)->FUN_00922750();
				delete local_14->field_0x118;
				local_14->field_0x118 = 0;
			}
			if (local_14->field_0x110 != 0)
			{
				(local_14->field_0x110)->FUN_00922750();
				delete local_14->field_0x110;
				local_14->field_0x110 = 0;
			}
			for (local_18i = 0; local_18i < local_14->field_0x11c.size(); local_18i++)
			{
				local_1c = local_14->field_0x11c[local_18i];
				if (local_1c->field_0x10 != 0)
				{
					(local_1c->field_0x10)->FUN_00922750();
					delete local_1c->field_0x10;
					local_1c->field_0x10 = 0;
				}
			}
			DAT_05b422dc.erase(DAT_05b422d8);
		}
	}
}

// FUNCTION: SADX 0x004b6460
void FUN_004b6460(struct NJS_TEXLIST *param_1, char *param_2)
{
	struct NJS_TEXLIST *local_8 = param_1;
	if (local_8 != 0 && param_2 != 0)
	{
		for (unsigned int local_c = 0; local_c < local_8->nbTexture; local_c++)
		{
			struct NJS_TEXNAME *local_10 = *(struct NJS_TEXNAME **)((char *)local_8->textures + local_c * 0xc + 8);
			if (local_10 != 0)
			{
				int local_14 = *(int *)((char *)local_10 + 0x34);
				if (local_14 != 0)
				{
					memset(DAT_05b42418, 0, 0x104);
					sprintf_s(DAT_05b42418, 0x104, "%s_%d_", param_2, local_c);
					FUN_004b1cb0((int)((char *)local_10 + 0x34), local_14, (int)DAT_05b42418, 1);
				}
			}
		}
	}
}

// FUNCTION: SADX 0x004b6520
void FUN_004b6520(int param_1)
{
	int *local_8 = (int *)param_1;
	if (local_8 != 0)
	{
		for (unsigned int local_c = 0; local_c < (unsigned int)local_8[1]; local_c++)
		{
			int local_10 = *(int *)(*local_8 + local_c * 0xc + 8);
			if (local_10 != 0)
			{
				int local_14 = *(int *)(local_10 + 0x34);
				if (local_14 != 0)
				{
					FUN_004b5e70((Magic::RenderCore::Texture **)(local_10 + 0x34));
				}
			}
		}
	}
}

