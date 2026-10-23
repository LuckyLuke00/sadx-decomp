#include "decls.h"
extern struct TEXUVINFO DAT_0480a118;
extern struct obj object_csn_showerhead_showerhead[1];
extern struct CCL_INFO coll_srh[1];
extern struct obj object_csn_sr_light_sr_light[1];
extern struct CCL_INFO coll_srl[1];
extern struct obj object_cas_obj_slot_yoko_a_slot_yoko_a[1];
extern struct CCL_INFO coll_slot[1];
extern struct TEXUVINFO2 DAT_0480a104[];
extern struct TEXUVINFO2 DAT_0480a0e4[2];
extern struct obj object_cas_obj_map_2f_map_2f[1];
extern struct CCL_INFO coll_map2f[1];
extern struct TEXUVINFO DAT_0480a0a8;
extern struct TEXUVINFO DAT_0480a058;
extern struct TEXUVINFO DAT_0480a044;
extern struct TEXUVINFO DAT_0480a030;
extern struct TEXUVINFO DAT_0480a01c;
extern struct TEXUVINFO DAT_0480a008;
extern struct TEXUVINFO DAT_04809f90;
extern struct TEXUVINFO DAT_04809f18;
extern struct TEXUVINFO DAT_04809e60;
extern struct TEXUVINFO DAT_04809e20;
extern struct obj object_cas_obj_roolette_roolette[1];
extern struct obj object_cas_obj_gomi_r_gomi_r[1];
extern struct CCL_INFO coll_9[1];
extern struct NJS_ACTION action_cas_obj_gomi_r[1];
extern struct obj object_cas_obj_fune_gbox_fune_gbox[];
extern struct CCL_INFO coll_7[];
extern struct obj object_cas_obj_fune_hako_fune_hako[1];
extern struct CCL_INFO coll_6[1];
extern struct obj object_cas_obj_taru_taru;
extern struct CCL_INFO coll_4;
extern struct obj object_cas_obj_slot_isu_slot_isu[1];
extern struct CCL_INFO coll_slotisu[1];
extern struct obj object_cas_obj_fune_kdan_b_fune_kdan_b[1];
extern struct obj object_cas_obj_fune_kdan_a_fune_kdan_a[1];
extern struct obj object_csn_t_light_b_t_light_b[1];
extern struct obj object_csn_t_light_a_t_light_a[1];
void ObjCasino_InitS3(struct task *tp, struct obj *pobject);

// FUNCTION: SADX 0x0086d210
void ObjectCasinoLightA(struct task *tp)
{
	ObjCasino_InitS3(tp, (struct obj *)&object_csn_t_light_a_t_light_a);
}

// FUNCTION: SADX 0x0086d230
void ObjectCasinoLightB(struct task *tp)
{
	ObjCasino_InitS3(tp, (struct obj *)&object_csn_t_light_b_t_light_b);
}

// FUNCTION: SADX 0x0086d250
void ObjectCasinoFKdanA(struct task *tp)
{
	ObjCasino_InitG(tp, (struct obj *)&object_cas_obj_fune_kdan_a_fune_kdan_a);
}

// FUNCTION: SADX 0x0086d270
void ObjectCasinoFKdanB(struct task *tp)
{
	ObjCasino_InitG(tp, (struct obj *)&object_cas_obj_fune_kdan_b_fune_kdan_b);
}

// FUNCTION: SADX 0x0086d290
void ObjectCasinoSlotisu(struct task *tp)
{
	ObjCasino_InitCV(tp, 62500.0f, &object_cas_obj_slot_isu_slot_isu[0], &coll_slotisu[0], 1);
}

// FUNCTION: SADX 0x0086d2c0
void ObjectCasinoDentou(struct task *tp)
{
	ObjCasino_InitSCV(tp, 160000.0f, (struct obj *)&object_csn_dentou_dentou, (struct CCL_INFO *)&coll_dentou, 1);
}

// FUNCTION: SADX 0x0086d2f0
void ObjectCasinoFlowerA(struct task *tp)
{
	ObjCasino_InitCV(tp, 160000.0f, (struct obj *)&object_cas_obj_flower_a_flower_a, (struct CCL_INFO *)&coll_1, 1);
}

// FUNCTION: SADX 0x0086d320
void ObjectCasinoFlowerB(struct task *tp)
{
	ObjCasino_InitCV(tp, 160000.0f, (struct obj *)&object_cas_obj_flower_b_flower_b, (struct CCL_INFO *)&coll_2, 1);
}

// FUNCTION: SADX 0x0086d350
void ObjectCasinoFlowerA_L(struct task *tp)
{
	ObjCasino_InitCVL(tp, 160000.0f, (struct obj *)&object_cas_obj_flower_a_flower_a, (struct CCL_INFO *)&coll_1, 1);
}

// FUNCTION: SADX 0x0086d380
void ObjectCasinoFlowerB_L(struct task *tp)
{
	ObjCasino_InitCVL(tp, 160000.0f, (struct obj *)&object_cas_obj_flower_b_flower_b, (struct CCL_INFO *)&coll_2, 1);
}

// FUNCTION: SADX 0x0086d3b0
void ObjectCasinoSaku(struct task *tp)
{
	ObjCasino_InitCV(tp, 160000.0f, (struct obj *)&object_cas_obj_saku_saku, (struct CCL_INFO *)&coll_3, 2);
}

// FUNCTION: SADX 0x0086d3e0
void ObjectCasinoTaru(struct task *tp)
{
	ObjCasino_InitCV(tp, 160000.0f, &object_cas_obj_taru_taru, &coll_4, 1);
}

// FUNCTION: SADX 0x0086d410
void ObjectCasinoHako(struct task *tp)
{
	ObjCasino_InitCV(tp, 160000.0f, (struct obj *)&object_cas_obj_fune_hako_fune_hako, (struct CCL_INFO *)&coll_6, 1);
}

// FUNCTION: SADX 0x0086d440
void ObjectCasinoGBox(struct task *tp)
{
	ObjCasino_InitCV(tp, 160000.0f, (struct obj *)&object_cas_obj_fune_gbox_fune_gbox, (struct CCL_INFO *)&coll_7, 1);
}

// FUNCTION: SADX 0x0086d470
void ObjectCasinoGomiB(struct task *tp)
{
	ObjCasino_InitH(tp, (struct obj *)&object_cas_obj_gomi_b_gomi_b, (struct CCL_INFO *)&coll_8, (struct NJS_ACTION *)&action_cas_obj_gomi_b);
}

// FUNCTION: SADX 0x0086d490
void ObjectCasinoGomiR(struct task *tp)
{
	ObjCasino_InitH(tp, (struct obj *)&object_cas_obj_gomi_r_gomi_r, (struct CCL_INFO *)&coll_9, (struct NJS_ACTION *)&action_cas_obj_gomi_r);
}

// FUNCTION: SADX 0x0086d4b0
void ObjectCasinoRoolette(struct task *tp)
{
	ObjCasino_InitR(tp, (struct obj *)&object_cas_obj_roolette_roolette, 0x16c);
}

// FUNCTION: SADX 0x0086d4d0
void ObjectCasinoYukafuti(struct task *tp)
{
	ObjCasino_InitUV(tp, (struct obj *)&object_cas_obj_yuka_futi_yuka_futi, &DAT_04809e20, 1, 3);
}

// FUNCTION: SADX 0x0086d4f0
void ObjectCasinoRooletIta(struct task *tp)
{
	ObjCasino_InitUV(tp, (struct obj *)&object_cas_obj_roolet_ita_roolet_ita, &DAT_04809e60, 3, 3);
}

// FUNCTION: SADX 0x0086d510
void ObjectCasinoKanbanB(struct task *tp)
{
	ObjCasino_InitUVG(tp, (struct obj *)&object_cas_obj_nkanban_b_nkanban_b, &DAT_04809f18, 2, 3);
}

// FUNCTION: SADX 0x0086d530
void ObjectCasinoKanbanR(struct task *tp)
{
	ObjCasino_InitUVG(tp, (struct obj *)&object_cas_obj_nkanban_r_nkanban_r, &DAT_04809f90, 2, 3);
}

// FUNCTION: SADX 0x0086d550
void ObjectCasinoKanban1(struct task *tp)
{
	ObjCasino_InitUVC(tp, (struct obj *)&object_csn_kanban_a_kanban_a, (struct CCL_INFO *)&coll_kb, 1, &DAT_0480a008, 1, 1);
}

// FUNCTION: SADX 0x0086d580
void ObjectCasinoKanban2(struct task *tp)
{
	ObjCasino_InitUVC(tp, (struct obj *)&object_csn_kanban_b_kanban_b, (struct CCL_INFO *)&coll_kb, 1, &DAT_0480a01c, 1, 1);
}

// FUNCTION: SADX 0x0086d5b0
void ObjectCasinoKanban3(struct task *tp)
{
	ObjCasino_InitUVC(tp, (struct obj *)&object_csn_kanban_c_kanban_c, (struct CCL_INFO *)&coll_kb, 1, &DAT_0480a030, 1, 1);
}

// FUNCTION: SADX 0x0086d5e0
void ObjectCasinoKanban4(struct task *tp)
{
	ObjCasino_InitUVC(tp, (struct obj *)&object_csn_kanban_d_kanban_d, (struct CCL_INFO *)&coll_kb, 1, &DAT_0480a044, 1, 1);
}

// FUNCTION: SADX 0x0086d610
void ObjectCasinoTuriDenki(struct task *tp)
{
	late_ObjCasino_InitUV(tp, (struct obj *)&object_cas_obj_turi_denki_turi_denki, &DAT_0480a058, 1, 1);
}

// FUNCTION: SADX 0x0086d660
void ObjectCasinoSDFutiB(struct task *tp)
{
	ObjCasino_InitUVC(tp, (struct obj *)&object_cas_obj1_sdai_futi_b_sdai_futi_b, (struct CCL_INFO *)&coll_sdfuti, 1, &DAT_0480a0a8, 1, 3);
}

// FUNCTION: SADX 0x0086d690
void ObjectCasinoMap2F(struct task *tp)
{
	ObjCasino_InitSCV(tp, 360000.0f, (struct obj *)&object_cas_obj_map_2f_map_2f, (struct CCL_INFO *)&coll_map2f, 1);
}

// FUNCTION: SADX 0x0086d6c0
void ObjectCasinoMonitor(struct task *tp)
{
	ObjCasino_InitTGR(tp, (struct obj *)&object_cas_obj_ten_monitor_ten_monitor, (struct TEXANIMINFO *)&texaniminfo_monitor, 8, 1);
}

// FUNCTION: SADX 0x0086d6e0
void ObjectCasinoMizuA(struct task *tp)
{
	ObjCasino_InitUV2SE(tp, (struct obj *)&object_cas_obj_mizu_a_mizu_a, (struct TEXUVINFO2 *)&DAT_0480a0e4, 2, 0x10b);
}

// FUNCTION: SADX 0x0086d700
void ObjectCasinoMizuB(struct task *tp)
{
	ObjCasino_InitUV2SE(tp, (struct obj *)&object_cas_obj_mizu_b_mizu_b, (struct TEXUVINFO2 *)&DAT_0480a104, 1, 0x10b);
}

// FUNCTION: SADX 0x0086d720
void ObjectCasinoFSYA(struct task *tp)
{
	ObjCasino_InitCV(tp, 160000.0f, (struct obj *)&object_cas_obj_slot_yoko_a_slot_yoko_a, (struct CCL_INFO *)&coll_slot, 2);
}

// FUNCTION: SADX 0x0086d750
void ObjectCasinoFSYB(struct task *tp)
{
	ObjCasino_InitCV(tp, 160000.0f, (struct obj *)&object_cas_obj_slot_yoko_b_slot_yoko_b, (struct CCL_INFO *)&coll_slot, 2);
}

// FUNCTION: SADX 0x0086d780
void ObjectCasinoShowerLight(struct task *tp)
{
	ObjCasino_InitCV(tp, 62500.0f, (struct obj *)&object_csn_sr_light_sr_light, (struct CCL_INFO *)&coll_srl, 1);
}

// FUNCTION: SADX 0x0086d7b0
void ObjectCasinoShowerHead(struct task *tp)
{
	ObjCasino_InitCV(tp, 62500.0f, (struct obj *)&object_csn_showerhead_showerhead, (struct CCL_INFO *)&coll_srh, 1);
}

// FUNCTION: SADX 0x0086d7e0
void ObjectCasinoNeonKabe(struct task *tp)
{
	ObjCasino_InitUV(tp, (struct obj *)&object_cas_obj_neon_kabe_neon_kabe, &DAT_0480a118, 2, 3);
}
