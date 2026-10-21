// Generated from the names the source files use. Do not edit: change the sources instead.

#pragma once
#pragma warning(disable: 4480)
#include <stddef.h>

struct ___stcClip;
struct ___stcFog;
struct __MYMEM_DATA;
struct _camcontwk;
struct _CameraSystemWork;
struct _OBJ_ADJUSTPARAM;
struct _OBJ_CAMERAPARAM;
struct _SC_NUMBERS;
struct ADV1_AL_BODY;
struct ADV1_AL_FACE;
struct ADV1_AL_ICON;
struct ADV1_AL_IMPLESSION;
struct ADV1_AL_IMPLESSION2;
struct ADV1_AL_MEMORY;
struct ADV1_AL_MOTION_CTRL;
struct ADV1_AL_PERCEPTION;
struct ADV1_AL_SHADOW;
struct ADV1_AL_TMP_STATUS;
struct al_action_ctrl;
struct al_motion_table;
struct AL_RECORD;
struct al_status;
struct alifewk;
struct Alr;
struct AlrCam;
struct AlrCamAround;
struct AlrCamData;
struct AlrCamEllipse;
struct AlrCamEndgoal;
struct AlrCamEntrance;
struct AlrCamFixed;
struct AlrData;
struct AlrEff;
struct AlrEffUnit;
struct AlrEntry;
struct AlrEvent;
struct AlrFanFan;
struct AlrGoalInfo;
struct AlrMemory;
struct AlrRank;
struct AlrReal;
struct AlrRoot;
struct AlrTimer;
struct AlrTimerUnit;
struct AlrVms;
struct AlrVmsTime;
struct AlrZoneUnit;
struct Angle3;
struct anywk;
struct bankdata;
struct bankdatalist;
struct BOSSPLAYER_CREATE_PARAM;
struct c_colli_hit_info;
struct CCL_INFO;
struct CharMdlWk;
struct colliwk;
struct CRUSHLIGHT_WK;
struct csts;
struct DDlgType;
struct DialogPrmType;
struct DlgSndPrmType;
struct erctrlstr;
struct eventwk;
struct FACETBL;
struct FileSelWk;
struct forcewk;
struct GH_FONT_INFO;
struct GHPARTICLE_INFO;
struct GHPARTICLE_UNIT;
struct GHSPRITE;
struct GHSPRITE_ANIM;
struct GHSPRITE_ANIM_TABLE;
struct HintMessageMemory;
struct HintMessageString;
struct HintMessageTable;
struct LATE_FAR_Z_T;
struct LATE_LNK;
struct LE_LIGHT_ENV;
struct LE_PALIGHT_ENV;
struct LightInfo;
struct MDHANDLE;
struct ModeSelPrmType;
struct motionwk;
struct motionwk2;
struct MSGC;
struct mtnjvwk;
struct NJS_ACTION;
struct NJS_ACTION_LINK;
struct NJS_ARGB;
struct NJS_BGRA;
struct NJS_CACTION;
struct NJS_CAMERA;
union NJS_COLOR;
struct NJS_MATERIAL;
struct NJS_MESHSET;
struct NJS_MODEL;
struct NJS_MOTION;
struct NJS_MOTION_LINK;
struct NJS_POINT2;
struct NJS_POINT2COL;
struct NJS_POINT3;
struct NJS_POINT3COL;
struct NJS_RGB;
struct NJS_SPRITE;
struct NJS_TEX;
struct NJS_TEXANIM;
struct NJS_TEXLIST;
struct NJS_TEXNAME;
struct NJS_TEXTURE_VTX;
struct NpcMessageTable;
struct obj;
struct OBJ_CONDITION;
struct OBJ_EDITENTRY;
struct OBJ_SLEEPCON;
struct PanelPrmType;
struct particle_entry;
struct particle_info;
struct pathtag;
struct pathtbl;
struct PL_ACTION;
struct PL_FACE;
struct PL_JOIN_VERTEX;
struct PL_LANDPOSI;
struct player_parameter;
struct playerwk;
struct SAVE_DATA;
struct SEQ_CLEAR_EQUIV;
struct SEQ_SECTION;
struct SEQ_SECTIONTBL;
struct SeqPrmType;
struct shadowwk;
struct sp_info;
struct sp_link;
struct sp_task;
struct task;
struct TaskCommunication;
struct TaskInfo;
struct taskwk;
struct thread;
struct u4s;
union UNION_STATUS;
struct VolumeInfo;
struct xssunit;
struct xyyzzxsdwstr;

enum AdvaModeEnum : int {
    ADVA_MODE_NONE = 0,
    ADVA_MODE_CHAR_SEL = 1,
    ADVA_MODE_FILE_SEL = 2,
    ADVA_MODE_TRIALACT_SEL = 3,
    ADVA_MODE_SND_TEST = 4,
    ADVA_MODE_TITLE_NEW = 5,
    ADVA_MODE_TITLE_MENU = 6,
    ADVA_MODE_OPTION_SEL = 7,
    ADVA_MODE_EXPLAIN = 8,
    ADVA_MODE_MINIGAME_SEL = 9,
    ADVA_MODE_EMBLEMVIEW = 10,
    ADVA_MODE_INETDEMO = 11,
    ADVA_MODE_TVSETTING = 12,
    ADVA_MODE_PUTI = 13,
    ADVA_MODE_TITLE_MENU_SUB = 14,
    ADVA_MODE_TITLE_MENU_LB = 15,
    ADVA_MODE_UN_TRIAL_GAME = 16,
    ADVA_MODE_UN_LEAD_BORADS = 17,
    ADVA_MODE_UN_ACHIVEMENT = 18,
    ADVA_MODE_OPTION_MENU_SUB = 19,
    ADVA_MODE_HOW_TO_PLAY = 20,
    ADVA_MODE_HOW_TO_PLAY2 = 21,
    ADVA_MODE_LB_MENU = 22,
    ADVA_MODE_OP_CREDITS = 23,
    ADVA_MODE_VANISH = 24,
    ADVA_MODE_END = 25,
    ADVA_MODE_END2 = 26,
    ADVA_MODE_MAX = 27,
};
static_assert(sizeof(AdvaModeEnum) == 4, "sizeof AdvaModeEnum");

enum AdvaStatEnum : int {
    ADVA_STAT_REQWAIT = 0,
    ADVA_STAT_FADEIN = 1,
    ADVA_STAT_KEEP = 2,
    ADVA_STAT_FADEOUT = 3,
    ADVA_STAT_MAX = 4,
};
static_assert(sizeof(AdvaStatEnum) == 4, "sizeof AdvaStatEnum");

enum AvaCharEnum : int {
    AVA_SONIC = 0,
    AVA_MILES = 1,
    AVA_KNUCKLES = 2,
    AVA_AMY = 3,
    AVA_BIG = 4,
    AVA_E_102 = 5,
    AVA_SUPERSONIC = 6,
    AVA_METALSONIC = 6,
    AVA_CHAR_MAX = 7,
};
static_assert(sizeof(AvaCharEnum) == 4, "sizeof AvaCharEnum");

enum DlgPnlStyleEnum : int {
    DLG_PNLSTYLE_MARU = 0,
    DLG_PNLSTYLE_SIKAKU = 1,
    DLG_PNLSTYLE_MARU4 = 2,
    DLG_PNLSTYLE_MARUSO = 3,
    DLG_PNLSTYLE_SIKAKU2 = 4,
    DLG_PNLSTYLE_MARU2 = 5,
    DLG_PNLSTYLE_MAX = 6,
};
static_assert(sizeof(DlgPnlStyleEnum) == 4, "sizeof DlgPnlStyleEnum");

enum EVBOSS_TYPE : int {
    EVBOSS_TYPE_SONIC_VS_KNUCKLES = 0,
    EVBOSS_TYPE_SONIC_VS_E102 = 1,
    EVBOSS_TYPE_KNUCKLES_VS_SONIC = 2,
    EVBOSS_TYPE_KNUCKLES_VS_MILES = 3,
    EVBOSS_TYPE_E102_VS_SONIC = 4,
    EVBOSS_TYPE_E102_VS_MILES = 5,
    NB_EVBOSS_TYPE = 6,
};
static_assert(sizeof(EVBOSS_TYPE) == 4, "sizeof EVBOSS_TYPE");

enum FileSbMdEnum : int {
    FILESEL_SMD_STAY = 0,
    FILESEL_SMD_STAY2 = 1,
    FILESEL_SMD_DECIDE = 2,
    FILESEL_SMD_DELETE = 3,
    FILESEL_SMD_DELETE2 = 4,
    FILESEL_SMD_DELETEMISS = 5,
    FILESEL_SMD_PRE_SAVE_INET_SC = 6,
    FILESEL_SMD_SAVE_INET_SC = 7,
    FILESEL_SMD_AFTER_SAVE_INET_SC = 8,
    FILESEL_SMD_BACK = 9,
    FILESEL_SMD_NWAIT = 10,
    FILESEL_SMD_CRC_ERR = 11,
    FILESEL_SMD_FIRST_SAVE = 12,
    FILESEL_SMD_FIRST_SAVE2 = 13,
    FILESEL_SMD_FILE_MAX = 14,
    FILESEL_SMD_FILE_MAX2 = 15,
    FILESEL_SMD_BROKEN = 16,
    FILESEL_SMD_MEMOCA = 17,
    FILESEL_SMD_MAX = 18,
};
static_assert(sizeof(FileSbMdEnum) == 4, "sizeof FileSbMdEnum");

// Offsets not checked against the code yet.
struct ADV1_AL_BODY {
    struct obj *object;
    struct obj *my_parts[50];
    struct obj *zero[50];
    struct obj *standard[50];
    struct obj *fly[50];
    struct obj *run[50];
    struct obj *power[50];
    struct obj *swim[50];
    struct NJS_TEXLIST *tex;
};
static_assert(sizeof(ADV1_AL_BODY) == 0x580, "sizeof ADV1_AL_BODY");
static_assert(offsetof(ADV1_AL_BODY, object) == 0x0, "ADV1_AL_BODY::object");
static_assert(offsetof(ADV1_AL_BODY, my_parts) == 0x4, "ADV1_AL_BODY::my_parts");
static_assert(offsetof(ADV1_AL_BODY, zero) == 0xcc, "ADV1_AL_BODY::zero");
static_assert(offsetof(ADV1_AL_BODY, standard) == 0x194, "ADV1_AL_BODY::standard");
static_assert(offsetof(ADV1_AL_BODY, fly) == 0x25c, "ADV1_AL_BODY::fly");
static_assert(offsetof(ADV1_AL_BODY, run) == 0x324, "ADV1_AL_BODY::run");
static_assert(offsetof(ADV1_AL_BODY, power) == 0x3ec, "ADV1_AL_BODY::power");
static_assert(offsetof(ADV1_AL_BODY, swim) == 0x4b4, "ADV1_AL_BODY::swim");
static_assert(offsetof(ADV1_AL_BODY, tex) == 0x57c, "ADV1_AL_BODY::tex");

struct ADV1_AL_FACE {
    unsigned short timer1;
    unsigned short timer2;
    unsigned short timer3;
    long eye_keep_timer;
    long mouse_keep_timer;
    long eyelid_keep_timer;
    unsigned long flag;
    long eyelid_brink_ang;
    long eyelid_close_ang;
    long eyelid_curr_close_ang;
    long eyelid_request_close_ang;
    long eyelid_default_close_ang;
    long eyelid_express_ang;
    long eyelid_curr_express_ang;
    long eyelid_request_express_ang;
    long eyelid_default_express_ang;
    short eye_default_num;
    short eye_request_num;
    short mouse1_default_num;
    short mouse2_default_num;
    short mouse1_request_num;
    short mouse2_request_num;
};
static_assert(sizeof(ADV1_AL_FACE) == 0x48, "sizeof ADV1_AL_FACE");
static_assert(offsetof(ADV1_AL_FACE, timer1) == 0x0, "ADV1_AL_FACE::timer1");
static_assert(offsetof(ADV1_AL_FACE, timer2) == 0x2, "ADV1_AL_FACE::timer2");
static_assert(offsetof(ADV1_AL_FACE, timer3) == 0x4, "ADV1_AL_FACE::timer3");
static_assert(offsetof(ADV1_AL_FACE, eye_keep_timer) == 0x8, "ADV1_AL_FACE::eye_keep_timer");
static_assert(offsetof(ADV1_AL_FACE, mouse_keep_timer) == 0xc, "ADV1_AL_FACE::mouse_keep_timer");
static_assert(offsetof(ADV1_AL_FACE, eyelid_keep_timer) == 0x10, "ADV1_AL_FACE::eyelid_keep_timer");
static_assert(offsetof(ADV1_AL_FACE, flag) == 0x14, "ADV1_AL_FACE::flag");
static_assert(offsetof(ADV1_AL_FACE, eyelid_brink_ang) == 0x18, "ADV1_AL_FACE::eyelid_brink_ang");
static_assert(offsetof(ADV1_AL_FACE, eyelid_close_ang) == 0x1c, "ADV1_AL_FACE::eyelid_close_ang");
static_assert(offsetof(ADV1_AL_FACE, eyelid_curr_close_ang) == 0x20, "ADV1_AL_FACE::eyelid_curr_close_ang");
static_assert(offsetof(ADV1_AL_FACE, eyelid_request_close_ang) == 0x24, "ADV1_AL_FACE::eyelid_request_close_ang");
static_assert(offsetof(ADV1_AL_FACE, eyelid_default_close_ang) == 0x28, "ADV1_AL_FACE::eyelid_default_close_ang");
static_assert(offsetof(ADV1_AL_FACE, eyelid_express_ang) == 0x2c, "ADV1_AL_FACE::eyelid_express_ang");
static_assert(offsetof(ADV1_AL_FACE, eyelid_curr_express_ang) == 0x30, "ADV1_AL_FACE::eyelid_curr_express_ang");
static_assert(offsetof(ADV1_AL_FACE, eyelid_request_express_ang) == 0x34, "ADV1_AL_FACE::eyelid_request_express_ang");
static_assert(offsetof(ADV1_AL_FACE, eyelid_default_express_ang) == 0x38, "ADV1_AL_FACE::eyelid_default_express_ang");
static_assert(offsetof(ADV1_AL_FACE, eye_default_num) == 0x3c, "ADV1_AL_FACE::eye_default_num");
static_assert(offsetof(ADV1_AL_FACE, eye_request_num) == 0x3e, "ADV1_AL_FACE::eye_request_num");
static_assert(offsetof(ADV1_AL_FACE, mouse1_default_num) == 0x40, "ADV1_AL_FACE::mouse1_default_num");
static_assert(offsetof(ADV1_AL_FACE, mouse2_default_num) == 0x42, "ADV1_AL_FACE::mouse2_default_num");
static_assert(offsetof(ADV1_AL_FACE, mouse1_request_num) == 0x44, "ADV1_AL_FACE::mouse1_request_num");
static_assert(offsetof(ADV1_AL_FACE, mouse2_request_num) == 0x46, "ADV1_AL_FACE::mouse2_request_num");

// Some offsets are wrong for this exe: check them against the code.
struct NJS_BGRA {
    unsigned char a;
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
static_assert(sizeof(NJS_BGRA) == 0x4, "sizeof NJS_BGRA");
static_assert(offsetof(NJS_BGRA, a) == 0x0, "NJS_BGRA::a");
static_assert(offsetof(NJS_BGRA, r) == 0x1, "NJS_BGRA::r");
static_assert(offsetof(NJS_BGRA, g) == 0x2, "NJS_BGRA::g");
static_assert(offsetof(NJS_BGRA, b) == 0x3, "NJS_BGRA::b");

// Some offsets are wrong for this exe: check them against the code.
struct NJS_TEX {
    short v;
    short u;
};
static_assert(sizeof(NJS_TEX) == 0x4, "sizeof NJS_TEX");
static_assert(offsetof(NJS_TEX, v) == 0x0, "NJS_TEX::v");
static_assert(offsetof(NJS_TEX, u) == 0x2, "NJS_TEX::u");

union NJS_COLOR {
    unsigned long color;
    struct NJS_TEX tex;
    struct NJS_BGRA argb;
};
static_assert(sizeof(NJS_COLOR) == 0x4, "sizeof NJS_COLOR");
static_assert(offsetof(NJS_COLOR, color) == 0x0, "NJS_COLOR::color");
static_assert(offsetof(NJS_COLOR, tex) == 0x0, "NJS_COLOR::tex");
static_assert(offsetof(NJS_COLOR, argb) == 0x0, "NJS_COLOR::argb");

struct NJS_POINT3 {
    float x;
    float y;
    float z;
};
static_assert(sizeof(NJS_POINT3) == 0xc, "sizeof NJS_POINT3");
static_assert(offsetof(NJS_POINT3, x) == 0x0, "NJS_POINT3::x");
static_assert(offsetof(NJS_POINT3, y) == 0x4, "NJS_POINT3::y");
static_assert(offsetof(NJS_POINT3, z) == 0x8, "NJS_POINT3::z");

struct ADV1_AL_ICON {
    unsigned short flag;
    unsigned short mode;
    unsigned short timer;
    unsigned short next_mode;
    unsigned short next_timer;
    struct NJS_POINT3 pos;
    struct NJS_POINT3 velo;
    struct NJS_POINT3 diff;
    long phase;
    unsigned short timer_u;
    unsigned short icon_num_u;
    unsigned short smode_u;
    float ang_u;
    float ang_spd_u;
    struct NJS_POINT3 pos_u;
    struct NJS_POINT3 velo_u;
    struct NJS_POINT3 scl_u;
    struct NJS_POINT3 sclspd_u;
    unsigned short timer_d;
    unsigned short icon_num_d;
    unsigned short smode_d;
    float ang_d;
    float ang_spd_d;
    struct NJS_POINT3 pos_d;
    struct NJS_POINT3 velo_d;
    struct NJS_POINT3 scl_d;
    struct NJS_POINT3 sclspd_d;
    union NJS_COLOR col;
};
static_assert(sizeof(ADV1_AL_ICON) == 0xb8, "sizeof ADV1_AL_ICON");
static_assert(offsetof(ADV1_AL_ICON, flag) == 0x0, "ADV1_AL_ICON::flag");
static_assert(offsetof(ADV1_AL_ICON, mode) == 0x2, "ADV1_AL_ICON::mode");
static_assert(offsetof(ADV1_AL_ICON, timer) == 0x4, "ADV1_AL_ICON::timer");
static_assert(offsetof(ADV1_AL_ICON, next_mode) == 0x6, "ADV1_AL_ICON::next_mode");
static_assert(offsetof(ADV1_AL_ICON, next_timer) == 0x8, "ADV1_AL_ICON::next_timer");
static_assert(offsetof(ADV1_AL_ICON, pos) == 0xc, "ADV1_AL_ICON::pos");
static_assert(offsetof(ADV1_AL_ICON, velo) == 0x18, "ADV1_AL_ICON::velo");
static_assert(offsetof(ADV1_AL_ICON, diff) == 0x24, "ADV1_AL_ICON::diff");
static_assert(offsetof(ADV1_AL_ICON, phase) == 0x30, "ADV1_AL_ICON::phase");
static_assert(offsetof(ADV1_AL_ICON, timer_u) == 0x34, "ADV1_AL_ICON::timer_u");
static_assert(offsetof(ADV1_AL_ICON, icon_num_u) == 0x36, "ADV1_AL_ICON::icon_num_u");
static_assert(offsetof(ADV1_AL_ICON, smode_u) == 0x38, "ADV1_AL_ICON::smode_u");
static_assert(offsetof(ADV1_AL_ICON, ang_u) == 0x3c, "ADV1_AL_ICON::ang_u");
static_assert(offsetof(ADV1_AL_ICON, ang_spd_u) == 0x40, "ADV1_AL_ICON::ang_spd_u");
static_assert(offsetof(ADV1_AL_ICON, pos_u) == 0x44, "ADV1_AL_ICON::pos_u");
static_assert(offsetof(ADV1_AL_ICON, velo_u) == 0x50, "ADV1_AL_ICON::velo_u");
static_assert(offsetof(ADV1_AL_ICON, scl_u) == 0x5c, "ADV1_AL_ICON::scl_u");
static_assert(offsetof(ADV1_AL_ICON, sclspd_u) == 0x68, "ADV1_AL_ICON::sclspd_u");
static_assert(offsetof(ADV1_AL_ICON, timer_d) == 0x74, "ADV1_AL_ICON::timer_d");
static_assert(offsetof(ADV1_AL_ICON, icon_num_d) == 0x76, "ADV1_AL_ICON::icon_num_d");
static_assert(offsetof(ADV1_AL_ICON, smode_d) == 0x78, "ADV1_AL_ICON::smode_d");
static_assert(offsetof(ADV1_AL_ICON, ang_d) == 0x7c, "ADV1_AL_ICON::ang_d");
static_assert(offsetof(ADV1_AL_ICON, ang_spd_d) == 0x80, "ADV1_AL_ICON::ang_spd_d");
static_assert(offsetof(ADV1_AL_ICON, pos_d) == 0x84, "ADV1_AL_ICON::pos_d");
static_assert(offsetof(ADV1_AL_ICON, velo_d) == 0x90, "ADV1_AL_ICON::velo_d");
static_assert(offsetof(ADV1_AL_ICON, scl_d) == 0x9c, "ADV1_AL_ICON::scl_d");
static_assert(offsetof(ADV1_AL_ICON, sclspd_d) == 0xa8, "ADV1_AL_ICON::sclspd_d");
static_assert(offsetof(ADV1_AL_ICON, col) == 0xb4, "ADV1_AL_ICON::col");

// Offsets not checked against the code yet.
struct ADV1_AL_IMPLESSION {
    signed char like;
    unsigned char meet;
};
static_assert(sizeof(ADV1_AL_IMPLESSION) == 0x2, "sizeof ADV1_AL_IMPLESSION");
static_assert(offsetof(ADV1_AL_IMPLESSION, like) == 0x0, "ADV1_AL_IMPLESSION::like");
static_assert(offsetof(ADV1_AL_IMPLESSION, meet) == 0x1, "ADV1_AL_IMPLESSION::meet");

// Offsets not checked against the code yet.
struct ADV1_AL_IMPLESSION2 {
    unsigned long id;
    unsigned char like;
    unsigned char meet;
};
static_assert(sizeof(ADV1_AL_IMPLESSION2) == 0x8, "sizeof ADV1_AL_IMPLESSION2");
static_assert(offsetof(ADV1_AL_IMPLESSION2, id) == 0x0, "ADV1_AL_IMPLESSION2::id");
static_assert(offsetof(ADV1_AL_IMPLESSION2, like) == 0x4, "ADV1_AL_IMPLESSION2::like");
static_assert(offsetof(ADV1_AL_IMPLESSION2, meet) == 0x5, "ADV1_AL_IMPLESSION2::meet");

// Offsets not checked against the code yet.
struct ADV1_AL_MEMORY {
    struct ADV1_AL_IMPLESSION player[6];
    struct ADV1_AL_IMPLESSION2 chao[32];
};
static_assert(sizeof(ADV1_AL_MEMORY) == 0x10c, "sizeof ADV1_AL_MEMORY");
static_assert(offsetof(ADV1_AL_MEMORY, player) == 0x0, "ADV1_AL_MEMORY::player");
static_assert(offsetof(ADV1_AL_MEMORY, chao) == 0xc, "ADV1_AL_MEMORY::chao");

// Offsets not checked against the code yet.
struct ADV1_AL_MOTION_CTRL {
    unsigned short mode;
    unsigned short flag;
    unsigned short timer;
    short curr_num;
    short link_num;
    short req_num;
    float nframe;
    float pframe;
    float lframe;
    float link_ratio;
    float multi_spd;
    struct al_motion_table *motion_table;
};
static_assert(sizeof(ADV1_AL_MOTION_CTRL) == 0x24, "sizeof ADV1_AL_MOTION_CTRL");
static_assert(offsetof(ADV1_AL_MOTION_CTRL, mode) == 0x0, "ADV1_AL_MOTION_CTRL::mode");
static_assert(offsetof(ADV1_AL_MOTION_CTRL, flag) == 0x2, "ADV1_AL_MOTION_CTRL::flag");
static_assert(offsetof(ADV1_AL_MOTION_CTRL, timer) == 0x4, "ADV1_AL_MOTION_CTRL::timer");
static_assert(offsetof(ADV1_AL_MOTION_CTRL, curr_num) == 0x6, "ADV1_AL_MOTION_CTRL::curr_num");
static_assert(offsetof(ADV1_AL_MOTION_CTRL, link_num) == 0x8, "ADV1_AL_MOTION_CTRL::link_num");
static_assert(offsetof(ADV1_AL_MOTION_CTRL, req_num) == 0xa, "ADV1_AL_MOTION_CTRL::req_num");
static_assert(offsetof(ADV1_AL_MOTION_CTRL, nframe) == 0xc, "ADV1_AL_MOTION_CTRL::nframe");
static_assert(offsetof(ADV1_AL_MOTION_CTRL, pframe) == 0x10, "ADV1_AL_MOTION_CTRL::pframe");
static_assert(offsetof(ADV1_AL_MOTION_CTRL, lframe) == 0x14, "ADV1_AL_MOTION_CTRL::lframe");
static_assert(offsetof(ADV1_AL_MOTION_CTRL, link_ratio) == 0x18, "ADV1_AL_MOTION_CTRL::link_ratio");
static_assert(offsetof(ADV1_AL_MOTION_CTRL, multi_spd) == 0x1c, "ADV1_AL_MOTION_CTRL::multi_spd");
static_assert(offsetof(ADV1_AL_MOTION_CTRL, motion_table) == 0x20, "ADV1_AL_MOTION_CTRL::motion_table");

// Offsets not checked against the code yet.
struct ADV1_AL_PERCEPTION {
    unsigned long flag;
};
static_assert(sizeof(ADV1_AL_PERCEPTION) == 0x4, "sizeof ADV1_AL_PERCEPTION");
static_assert(offsetof(ADV1_AL_PERCEPTION, flag) == 0x0, "ADV1_AL_PERCEPTION::flag");

struct xssunit {
    long findflag;
    long objatt;
    long angx;
    long angz;
    float onpos;
    struct NJS_POINT3 normal;
};
static_assert(sizeof(xssunit) == 0x20, "sizeof xssunit");
static_assert(offsetof(xssunit, findflag) == 0x0, "xssunit::findflag");
static_assert(offsetof(xssunit, objatt) == 0x4, "xssunit::objatt");
static_assert(offsetof(xssunit, angx) == 0x8, "xssunit::angx");
static_assert(offsetof(xssunit, angz) == 0xc, "xssunit::angz");
static_assert(offsetof(xssunit, onpos) == 0x10, "xssunit::onpos");
static_assert(offsetof(xssunit, normal) == 0x14, "xssunit::normal");

struct xyyzzxsdwstr {
    struct NJS_POINT3 pos;
    struct xssunit hit[6];
};
static_assert(sizeof(xyyzzxsdwstr) == 0xcc, "sizeof xyyzzxsdwstr");
static_assert(offsetof(xyyzzxsdwstr, pos) == 0x0, "xyyzzxsdwstr::pos");
static_assert(offsetof(xyyzzxsdwstr, hit) == 0xc, "xyyzzxsdwstr::hit");

// Offsets not checked against the code yet.
struct ADV1_AL_SHADOW {
    unsigned short flag;
    struct NJS_POINT3 colli_center;
    float colli_top;
    float colli_radius;
    float colli_bottom;
    float cliff_height;
    float bound_side;
    float bound_floor;
    float bound_friction;
    float bound_ceiling;
    long bound_add_angle;
    float shadow_scl;
    float shadow_scl_ratio;
    float water_pos;
    struct xyyzzxsdwstr si;
};
static_assert(sizeof(ADV1_AL_SHADOW) == 0x10c, "sizeof ADV1_AL_SHADOW");
static_assert(offsetof(ADV1_AL_SHADOW, flag) == 0x0, "ADV1_AL_SHADOW::flag");
static_assert(offsetof(ADV1_AL_SHADOW, colli_center) == 0x4, "ADV1_AL_SHADOW::colli_center");
static_assert(offsetof(ADV1_AL_SHADOW, colli_top) == 0x10, "ADV1_AL_SHADOW::colli_top");
static_assert(offsetof(ADV1_AL_SHADOW, colli_radius) == 0x14, "ADV1_AL_SHADOW::colli_radius");
static_assert(offsetof(ADV1_AL_SHADOW, colli_bottom) == 0x18, "ADV1_AL_SHADOW::colli_bottom");
static_assert(offsetof(ADV1_AL_SHADOW, cliff_height) == 0x1c, "ADV1_AL_SHADOW::cliff_height");
static_assert(offsetof(ADV1_AL_SHADOW, bound_side) == 0x20, "ADV1_AL_SHADOW::bound_side");
static_assert(offsetof(ADV1_AL_SHADOW, bound_floor) == 0x24, "ADV1_AL_SHADOW::bound_floor");
static_assert(offsetof(ADV1_AL_SHADOW, bound_friction) == 0x28, "ADV1_AL_SHADOW::bound_friction");
static_assert(offsetof(ADV1_AL_SHADOW, bound_ceiling) == 0x2c, "ADV1_AL_SHADOW::bound_ceiling");
static_assert(offsetof(ADV1_AL_SHADOW, bound_add_angle) == 0x30, "ADV1_AL_SHADOW::bound_add_angle");
static_assert(offsetof(ADV1_AL_SHADOW, shadow_scl) == 0x34, "ADV1_AL_SHADOW::shadow_scl");
static_assert(offsetof(ADV1_AL_SHADOW, shadow_scl_ratio) == 0x38, "ADV1_AL_SHADOW::shadow_scl_ratio");
static_assert(offsetof(ADV1_AL_SHADOW, water_pos) == 0x3c, "ADV1_AL_SHADOW::water_pos");
static_assert(offsetof(ADV1_AL_SHADOW, si) == 0x40, "ADV1_AL_SHADOW::si");

struct NJS_ARGB {
    float a;
    float r;
    float g;
    float b;
};
static_assert(sizeof(NJS_ARGB) == 0x10, "sizeof NJS_ARGB");
static_assert(offsetof(NJS_ARGB, a) == 0x0, "NJS_ARGB::a");
static_assert(offsetof(NJS_ARGB, r) == 0x4, "NJS_ARGB::r");
static_assert(offsetof(NJS_ARGB, g) == 0x8, "NJS_ARGB::g");
static_assert(offsetof(NJS_ARGB, b) == 0xc, "NJS_ARGB::b");

// Offsets not checked against the code yet.
struct ADV1_AL_TMP_STATUS {
    float aim_h_pos;
    float aim_v_pos;
    float aim_grouth;
    struct NJS_ARGB aim_argb;
};
static_assert(sizeof(ADV1_AL_TMP_STATUS) == 0x1c, "sizeof ADV1_AL_TMP_STATUS");
static_assert(offsetof(ADV1_AL_TMP_STATUS, aim_h_pos) == 0x0, "ADV1_AL_TMP_STATUS::aim_h_pos");
static_assert(offsetof(ADV1_AL_TMP_STATUS, aim_v_pos) == 0x4, "ADV1_AL_TMP_STATUS::aim_v_pos");
static_assert(offsetof(ADV1_AL_TMP_STATUS, aim_grouth) == 0x8, "ADV1_AL_TMP_STATUS::aim_grouth");
static_assert(offsetof(ADV1_AL_TMP_STATUS, aim_argb) == 0xc, "ADV1_AL_TMP_STATUS::aim_argb");

struct Angle3 {
    long x;
    long y;
    long z;
};
static_assert(sizeof(Angle3) == 0xc, "sizeof Angle3");
static_assert(offsetof(Angle3, x) == 0x0, "Angle3::x");
static_assert(offsetof(Angle3, y) == 0x4, "Angle3::y");
static_assert(offsetof(Angle3, z) == 0x8, "Angle3::z");

// Offsets not checked against the code yet.
struct AlrEffUnit {
    struct NJS_POINT3 trans;
    struct NJS_POINT3 velocity;
    unsigned char frame;
    signed char frame_inc_time;
    unsigned char mode;
    unsigned char flag;
    unsigned short timer;
    unsigned short tmp;
};
static_assert(sizeof(AlrEffUnit) == 0x20, "sizeof AlrEffUnit");
static_assert(offsetof(AlrEffUnit, trans) == 0x0, "AlrEffUnit::trans");
static_assert(offsetof(AlrEffUnit, velocity) == 0xc, "AlrEffUnit::velocity");
static_assert(offsetof(AlrEffUnit, frame) == 0x18, "AlrEffUnit::frame");
static_assert(offsetof(AlrEffUnit, frame_inc_time) == 0x19, "AlrEffUnit::frame_inc_time");
static_assert(offsetof(AlrEffUnit, mode) == 0x1a, "AlrEffUnit::mode");
static_assert(offsetof(AlrEffUnit, flag) == 0x1b, "AlrEffUnit::flag");
static_assert(offsetof(AlrEffUnit, timer) == 0x1c, "AlrEffUnit::timer");
static_assert(offsetof(AlrEffUnit, tmp) == 0x1e, "AlrEffUnit::tmp");

struct AlrEff {
    struct AlrEffUnit unit[5];
    struct NJS_TEXLIST *texlist;
    struct NJS_TEXANIM *anim;
    float scale;
    void (*exec)(struct AlrEffUnit *, struct NJS_POINT3 *, struct NJS_POINT3 *);
    unsigned short frame_inc_time_max;
    unsigned char anim_num;
    unsigned char unit_num;
};
static_assert(sizeof(AlrEff) == 0xb4, "sizeof AlrEff");
static_assert(offsetof(AlrEff, unit) == 0x0, "AlrEff::unit");
static_assert(offsetof(AlrEff, texlist) == 0xa0, "AlrEff::texlist");
static_assert(offsetof(AlrEff, anim) == 0xa4, "AlrEff::anim");
static_assert(offsetof(AlrEff, scale) == 0xa8, "AlrEff::scale");
static_assert(offsetof(AlrEff, exec) == 0xac, "AlrEff::exec");
static_assert(offsetof(AlrEff, frame_inc_time_max) == 0xb0, "AlrEff::frame_inc_time_max");
static_assert(offsetof(AlrEff, anim_num) == 0xb2, "AlrEff::anim_num");
static_assert(offsetof(AlrEff, unit_num) == 0xb3, "AlrEff::unit_num");

struct AlrEvent {
    unsigned char level;
    unsigned char cnt;
    unsigned short timer;
    void (*event)(struct Alr *);
};
static_assert(sizeof(AlrEvent) == 0x8, "sizeof AlrEvent");
static_assert(offsetof(AlrEvent, level) == 0x0, "AlrEvent::level");
static_assert(offsetof(AlrEvent, cnt) == 0x1, "AlrEvent::cnt");
static_assert(offsetof(AlrEvent, timer) == 0x2, "AlrEvent::timer");
static_assert(offsetof(AlrEvent, event) == 0x4, "AlrEvent::event");

struct TaskCommunication {
    struct task *obj_tp;
    signed char obj_kind;
    signed char command;
    unsigned char status;
};
static_assert(sizeof(TaskCommunication) == 0x8, "sizeof TaskCommunication");
static_assert(offsetof(TaskCommunication, obj_tp) == 0x0, "TaskCommunication::obj_tp");
static_assert(offsetof(TaskCommunication, obj_kind) == 0x4, "TaskCommunication::obj_kind");
static_assert(offsetof(TaskCommunication, command) == 0x5, "TaskCommunication::command");
static_assert(offsetof(TaskCommunication, status) == 0x6, "TaskCommunication::status");

struct Alr {
    struct AlrEff eff;
    struct AlrEvent event;
    struct TaskCommunication communication;
    unsigned char id;
    unsigned char area;
    unsigned short flag;
    unsigned char rank;
    unsigned char mode;
    unsigned char command;
    unsigned char smode;
    float sloop;
    float pathpos;
    unsigned char use_path;
    unsigned char ex_mode;
    unsigned short ex_cnt;
    long amplitude;
    unsigned char now;
    unsigned char motion;
    unsigned char chao_flag;
    unsigned char voice;
    unsigned char zone;
    unsigned short para_timer;
    float monooto;
    signed char sleep;
    signed char tire;
    signed char stress;
    signed char tmp;
    struct alifewk *awp;
    struct taskwk *twp;
};
static_assert(sizeof(Alr) == 0xf4, "sizeof Alr");
static_assert(offsetof(Alr, eff) == 0x0, "Alr::eff");
static_assert(offsetof(Alr, event) == 0xb4, "Alr::event");
static_assert(offsetof(Alr, communication) == 0xbc, "Alr::communication");
static_assert(offsetof(Alr, id) == 0xc4, "Alr::id");
static_assert(offsetof(Alr, area) == 0xc5, "Alr::area");
static_assert(offsetof(Alr, flag) == 0xc6, "Alr::flag");
static_assert(offsetof(Alr, rank) == 0xc8, "Alr::rank");
static_assert(offsetof(Alr, mode) == 0xc9, "Alr::mode");
static_assert(offsetof(Alr, command) == 0xca, "Alr::command");
static_assert(offsetof(Alr, smode) == 0xcb, "Alr::smode");
static_assert(offsetof(Alr, sloop) == 0xcc, "Alr::sloop");
static_assert(offsetof(Alr, pathpos) == 0xd0, "Alr::pathpos");
static_assert(offsetof(Alr, use_path) == 0xd4, "Alr::use_path");
static_assert(offsetof(Alr, ex_mode) == 0xd5, "Alr::ex_mode");
static_assert(offsetof(Alr, ex_cnt) == 0xd6, "Alr::ex_cnt");
static_assert(offsetof(Alr, amplitude) == 0xd8, "Alr::amplitude");
static_assert(offsetof(Alr, now) == 0xdc, "Alr::now");
static_assert(offsetof(Alr, motion) == 0xdd, "Alr::motion");
static_assert(offsetof(Alr, chao_flag) == 0xde, "Alr::chao_flag");
static_assert(offsetof(Alr, voice) == 0xdf, "Alr::voice");
static_assert(offsetof(Alr, zone) == 0xe0, "Alr::zone");
static_assert(offsetof(Alr, para_timer) == 0xe2, "Alr::para_timer");
static_assert(offsetof(Alr, monooto) == 0xe4, "Alr::monooto");
static_assert(offsetof(Alr, sleep) == 0xe8, "Alr::sleep");
static_assert(offsetof(Alr, tire) == 0xe9, "Alr::tire");
static_assert(offsetof(Alr, stress) == 0xea, "Alr::stress");
static_assert(offsetof(Alr, tmp) == 0xeb, "Alr::tmp");
static_assert(offsetof(Alr, awp) == 0xec, "Alr::awp");
static_assert(offsetof(Alr, twp) == 0xf0, "Alr::twp");

// Offsets not checked against the code yet.
struct AlrCamAround {
    long angle;
    float dist;
    unsigned short old_area;
    unsigned short old_look;
};
static_assert(sizeof(AlrCamAround) == 0xc, "sizeof AlrCamAround");
static_assert(offsetof(AlrCamAround, angle) == 0x0, "AlrCamAround::angle");
static_assert(offsetof(AlrCamAround, dist) == 0x4, "AlrCamAround::dist");
static_assert(offsetof(AlrCamAround, old_area) == 0x8, "AlrCamAround::old_area");
static_assert(offsetof(AlrCamAround, old_look) == 0xa, "AlrCamAround::old_look");

// Offsets not checked against the code yet.
struct AlrCamEllipse {
    long angle;
    int old;
};
static_assert(sizeof(AlrCamEllipse) == 0x8, "sizeof AlrCamEllipse");
static_assert(offsetof(AlrCamEllipse, angle) == 0x0, "AlrCamEllipse::angle");
static_assert(offsetof(AlrCamEllipse, old) == 0x4, "AlrCamEllipse::old");

// Offsets not checked against the code yet.
struct AlrCamEndgoal {
    float para;
    long angle;
    int mode;
};
static_assert(sizeof(AlrCamEndgoal) == 0xc, "sizeof AlrCamEndgoal");
static_assert(offsetof(AlrCamEndgoal, para) == 0x0, "AlrCamEndgoal::para");
static_assert(offsetof(AlrCamEndgoal, angle) == 0x4, "AlrCamEndgoal::angle");
static_assert(offsetof(AlrCamEndgoal, mode) == 0x8, "AlrCamEndgoal::mode");

// Offsets not checked against the code yet.
struct AlrCamEntrance {
    unsigned char colli;
    unsigned char flag;
};
static_assert(sizeof(AlrCamEntrance) == 0x2, "sizeof AlrCamEntrance");
static_assert(offsetof(AlrCamEntrance, colli) == 0x0, "AlrCamEntrance::colli");
static_assert(offsetof(AlrCamEntrance, flag) == 0x1, "AlrCamEntrance::flag");

// Offsets not checked against the code yet.
struct AlrCamFixed {
    int old;
};
static_assert(sizeof(AlrCamFixed) == 0x4, "sizeof AlrCamFixed");
static_assert(offsetof(AlrCamFixed, old) == 0x0, "AlrCamFixed::old");

struct AlrCam {
    unsigned char mode;
    unsigned char smode;
    unsigned char old_mode;
    unsigned char dummy00;
    unsigned short flag;
    unsigned short dummy01;
    long angle;
    long aim_angle;
    struct NJS_POINT3 tgt_velocity;
    struct NJS_POINT3 cam_velocity;
    struct NJS_POINT3 tgt_accel;
    struct NJS_POINT3 cam_accel;
    union {
        struct AlrCamFixed fixed;
        struct AlrCamAround around;
        struct AlrCamEllipse ellipse;
        struct AlrCamEndgoal goal;
        struct AlrCamEntrance ecam;
    } camera;
};
static_assert(sizeof(AlrCam) == 0x4c, "sizeof AlrCam");
static_assert(offsetof(AlrCam, mode) == 0x0, "AlrCam::mode");
static_assert(offsetof(AlrCam, smode) == 0x1, "AlrCam::smode");
static_assert(offsetof(AlrCam, old_mode) == 0x2, "AlrCam::old_mode");
static_assert(offsetof(AlrCam, dummy00) == 0x3, "AlrCam::dummy00");
static_assert(offsetof(AlrCam, flag) == 0x4, "AlrCam::flag");
static_assert(offsetof(AlrCam, dummy01) == 0x6, "AlrCam::dummy01");
static_assert(offsetof(AlrCam, angle) == 0x8, "AlrCam::angle");
static_assert(offsetof(AlrCam, aim_angle) == 0xc, "AlrCam::aim_angle");
static_assert(offsetof(AlrCam, tgt_velocity) == 0x10, "AlrCam::tgt_velocity");
static_assert(offsetof(AlrCam, cam_velocity) == 0x1c, "AlrCam::cam_velocity");
static_assert(offsetof(AlrCam, tgt_accel) == 0x28, "AlrCam::tgt_accel");
static_assert(offsetof(AlrCam, cam_accel) == 0x34, "AlrCam::cam_accel");
static_assert(offsetof(AlrCam, camera) == 0x40, "AlrCam::camera");

struct AlrData {
    int cup_num;
    const struct NJS_POINT3 (*startpos)[];
    const float *endpathpos;
    const struct AlrCamData *alrcamdata;
    const struct NJS_POINT3 *fixedposition;
};
static_assert(sizeof(AlrData) == 0x14, "sizeof AlrData");
static_assert(offsetof(AlrData, cup_num) == 0x0, "AlrData::cup_num");
static_assert(offsetof(AlrData, startpos) == 0x4, "AlrData::startpos");
static_assert(offsetof(AlrData, endpathpos) == 0x8, "AlrData::endpathpos");
static_assert(offsetof(AlrData, alrcamdata) == 0xc, "AlrData::alrcamdata");
static_assert(offsetof(AlrData, fixedposition) == 0x10, "AlrData::fixedposition");

// Offsets not checked against the code yet.
struct AlrEntry {
    unsigned char garden;
    unsigned char id;
};
static_assert(sizeof(AlrEntry) == 0x2, "sizeof AlrEntry");
static_assert(offsetof(AlrEntry, garden) == 0x0, "AlrEntry::garden");
static_assert(offsetof(AlrEntry, id) == 0x1, "AlrEntry::id");

// Offsets not checked against the code yet.
struct AlrFanFan {
    unsigned short timer;
    unsigned char mode;
    unsigned char extra;
    unsigned char look;
    unsigned char hit;
    signed char se_timing;
    signed char tmp;
};
static_assert(sizeof(AlrFanFan) == 0x8, "sizeof AlrFanFan");
static_assert(offsetof(AlrFanFan, timer) == 0x0, "AlrFanFan::timer");
static_assert(offsetof(AlrFanFan, mode) == 0x2, "AlrFanFan::mode");
static_assert(offsetof(AlrFanFan, extra) == 0x3, "AlrFanFan::extra");
static_assert(offsetof(AlrFanFan, look) == 0x4, "AlrFanFan::look");
static_assert(offsetof(AlrFanFan, hit) == 0x5, "AlrFanFan::hit");
static_assert(offsetof(AlrFanFan, se_timing) == 0x6, "AlrFanFan::se_timing");
static_assert(offsetof(AlrFanFan, tmp) == 0x7, "AlrFanFan::tmp");

// Offsets not checked against the code yet.
struct AlrGoalInfo {
    float flag;
    float dummyA;
    float dummyB;
};
static_assert(sizeof(AlrGoalInfo) == 0xc, "sizeof AlrGoalInfo");
static_assert(offsetof(AlrGoalInfo, flag) == 0x0, "AlrGoalInfo::flag");
static_assert(offsetof(AlrGoalInfo, dummyA) == 0x4, "AlrGoalInfo::dummyA");
static_assert(offsetof(AlrGoalInfo, dummyB) == 0x8, "AlrGoalInfo::dummyB");

struct AlrRank {
    unsigned char rank[8];
    unsigned char flag[8];
    float scale[8];
    long look_angle;
    float pos_y;
    float velo_y;
    unsigned char mode;
    unsigned char old_num;
    unsigned short cnt;
};
static_assert(sizeof(AlrRank) == 0x40, "sizeof AlrRank");
static_assert(offsetof(AlrRank, rank) == 0x0, "AlrRank::rank");
static_assert(offsetof(AlrRank, flag) == 0x8, "AlrRank::flag");
static_assert(offsetof(AlrRank, scale) == 0x10, "AlrRank::scale");
static_assert(offsetof(AlrRank, look_angle) == 0x30, "AlrRank::look_angle");
static_assert(offsetof(AlrRank, pos_y) == 0x34, "AlrRank::pos_y");
static_assert(offsetof(AlrRank, velo_y) == 0x38, "AlrRank::velo_y");
static_assert(offsetof(AlrRank, mode) == 0x3c, "AlrRank::mode");
static_assert(offsetof(AlrRank, old_num) == 0x3d, "AlrRank::old_num");
static_assert(offsetof(AlrRank, cnt) == 0x3e, "AlrRank::cnt");

// Offsets not checked against the code yet.
struct AlrRoot {
    union {
        struct NJS_POINT3 goal;
        struct AlrGoalInfo info;
    } goal_info;
    struct AlrZoneUnit *subpath;
    struct pathtag **pathdata;
    int subpath_max;
};
static_assert(sizeof(AlrRoot) == 0x18, "sizeof AlrRoot");
static_assert(offsetof(AlrRoot, goal_info) == 0x0, "AlrRoot::goal_info");
static_assert(offsetof(AlrRoot, subpath) == 0xc, "AlrRoot::subpath");
static_assert(offsetof(AlrRoot, pathdata) == 0x10, "AlrRoot::pathdata");
static_assert(offsetof(AlrRoot, subpath_max) == 0x14, "AlrRoot::subpath_max");

// Offsets not checked against the code yet.
struct AlrTimerUnit {
    unsigned char timer[3];
};
static_assert(sizeof(AlrTimerUnit) == 0x3, "sizeof AlrTimerUnit");
static_assert(offsetof(AlrTimerUnit, timer) == 0x0, "AlrTimerUnit::timer");

struct AlrTimer {
    struct AlrTimerUnit current;
    struct AlrTimerUnit *high;
};
static_assert(sizeof(AlrTimer) == 0x8, "sizeof AlrTimer");
static_assert(offsetof(AlrTimer, current) == 0x0, "AlrTimer::current");
static_assert(offsetof(AlrTimer, high) == 0x4, "AlrTimer::high");

// Offsets not checked against the code yet.
struct AlrVmsTime {
    unsigned short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
    unsigned char dayofweek;
};
static_assert(sizeof(AlrVmsTime) == 0x8, "sizeof AlrVmsTime");
static_assert(offsetof(AlrVmsTime, year) == 0x0, "AlrVmsTime::year");
static_assert(offsetof(AlrVmsTime, month) == 0x2, "AlrVmsTime::month");
static_assert(offsetof(AlrVmsTime, day) == 0x3, "AlrVmsTime::day");
static_assert(offsetof(AlrVmsTime, hour) == 0x4, "AlrVmsTime::hour");
static_assert(offsetof(AlrVmsTime, minute) == 0x5, "AlrVmsTime::minute");
static_assert(offsetof(AlrVmsTime, second) == 0x6, "AlrVmsTime::second");
static_assert(offsetof(AlrVmsTime, dayofweek) == 0x7, "AlrVmsTime::dayofweek");

// Offsets not checked against the code yet.
struct AlrVms {
    struct AlrVmsTime time[8];
    unsigned char ready_flag;
    unsigned char hold_flag;
    unsigned char vms_num;
    unsigned char tmp00;
};
static_assert(sizeof(AlrVms) == 0x44, "sizeof AlrVms");
static_assert(offsetof(AlrVms, time) == 0x0, "AlrVms::time");
static_assert(offsetof(AlrVms, ready_flag) == 0x40, "AlrVms::ready_flag");
static_assert(offsetof(AlrVms, hold_flag) == 0x41, "AlrVms::hold_flag");
static_assert(offsetof(AlrVms, vms_num) == 0x42, "AlrVms::vms_num");
static_assert(offsetof(AlrVms, tmp00) == 0x43, "AlrVms::tmp00");

struct al_status {
    unsigned char type;
    unsigned char garden_num;
    signed char like;
    unsigned char key1;
    unsigned char name[8];
    unsigned short swim;
    unsigned short fly;
    unsigned short run;
    unsigned short power;
    unsigned short health;
    unsigned short health_max;
    unsigned char fruit_kind[8];
    float h_pos;
    float v_pos;
    float growth;
    unsigned short intimate;
    unsigned short life;
    unsigned short old;
    unsigned short get_minimal;
    unsigned char win;
    unsigned char key2;
    unsigned short flag;
    struct NJS_POINT3 pos;
    unsigned long age;
    unsigned long id;
    signed char animal_part_num[7];
    unsigned char key3;
    unsigned short pt_swim;
    unsigned short pt_fly;
    unsigned short pt_run;
    unsigned short pt_power;
    signed char kindness;
    signed char aggressive;
    signed char curiosity;
    unsigned char charm;
    unsigned char breed;
    unsigned char sleep;
    unsigned char hunger;
    unsigned char tedious;
    unsigned char tire;
    unsigned char stress;
    unsigned char narrow;
    unsigned char pleasure;
    unsigned char anger;
    unsigned char sorrow;
    unsigned char fear;
    unsigned char lonely;
    struct ADV1_AL_MEMORY memory;
    unsigned char nbSucceed;
    unsigned char lane;
    unsigned char IsCPU;
    signed char key4;
    signed char exist;
    unsigned short mayu_timer;
    unsigned char race_time[20];
    unsigned char extra_num;
};
static_assert(sizeof(al_status) == 0x198, "sizeof al_status");
static_assert(offsetof(al_status, type) == 0x0, "al_status::type");
static_assert(offsetof(al_status, garden_num) == 0x1, "al_status::garden_num");
static_assert(offsetof(al_status, like) == 0x2, "al_status::like");
static_assert(offsetof(al_status, key1) == 0x3, "al_status::key1");
static_assert(offsetof(al_status, name) == 0x4, "al_status::name");
static_assert(offsetof(al_status, swim) == 0xc, "al_status::swim");
static_assert(offsetof(al_status, fly) == 0xe, "al_status::fly");
static_assert(offsetof(al_status, run) == 0x10, "al_status::run");
static_assert(offsetof(al_status, power) == 0x12, "al_status::power");
static_assert(offsetof(al_status, health) == 0x14, "al_status::health");
static_assert(offsetof(al_status, health_max) == 0x16, "al_status::health_max");
static_assert(offsetof(al_status, fruit_kind) == 0x18, "al_status::fruit_kind");
static_assert(offsetof(al_status, h_pos) == 0x20, "al_status::h_pos");
static_assert(offsetof(al_status, v_pos) == 0x24, "al_status::v_pos");
static_assert(offsetof(al_status, growth) == 0x28, "al_status::growth");
static_assert(offsetof(al_status, intimate) == 0x2c, "al_status::intimate");
static_assert(offsetof(al_status, life) == 0x2e, "al_status::life");
static_assert(offsetof(al_status, old) == 0x30, "al_status::old");
static_assert(offsetof(al_status, get_minimal) == 0x32, "al_status::get_minimal");
static_assert(offsetof(al_status, win) == 0x34, "al_status::win");
static_assert(offsetof(al_status, key2) == 0x35, "al_status::key2");
static_assert(offsetof(al_status, flag) == 0x36, "al_status::flag");
static_assert(offsetof(al_status, pos) == 0x38, "al_status::pos");
static_assert(offsetof(al_status, age) == 0x44, "al_status::age");
static_assert(offsetof(al_status, id) == 0x48, "al_status::id");
static_assert(offsetof(al_status, animal_part_num) == 0x4c, "al_status::animal_part_num");
static_assert(offsetof(al_status, key3) == 0x53, "al_status::key3");
static_assert(offsetof(al_status, pt_swim) == 0x54, "al_status::pt_swim");
static_assert(offsetof(al_status, pt_fly) == 0x56, "al_status::pt_fly");
static_assert(offsetof(al_status, pt_run) == 0x58, "al_status::pt_run");
static_assert(offsetof(al_status, pt_power) == 0x5a, "al_status::pt_power");
static_assert(offsetof(al_status, kindness) == 0x5c, "al_status::kindness");
static_assert(offsetof(al_status, aggressive) == 0x5d, "al_status::aggressive");
static_assert(offsetof(al_status, curiosity) == 0x5e, "al_status::curiosity");
static_assert(offsetof(al_status, charm) == 0x5f, "al_status::charm");
static_assert(offsetof(al_status, breed) == 0x60, "al_status::breed");
static_assert(offsetof(al_status, sleep) == 0x61, "al_status::sleep");
static_assert(offsetof(al_status, hunger) == 0x62, "al_status::hunger");
static_assert(offsetof(al_status, tedious) == 0x63, "al_status::tedious");
static_assert(offsetof(al_status, tire) == 0x64, "al_status::tire");
static_assert(offsetof(al_status, stress) == 0x65, "al_status::stress");
static_assert(offsetof(al_status, narrow) == 0x66, "al_status::narrow");
static_assert(offsetof(al_status, pleasure) == 0x67, "al_status::pleasure");
static_assert(offsetof(al_status, anger) == 0x68, "al_status::anger");
static_assert(offsetof(al_status, sorrow) == 0x69, "al_status::sorrow");
static_assert(offsetof(al_status, fear) == 0x6a, "al_status::fear");
static_assert(offsetof(al_status, lonely) == 0x6b, "al_status::lonely");
static_assert(offsetof(al_status, memory) == 0x6c, "al_status::memory");
static_assert(offsetof(al_status, nbSucceed) == 0x178, "al_status::nbSucceed");
static_assert(offsetof(al_status, lane) == 0x179, "al_status::lane");
static_assert(offsetof(al_status, IsCPU) == 0x17a, "al_status::IsCPU");
static_assert(offsetof(al_status, key4) == 0x17b, "al_status::key4");
static_assert(offsetof(al_status, exist) == 0x17c, "al_status::exist");
static_assert(offsetof(al_status, mayu_timer) == 0x17e, "al_status::mayu_timer");
static_assert(offsetof(al_status, race_time) == 0x180, "al_status::race_time");
static_assert(offsetof(al_status, extra_num) == 0x194, "al_status::extra_num");

struct AlrReal {
    struct al_status status[8];
    struct Alr alr[8];
    struct AlrCam alrcam;
    struct AlrMemory *alrmemory;
    struct AlrEntry entry[8];
    struct AlrRank alrrank;
    struct AlrRoot alrroot;
    struct AlrTimer alrtimer;
    struct AlrVms alrvms;
    struct AlrFanFan alrfanfan;
    signed char look;
    signed char tmp_look;
    unsigned char mode;
    signed char tmp_csl;
    signed char player;
    signed char scnt;
    float average;
    void (*stage_exe)(struct AlrReal *);
    unsigned short flag;
    unsigned short stimer;
    unsigned short total_timer;
    unsigned short stage_timer;
    unsigned char stage_mode;
    signed char entry_num;
    unsigned short camera_timer;
    unsigned char vms_lane;
    unsigned char tmp04;
    struct task *emblem;
};
static_assert(sizeof(AlrReal) == 0x1590, "sizeof AlrReal");
static_assert(offsetof(AlrReal, status) == 0x0, "AlrReal::status");
static_assert(offsetof(AlrReal, alr) == 0xcc0, "AlrReal::alr");
static_assert(offsetof(AlrReal, alrcam) == 0x1460, "AlrReal::alrcam");
static_assert(offsetof(AlrReal, alrmemory) == 0x14ac, "AlrReal::alrmemory");
static_assert(offsetof(AlrReal, entry) == 0x14b0, "AlrReal::entry");
static_assert(offsetof(AlrReal, alrrank) == 0x14c0, "AlrReal::alrrank");
static_assert(offsetof(AlrReal, alrroot) == 0x1500, "AlrReal::alrroot");
static_assert(offsetof(AlrReal, alrtimer) == 0x1518, "AlrReal::alrtimer");
static_assert(offsetof(AlrReal, alrvms) == 0x1520, "AlrReal::alrvms");
static_assert(offsetof(AlrReal, alrfanfan) == 0x1564, "AlrReal::alrfanfan");
static_assert(offsetof(AlrReal, look) == 0x156c, "AlrReal::look");
static_assert(offsetof(AlrReal, tmp_look) == 0x156d, "AlrReal::tmp_look");
static_assert(offsetof(AlrReal, mode) == 0x156e, "AlrReal::mode");
static_assert(offsetof(AlrReal, tmp_csl) == 0x156f, "AlrReal::tmp_csl");
static_assert(offsetof(AlrReal, player) == 0x1570, "AlrReal::player");
static_assert(offsetof(AlrReal, scnt) == 0x1571, "AlrReal::scnt");
static_assert(offsetof(AlrReal, average) == 0x1574, "AlrReal::average");
static_assert(offsetof(AlrReal, stage_exe) == 0x1578, "AlrReal::stage_exe");
static_assert(offsetof(AlrReal, flag) == 0x157c, "AlrReal::flag");
static_assert(offsetof(AlrReal, stimer) == 0x157e, "AlrReal::stimer");
static_assert(offsetof(AlrReal, total_timer) == 0x1580, "AlrReal::total_timer");
static_assert(offsetof(AlrReal, stage_timer) == 0x1582, "AlrReal::stage_timer");
static_assert(offsetof(AlrReal, stage_mode) == 0x1584, "AlrReal::stage_mode");
static_assert(offsetof(AlrReal, entry_num) == 0x1585, "AlrReal::entry_num");
static_assert(offsetof(AlrReal, camera_timer) == 0x1586, "AlrReal::camera_timer");
static_assert(offsetof(AlrReal, vms_lane) == 0x1588, "AlrReal::vms_lane");
static_assert(offsetof(AlrReal, tmp04) == 0x1589, "AlrReal::tmp04");
static_assert(offsetof(AlrReal, emblem) == 0x158c, "AlrReal::emblem");

struct BOSSPLAYER_CREATE_PARAM {
    enum EVBOSS_TYPE type;
    struct task *player_tp;
    struct task *boss_tp;
    void (*exec)(struct task *);
    void (*exit)(struct task *);
    int flag;
    struct NJS_POINT3 player_pos;
    struct NJS_POINT3 boss_pos;
};
static_assert(sizeof(BOSSPLAYER_CREATE_PARAM) == 0x30, "sizeof BOSSPLAYER_CREATE_PARAM");
static_assert(offsetof(BOSSPLAYER_CREATE_PARAM, type) == 0x0, "BOSSPLAYER_CREATE_PARAM::type");
static_assert(offsetof(BOSSPLAYER_CREATE_PARAM, player_tp) == 0x4, "BOSSPLAYER_CREATE_PARAM::player_tp");
static_assert(offsetof(BOSSPLAYER_CREATE_PARAM, boss_tp) == 0x8, "BOSSPLAYER_CREATE_PARAM::boss_tp");
static_assert(offsetof(BOSSPLAYER_CREATE_PARAM, exec) == 0xc, "BOSSPLAYER_CREATE_PARAM::exec");
static_assert(offsetof(BOSSPLAYER_CREATE_PARAM, exit) == 0x10, "BOSSPLAYER_CREATE_PARAM::exit");
static_assert(offsetof(BOSSPLAYER_CREATE_PARAM, flag) == 0x14, "BOSSPLAYER_CREATE_PARAM::flag");
static_assert(offsetof(BOSSPLAYER_CREATE_PARAM, player_pos) == 0x18, "BOSSPLAYER_CREATE_PARAM::player_pos");
static_assert(offsetof(BOSSPLAYER_CREATE_PARAM, boss_pos) == 0x24, "BOSSPLAYER_CREATE_PARAM::boss_pos");

struct CCL_INFO {
    unsigned char kind;
    unsigned char form;
    unsigned char push;
    unsigned char damage;
    unsigned long attr;
    struct NJS_POINT3 center;
    float a;
    float b;
    float c;
    float d;
    long angx;
    long angy;
    long angz;
};
static_assert(sizeof(CCL_INFO) == 0x30, "sizeof CCL_INFO");
static_assert(offsetof(CCL_INFO, kind) == 0x0, "CCL_INFO::kind");
static_assert(offsetof(CCL_INFO, form) == 0x1, "CCL_INFO::form");
static_assert(offsetof(CCL_INFO, push) == 0x2, "CCL_INFO::push");
static_assert(offsetof(CCL_INFO, damage) == 0x3, "CCL_INFO::damage");
static_assert(offsetof(CCL_INFO, attr) == 0x4, "CCL_INFO::attr");
static_assert(offsetof(CCL_INFO, center) == 0x8, "CCL_INFO::center");
static_assert(offsetof(CCL_INFO, a) == 0x14, "CCL_INFO::a");
static_assert(offsetof(CCL_INFO, b) == 0x18, "CCL_INFO::b");
static_assert(offsetof(CCL_INFO, c) == 0x1c, "CCL_INFO::c");
static_assert(offsetof(CCL_INFO, d) == 0x20, "CCL_INFO::d");
static_assert(offsetof(CCL_INFO, angx) == 0x24, "CCL_INFO::angx");
static_assert(offsetof(CCL_INFO, angy) == 0x28, "CCL_INFO::angy");
static_assert(offsetof(CCL_INFO, angz) == 0x2c, "CCL_INFO::angz");

struct DDlgType {
    float CntrX;
    float CntrY;
    float BaseZ;
    float SclX;
    float SclY;
    signed char Csr;
};
static_assert(sizeof(DDlgType) == 0x18, "sizeof DDlgType");
static_assert(offsetof(DDlgType, CntrX) == 0x0, "DDlgType::CntrX");
static_assert(offsetof(DDlgType, CntrY) == 0x4, "DDlgType::CntrY");
static_assert(offsetof(DDlgType, BaseZ) == 0x8, "DDlgType::BaseZ");
static_assert(offsetof(DDlgType, SclX) == 0xc, "DDlgType::SclX");
static_assert(offsetof(DDlgType, SclY) == 0x10, "DDlgType::SclY");
static_assert(offsetof(DDlgType, Csr) == 0x14, "DDlgType::Csr");

struct DialogPrmType {
    enum DlgPnlStyleEnum DlgStyle;
    void (*EachDrawFnc)(struct DDlgType *);
    struct NJS_TEXLIST *PnlTlsPtr;
    struct PanelPrmType *PnlPrmPtr;
    struct DlgSndPrmType *DlgSndPrmPtr;
    unsigned long DlgColU;
    unsigned long DlgColD;
    float CntrX;
    float CntrY;
    float BaseZ;
    float SzX;
    float SzY;
    float MagX;
    float MagY;
    signed char CsrMax;
    signed char CsrCancel;
};
static_assert(sizeof(DialogPrmType) == 0x3c, "sizeof DialogPrmType");
static_assert(offsetof(DialogPrmType, DlgStyle) == 0x0, "DialogPrmType::DlgStyle");
static_assert(offsetof(DialogPrmType, EachDrawFnc) == 0x4, "DialogPrmType::EachDrawFnc");
static_assert(offsetof(DialogPrmType, PnlTlsPtr) == 0x8, "DialogPrmType::PnlTlsPtr");
static_assert(offsetof(DialogPrmType, PnlPrmPtr) == 0xc, "DialogPrmType::PnlPrmPtr");
static_assert(offsetof(DialogPrmType, DlgSndPrmPtr) == 0x10, "DialogPrmType::DlgSndPrmPtr");
static_assert(offsetof(DialogPrmType, DlgColU) == 0x14, "DialogPrmType::DlgColU");
static_assert(offsetof(DialogPrmType, DlgColD) == 0x18, "DialogPrmType::DlgColD");
static_assert(offsetof(DialogPrmType, CntrX) == 0x1c, "DialogPrmType::CntrX");
static_assert(offsetof(DialogPrmType, CntrY) == 0x20, "DialogPrmType::CntrY");
static_assert(offsetof(DialogPrmType, BaseZ) == 0x24, "DialogPrmType::BaseZ");
static_assert(offsetof(DialogPrmType, SzX) == 0x28, "DialogPrmType::SzX");
static_assert(offsetof(DialogPrmType, SzY) == 0x2c, "DialogPrmType::SzY");
static_assert(offsetof(DialogPrmType, MagX) == 0x30, "DialogPrmType::MagX");
static_assert(offsetof(DialogPrmType, MagY) == 0x34, "DialogPrmType::MagY");
static_assert(offsetof(DialogPrmType, CsrMax) == 0x38, "DialogPrmType::CsrMax");
static_assert(offsetof(DialogPrmType, CsrCancel) == 0x39, "DialogPrmType::CsrCancel");

struct NJS_ACTION {
    struct obj *object;
    struct NJS_MOTION *motion;
};
static_assert(sizeof(NJS_ACTION) == 0x8, "sizeof NJS_ACTION");
static_assert(offsetof(NJS_ACTION, object) == 0x0, "NJS_ACTION::object");
static_assert(offsetof(NJS_ACTION, motion) == 0x4, "NJS_ACTION::motion");

struct FileSelWk {
    enum AdvaStatEnum Stat;
    enum AdvaModeEnum PrevMode;
    enum AdvaModeEnum NextMode;
    float BaseZ;
    float T;
    unsigned long BaseCol;
    float CsrScale;
    unsigned long CsrCol;
    long CsrAniAng;
    enum FileSbMdEnum SubMode;
    int GB_plBak;
    enum AvaCharEnum SelCh;
    short WaitTime;
    unsigned char CsrAlpha;
    float OfsX;
};
static_assert(sizeof(FileSelWk) == 0x38, "sizeof FileSelWk");
static_assert(offsetof(FileSelWk, Stat) == 0x0, "FileSelWk::Stat");
static_assert(offsetof(FileSelWk, PrevMode) == 0x4, "FileSelWk::PrevMode");
static_assert(offsetof(FileSelWk, NextMode) == 0x8, "FileSelWk::NextMode");
static_assert(offsetof(FileSelWk, BaseZ) == 0xc, "FileSelWk::BaseZ");
static_assert(offsetof(FileSelWk, T) == 0x10, "FileSelWk::T");
static_assert(offsetof(FileSelWk, BaseCol) == 0x14, "FileSelWk::BaseCol");
static_assert(offsetof(FileSelWk, CsrScale) == 0x18, "FileSelWk::CsrScale");
static_assert(offsetof(FileSelWk, CsrCol) == 0x1c, "FileSelWk::CsrCol");
static_assert(offsetof(FileSelWk, CsrAniAng) == 0x20, "FileSelWk::CsrAniAng");
static_assert(offsetof(FileSelWk, SubMode) == 0x24, "FileSelWk::SubMode");
static_assert(offsetof(FileSelWk, GB_plBak) == 0x28, "FileSelWk::GB_plBak");
static_assert(offsetof(FileSelWk, SelCh) == 0x2c, "FileSelWk::SelCh");
static_assert(offsetof(FileSelWk, WaitTime) == 0x30, "FileSelWk::WaitTime");
static_assert(offsetof(FileSelWk, CsrAlpha) == 0x32, "FileSelWk::CsrAlpha");
static_assert(offsetof(FileSelWk, OfsX) == 0x34, "FileSelWk::OfsX");

struct NJS_POINT2 {
    float x;
    float y;
};
static_assert(sizeof(NJS_POINT2) == 0x8, "sizeof NJS_POINT2");
static_assert(offsetof(NJS_POINT2, x) == 0x0, "NJS_POINT2::x");
static_assert(offsetof(NJS_POINT2, y) == 0x4, "NJS_POINT2::y");

struct GHSPRITE_ANIM_TABLE {
    short nTexId;
    unsigned char flag;
    unsigned long gIndex;
    struct NJS_POINT2 size;
    struct NJS_POINT2 trans;
    float fFrame;
    struct NJS_ARGB argb;
};
static_assert(sizeof(GHSPRITE_ANIM_TABLE) == 0x2c, "sizeof GHSPRITE_ANIM_TABLE");
static_assert(offsetof(GHSPRITE_ANIM_TABLE, nTexId) == 0x0, "GHSPRITE_ANIM_TABLE::nTexId");
static_assert(offsetof(GHSPRITE_ANIM_TABLE, flag) == 0x2, "GHSPRITE_ANIM_TABLE::flag");
static_assert(offsetof(GHSPRITE_ANIM_TABLE, gIndex) == 0x4, "GHSPRITE_ANIM_TABLE::gIndex");
static_assert(offsetof(GHSPRITE_ANIM_TABLE, size) == 0x8, "GHSPRITE_ANIM_TABLE::size");
static_assert(offsetof(GHSPRITE_ANIM_TABLE, trans) == 0x10, "GHSPRITE_ANIM_TABLE::trans");
static_assert(offsetof(GHSPRITE_ANIM_TABLE, fFrame) == 0x18, "GHSPRITE_ANIM_TABLE::fFrame");
static_assert(offsetof(GHSPRITE_ANIM_TABLE, argb) == 0x1c, "GHSPRITE_ANIM_TABLE::argb");

struct GH_FONT_INFO {
    float char_width;
    float char_height;
    float tex_width;
    float tex_height;
    struct NJS_TEXLIST *texlist;
    unsigned char *prop_tbl;
    unsigned long color[4];
};
static_assert(sizeof(GH_FONT_INFO) == 0x28, "sizeof GH_FONT_INFO");
static_assert(offsetof(GH_FONT_INFO, char_width) == 0x0, "GH_FONT_INFO::char_width");
static_assert(offsetof(GH_FONT_INFO, char_height) == 0x4, "GH_FONT_INFO::char_height");
static_assert(offsetof(GH_FONT_INFO, tex_width) == 0x8, "GH_FONT_INFO::tex_width");
static_assert(offsetof(GH_FONT_INFO, tex_height) == 0xc, "GH_FONT_INFO::tex_height");
static_assert(offsetof(GH_FONT_INFO, texlist) == 0x10, "GH_FONT_INFO::texlist");
static_assert(offsetof(GH_FONT_INFO, prop_tbl) == 0x14, "GH_FONT_INFO::prop_tbl");
static_assert(offsetof(GH_FONT_INFO, color) == 0x18, "GH_FONT_INFO::color");

struct HintMessageMemory {
    const struct HintMessageString *message_p;
    long adx_index;
    long flag_index;
};
static_assert(sizeof(HintMessageMemory) == 0xc, "sizeof HintMessageMemory");
static_assert(offsetof(HintMessageMemory, message_p) == 0x0, "HintMessageMemory::message_p");
static_assert(offsetof(HintMessageMemory, adx_index) == 0x4, "HintMessageMemory::adx_index");
static_assert(offsetof(HintMessageMemory, flag_index) == 0x8, "HintMessageMemory::flag_index");

struct HintMessageTable {
    const short *code;
    const struct HintMessageString *message;
};
static_assert(sizeof(HintMessageTable) == 0x8, "sizeof HintMessageTable");
static_assert(offsetof(HintMessageTable, code) == 0x0, "HintMessageTable::code");
static_assert(offsetof(HintMessageTable, message) == 0x4, "HintMessageTable::message");

struct LATE_FAR_Z_T {
    float nor;
    float ex;
    float mesh;
};
static_assert(sizeof(LATE_FAR_Z_T) == 0xc, "sizeof LATE_FAR_Z_T");
static_assert(offsetof(LATE_FAR_Z_T, nor) == 0x0, "LATE_FAR_Z_T::nor");
static_assert(offsetof(LATE_FAR_Z_T, ex) == 0x4, "LATE_FAR_Z_T::ex");
static_assert(offsetof(LATE_FAR_Z_T, mesh) == 0x8, "LATE_FAR_Z_T::mesh");

struct LE_LIGHT_ENV {
    unsigned char stgNo;
    unsigned char actNo;
    unsigned char ligNo;
    unsigned char flgs;
    struct NJS_POINT3 vec;
    float spe;
    float dif;
    float r;
    float g;
    float b;
    float ambR;
    float ambG;
    float ambB;
};
static_assert(sizeof(LE_LIGHT_ENV) == 0x30, "sizeof LE_LIGHT_ENV");
static_assert(offsetof(LE_LIGHT_ENV, stgNo) == 0x0, "LE_LIGHT_ENV::stgNo");
static_assert(offsetof(LE_LIGHT_ENV, actNo) == 0x1, "LE_LIGHT_ENV::actNo");
static_assert(offsetof(LE_LIGHT_ENV, ligNo) == 0x2, "LE_LIGHT_ENV::ligNo");
static_assert(offsetof(LE_LIGHT_ENV, flgs) == 0x3, "LE_LIGHT_ENV::flgs");
static_assert(offsetof(LE_LIGHT_ENV, vec) == 0x4, "LE_LIGHT_ENV::vec");
static_assert(offsetof(LE_LIGHT_ENV, spe) == 0x10, "LE_LIGHT_ENV::spe");
static_assert(offsetof(LE_LIGHT_ENV, dif) == 0x14, "LE_LIGHT_ENV::dif");
static_assert(offsetof(LE_LIGHT_ENV, r) == 0x18, "LE_LIGHT_ENV::r");
static_assert(offsetof(LE_LIGHT_ENV, g) == 0x1c, "LE_LIGHT_ENV::g");
static_assert(offsetof(LE_LIGHT_ENV, b) == 0x20, "LE_LIGHT_ENV::b");
static_assert(offsetof(LE_LIGHT_ENV, ambR) == 0x24, "LE_LIGHT_ENV::ambR");
static_assert(offsetof(LE_LIGHT_ENV, ambG) == 0x28, "LE_LIGHT_ENV::ambG");
static_assert(offsetof(LE_LIGHT_ENV, ambB) == 0x2c, "LE_LIGHT_ENV::ambB");

struct NJS_RGB {
    float r;
    float g;
    float b;
};
static_assert(sizeof(NJS_RGB) == 0xc, "sizeof NJS_RGB");
static_assert(offsetof(NJS_RGB, r) == 0x0, "NJS_RGB::r");
static_assert(offsetof(NJS_RGB, g) == 0x4, "NJS_RGB::g");
static_assert(offsetof(NJS_RGB, b) == 0x8, "NJS_RGB::b");

struct LE_PALIGHT_ENV {
    unsigned char stgNo;
    unsigned char actNo;
    unsigned char chrNo;
    unsigned char flgs;
    struct NJS_POINT3 vec;
    float dif;
    struct NJS_RGB amb;
    float cpow;
    struct NJS_RGB co;
    float spow;
    struct NJS_RGB spe;
    float cpow2;
    struct NJS_RGB co2;
    float spow2;
    struct NJS_RGB spe2;
};
static_assert(sizeof(LE_PALIGHT_ENV) == 0x60, "sizeof LE_PALIGHT_ENV");
static_assert(offsetof(LE_PALIGHT_ENV, stgNo) == 0x0, "LE_PALIGHT_ENV::stgNo");
static_assert(offsetof(LE_PALIGHT_ENV, actNo) == 0x1, "LE_PALIGHT_ENV::actNo");
static_assert(offsetof(LE_PALIGHT_ENV, chrNo) == 0x2, "LE_PALIGHT_ENV::chrNo");
static_assert(offsetof(LE_PALIGHT_ENV, flgs) == 0x3, "LE_PALIGHT_ENV::flgs");
static_assert(offsetof(LE_PALIGHT_ENV, vec) == 0x4, "LE_PALIGHT_ENV::vec");
static_assert(offsetof(LE_PALIGHT_ENV, dif) == 0x10, "LE_PALIGHT_ENV::dif");
static_assert(offsetof(LE_PALIGHT_ENV, amb) == 0x14, "LE_PALIGHT_ENV::amb");
static_assert(offsetof(LE_PALIGHT_ENV, cpow) == 0x20, "LE_PALIGHT_ENV::cpow");
static_assert(offsetof(LE_PALIGHT_ENV, co) == 0x24, "LE_PALIGHT_ENV::co");
static_assert(offsetof(LE_PALIGHT_ENV, spow) == 0x30, "LE_PALIGHT_ENV::spow");
static_assert(offsetof(LE_PALIGHT_ENV, spe) == 0x34, "LE_PALIGHT_ENV::spe");
static_assert(offsetof(LE_PALIGHT_ENV, cpow2) == 0x40, "LE_PALIGHT_ENV::cpow2");
static_assert(offsetof(LE_PALIGHT_ENV, co2) == 0x44, "LE_PALIGHT_ENV::co2");
static_assert(offsetof(LE_PALIGHT_ENV, spow2) == 0x50, "LE_PALIGHT_ENV::spow2");
static_assert(offsetof(LE_PALIGHT_ENV, spe2) == 0x54, "LE_PALIGHT_ENV::spe2");

struct LightInfo {
    int lsrc;
    float spc;
    float dif;
    float amb;
    struct NJS_ARGB argb;
    struct NJS_POINT3 pos;
    struct NJS_POINT3 vec;
    float nrang;
    float frang;
    long iang;
    long oang;
};
static_assert(sizeof(LightInfo) == 0x48, "sizeof LightInfo");
static_assert(offsetof(LightInfo, lsrc) == 0x0, "LightInfo::lsrc");
static_assert(offsetof(LightInfo, spc) == 0x4, "LightInfo::spc");
static_assert(offsetof(LightInfo, dif) == 0x8, "LightInfo::dif");
static_assert(offsetof(LightInfo, amb) == 0xc, "LightInfo::amb");
static_assert(offsetof(LightInfo, argb) == 0x10, "LightInfo::argb");
static_assert(offsetof(LightInfo, pos) == 0x20, "LightInfo::pos");
static_assert(offsetof(LightInfo, vec) == 0x2c, "LightInfo::vec");
static_assert(offsetof(LightInfo, nrang) == 0x38, "LightInfo::nrang");
static_assert(offsetof(LightInfo, frang) == 0x3c, "LightInfo::frang");
static_assert(offsetof(LightInfo, iang) == 0x40, "LightInfo::iang");
static_assert(offsetof(LightInfo, oang) == 0x44, "LightInfo::oang");

struct NJS_TEXLIST {
    struct NJS_TEXNAME *textures;
    unsigned long nbTexture;
};
static_assert(sizeof(NJS_TEXLIST) == 0x8, "sizeof NJS_TEXLIST");
static_assert(offsetof(NJS_TEXLIST, textures) == 0x0, "NJS_TEXLIST::textures");
static_assert(offsetof(NJS_TEXLIST, nbTexture) == 0x4, "NJS_TEXLIST::nbTexture");

struct NJS_TEXNAME {
    void *filename;
    unsigned long attr;
    unsigned long texaddr;
};
static_assert(sizeof(NJS_TEXNAME) == 0xc, "sizeof NJS_TEXNAME");
static_assert(offsetof(NJS_TEXNAME, filename) == 0x0, "NJS_TEXNAME::filename");
static_assert(offsetof(NJS_TEXNAME, attr) == 0x4, "NJS_TEXNAME::attr");
static_assert(offsetof(NJS_TEXNAME, texaddr) == 0x8, "NJS_TEXNAME::texaddr");

struct MSGC {
    unsigned char kind;
    short x;
    short y;
    unsigned short width;
    unsigned short height;
    unsigned short buf_width;
    unsigned short buf_height;
    unsigned short buf_width2;
    unsigned short buf_height2;
    short lx;
    short ly;
    short sx;
    short sy;
    unsigned short color;
    union NJS_COLOR fc;
    union NJS_COLOR bc;
    float scale;
    void *bitmap;
    unsigned long globalindex;
    struct NJS_TEXLIST texlist;
    struct NJS_TEXNAME texname;
    int msgc_flag;
};
static_assert(sizeof(MSGC) == 0x48, "sizeof MSGC");
static_assert(offsetof(MSGC, kind) == 0x0, "MSGC::kind");
static_assert(offsetof(MSGC, x) == 0x2, "MSGC::x");
static_assert(offsetof(MSGC, y) == 0x4, "MSGC::y");
static_assert(offsetof(MSGC, width) == 0x6, "MSGC::width");
static_assert(offsetof(MSGC, height) == 0x8, "MSGC::height");
static_assert(offsetof(MSGC, buf_width) == 0xa, "MSGC::buf_width");
static_assert(offsetof(MSGC, buf_height) == 0xc, "MSGC::buf_height");
static_assert(offsetof(MSGC, buf_width2) == 0xe, "MSGC::buf_width2");
static_assert(offsetof(MSGC, buf_height2) == 0x10, "MSGC::buf_height2");
static_assert(offsetof(MSGC, lx) == 0x12, "MSGC::lx");
static_assert(offsetof(MSGC, ly) == 0x14, "MSGC::ly");
static_assert(offsetof(MSGC, sx) == 0x16, "MSGC::sx");
static_assert(offsetof(MSGC, sy) == 0x18, "MSGC::sy");
static_assert(offsetof(MSGC, color) == 0x1a, "MSGC::color");
static_assert(offsetof(MSGC, fc) == 0x1c, "MSGC::fc");
static_assert(offsetof(MSGC, bc) == 0x20, "MSGC::bc");
static_assert(offsetof(MSGC, scale) == 0x24, "MSGC::scale");
static_assert(offsetof(MSGC, bitmap) == 0x28, "MSGC::bitmap");
static_assert(offsetof(MSGC, globalindex) == 0x2c, "MSGC::globalindex");
static_assert(offsetof(MSGC, texlist) == 0x30, "MSGC::texlist");
static_assert(offsetof(MSGC, texname) == 0x38, "MSGC::texname");
static_assert(offsetof(MSGC, msgc_flag) == 0x44, "MSGC::msgc_flag");

struct NJS_CACTION {
    struct NJS_CAMERA *camera;
    struct NJS_MOTION *motion;
};
static_assert(sizeof(NJS_CACTION) == 0x8, "sizeof NJS_CACTION");
static_assert(offsetof(NJS_CACTION, camera) == 0x0, "NJS_CACTION::camera");
static_assert(offsetof(NJS_CACTION, motion) == 0x4, "NJS_CACTION::motion");

struct NJS_CAMERA {
    float px;
    float py;
    float pz;
    float vx;
    float vy;
    float vz;
    long roll;
    long ang;
    float n_clip;
    float f_clip;
    struct NJS_POINT3 lx;
    struct NJS_POINT3 ly;
};
static_assert(sizeof(NJS_CAMERA) == 0x40, "sizeof NJS_CAMERA");
static_assert(offsetof(NJS_CAMERA, px) == 0x0, "NJS_CAMERA::px");
static_assert(offsetof(NJS_CAMERA, py) == 0x4, "NJS_CAMERA::py");
static_assert(offsetof(NJS_CAMERA, pz) == 0x8, "NJS_CAMERA::pz");
static_assert(offsetof(NJS_CAMERA, vx) == 0xc, "NJS_CAMERA::vx");
static_assert(offsetof(NJS_CAMERA, vy) == 0x10, "NJS_CAMERA::vy");
static_assert(offsetof(NJS_CAMERA, vz) == 0x14, "NJS_CAMERA::vz");
static_assert(offsetof(NJS_CAMERA, roll) == 0x18, "NJS_CAMERA::roll");
static_assert(offsetof(NJS_CAMERA, ang) == 0x1c, "NJS_CAMERA::ang");
static_assert(offsetof(NJS_CAMERA, n_clip) == 0x20, "NJS_CAMERA::n_clip");
static_assert(offsetof(NJS_CAMERA, f_clip) == 0x24, "NJS_CAMERA::f_clip");
static_assert(offsetof(NJS_CAMERA, lx) == 0x28, "NJS_CAMERA::lx");
static_assert(offsetof(NJS_CAMERA, ly) == 0x34, "NJS_CAMERA::ly");

struct NJS_MODEL {
    struct NJS_POINT3 *points;
    struct NJS_POINT3 *normals;
    long nbPoint;
    struct NJS_MESHSET *meshsets;
    struct NJS_MATERIAL *mats;
    unsigned short nbMeshset;
    unsigned short nbMat;
    struct NJS_POINT3 center;
    float r;
    void *res;
};
static_assert(sizeof(NJS_MODEL) == 0x2c, "sizeof NJS_MODEL");
static_assert(offsetof(NJS_MODEL, points) == 0x0, "NJS_MODEL::points");
static_assert(offsetof(NJS_MODEL, normals) == 0x4, "NJS_MODEL::normals");
static_assert(offsetof(NJS_MODEL, nbPoint) == 0x8, "NJS_MODEL::nbPoint");
static_assert(offsetof(NJS_MODEL, meshsets) == 0xc, "NJS_MODEL::meshsets");
static_assert(offsetof(NJS_MODEL, mats) == 0x10, "NJS_MODEL::mats");
static_assert(offsetof(NJS_MODEL, nbMeshset) == 0x14, "NJS_MODEL::nbMeshset");
static_assert(offsetof(NJS_MODEL, nbMat) == 0x16, "NJS_MODEL::nbMat");
static_assert(offsetof(NJS_MODEL, center) == 0x18, "NJS_MODEL::center");
static_assert(offsetof(NJS_MODEL, r) == 0x24, "NJS_MODEL::r");
static_assert(offsetof(NJS_MODEL, res) == 0x28, "NJS_MODEL::res");

struct NJS_MOTION {
    void *mdata;
    unsigned long nbFrame;
    unsigned short type;
    unsigned short inp_fn;
};
static_assert(sizeof(NJS_MOTION) == 0xc, "sizeof NJS_MOTION");
static_assert(offsetof(NJS_MOTION, mdata) == 0x0, "NJS_MOTION::mdata");
static_assert(offsetof(NJS_MOTION, nbFrame) == 0x4, "NJS_MOTION::nbFrame");
static_assert(offsetof(NJS_MOTION, type) == 0x8, "NJS_MOTION::type");
static_assert(offsetof(NJS_MOTION, inp_fn) == 0xa, "NJS_MOTION::inp_fn");

struct NJS_POINT2COL {
    struct NJS_POINT2 *p;
    union NJS_COLOR *col;
    union NJS_COLOR *tex;
    unsigned long num;
};
static_assert(sizeof(NJS_POINT2COL) == 0x10, "sizeof NJS_POINT2COL");
static_assert(offsetof(NJS_POINT2COL, p) == 0x0, "NJS_POINT2COL::p");
static_assert(offsetof(NJS_POINT2COL, col) == 0x4, "NJS_POINT2COL::col");
static_assert(offsetof(NJS_POINT2COL, tex) == 0x8, "NJS_POINT2COL::tex");
static_assert(offsetof(NJS_POINT2COL, num) == 0xc, "NJS_POINT2COL::num");

struct NJS_POINT3COL {
    struct NJS_POINT3 *p;
    union NJS_COLOR *col;
    union NJS_COLOR *tex;
    unsigned long num;
};
static_assert(sizeof(NJS_POINT3COL) == 0x10, "sizeof NJS_POINT3COL");
static_assert(offsetof(NJS_POINT3COL, p) == 0x0, "NJS_POINT3COL::p");
static_assert(offsetof(NJS_POINT3COL, col) == 0x4, "NJS_POINT3COL::col");
static_assert(offsetof(NJS_POINT3COL, tex) == 0x8, "NJS_POINT3COL::tex");
static_assert(offsetof(NJS_POINT3COL, num) == 0xc, "NJS_POINT3COL::num");

struct NJS_SPRITE {
    struct NJS_POINT3 p;
    float sx;
    float sy;
    long ang;
    struct NJS_TEXLIST *tlist;
    struct NJS_TEXANIM *tanim;
};
static_assert(sizeof(NJS_SPRITE) == 0x20, "sizeof NJS_SPRITE");
static_assert(offsetof(NJS_SPRITE, p) == 0x0, "NJS_SPRITE::p");
static_assert(offsetof(NJS_SPRITE, sx) == 0xc, "NJS_SPRITE::sx");
static_assert(offsetof(NJS_SPRITE, sy) == 0x10, "NJS_SPRITE::sy");
static_assert(offsetof(NJS_SPRITE, ang) == 0x14, "NJS_SPRITE::ang");
static_assert(offsetof(NJS_SPRITE, tlist) == 0x18, "NJS_SPRITE::tlist");
static_assert(offsetof(NJS_SPRITE, tanim) == 0x1c, "NJS_SPRITE::tanim");

struct NJS_TEXANIM {
    short sx;
    short sy;
    short cx;
    short cy;
    short u1;
    short v1;
    short u2;
    short v2;
    short texid;
    short attr;
};
static_assert(sizeof(NJS_TEXANIM) == 0x14, "sizeof NJS_TEXANIM");
static_assert(offsetof(NJS_TEXANIM, sx) == 0x0, "NJS_TEXANIM::sx");
static_assert(offsetof(NJS_TEXANIM, sy) == 0x2, "NJS_TEXANIM::sy");
static_assert(offsetof(NJS_TEXANIM, cx) == 0x4, "NJS_TEXANIM::cx");
static_assert(offsetof(NJS_TEXANIM, cy) == 0x6, "NJS_TEXANIM::cy");
static_assert(offsetof(NJS_TEXANIM, u1) == 0x8, "NJS_TEXANIM::u1");
static_assert(offsetof(NJS_TEXANIM, v1) == 0xa, "NJS_TEXANIM::v1");
static_assert(offsetof(NJS_TEXANIM, u2) == 0xc, "NJS_TEXANIM::u2");
static_assert(offsetof(NJS_TEXANIM, v2) == 0xe, "NJS_TEXANIM::v2");
static_assert(offsetof(NJS_TEXANIM, texid) == 0x10, "NJS_TEXANIM::texid");
static_assert(offsetof(NJS_TEXANIM, attr) == 0x12, "NJS_TEXANIM::attr");

union UNION_STATUS {
    float fRangeOut;
    struct OBJ_SLEEPCON *pObjSleepCondition;
};
static_assert(sizeof(UNION_STATUS) == 0x4, "sizeof UNION_STATUS");
static_assert(offsetof(UNION_STATUS, fRangeOut) == 0x0, "UNION_STATUS::fRangeOut");
static_assert(offsetof(UNION_STATUS, pObjSleepCondition) == 0x0, "UNION_STATUS::pObjSleepCondition");

struct OBJ_CONDITION {
    signed char scCount;
    signed char scUserFlag;
    short ssCondition;
    struct task *pTask;
    struct OBJ_EDITENTRY *pObjEditEntry;
    union UNION_STATUS unionStatus;
};
static_assert(sizeof(OBJ_CONDITION) == 0x10, "sizeof OBJ_CONDITION");
static_assert(offsetof(OBJ_CONDITION, scCount) == 0x0, "OBJ_CONDITION::scCount");
static_assert(offsetof(OBJ_CONDITION, scUserFlag) == 0x1, "OBJ_CONDITION::scUserFlag");
static_assert(offsetof(OBJ_CONDITION, ssCondition) == 0x2, "OBJ_CONDITION::ssCondition");
static_assert(offsetof(OBJ_CONDITION, pTask) == 0x4, "OBJ_CONDITION::pTask");
static_assert(offsetof(OBJ_CONDITION, pObjEditEntry) == 0x8, "OBJ_CONDITION::pObjEditEntry");
static_assert(offsetof(OBJ_CONDITION, unionStatus) == 0xc, "OBJ_CONDITION::unionStatus");

struct SEQ_CLEAR_EQUIV {
    short stageno;
    short flagno;
};
static_assert(sizeof(SEQ_CLEAR_EQUIV) == 0x4, "sizeof SEQ_CLEAR_EQUIV");
static_assert(offsetof(SEQ_CLEAR_EQUIV, stageno) == 0x0, "SEQ_CLEAR_EQUIV::stageno");
static_assert(offsetof(SEQ_CLEAR_EQUIV, flagno) == 0x2, "SEQ_CLEAR_EQUIV::flagno");

struct SEQ_SECTIONTBL {
    struct SEQ_SECTION *psec;
    unsigned char stg;
    unsigned char act;
    unsigned short entrance;
    char name[32];
};
static_assert(sizeof(SEQ_SECTIONTBL) == 0x28, "sizeof SEQ_SECTIONTBL");
static_assert(offsetof(SEQ_SECTIONTBL, psec) == 0x0, "SEQ_SECTIONTBL::psec");
static_assert(offsetof(SEQ_SECTIONTBL, stg) == 0x4, "SEQ_SECTIONTBL::stg");
static_assert(offsetof(SEQ_SECTIONTBL, act) == 0x5, "SEQ_SECTIONTBL::act");
static_assert(offsetof(SEQ_SECTIONTBL, entrance) == 0x6, "SEQ_SECTIONTBL::entrance");
static_assert(offsetof(SEQ_SECTIONTBL, name) == 0x8, "SEQ_SECTIONTBL::name");

struct TaskInfo {
    unsigned int size;
    unsigned long initMode;
    void (*init_p)(struct task *, void *);
    void (*exec_p)(struct task *);
    void (*disp_p)(struct task *);
    void (*dest_p)(struct task *);
};
static_assert(sizeof(TaskInfo) == 0x18, "sizeof TaskInfo");
static_assert(offsetof(TaskInfo, size) == 0x0, "TaskInfo::size");
static_assert(offsetof(TaskInfo, initMode) == 0x4, "TaskInfo::initMode");
static_assert(offsetof(TaskInfo, init_p) == 0x8, "TaskInfo::init_p");
static_assert(offsetof(TaskInfo, exec_p) == 0xc, "TaskInfo::exec_p");
static_assert(offsetof(TaskInfo, disp_p) == 0x10, "TaskInfo::disp_p");
static_assert(offsetof(TaskInfo, dest_p) == 0x14, "TaskInfo::dest_p");

struct VolumeInfo {
    short nearVolOfs;
    short farVolOfs;
    float nearDist;
    float farDist;
};
static_assert(sizeof(VolumeInfo) == 0xc, "sizeof VolumeInfo");
static_assert(offsetof(VolumeInfo, nearVolOfs) == 0x0, "VolumeInfo::nearVolOfs");
static_assert(offsetof(VolumeInfo, farVolOfs) == 0x2, "VolumeInfo::farVolOfs");
static_assert(offsetof(VolumeInfo, nearDist) == 0x4, "VolumeInfo::nearDist");
static_assert(offsetof(VolumeInfo, farDist) == 0x8, "VolumeInfo::farDist");

// Offsets not checked against the code yet.
struct al_action_ctrl {
    unsigned short old_mode;
    unsigned short curr_mode;
    unsigned short req_mode;
    unsigned short flag;
    unsigned short timer;
};
static_assert(sizeof(al_action_ctrl) == 0xa, "sizeof al_action_ctrl");
static_assert(offsetof(al_action_ctrl, old_mode) == 0x0, "al_action_ctrl::old_mode");
static_assert(offsetof(al_action_ctrl, curr_mode) == 0x2, "al_action_ctrl::curr_mode");
static_assert(offsetof(al_action_ctrl, req_mode) == 0x4, "al_action_ctrl::req_mode");
static_assert(offsetof(al_action_ctrl, flag) == 0x6, "al_action_ctrl::flag");
static_assert(offsetof(al_action_ctrl, timer) == 0x8, "al_action_ctrl::timer");

struct alifewk {
    union {
        signed char b[4];
        short w[2];
        long l;
        float f;
        void *ptr;
    } work;
    struct NJS_POINT3 velo;
    struct NJS_POINT3 acc;
    struct Angle3 ang_aim;
    struct Angle3 ang_spd;
    float rad;
    float height;
    float weight;
    struct task *lock_tp;
    void (*dest_org)(struct task *);
    unsigned short action_timer;
    unsigned short stimer;
    unsigned short voice_timer;
    unsigned short rhythm_timer;
    short old_mode;
    short old_smode;
    short curr_mode;
    short curr_smode;
    short req_mode;
    short req_smode;
    short hold_mode;
    unsigned long flag;
    unsigned short action_mode;
    struct NJS_BGRA mat_col;
    float mayu_scl;
    float mayu_alpha;
    long name_alpha;
    unsigned short name_timer;
    unsigned short damage_timer;
    long pitch;
    long yaw;
    long roll;
    short aim_num;
    struct NJS_POINT3 home;
    struct NJS_POINT3 aim;
    struct NJS_POINT3 pre;
    struct NJS_POINT3 offset;
    struct Angle3 aim_ang;
    long view_angle;
    float view_range2;
    float hear_range2;
    float buyo_scale;
    float chao_scl;
    float aim_hpos;
    float aim_vpos;
    float aim_growth;
    unsigned short sekkachi_timer;
    struct al_status *status;
    struct ADV1_AL_TMP_STATUS tmp_status;
    struct al_action_ctrl action_ctrl;
    struct ADV1_AL_MOTION_CTRL motion_ctrl;
    struct ADV1_AL_SHADOW shadow;
    struct ADV1_AL_BODY body;
    struct ADV1_AL_FACE face;
    struct ADV1_AL_ICON icon;
    struct ADV1_AL_PERCEPTION perception;
    struct task *mytask;
    struct task *pAdv2ChaoTask;
};
static_assert(sizeof(alifewk) == 0x8d4, "sizeof alifewk");
static_assert(offsetof(alifewk, work) == 0x0, "alifewk::work");
static_assert(offsetof(alifewk, velo) == 0x4, "alifewk::velo");
static_assert(offsetof(alifewk, acc) == 0x10, "alifewk::acc");
static_assert(offsetof(alifewk, ang_aim) == 0x1c, "alifewk::ang_aim");
static_assert(offsetof(alifewk, ang_spd) == 0x28, "alifewk::ang_spd");
static_assert(offsetof(alifewk, rad) == 0x34, "alifewk::rad");
static_assert(offsetof(alifewk, height) == 0x38, "alifewk::height");
static_assert(offsetof(alifewk, weight) == 0x3c, "alifewk::weight");
static_assert(offsetof(alifewk, lock_tp) == 0x40, "alifewk::lock_tp");
static_assert(offsetof(alifewk, dest_org) == 0x44, "alifewk::dest_org");
static_assert(offsetof(alifewk, action_timer) == 0x48, "alifewk::action_timer");
static_assert(offsetof(alifewk, stimer) == 0x4a, "alifewk::stimer");
static_assert(offsetof(alifewk, voice_timer) == 0x4c, "alifewk::voice_timer");
static_assert(offsetof(alifewk, rhythm_timer) == 0x4e, "alifewk::rhythm_timer");
static_assert(offsetof(alifewk, old_mode) == 0x50, "alifewk::old_mode");
static_assert(offsetof(alifewk, old_smode) == 0x52, "alifewk::old_smode");
static_assert(offsetof(alifewk, curr_mode) == 0x54, "alifewk::curr_mode");
static_assert(offsetof(alifewk, curr_smode) == 0x56, "alifewk::curr_smode");
static_assert(offsetof(alifewk, req_mode) == 0x58, "alifewk::req_mode");
static_assert(offsetof(alifewk, req_smode) == 0x5a, "alifewk::req_smode");
static_assert(offsetof(alifewk, hold_mode) == 0x5c, "alifewk::hold_mode");
static_assert(offsetof(alifewk, flag) == 0x60, "alifewk::flag");
static_assert(offsetof(alifewk, action_mode) == 0x64, "alifewk::action_mode");
static_assert(offsetof(alifewk, mat_col) == 0x66, "alifewk::mat_col");
static_assert(offsetof(alifewk, mayu_scl) == 0x6c, "alifewk::mayu_scl");
static_assert(offsetof(alifewk, mayu_alpha) == 0x70, "alifewk::mayu_alpha");
static_assert(offsetof(alifewk, name_alpha) == 0x74, "alifewk::name_alpha");
static_assert(offsetof(alifewk, name_timer) == 0x78, "alifewk::name_timer");
static_assert(offsetof(alifewk, damage_timer) == 0x7a, "alifewk::damage_timer");
static_assert(offsetof(alifewk, pitch) == 0x7c, "alifewk::pitch");
static_assert(offsetof(alifewk, yaw) == 0x80, "alifewk::yaw");
static_assert(offsetof(alifewk, roll) == 0x84, "alifewk::roll");
static_assert(offsetof(alifewk, aim_num) == 0x88, "alifewk::aim_num");
static_assert(offsetof(alifewk, home) == 0x8c, "alifewk::home");
static_assert(offsetof(alifewk, aim) == 0x98, "alifewk::aim");
static_assert(offsetof(alifewk, pre) == 0xa4, "alifewk::pre");
static_assert(offsetof(alifewk, offset) == 0xb0, "alifewk::offset");
static_assert(offsetof(alifewk, aim_ang) == 0xbc, "alifewk::aim_ang");
static_assert(offsetof(alifewk, view_angle) == 0xc8, "alifewk::view_angle");
static_assert(offsetof(alifewk, view_range2) == 0xcc, "alifewk::view_range2");
static_assert(offsetof(alifewk, hear_range2) == 0xd0, "alifewk::hear_range2");
static_assert(offsetof(alifewk, buyo_scale) == 0xd4, "alifewk::buyo_scale");
static_assert(offsetof(alifewk, chao_scl) == 0xd8, "alifewk::chao_scl");
static_assert(offsetof(alifewk, aim_hpos) == 0xdc, "alifewk::aim_hpos");
static_assert(offsetof(alifewk, aim_vpos) == 0xe0, "alifewk::aim_vpos");
static_assert(offsetof(alifewk, aim_growth) == 0xe4, "alifewk::aim_growth");
static_assert(offsetof(alifewk, sekkachi_timer) == 0xe8, "alifewk::sekkachi_timer");
static_assert(offsetof(alifewk, status) == 0xec, "alifewk::status");
static_assert(offsetof(alifewk, tmp_status) == 0xf0, "alifewk::tmp_status");
static_assert(offsetof(alifewk, action_ctrl) == 0x10c, "alifewk::action_ctrl");
static_assert(offsetof(alifewk, motion_ctrl) == 0x118, "alifewk::motion_ctrl");
static_assert(offsetof(alifewk, shadow) == 0x13c, "alifewk::shadow");
static_assert(offsetof(alifewk, body) == 0x248, "alifewk::body");
static_assert(offsetof(alifewk, face) == 0x7c8, "alifewk::face");
static_assert(offsetof(alifewk, icon) == 0x810, "alifewk::icon");
static_assert(offsetof(alifewk, perception) == 0x8c8, "alifewk::perception");
static_assert(offsetof(alifewk, mytask) == 0x8cc, "alifewk::mytask");
static_assert(offsetof(alifewk, pAdv2ChaoTask) == 0x8d0, "alifewk::pAdv2ChaoTask");

struct anywk {
    union {
        unsigned char ub[16];
        signed char sb[16];
        unsigned short uw[8];
        short sw[8];
        unsigned long ul[4];
        long sl[4];
        float f[4];
        void *ptr[4];
    } work;
};
static_assert(sizeof(anywk) == 0x10, "sizeof anywk");
static_assert(offsetof(anywk, work) == 0x0, "anywk::work");

struct bankdata {
    unsigned char banknum;
    char *bankfilename;
};
static_assert(sizeof(bankdata) == 0x8, "sizeof bankdata");
static_assert(offsetof(bankdata, banknum) == 0x0, "bankdata::banknum");
static_assert(offsetof(bankdata, bankfilename) == 0x4, "bankdata::bankfilename");

struct bankdatalist {
    unsigned char datasize;
    struct bankdata *data;
};
static_assert(sizeof(bankdatalist) == 0x8, "sizeof bankdatalist");
static_assert(offsetof(bankdatalist, datasize) == 0x0, "bankdatalist::datasize");
static_assert(offsetof(bankdatalist, data) == 0x4, "bankdatalist::data");

// Offsets not checked against the code yet.
struct c_colli_hit_info {
    signed char my_num;
    signed char hit_num;
    unsigned short flag;
    struct taskwk *hit_twp;
};
static_assert(sizeof(c_colli_hit_info) == 0x8, "sizeof c_colli_hit_info");
static_assert(offsetof(c_colli_hit_info, my_num) == 0x0, "c_colli_hit_info::my_num");
static_assert(offsetof(c_colli_hit_info, hit_num) == 0x1, "c_colli_hit_info::hit_num");
static_assert(offsetof(c_colli_hit_info, flag) == 0x2, "c_colli_hit_info::flag");
static_assert(offsetof(c_colli_hit_info, hit_twp) == 0x4, "c_colli_hit_info::hit_twp");

struct colliwk {
    unsigned short id;
    short nbHit;
    unsigned short flag;
    unsigned short nbInfo;
    float colli_range;
    struct CCL_INFO *info;
    struct c_colli_hit_info hit_info[16];
    struct NJS_POINT3 normal;
    struct task *mytask;
    short my_num;
    short hit_num;
    struct colliwk *hit_cwp;
};
static_assert(sizeof(colliwk) == 0xa8, "sizeof colliwk");
static_assert(offsetof(colliwk, id) == 0x0, "colliwk::id");
static_assert(offsetof(colliwk, nbHit) == 0x2, "colliwk::nbHit");
static_assert(offsetof(colliwk, flag) == 0x4, "colliwk::flag");
static_assert(offsetof(colliwk, nbInfo) == 0x6, "colliwk::nbInfo");
static_assert(offsetof(colliwk, colli_range) == 0x8, "colliwk::colli_range");
static_assert(offsetof(colliwk, info) == 0xc, "colliwk::info");
static_assert(offsetof(colliwk, hit_info) == 0x10, "colliwk::hit_info");
static_assert(offsetof(colliwk, normal) == 0x90, "colliwk::normal");
static_assert(offsetof(colliwk, mytask) == 0x9c, "colliwk::mytask");
static_assert(offsetof(colliwk, my_num) == 0xa0, "colliwk::my_num");
static_assert(offsetof(colliwk, hit_num) == 0xa2, "colliwk::hit_num");
static_assert(offsetof(colliwk, hit_cwp) == 0xa4, "colliwk::hit_cwp");

struct forcewk {
    void (*call_back)(struct task *, struct taskwk *, struct forcewk *);
    struct Angle3 ang_spd;
    struct NJS_POINT3 pos_spd;
};
static_assert(sizeof(forcewk) == 0x1c, "sizeof forcewk");
static_assert(offsetof(forcewk, call_back) == 0x0, "forcewk::call_back");
static_assert(offsetof(forcewk, ang_spd) == 0x4, "forcewk::ang_spd");
static_assert(offsetof(forcewk, pos_spd) == 0x10, "forcewk::pos_spd");

struct motionwk {
    union {
        signed char b[4];
        short w[2];
        long l;
        float f;
        void *ptr;
    } work;
    struct NJS_POINT3 spd;
    struct NJS_POINT3 acc;
    struct Angle3 ang_aim;
    struct Angle3 ang_spd;
    float rad;
    float height;
    float weight;
};
static_assert(sizeof(motionwk) == 0x40, "sizeof motionwk");
static_assert(offsetof(motionwk, work) == 0x0, "motionwk::work");
static_assert(offsetof(motionwk, spd) == 0x4, "motionwk::spd");
static_assert(offsetof(motionwk, acc) == 0x10, "motionwk::acc");
static_assert(offsetof(motionwk, ang_aim) == 0x1c, "motionwk::ang_aim");
static_assert(offsetof(motionwk, ang_spd) == 0x28, "motionwk::ang_spd");
static_assert(offsetof(motionwk, rad) == 0x34, "motionwk::rad");
static_assert(offsetof(motionwk, height) == 0x38, "motionwk::height");
static_assert(offsetof(motionwk, weight) == 0x3c, "motionwk::weight");

struct motionwk2 {
    union {
        signed char b[4];
        short w[2];
        long l;
        float f;
        void *ptr;
    } work;
    struct NJS_POINT3 spd;
    struct NJS_POINT3 acc;
    struct Angle3 ang_aim;
    struct Angle3 ang_spd;
    float force;
    float accel;
    float frict;
};
static_assert(sizeof(motionwk2) == 0x40, "sizeof motionwk2");
static_assert(offsetof(motionwk2, work) == 0x0, "motionwk2::work");
static_assert(offsetof(motionwk2, spd) == 0x4, "motionwk2::spd");
static_assert(offsetof(motionwk2, acc) == 0x10, "motionwk2::acc");
static_assert(offsetof(motionwk2, ang_aim) == 0x1c, "motionwk2::ang_aim");
static_assert(offsetof(motionwk2, ang_spd) == 0x28, "motionwk2::ang_spd");
static_assert(offsetof(motionwk2, force) == 0x34, "motionwk2::force");
static_assert(offsetof(motionwk2, accel) == 0x38, "motionwk2::accel");
static_assert(offsetof(motionwk2, frict) == 0x3c, "motionwk2::frict");

struct mtnjvwk {
    short mtnmode;
    short jvmode;
    unsigned short reqaction;
    unsigned short action;
    unsigned short lastaction;
    unsigned short nextaction;
    unsigned short acttimer;
    short flag;
    float nframe;
    float start_frame;
    float *spdp;
    float *workp;
    struct PL_ACTION *plactptr;
    struct PL_JOIN_VERTEX *pljvptr;
    struct NJS_ACTION *actwkptr;
};
static_assert(sizeof(mtnjvwk) == 0x2c, "sizeof mtnjvwk");
static_assert(offsetof(mtnjvwk, mtnmode) == 0x0, "mtnjvwk::mtnmode");
static_assert(offsetof(mtnjvwk, jvmode) == 0x2, "mtnjvwk::jvmode");
static_assert(offsetof(mtnjvwk, reqaction) == 0x4, "mtnjvwk::reqaction");
static_assert(offsetof(mtnjvwk, action) == 0x6, "mtnjvwk::action");
static_assert(offsetof(mtnjvwk, lastaction) == 0x8, "mtnjvwk::lastaction");
static_assert(offsetof(mtnjvwk, nextaction) == 0xa, "mtnjvwk::nextaction");
static_assert(offsetof(mtnjvwk, acttimer) == 0xc, "mtnjvwk::acttimer");
static_assert(offsetof(mtnjvwk, flag) == 0xe, "mtnjvwk::flag");
static_assert(offsetof(mtnjvwk, nframe) == 0x10, "mtnjvwk::nframe");
static_assert(offsetof(mtnjvwk, start_frame) == 0x14, "mtnjvwk::start_frame");
static_assert(offsetof(mtnjvwk, spdp) == 0x18, "mtnjvwk::spdp");
static_assert(offsetof(mtnjvwk, workp) == 0x1c, "mtnjvwk::workp");
static_assert(offsetof(mtnjvwk, plactptr) == 0x20, "mtnjvwk::plactptr");
static_assert(offsetof(mtnjvwk, pljvptr) == 0x24, "mtnjvwk::pljvptr");
static_assert(offsetof(mtnjvwk, actwkptr) == 0x28, "mtnjvwk::actwkptr");

struct obj {
    unsigned long evalflags;
    struct NJS_MODEL *model;
    float pos[3];
    long ang[3];
    float scl[3];
    struct obj *child;
    struct obj *sibling;
};
static_assert(sizeof(obj) == 0x34, "sizeof obj");
static_assert(offsetof(obj, evalflags) == 0x0, "obj::evalflags");
static_assert(offsetof(obj, model) == 0x4, "obj::model");
static_assert(offsetof(obj, pos) == 0x8, "obj::pos");
static_assert(offsetof(obj, ang) == 0x14, "obj::ang");
static_assert(offsetof(obj, scl) == 0x20, "obj::scl");
static_assert(offsetof(obj, child) == 0x2c, "obj::child");
static_assert(offsetof(obj, sibling) == 0x30, "obj::sibling");

struct particle_entry {
    struct sp_info *info;
    unsigned long wksize;
    void (*exec)(struct sp_link *);
    struct sp_link *link;
};
static_assert(sizeof(particle_entry) == 0x10, "sizeof particle_entry");
static_assert(offsetof(particle_entry, info) == 0x0, "particle_entry::info");
static_assert(offsetof(particle_entry, wksize) == 0x4, "particle_entry::wksize");
static_assert(offsetof(particle_entry, exec) == 0x8, "particle_entry::exec");
static_assert(offsetof(particle_entry, link) == 0xc, "particle_entry::link");

struct particle_info {
    float scl;
    float sclspd;
    float animspd;
    float friction;
    float yacc;
    struct NJS_POINT3 pos;
    struct NJS_POINT3 velo;
    struct NJS_ARGB argb;
};
static_assert(sizeof(particle_info) == 0x3c, "sizeof particle_info");
static_assert(offsetof(particle_info, scl) == 0x0, "particle_info::scl");
static_assert(offsetof(particle_info, sclspd) == 0x4, "particle_info::sclspd");
static_assert(offsetof(particle_info, animspd) == 0x8, "particle_info::animspd");
static_assert(offsetof(particle_info, friction) == 0xc, "particle_info::friction");
static_assert(offsetof(particle_info, yacc) == 0x10, "particle_info::yacc");
static_assert(offsetof(particle_info, pos) == 0x14, "particle_info::pos");
static_assert(offsetof(particle_info, velo) == 0x20, "particle_info::velo");
static_assert(offsetof(particle_info, argb) == 0x2c, "particle_info::argb");

struct pathtag {
    unsigned char pathtype;
    unsigned short points;
    float totallen;
    struct pathtbl *tblhead;
    void *pathtask;
};
static_assert(sizeof(pathtag) == 0x10, "sizeof pathtag");
static_assert(offsetof(pathtag, pathtype) == 0x0, "pathtag::pathtype");
static_assert(offsetof(pathtag, points) == 0x2, "pathtag::points");
static_assert(offsetof(pathtag, totallen) == 0x4, "pathtag::totallen");
static_assert(offsetof(pathtag, tblhead) == 0x8, "pathtag::tblhead");
static_assert(offsetof(pathtag, pathtask) == 0xc, "pathtag::pathtask");

struct player_parameter {
    long jump2_timer;
    float pos_error;
    float lim_h_spd;
    float lim_v_spd;
    float max_x_spd;
    float max_psh_spd;
    float jmp_y_spd;
    float nocon_speed;
    float slide_speed;
    float jog_speed;
    float run_speed;
    float rush_speed;
    float crash_speed;
    float dash_speed;
    float jmp_addit;
    float run_accel;
    float air_accel;
    float slow_down;
    float run_break;
    float air_break;
    float air_resist_air;
    float air_resist;
    float air_resist_y;
    float air_resist_z;
    float grd_frict;
    float grd_frict_z;
    float lim_frict;
    float rat_bound;
    float rad;
    float height;
    float weight;
    float eyes_height;
    float center_height;
};
static_assert(sizeof(player_parameter) == 0x84, "sizeof player_parameter");
static_assert(offsetof(player_parameter, jump2_timer) == 0x0, "player_parameter::jump2_timer");
static_assert(offsetof(player_parameter, pos_error) == 0x4, "player_parameter::pos_error");
static_assert(offsetof(player_parameter, lim_h_spd) == 0x8, "player_parameter::lim_h_spd");
static_assert(offsetof(player_parameter, lim_v_spd) == 0xc, "player_parameter::lim_v_spd");
static_assert(offsetof(player_parameter, max_x_spd) == 0x10, "player_parameter::max_x_spd");
static_assert(offsetof(player_parameter, max_psh_spd) == 0x14, "player_parameter::max_psh_spd");
static_assert(offsetof(player_parameter, jmp_y_spd) == 0x18, "player_parameter::jmp_y_spd");
static_assert(offsetof(player_parameter, nocon_speed) == 0x1c, "player_parameter::nocon_speed");
static_assert(offsetof(player_parameter, slide_speed) == 0x20, "player_parameter::slide_speed");
static_assert(offsetof(player_parameter, jog_speed) == 0x24, "player_parameter::jog_speed");
static_assert(offsetof(player_parameter, run_speed) == 0x28, "player_parameter::run_speed");
static_assert(offsetof(player_parameter, rush_speed) == 0x2c, "player_parameter::rush_speed");
static_assert(offsetof(player_parameter, crash_speed) == 0x30, "player_parameter::crash_speed");
static_assert(offsetof(player_parameter, dash_speed) == 0x34, "player_parameter::dash_speed");
static_assert(offsetof(player_parameter, jmp_addit) == 0x38, "player_parameter::jmp_addit");
static_assert(offsetof(player_parameter, run_accel) == 0x3c, "player_parameter::run_accel");
static_assert(offsetof(player_parameter, air_accel) == 0x40, "player_parameter::air_accel");
static_assert(offsetof(player_parameter, slow_down) == 0x44, "player_parameter::slow_down");
static_assert(offsetof(player_parameter, run_break) == 0x48, "player_parameter::run_break");
static_assert(offsetof(player_parameter, air_break) == 0x4c, "player_parameter::air_break");
static_assert(offsetof(player_parameter, air_resist_air) == 0x50, "player_parameter::air_resist_air");
static_assert(offsetof(player_parameter, air_resist) == 0x54, "player_parameter::air_resist");
static_assert(offsetof(player_parameter, air_resist_y) == 0x58, "player_parameter::air_resist_y");
static_assert(offsetof(player_parameter, air_resist_z) == 0x5c, "player_parameter::air_resist_z");
static_assert(offsetof(player_parameter, grd_frict) == 0x60, "player_parameter::grd_frict");
static_assert(offsetof(player_parameter, grd_frict_z) == 0x64, "player_parameter::grd_frict_z");
static_assert(offsetof(player_parameter, lim_frict) == 0x68, "player_parameter::lim_frict");
static_assert(offsetof(player_parameter, rat_bound) == 0x6c, "player_parameter::rat_bound");
static_assert(offsetof(player_parameter, rad) == 0x70, "player_parameter::rad");
static_assert(offsetof(player_parameter, height) == 0x74, "player_parameter::height");
static_assert(offsetof(player_parameter, weight) == 0x78, "player_parameter::weight");
static_assert(offsetof(player_parameter, eyes_height) == 0x7c, "player_parameter::eyes_height");
static_assert(offsetof(player_parameter, center_height) == 0x80, "player_parameter::center_height");

// Offsets not checked against the code yet.
struct shadowwk {
    long angx;
    long angz;
    unsigned long Attr_top;
    unsigned long Attr_bottom;
    float y_top;
    float y_bottom;
    unsigned long _Attr_top;
    unsigned long _Attr_bottom;
    float scl;
};
static_assert(sizeof(shadowwk) == 0x24, "sizeof shadowwk");
static_assert(offsetof(shadowwk, angx) == 0x0, "shadowwk::angx");
static_assert(offsetof(shadowwk, angz) == 0x4, "shadowwk::angz");
static_assert(offsetof(shadowwk, Attr_top) == 0x8, "shadowwk::Attr_top");
static_assert(offsetof(shadowwk, Attr_bottom) == 0xc, "shadowwk::Attr_bottom");
static_assert(offsetof(shadowwk, y_top) == 0x10, "shadowwk::y_top");
static_assert(offsetof(shadowwk, y_bottom) == 0x14, "shadowwk::y_bottom");
static_assert(offsetof(shadowwk, _Attr_top) == 0x18, "shadowwk::_Attr_top");
static_assert(offsetof(shadowwk, _Attr_bottom) == 0x1c, "shadowwk::_Attr_bottom");
static_assert(offsetof(shadowwk, scl) == 0x20, "shadowwk::scl");

struct playerwk {
    union {
        signed char b[4];
        short w[2];
        long l;
        float f;
        void *ptr;
    } work;
    short equipment;
    short item;
    short jumptimer;
    short nocontimer;
    short breathtimer;
    short waittimer;
    short flag;
    short island_num;
    short path_point;
    float hpos;
    float dotp;
    struct NJS_POINT3 eff;
    struct NJS_POINT3 acc;
    struct NJS_POINT3 spd;
    struct NJS_POINT3 wall_normal;
    struct NJS_POINT3 floor_normal;
    unsigned long attr;
    unsigned long last_attr;
    struct csts *cstsp;
    struct task *htp;
    struct task *ttp;
    struct PL_FACE *pfp;
    struct obj *lclop;
    struct PL_LANDPOSI *island_list;
    union {
        signed char sb[32];
        unsigned char ub[32];
        short sw[16];
        unsigned short uw[16];
        long sl[8];
        unsigned long ul[8];
        float f[8];
        void *ptr[8];
    } free;
    struct player_parameter p;
    struct mtnjvwk mj;
    struct NJS_POINT3 righthand_pos;
    struct NJS_POINT3 lefthand_pos;
    struct NJS_POINT3 rightfoot_pos;
    struct NJS_POINT3 leftfoot_pos;
    struct NJS_POINT3 user0_pos;
    struct NJS_POINT3 user1_pos;
    struct NJS_POINT3 righthand_vec;
    struct NJS_POINT3 lefthand_vec;
    struct NJS_POINT3 rightfoot_vec;
    struct NJS_POINT3 leftfoot_vec;
    struct NJS_POINT3 user0_vec;
    struct NJS_POINT3 user1_vec;
    struct shadowwk shadow;
};
static_assert(sizeof(playerwk) == 0x200, "sizeof playerwk");
static_assert(offsetof(playerwk, work) == 0x0, "playerwk::work");
static_assert(offsetof(playerwk, equipment) == 0x4, "playerwk::equipment");
static_assert(offsetof(playerwk, item) == 0x6, "playerwk::item");
static_assert(offsetof(playerwk, jumptimer) == 0x8, "playerwk::jumptimer");
static_assert(offsetof(playerwk, nocontimer) == 0xa, "playerwk::nocontimer");
static_assert(offsetof(playerwk, breathtimer) == 0xc, "playerwk::breathtimer");
static_assert(offsetof(playerwk, waittimer) == 0xe, "playerwk::waittimer");
static_assert(offsetof(playerwk, flag) == 0x10, "playerwk::flag");
static_assert(offsetof(playerwk, island_num) == 0x12, "playerwk::island_num");
static_assert(offsetof(playerwk, path_point) == 0x14, "playerwk::path_point");
static_assert(offsetof(playerwk, hpos) == 0x18, "playerwk::hpos");
static_assert(offsetof(playerwk, dotp) == 0x1c, "playerwk::dotp");
static_assert(offsetof(playerwk, eff) == 0x20, "playerwk::eff");
static_assert(offsetof(playerwk, acc) == 0x2c, "playerwk::acc");
static_assert(offsetof(playerwk, spd) == 0x38, "playerwk::spd");
static_assert(offsetof(playerwk, wall_normal) == 0x44, "playerwk::wall_normal");
static_assert(offsetof(playerwk, floor_normal) == 0x50, "playerwk::floor_normal");
static_assert(offsetof(playerwk, attr) == 0x5c, "playerwk::attr");
static_assert(offsetof(playerwk, last_attr) == 0x60, "playerwk::last_attr");
static_assert(offsetof(playerwk, cstsp) == 0x64, "playerwk::cstsp");
static_assert(offsetof(playerwk, htp) == 0x68, "playerwk::htp");
static_assert(offsetof(playerwk, ttp) == 0x6c, "playerwk::ttp");
static_assert(offsetof(playerwk, pfp) == 0x70, "playerwk::pfp");
static_assert(offsetof(playerwk, lclop) == 0x74, "playerwk::lclop");
static_assert(offsetof(playerwk, island_list) == 0x78, "playerwk::island_list");
static_assert(offsetof(playerwk, free) == 0x7c, "playerwk::free");
static_assert(offsetof(playerwk, p) == 0x9c, "playerwk::p");
static_assert(offsetof(playerwk, mj) == 0x120, "playerwk::mj");
static_assert(offsetof(playerwk, righthand_pos) == 0x14c, "playerwk::righthand_pos");
static_assert(offsetof(playerwk, lefthand_pos) == 0x158, "playerwk::lefthand_pos");
static_assert(offsetof(playerwk, rightfoot_pos) == 0x164, "playerwk::rightfoot_pos");
static_assert(offsetof(playerwk, leftfoot_pos) == 0x170, "playerwk::leftfoot_pos");
static_assert(offsetof(playerwk, user0_pos) == 0x17c, "playerwk::user0_pos");
static_assert(offsetof(playerwk, user1_pos) == 0x188, "playerwk::user1_pos");
static_assert(offsetof(playerwk, righthand_vec) == 0x194, "playerwk::righthand_vec");
static_assert(offsetof(playerwk, lefthand_vec) == 0x1a0, "playerwk::lefthand_vec");
static_assert(offsetof(playerwk, rightfoot_vec) == 0x1ac, "playerwk::rightfoot_vec");
static_assert(offsetof(playerwk, leftfoot_vec) == 0x1b8, "playerwk::leftfoot_vec");
static_assert(offsetof(playerwk, user0_vec) == 0x1c4, "playerwk::user0_vec");
static_assert(offsetof(playerwk, user1_vec) == 0x1d0, "playerwk::user1_vec");
static_assert(offsetof(playerwk, shadow) == 0x1dc, "playerwk::shadow");

struct sp_info {
    struct NJS_TEXLIST *texlist;
    struct NJS_TEXANIM *texanim;
    int animnum;
    int srcblend;
    int dstblend;
};
static_assert(sizeof(sp_info) == 0x14, "sizeof sp_info");
static_assert(offsetof(sp_info, texlist) == 0x0, "sp_info::texlist");
static_assert(offsetof(sp_info, texanim) == 0x4, "sp_info::texanim");
static_assert(offsetof(sp_info, animnum) == 0x8, "sp_info::animnum");
static_assert(offsetof(sp_info, srcblend) == 0xc, "sp_info::srcblend");
static_assert(offsetof(sp_info, dstblend) == 0x10, "sp_info::dstblend");

struct sp_link {
    struct sp_link *next;
    struct sp_task *head;
    void (*exec)(struct sp_link *);
    unsigned long numtask;
    struct sp_info *info;
    unsigned long sysflag;
    void *work;
};
static_assert(sizeof(sp_link) == 0x1c, "sizeof sp_link");
static_assert(offsetof(sp_link, next) == 0x0, "sp_link::next");
static_assert(offsetof(sp_link, head) == 0x4, "sp_link::head");
static_assert(offsetof(sp_link, exec) == 0x8, "sp_link::exec");
static_assert(offsetof(sp_link, numtask) == 0xc, "sp_link::numtask");
static_assert(offsetof(sp_link, info) == 0x10, "sp_link::info");
static_assert(offsetof(sp_link, sysflag) == 0x14, "sp_link::sysflag");
static_assert(offsetof(sp_link, work) == 0x18, "sp_link::work");

struct sp_task {
    struct sp_task *next;
    void (*exec)(struct sp_task *, struct sp_link *);
    unsigned char mode;
    unsigned char flag;
    short no;
    long ang;
    float frame;
    float scl;
    struct NJS_POINT3 pos;
    struct NJS_POINT3 spd;
    struct NJS_ARGB argb;
    float offset;
    union {
        short w[2];
        long l;
        float f;
        void *ptr;
    } work[2];
    unsigned char wrtZflg;
};
static_assert(sizeof(sp_task) == 0x50, "sizeof sp_task");
static_assert(offsetof(sp_task, next) == 0x0, "sp_task::next");
static_assert(offsetof(sp_task, exec) == 0x4, "sp_task::exec");
static_assert(offsetof(sp_task, mode) == 0x8, "sp_task::mode");
static_assert(offsetof(sp_task, flag) == 0x9, "sp_task::flag");
static_assert(offsetof(sp_task, no) == 0xa, "sp_task::no");
static_assert(offsetof(sp_task, ang) == 0xc, "sp_task::ang");
static_assert(offsetof(sp_task, frame) == 0x10, "sp_task::frame");
static_assert(offsetof(sp_task, scl) == 0x14, "sp_task::scl");
static_assert(offsetof(sp_task, pos) == 0x18, "sp_task::pos");
static_assert(offsetof(sp_task, spd) == 0x24, "sp_task::spd");
static_assert(offsetof(sp_task, argb) == 0x30, "sp_task::argb");
static_assert(offsetof(sp_task, offset) == 0x40, "sp_task::offset");
static_assert(offsetof(sp_task, work) == 0x44, "sp_task::work");
static_assert(offsetof(sp_task, wrtZflg) == 0x4c, "sp_task::wrtZflg");

struct task {
    struct task *next;
    struct task *last;
    struct task *ptp;
    struct task *ctp;
    void (*exec)(struct task *);
    void (*disp)(struct task *);
    void (*dest)(struct task *);
    struct OBJ_CONDITION *ocp;
    struct taskwk *twp;
    struct motionwk *mwp;
    struct forcewk *fwp;
    struct anywk *awp;
    void *thp;
};
static_assert(sizeof(task) == 0x34, "sizeof task");
static_assert(offsetof(task, next) == 0x0, "task::next");
static_assert(offsetof(task, last) == 0x4, "task::last");
static_assert(offsetof(task, ptp) == 0x8, "task::ptp");
static_assert(offsetof(task, ctp) == 0xc, "task::ctp");
static_assert(offsetof(task, exec) == 0x10, "task::exec");
static_assert(offsetof(task, disp) == 0x14, "task::disp");
static_assert(offsetof(task, dest) == 0x18, "task::dest");
static_assert(offsetof(task, ocp) == 0x1c, "task::ocp");
static_assert(offsetof(task, twp) == 0x20, "task::twp");
static_assert(offsetof(task, mwp) == 0x24, "task::mwp");
static_assert(offsetof(task, fwp) == 0x28, "task::fwp");
static_assert(offsetof(task, awp) == 0x2c, "task::awp");
static_assert(offsetof(task, thp) == 0x30, "task::thp");

struct taskwk {
    signed char mode;
    signed char smode;
    unsigned char id;
    unsigned char btimer;
    short flag;
    unsigned short wtimer;
    union {
        unsigned char b[4];
        unsigned short w[2];
        unsigned long l;
        float f;
        void *ptr;
    } counter;
    union {
        signed char b[4];
        short w[2];
        long l;
        float f;
        void *ptr;
    } timer;
    union {
        signed char b[4];
        short w[2];
        long l;
        float f;
        void *ptr;
    } value;
    struct Angle3 ang;
    struct NJS_POINT3 pos;
    struct NJS_POINT3 scl;
    struct colliwk *cwp;
    struct eventwk *ewp;
};
static_assert(sizeof(taskwk) == 0x40, "sizeof taskwk");
static_assert(offsetof(taskwk, mode) == 0x0, "taskwk::mode");
static_assert(offsetof(taskwk, smode) == 0x1, "taskwk::smode");
static_assert(offsetof(taskwk, id) == 0x2, "taskwk::id");
static_assert(offsetof(taskwk, btimer) == 0x3, "taskwk::btimer");
static_assert(offsetof(taskwk, flag) == 0x4, "taskwk::flag");
static_assert(offsetof(taskwk, wtimer) == 0x6, "taskwk::wtimer");
static_assert(offsetof(taskwk, counter) == 0x8, "taskwk::counter");
static_assert(offsetof(taskwk, timer) == 0xc, "taskwk::timer");
static_assert(offsetof(taskwk, value) == 0x10, "taskwk::value");
static_assert(offsetof(taskwk, ang) == 0x14, "taskwk::ang");
static_assert(offsetof(taskwk, pos) == 0x20, "taskwk::pos");
static_assert(offsetof(taskwk, scl) == 0x2c, "taskwk::scl");
static_assert(offsetof(taskwk, cwp) == 0x38, "taskwk::cwp");
static_assert(offsetof(taskwk, ewp) == 0x3c, "taskwk::ewp");

struct u4s {
    unsigned char u4_ACT1 : 4;
    unsigned char u4_ACT2 : 4;
    unsigned char u4_ACT3 : 4;
    unsigned char u4_ACT4 : 4;
    unsigned char u4_ACT5 : 4;
    unsigned char u4_ACT6 : 4;
    unsigned char u4_ACT7 : 4;
    unsigned char u4_ACT8 : 4;
};
static_assert(sizeof(u4s) == 4, "sizeof u4s");
