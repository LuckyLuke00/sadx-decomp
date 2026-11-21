#include "decls.h"
#include "../advertise.h"
extern int DAT_05b422ec;
extern Magic::RenderCore::Texture *DAT_05b3e360;
extern Magic::RenderCore::Texture *DAT_05b3e364;
extern Magic::RenderCore::Texture *DAT_05b3e368;

// DIFF: frame: the original frame has 44 more bytes; their source is unknown.
// FUNCTION: SADX 0x004b0aa0
void LoadGameDDS()
{
	if (!DAT_05b3e364)
	{
		SOCFileStream local_1a4;

		if (local_1a4.ReadFile("system\\Tips_DDS\\BackTips.dds"))
		{
			DAT_05b3e364 = new Magic::RenderCore::Texture;
			DAT_05b3e364->Load(local_1a4.FUN_00424960(), 1, local_1a4.FUN_0040b8a0(), 0, 1, 0);
		}
	}
	if (!DAT_05b3e360)
	{
		SOCFileStream local_1ac;

		if (!FUN_0040ae00())
		{
			if (local_1ac.ReadFile("system\\DC\\AVA_TITLE_BACK2_E.dds"))
			{
				DAT_05b3e360 = new Magic::RenderCore::Texture;
				DAT_05b3e360->Load(local_1ac.FUN_00424960(), 1, local_1ac.FUN_0040b8a0(), 0, 1, 0);
			}
		}
		else
		{
			DAT_05b3e360 = 0;
		}
	}
	if (!DAT_05b3e368)
	{
		SOCFileStream local_1b4;

		switch (DAT_05b42a90)
		{
		case 5:
			if (local_1b4.ReadFile("system\\Tips_DDS\\Tips_I.dds"))
			{
				DAT_05b3e368 = new Magic::RenderCore::Texture;
				DAT_05b3e368->Load(local_1b4.FUN_00424960(), 1, local_1b4.FUN_0040b8a0(), 0, 1, 0);
			}
			break;
		case 4:
			if (local_1b4.ReadFile("system\\Tips_DDS\\Tips_G.dds"))
			{
				DAT_05b3e368 = new Magic::RenderCore::Texture;
				DAT_05b3e368->Load(local_1b4.FUN_00424960(), 1, local_1b4.FUN_0040b8a0(), 0, 1, 0);
			}
			break;
		case 3:
			if (local_1b4.ReadFile("system\\Tips_DDS\\Tips_S.dds"))
			{
				DAT_05b3e368 = new Magic::RenderCore::Texture;
				DAT_05b3e368->Load(local_1b4.FUN_00424960(), 1, local_1b4.FUN_0040b8a0(), 0, 1, 0);
			}
			break;
		case 2:
			if (local_1b4.ReadFile("system\\Tips_DDS\\Tips_F.dds"))
			{
				DAT_05b3e368 = new Magic::RenderCore::Texture;
				DAT_05b3e368->Load(local_1b4.FUN_00424960(), 1, local_1b4.FUN_0040b8a0(), 0, 1, 0);
			}
			break;
		case 0:
			if (local_1b4.ReadFile("system\\Tips_DDS\\Tips_J.dds"))
			{
				DAT_05b3e368 = new Magic::RenderCore::Texture;
				DAT_05b3e368->Load(local_1b4.FUN_00424960(), 1, local_1b4.FUN_0040b8a0(), 0, 1, 0);
			}
			break;
		default:
			if (local_1b4.ReadFile("system\\Tips_DDS\\Tips.dds"))
			{
				DAT_05b3e368 = new Magic::RenderCore::Texture;
				DAT_05b3e368->Load(local_1b4.FUN_00424960(), 1, local_1b4.FUN_0040b8a0(), 0, 1, 0);
			}
			break;
		}
	}
	static int DAT_05b422ec = DAT_05b3ebbc;
	if (!DAT_05b3e36c)
	{
		SOCFileStream local_1bc;

		switch (DAT_05b42a90)
		{
		case 5:
			if (local_1bc.ReadFile("system\\Tips_DDS\\Button_it.dds"))
			{
				DAT_05b3e36c = new Magic::RenderCore::Texture;
				DAT_05b3e36c->Load(local_1bc.FUN_00424960(), 1, local_1bc.FUN_0040b8a0(), 0, 1, 0);
				FUN_004b23e0(&DAT_05b3e36c, local_1bc.FUN_00424960(), local_1bc.FUN_0040b8a0(), "system_Tips_DDS_Button_it", DAT_05b42a90);
			}
			break;
		case 4:
			if (local_1bc.ReadFile("system\\Tips_DDS\\Button_de.dds"))
			{
				DAT_05b3e36c = new Magic::RenderCore::Texture;
				DAT_05b3e36c->Load(local_1bc.FUN_00424960(), 1, local_1bc.FUN_0040b8a0(), 0, 1, 0);
				FUN_004b23e0(&DAT_05b3e36c, local_1bc.FUN_00424960(), local_1bc.FUN_0040b8a0(), "system_Tips_DDS_Button_de", DAT_05b42a90);
			}
			break;
		case 3:
			if (local_1bc.ReadFile("system\\Tips_DDS\\Button_es.dds"))
			{
				DAT_05b3e36c = new Magic::RenderCore::Texture;
				DAT_05b3e36c->Load(local_1bc.FUN_00424960(), 1, local_1bc.FUN_0040b8a0(), 0, 1, 0);
				FUN_004b23e0(&DAT_05b3e36c, local_1bc.FUN_00424960(), local_1bc.FUN_0040b8a0(), "system_Tips_DDS_Button_es", DAT_05b42a90);
			}
			break;
		case 2:
			if (local_1bc.ReadFile("system\\Tips_DDS\\Button_fr.dds"))
			{
				DAT_05b3e36c = new Magic::RenderCore::Texture;
				DAT_05b3e36c->Load(local_1bc.FUN_00424960(), 1, local_1bc.FUN_0040b8a0(), 0, 1, 0);
				FUN_004b23e0(&DAT_05b3e36c, local_1bc.FUN_00424960(), local_1bc.FUN_0040b8a0(), "system_Tips_DDS_Button_fr", DAT_05b42a90);
			}
			break;
		case 0:
			if (local_1bc.ReadFile("system\\Tips_DDS\\Button_J.dds"))
			{
				DAT_05b3e36c = new Magic::RenderCore::Texture;
				DAT_05b3e36c->Load(local_1bc.FUN_00424960(), 1, local_1bc.FUN_0040b8a0(), 0, 1, 0);
				FUN_004b23e0(&DAT_05b3e36c, local_1bc.FUN_00424960(), local_1bc.FUN_0040b8a0(), "system_Tips_DDS_Button_it", DAT_05b42a90);
			}
			break;
		default:
			if (local_1bc.ReadFile("system\\Tips_DDS\\Button.dds"))
			{
				DAT_05b3e36c = new Magic::RenderCore::Texture;
				DAT_05b3e36c->Load(local_1bc.FUN_00424960(), 1, local_1bc.FUN_0040b8a0(), 0, 1, 0);
				FUN_004b23e0(&DAT_05b3e36c, local_1bc.FUN_00424960(), local_1bc.FUN_0040b8a0(), "system_Tips_DDS_Button", DAT_05b42a90);
			}
			break;
		}
	}
}
