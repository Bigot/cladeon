#include "cladeonscreen.h"
#include "cladeonsound.h"
#include "cladeonkbd.h"
#include "debug.h"

// page startup variables
int modselected          = 0 ;
int PageSelected         = PAGE_NORM ;
int PreviousPageSelected = PAGE_NORM ;
int PageLock             = 0 ;
int keyboard_modifier    = 0;
int modifierLock         = 0 ;
int lastkey              = 0 ;
int accentiterator       = 0 ;


// void (CladeonKbd::*pointeurfct)(int) = &CladeonKbd::switchToPage ;

//=====================================================================
// keyboard codes
//=====================================================================


const PROGMEM  KeyWord K_ENTER = {   5,40,"","ENTER",0,NULL};
const PROGMEM  KeyWord K_ESC = {   5,41,"","ESC",0,NULL};
const PROGMEM  KeyWord K_INSERT = {   5,73,"","INSERT",0,NULL};
const PROGMEM  KeyWord K_BACKSPACE = {   5,42,"","BACKSPACE",0,NULL};
const PROGMEM  KeyWord K_TAB = {   5,43,"","TAB",0,NULL};
const PROGMEM  KeyWord K_SPACE = {  5,44,"","space",0,NULL};
const PROGMEM  KeyWord K_F1 = {   5,58,"","F1",0,NULL};
const PROGMEM  KeyWord K_F2 = {   5,59,"","F2" ,0,NULL};
const PROGMEM  KeyWord K_F3 = {   5,60,"","F3" ,0,NULL};
const PROGMEM  KeyWord K_F4 = {   5,61,"","F4" ,0,NULL};
const PROGMEM  KeyWord K_F5 = {   5,62,"","F5" ,0,NULL};
const PROGMEM  KeyWord K_F6 = {   5,63,"","F6" ,0,NULL};
const PROGMEM  KeyWord K_F7 = {   5,64,"","F7" ,0,NULL};
const PROGMEM  KeyWord K_F8 = {   5,65,"","F8" ,0,NULL};
const PROGMEM  KeyWord K_F9 = {   5,66,"","F9" ,0,NULL};
const PROGMEM  KeyWord K_F10 = {  5,67,"","F10" ,0,NULL};
const PROGMEM  KeyWord K_F11 = {  5,68,"","F11" ,0,NULL};
const PROGMEM  KeyWord K_F12 = {  5,69,"","F12" ,0,NULL};
const PROGMEM  KeyWord K_RIGHT = {   5,79,"","RIGHT" ,0,NULL};
const PROGMEM  KeyWord K_LEFT = {   5,80,"","LEFT" ,0,NULL};
const PROGMEM  KeyWord K_DOWN = {   5,81,"","DOWN" ,0,NULL};
const PROGMEM  KeyWord K_UP = {   5,82,"","UP" ,0,NULL};
const PROGMEM  KeyWord K_DELETE = {   5,76,"","DELETE" ,0,NULL};
const PROGMEM  KeyWord K_END = {   5,77,"","END" ,0,NULL};
const PROGMEM  KeyWord K_HOME = {  5,74,"","HOME" ,0,NULL};
const PROGMEM  KeyWord K_PAGE_UP = {   5,75,"","PAGEUP" ,0,NULL};
const PROGMEM  KeyWord K_PAGE_DOWN = {   5,78,"","PAGEDOWN" ,0,NULL};
const PROGMEM  KeyWord K_NUMLOCK = {   5,83,"","NUMLOCK" ,0,NULL};

// Numeric
const PROGMEM  KeyWord K_N_1 = {   5,89,"","1" ,0,NULL};
const PROGMEM  KeyWord K_N_2 = {   5,90,"","2" ,0,NULL};
const PROGMEM  KeyWord K_N_3 = {   5,91,"","3" ,0,NULL};
const PROGMEM  KeyWord K_N_4 = {   5,92,"","4" ,0,NULL};
const PROGMEM  KeyWord K_N_5 = {   5,93,"","5" ,0,NULL};
const PROGMEM  KeyWord K_N_6 = {   5,94,"","6" ,0,NULL};
const PROGMEM  KeyWord K_N_7 = {   5,95,"","7" ,0,NULL};
const PROGMEM  KeyWord K_N_8 = {   5,96,"","8" ,0,NULL};
const PROGMEM  KeyWord K_N_9 = {   5,97,"","9" ,0,NULL};
const PROGMEM  KeyWord K_N_0 = {   5,98,"","0" ,0,NULL};
const PROGMEM  KeyWord K_N_00 = {  2,0,"","00" ,0,NULL};

// Null Key

const PROGMEM  KeyWord K_A___ = {  2,0    ,"","",0,NULL};

// Ascii : A

const PROGMEM  KeyWord K_A_1 = {  3,0    ,"1","☻",0,NULL};
const PROGMEM  KeyWord K_A_2 = {  3,0    ,"2","♥",0,NULL};
const PROGMEM  KeyWord K_A_3 = {  3,0    ,"3","-",0,NULL};
const PROGMEM  KeyWord K_A_4 = {  3,0    ,"4","8",0,NULL};
const PROGMEM  KeyWord K_A_5 = {  3,0    ,"5","♠",0,NULL};
const PROGMEM  KeyWord K_A_6 = {  3,0    ,"6","•",0,NULL};
const PROGMEM  KeyWord K_A_7 = {  3,0    ,"7","Y",0,NULL};
const PROGMEM  KeyWord K_A_8 = {  3,0    ,"8","○",0,NULL};
const PROGMEM  KeyWord K_A_9 = {  3,0    ,"9","◙",0,NULL};
const PROGMEM  KeyWord K_A_A = {  3,0    ,"10","♂",0,NULL};
const PROGMEM  KeyWord K_A_B = {  3,0    ,"11","♀",0,NULL};
const PROGMEM  KeyWord K_A_C = {  3,0    ,"12","♪",0,NULL};
const PROGMEM  KeyWord K_A_D = {  3,0    ,"13","♫",0,NULL};
const PROGMEM  KeyWord K_A_E = {  3,0    ,"14","☼",0,NULL};
const PROGMEM  KeyWord K_A_F = {  3,0    ,"15","►",0,NULL};
const PROGMEM  KeyWord K_A_10 = {  3,0    ,"16","◄",0,NULL};
const PROGMEM  KeyWord K_A_11 = {  3,0    ,"17","‼",0,NULL};
const PROGMEM  KeyWord K_A_12 = {  3,0    ,"18","╡",0,NULL};
const PROGMEM  KeyWord K_A_13 = {  3,0    ,"19","‼",0,NULL};
const PROGMEM  KeyWord K_A_14 = {  3,0    ,"20","¶",0,NULL};
const PROGMEM  KeyWord K_A_15 = {  3,0    ,"21","§",0,NULL};
const PROGMEM  KeyWord K_A_16 = {  3,0    ,"22","▬",0,NULL};
const PROGMEM  KeyWord K_A_17 = {  3,0    ,"23","↨",0,NULL};
const PROGMEM  KeyWord K_A_18 = {  3,0    ,"24","↑",0,NULL};
const PROGMEM  KeyWord K_A_19 = {  3,0    ,"25","↓",0,NULL};
const PROGMEM  KeyWord K_A_1A = {  3,0    ,"26","→",0,NULL};
const PROGMEM  KeyWord K_A_1B = {  3,0    ,"27","►",0,NULL};
const PROGMEM  KeyWord K_A_1C = {  3,0    ,"28","∟",0,NULL};
const PROGMEM  KeyWord K_A_1D = {  3,0    ,"29","↔",0,NULL};
const PROGMEM  KeyWord K_A_1E = {  3,0    ,"30","▲",0,NULL};
const PROGMEM  KeyWord K_A_1F = {  3,0    ,"31","▼",0,NULL};
const PROGMEM  KeyWord K_A_20 = {  1,KEY_SPACE    ,"","",0,NULL};
const PROGMEM  KeyWord K_A_21 = {  1,KEY_SLASH    ,"","!",0,NULL};
const PROGMEM  KeyWord K_A_22 = {  1,KEY_3     ,"","\"",0,NULL};
// debut util
const PROGMEM  KeyWord K_A_23 = {  1,KEY_3 + ALTGR_MASK   ,"","#",0,NULL};
const PROGMEM  KeyWord K_A_24 = {  1,KEY_RIGHT_BRACE    ,"","$",0,NULL};
const PROGMEM  KeyWord K_A_25 = {  1,KEY_QUOTE + SHIFT_MASK   ,"","%",0,NULL};
const PROGMEM  KeyWord K_A_26 = {  1,KEY_1     ,"","&",0,NULL};
const PROGMEM  KeyWord K_A_27 = {  1,KEY_4     ,"","'",0,NULL};
const PROGMEM  KeyWord K_A_28 = {  1,KEY_5     ,"","(",0,NULL};
const PROGMEM  KeyWord K_A_29 = {  1,KEY_MINUS    ,"",")",0,NULL};
const PROGMEM  KeyWord K_A_2A = {  1,KEY_BACKSLASH    ,"","*",0,NULL};
const PROGMEM  KeyWord K_A_2B = {  1,KEY_EQUAL + SHIFT_MASK   ,"","+",0,NULL};
const PROGMEM  KeyWord K_A_2C = {  1,KEY_M     ,"",",",0,NULL};
const PROGMEM  KeyWord K_A_2D = {  1,KEY_6     ,"","-",0,NULL};
const PROGMEM  KeyWord K_A_2E = {  1,KEY_COMMA + SHIFT_MASK   ,"",".",0,NULL};
const PROGMEM  KeyWord K_A_2F = {  1,KEY_PERIOD + SHIFT_MASK   ,"","/",0,NULL};
const PROGMEM  KeyWord K_A_30 = {  1,KEY_0 + SHIFT_MASK   ,"","0",0,NULL};
const PROGMEM  KeyWord K_A_31 = {  1,KEY_1 + SHIFT_MASK   ,"","1",0,NULL};
const PROGMEM  KeyWord K_A_32 = {  1,KEY_2 + SHIFT_MASK   ,"","2",0,NULL};
const PROGMEM  KeyWord K_A_33 = {  1,KEY_3 + SHIFT_MASK   ,"","3",0,NULL};
const PROGMEM  KeyWord K_A_34 = {  1,KEY_4 + SHIFT_MASK   ,"","4",0,NULL};
const PROGMEM  KeyWord K_A_35 = {  1,KEY_5 + SHIFT_MASK   ,"","5",0,NULL};
const PROGMEM  KeyWord K_A_36 = {  1,KEY_6 + SHIFT_MASK   ,"","6",0,NULL};
const PROGMEM  KeyWord K_A_37 = {  1,KEY_7 + SHIFT_MASK   ,"","7",0,NULL};
const PROGMEM  KeyWord K_A_38 = {  1,KEY_8 + SHIFT_MASK   ,"","8",0,NULL};
const PROGMEM  KeyWord K_A_39 = {  1,KEY_9 + SHIFT_MASK   ,"","9",0,NULL};
const PROGMEM  KeyWord K_A_3A = {  1,KEY_PERIOD    ,"",":",0,NULL};
const PROGMEM  KeyWord K_A_3B = {  1,KEY_COMMA    ,"",";",0,NULL};
const PROGMEM  KeyWord K_A_3C = {  1,KEY_NON_US_100    ,"","<",0,NULL};
const PROGMEM  KeyWord K_A_3D = {  1,KEY_EQUAL    ,"","=",0,NULL};
const PROGMEM  KeyWord K_A_3E = {  1,KEY_NON_US_100 + SHIFT_MASK  ,"",">",0,NULL};
const PROGMEM  KeyWord K_A_3F = {  1,KEY_M + SHIFT_MASK   ,"","?",0,NULL};
const PROGMEM  KeyWord K_A_40 = {  1,KEY_0 + ALTGR_MASK   ,"","@",0,NULL};
const PROGMEM  KeyWord K_A_41 = {  1,KEY_Q + SHIFT_MASK   ,"","A",0,NULL};
const PROGMEM  KeyWord K_A_42 = {  1,KEY_B + SHIFT_MASK   ,"","B",0,NULL};
const PROGMEM  KeyWord K_A_43 = {  1,KEY_C + SHIFT_MASK   ,"","C",0,NULL};
const PROGMEM  KeyWord K_A_44 = {  1,KEY_D + SHIFT_MASK   ,"","D",0,NULL};
const PROGMEM  KeyWord K_A_45 = {  1,KEY_E + SHIFT_MASK   ,"","E",0,NULL};
const PROGMEM  KeyWord K_A_46 = {  1,KEY_F + SHIFT_MASK   ,"","F",0,NULL};
const PROGMEM  KeyWord K_A_47 = {  1,KEY_G + SHIFT_MASK   ,"","G",0,NULL};
const PROGMEM  KeyWord K_A_48 = {  1,KEY_H + SHIFT_MASK   ,"","H",0,NULL};
const PROGMEM  KeyWord K_A_49 = {  1,KEY_I + SHIFT_MASK   ,"","I",0,NULL};
const PROGMEM  KeyWord K_A_4A = {  1,KEY_J + SHIFT_MASK   ,"","J",0,NULL};
const PROGMEM  KeyWord K_A_4B = {  1,KEY_K + SHIFT_MASK   ,"","K",0,NULL};
const PROGMEM  KeyWord K_A_4C = {  1,KEY_L + SHIFT_MASK   ,"","L",0,NULL};
const PROGMEM  KeyWord K_A_4D = {  1,KEY_SEMICOLON + SHIFT_MASK  ,"","M",0,NULL};
const PROGMEM  KeyWord K_A_4E = {  1,KEY_N + SHIFT_MASK   ,"","N",0,NULL};
const PROGMEM  KeyWord K_A_4F = {  1,KEY_O + SHIFT_MASK   ,"","O",0,NULL};
const PROGMEM  KeyWord K_A_50 = {  1,KEY_P + SHIFT_MASK   ,"","P",0,NULL};
const PROGMEM  KeyWord K_A_51 = {  1,KEY_A + SHIFT_MASK   ,"","Q",0,NULL};
const PROGMEM  KeyWord K_A_52 = {  1,KEY_R + SHIFT_MASK   ,"","R",0,NULL};
const PROGMEM  KeyWord K_A_53 = {  1,KEY_S + SHIFT_MASK   ,"","S",0,NULL};
const PROGMEM  KeyWord K_A_54 = {  1,KEY_T + SHIFT_MASK   ,"","T",0,NULL};
const PROGMEM  KeyWord K_A_55 = {  1,KEY_U + SHIFT_MASK   ,"","U",0,NULL};
const PROGMEM  KeyWord K_A_56 = {  1,KEY_V + SHIFT_MASK   ,"","V",0,NULL};
const PROGMEM  KeyWord K_A_57 = {  1,KEY_Z + SHIFT_MASK   ,"","W",0,NULL};
const PROGMEM  KeyWord K_A_58 = {  1,KEY_X + SHIFT_MASK   ,"","X",0,NULL};
const PROGMEM  KeyWord K_A_59 = {  1,KEY_Y + SHIFT_MASK   ,"","Y",0,NULL};
const PROGMEM  KeyWord K_A_5A = {  1,KEY_W + SHIFT_MASK   ,"","Z",0,NULL};
const PROGMEM  KeyWord K_A_5B = {  1,KEY_5 + ALTGR_MASK   ,"","[",0,NULL};
const PROGMEM  KeyWord K_A_5C = {  1,KEY_8 + ALTGR_MASK   ,"","\\",0,NULL};
const PROGMEM  KeyWord K_A_5D = {  1,KEY_MINUS + ALTGR_MASK   ,"","]",0,NULL};
const PROGMEM  KeyWord K_A_5E = {  1,KEY_9 + ALTGR_MASK   ,"","^",0,NULL};
const PROGMEM  KeyWord K_A_5F = {  1,KEY_8     ,"","_",0,NULL};
const PROGMEM  KeyWord K_A_60 = {  1,GRAVE_ACCENT_BITS + KEY_SPACE  ,"","`",0,NULL};
const PROGMEM  KeyWord K_A_61 = {  1,KEY_Q     ,"","a",0,NULL};
const PROGMEM  KeyWord K_A_62 = {  1,KEY_B     ,"","b",0,NULL};
const PROGMEM  KeyWord K_A_63 = {  1,KEY_C     ,"","c",0,NULL};
const PROGMEM  KeyWord K_A_64 = {  1,KEY_D     ,""," d",0,NULL};
const PROGMEM  KeyWord K_A_65 = {  1,KEY_E     ,""," e",0,NULL};
const PROGMEM  KeyWord K_A_66 = {  1,KEY_F     ,""," f",0,NULL};
const PROGMEM  KeyWord K_A_67 = {  1,KEY_G     ,""," g",0,NULL};
const PROGMEM  KeyWord K_A_68 = {  1,KEY_H     ,""," h",0,NULL};
const PROGMEM  KeyWord K_A_69 = {  1,KEY_I     ,""," i",0,NULL};
const PROGMEM  KeyWord K_A_6A = {  1,KEY_J     ,""," j",0,NULL};
const PROGMEM  KeyWord K_A_6B = {  1,KEY_K     ,""," k",0,NULL};
const PROGMEM  KeyWord K_A_6C = {  1,KEY_L     ,""," l",0,NULL};
const PROGMEM  KeyWord K_A_6D = {  1,KEY_SEMICOLON    ,""," m",0,NULL};
const PROGMEM  KeyWord K_A_6E = {  1,KEY_N     ,""," n",0,NULL};
const PROGMEM  KeyWord K_A_6F = {  1,KEY_O     ,""," o",0,NULL};
const PROGMEM  KeyWord K_A_70 = {  1,KEY_P     ,""," p",0,NULL};
const PROGMEM  KeyWord K_A_71 = {  1,KEY_A     ,""," q",0,NULL};
const PROGMEM  KeyWord K_A_72 = {  1,KEY_R     ,""," r",0,NULL};
const PROGMEM  KeyWord K_A_73 = {  1,KEY_S     ,""," s",0,NULL};
const PROGMEM  KeyWord K_A_74 = {  1,KEY_T     ,""," t",0,NULL};
const PROGMEM  KeyWord K_A_75 = {  1,KEY_U     ,""," u",0,NULL};
const PROGMEM  KeyWord K_A_76 = { 1,KEY_V     ,""," v",0,NULL};
const PROGMEM  KeyWord K_A_77 = {  1,KEY_Z     ,""," w",0,NULL};
const PROGMEM  KeyWord K_A_78 = {  1,KEY_X     ,""," x",0,NULL};
const PROGMEM  KeyWord K_A_79 = {  1,KEY_Y     ,""," y",0,NULL};
const PROGMEM  KeyWord K_A_7A = {  1,KEY_W     ,""," z",0,NULL};
const PROGMEM  KeyWord K_A_7B = {  1,KEY_4 + ALTGR_MASK   ,""," {",0,NULL};
const PROGMEM  KeyWord K_A_7C = {  1,KEY_6 + ALTGR_MASK   ,""," |",0,NULL};
const PROGMEM  KeyWord K_A_7D = {  1,KEY_EQUAL + ALTGR_MASK   ,"","}",0,NULL};
const PROGMEM  KeyWord K_A_7E = {  1,TILDE_BITS + KEY_SPACE   ,"","~",0,NULL};
//TODO remove
const PROGMEM  KeyWord K_A_7F = {  1,KEY_BACKSPACE    ,"","",0,NULL};
//TODO remove
const PROGMEM  KeyWord K_A_A0 = {  1,KEY_SPACE    ,"","",0,NULL};
const PROGMEM  KeyWord K_A_A1 = {  3,0,"0161","¡",0,NULL};
const PROGMEM  KeyWord K_A_A2 = {  3,0,"0162","¢",0,NULL};
const PROGMEM  KeyWord K_A_A3 = {  1,KEY_RIGHT_BRACE + SHIFT_MASK  ,"","£",0,NULL};
const PROGMEM  KeyWord K_A_A4 = {  1,KEY_RIGHT_BRACE + ALTGR_MASK  ,"","¤",0,NULL};
const PROGMEM  KeyWord K_A_A5 = {  3,0,"0165","¥",0,NULL};
const PROGMEM  KeyWord K_A_A6 = {  3,0,"0166","¦",0,NULL};
const PROGMEM  KeyWord K_A_A7 = {  1,KEY_SLASH + SHIFT_MASK   ,"","§",0,NULL};
const PROGMEM  KeyWord K_A_A8 = {  1,DIAERESIS_BITS + KEY_SPACE  ,"","¨",0,NULL};
const PROGMEM  KeyWord K_A_A9 = {  3,0,"0169","©",0,NULL};
const PROGMEM  KeyWord K_A_AA = {  3,0,"0170","ª",0,NULL};
const PROGMEM  KeyWord K_A_AB = {  3,0,"0171","«",0,NULL};
const PROGMEM  KeyWord K_A_AC = {  3,0,"0172","¬",0,NULL};
const PROGMEM  KeyWord K_A_AD = {  3,0,"0173","­",0,NULL};
const PROGMEM  KeyWord K_A_AE = {  3,0,"0174","®",0,NULL};
const PROGMEM  KeyWord K_A_AF = {  3,0,"0175","¯",0,NULL};
const PROGMEM  KeyWord K_A_B0 = {  1,KEY_MINUS + SHIFT_MASK   ,"","°",0,NULL};
const PROGMEM  KeyWord K_A_B1 = {  3,0,"0177","±",0,NULL};
const PROGMEM  KeyWord K_A_B2 = {  1,KEY_TILDE    ,"","²",0,NULL};
const PROGMEM  KeyWord K_A_B3 = {  3,0,"0179","³",0,NULL};
const PROGMEM  KeyWord K_A_B4 = {  3,0,"0180","´",0,NULL};
const PROGMEM  KeyWord K_A_B5 = {  1,KEY_BACKSLASH + SHIFT_MASK  ,"","µ",0,NULL};
const PROGMEM  KeyWord K_A_B6 = {  3,0,"0182","¶",0,NULL};
const PROGMEM  KeyWord K_A_B7 = {  3,0,"0183","·",0,NULL};
const PROGMEM  KeyWord K_A_B8 = {  3,0,"0184","¸",0,NULL};
const PROGMEM  KeyWord K_A_B9 = {  3,0,"0185","¹",0,NULL};
const PROGMEM  KeyWord K_A_BA = {  3,0,"0186","º",0,NULL};
const PROGMEM  KeyWord K_A_BB = {  3,0,"0187","»",0,NULL};
const PROGMEM  KeyWord K_A_BC = {  3,0,"0188","¼",0,NULL};
const PROGMEM  KeyWord K_A_BD = {  3,0,"0189","½",0,NULL};
const PROGMEM  KeyWord K_A_BE = {  3,0,"0190","¾",0,NULL};
const PROGMEM  KeyWord K_A_BF = {  3,0,"0191","¿",0,NULL};
const PROGMEM  KeyWord K_A_C0 = {  1,GRAVE_ACCENT_BITS + KEY_Q + SHIFT_MASK ,"","À",0,NULL};
const PROGMEM  KeyWord K_A_C1 = {  3,0,"0193","Á",0,NULL};
const PROGMEM  KeyWord K_A_C2 = {  1,CIRCUMFLEX_BITS + KEY_Q + SHIFT_MASK ,"","Â",0,NULL};
const PROGMEM  KeyWord K_A_C3 = {  1,TILDE_BITS + KEY_Q + SHIFT_MASK  ,"","Ã",0,NULL};
const PROGMEM  KeyWord K_A_C4 = {  1,DIAERESIS_BITS + KEY_Q + SHIFT_MASK ,"","Ä",0,NULL};
const PROGMEM  KeyWord K_A_C5 = {  3,0,"0197","Å",0,NULL};
const PROGMEM  KeyWord K_A_C6 = {  3,0,"0198","Æ",0,NULL};
const PROGMEM  KeyWord K_A_C7 = {  3,0,"0199","Ç",0,NULL};
const PROGMEM  KeyWord K_A_C8 = {  1,GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK ,"","È",0,NULL};
const PROGMEM  KeyWord K_A_C9 = {  3,0,"0201","É",0,NULL};
const PROGMEM  KeyWord K_A_CA = {  1,CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK ,"","Ê",0,NULL};
const PROGMEM  KeyWord K_A_CB = {  1,DIAERESIS_BITS + KEY_E + SHIFT_MASK ,"","Ë",0,NULL};
const PROGMEM  KeyWord K_A_CC = {  1,GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK ,"","Ì",0,NULL};
const PROGMEM  KeyWord K_A_CD = {  3,0,"0205","Í",0,NULL};
const PROGMEM  KeyWord K_A_CE = {  1,CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK ,"","Î",0,NULL};
const PROGMEM  KeyWord K_A_CF = {  1,DIAERESIS_BITS + KEY_I + SHIFT_MASK ,"","Ï",0,NULL};
const PROGMEM  KeyWord K_A_D0 = {  3,0,"0208","Ð",0,NULL};
const PROGMEM  KeyWord K_A_D1 = {  1,TILDE_BITS + KEY_N + SHIFT_MASK  ,"","Ñ",0,NULL};
const PROGMEM  KeyWord K_A_D2 = {  1,GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK ,"","Ò",0,NULL};
const PROGMEM  KeyWord K_A_D3 = {  3,0,"0211","Ó",0,NULL};
const PROGMEM  KeyWord K_A_D4 = {  1,CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK ,"","Ô",0,NULL};
const PROGMEM  KeyWord K_A_D5 = {  1,TILDE_BITS + KEY_O + SHIFT_MASK  ,"","Õ",0,NULL};
const PROGMEM  KeyWord K_A_D6 = {  1,DIAERESIS_BITS + KEY_O + SHIFT_MASK ,"","Ö",0,NULL};
const PROGMEM  KeyWord K_A_D7 = {  3,0,"0215","×",0,NULL};
const PROGMEM  KeyWord K_A_D8 = {  3,0,"0216","Ø",0,NULL};
const PROGMEM  KeyWord K_A_D9 = {  1,GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK ,"","Ù",0,NULL};
const PROGMEM  KeyWord K_A_DA = {  3,0,"0218","Ú",0,NULL};
const PROGMEM  KeyWord K_A_DB = {  1,CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK ,"","Û",0,NULL};
const PROGMEM  KeyWord K_A_DC = {  1,DIAERESIS_BITS + KEY_U   ,"","ü",0,NULL};
const PROGMEM  KeyWord K_A_DD = {  3,0,"0221","Ý",0,NULL};
const PROGMEM  KeyWord K_A_DE = {  3,0,"0222","Þ",0,NULL};
const PROGMEM  KeyWord K_A_DF = {  3,0,"0223","ß",0,NULL};
const PROGMEM  KeyWord K_A_E0 = {  1,KEY_0     ,"","à",0,NULL};
const PROGMEM  KeyWord K_A_E1 = {  3,0,"0225","á",0,NULL};
const PROGMEM  KeyWord K_A_E2 = {  1,CIRCUMFLEX_BITS + KEY_Q   ,"","â",0,NULL};
const PROGMEM  KeyWord K_A_E3 = {  1,TILDE_BITS + KEY_Q   ,"","ã",0,NULL};
const PROGMEM  KeyWord K_A_E4 = {  1,DIAERESIS_BITS + KEY_Q   ,"","ä",0,NULL};
const PROGMEM  KeyWord K_A_E5 = {  3,0,"0229","å",0,NULL};
const PROGMEM  KeyWord K_A_E6 = {  3,0,"0230","æ",0,NULL};
const PROGMEM  KeyWord K_A_E7 = {  1,KEY_9     ,"","ç",0,NULL};
const PROGMEM  KeyWord K_A_E8 = {  1,KEY_7     ,"","è",0,NULL};
const PROGMEM  KeyWord K_A_E9 = {  1,KEY_2     ,"","é",0,NULL};
//const PROGMEM  KeyWord K_A_EA = {1,CIRCUMFLEX_BITS + KEY_E   ,"","ª",0,NULL};
const PROGMEM  KeyWord K_A_EA = {  2,0  ,"","ê",0,NULL};
const PROGMEM  KeyWord K_A_EB = {  1,DIAERESIS_BITS + KEY_E   ,"","ë",0,NULL};
const PROGMEM  KeyWord K_A_EC = {  1,GRAVE_ACCENT_BITS + KEY_I  ,"","ì",0,NULL};
const PROGMEM  KeyWord K_A_ED = {  3,0,"0237","í",0,NULL};
const PROGMEM  KeyWord K_A_EE = {  1,CIRCUMFLEX_BITS + KEY_I   ,"","î",0,NULL};
const PROGMEM  KeyWord K_A_EF = {  1,DIAERESIS_BITS + KEY_I   ,"","ï",0,NULL};
const PROGMEM  KeyWord K_A_F0 = {  3,0,"0240","ð",0,NULL};
const PROGMEM  KeyWord K_A_F1 = {  1,TILDE_BITS + KEY_N   ,"","ñ",0,NULL};
const PROGMEM  KeyWord K_A_F2 = {  1,GRAVE_ACCENT_BITS + KEY_O  ,"","ò",0,NULL};
const PROGMEM  KeyWord K_A_F3 = {  3,0,"0243","ó",0,NULL};
const PROGMEM  KeyWord K_A_F4 = {  1,CIRCUMFLEX_BITS + KEY_O   ,"","ô",0,NULL};
const PROGMEM  KeyWord K_A_F5 = {  1,TILDE_BITS + KEY_O   ,"","õ",0,NULL};
const PROGMEM  KeyWord K_A_F6 = {  1,DIAERESIS_BITS + KEY_O   ,"","ö",0,NULL};
const PROGMEM  KeyWord K_A_F7 = {  3,0,"0247","÷",0,NULL};
const PROGMEM  KeyWord K_A_F8 = {  3,0,"0248","ø",0,NULL};
const PROGMEM  KeyWord K_A_F9 = {  1,KEY_COMMA    ,"",";",0,NULL};
const PROGMEM  KeyWord K_A_FA = {  3,0,"0250","ú",0,NULL};
const PROGMEM  KeyWord K_A_FB = {  1,CIRCUMFLEX_BITS + KEY_U   ,"","û",0,NULL};
const PROGMEM  KeyWord K_A_FC = {  1,DIAERESIS_BITS + KEY_U   ,"","ü",0,NULL};
const PROGMEM  KeyWord K_A_FD = {  3,0,"0253","ý",0,NULL};
const PROGMEM  KeyWord K_A_FE = {  3,0,"0254","þ",0,NULL};
const PROGMEM  KeyWord K_A_FF = {  1,DIAERESIS_BITS + KEY_Y   ,"","ÿ",0,NULL};
const PROGMEM  KeyWord K_A_20AC = {  1,KEY_E + ALTGR_MASK   ,"","€",0,NULL};

// Media Keys : M

const PROGMEM  KeyWord K_M_PREV = {  1,KEY_MEDIA_PREV_TRACK,"","Prev",0,NULL};
const PROGMEM  KeyWord K_M_PLAY = {  1,KEY_MEDIA_PLAY_PAUSE,"","Play",0,NULL};
const PROGMEM  KeyWord K_M_NEXT = {  1,KEY_MEDIA_NEXT_TRACK,"","Next",0,NULL};
const PROGMEM  KeyWord K_M_DEC = {  1,KEY_MEDIA_VOLUME_DEC,"","Dec",0,NULL};
const PROGMEM  KeyWord K_M_INC = {  1,KEY_MEDIA_VOLUME_INC,"","Inc",0,NULL};
const PROGMEM  KeyWord K_M_EJECT = {  1,KEY_MEDIA_EJECT,"","Eject",0,NULL};




// Ascii drawing : D

const PROGMEM  KeyWord K_D_01 = {  0,0  ,"","",0,NULL};
const PROGMEM  KeyWord K_D_02 = {  3,0  ,"176","░",0,NULL};
const PROGMEM  KeyWord K_D_03 = {  3,0  ,"177","▒",0,NULL};
const PROGMEM  KeyWord K_D_04 = {  3,0  ,"178","▓",0,NULL};
const PROGMEM  KeyWord K_D_05 = {  3,0  ,"179","│",0,NULL};
const PROGMEM  KeyWord K_D_06 = {  3,0  ,"180","┤",0,NULL};
const PROGMEM  KeyWord K_D_07 = {  3,0  ,"181","╡",0,NULL};
const PROGMEM  KeyWord K_D_08 = {  3,0  ,"182","╢",0,NULL};
const PROGMEM  KeyWord K_D_09 = {  3,0  ,"183","╖",0,NULL};
const PROGMEM  KeyWord K_D_10 = {  3,0  ,"184","╕",0,NULL};
const PROGMEM  KeyWord K_D_11 = {  3,0  ,"185","╣",0,NULL};
const PROGMEM  KeyWord K_D_12 = {  3,0  ,"186","║",0,NULL};
const PROGMEM  KeyWord K_D_13 = {  3,0  ,"187","╗",0,NULL};
const PROGMEM  KeyWord K_D_14 = {  3,0  ,"188","╝",0,NULL};
const PROGMEM  KeyWord K_D_15 = {  3,0  ,"189","╜",0,NULL};
const PROGMEM  KeyWord K_D_16 = {  3,0  ,"190","╛",0,NULL};
const PROGMEM  KeyWord K_D_17 = {  3,0  ,"191","┐",0,NULL};
const PROGMEM  KeyWord K_D_18 = {  3,0  ,"192","└",0,NULL};
const PROGMEM  KeyWord K_D_19 = {  3,0  ,"193","┴",0,NULL};
const PROGMEM  KeyWord K_D_20 = {  3,0  ,"194","┬",0,NULL};
const PROGMEM  KeyWord K_D_21 = {  3,0  ,"195","├",0,NULL};
const PROGMEM  KeyWord K_D_22 = {  3,0  ,"196","─",0,NULL};
const PROGMEM  KeyWord K_D_23 = {  3,0  ,"197","┼",0,NULL};
const PROGMEM  KeyWord K_D_24 = {  3,0  ,"198","╞",0,NULL};
const PROGMEM  KeyWord K_D_25 = {  3,0  ,"199","╟",0,NULL};
const PROGMEM  KeyWord K_D_26 = {  3,0  ,"200","╚",0,NULL};
const PROGMEM  KeyWord K_D_27 = {  3,0  ,"201","╔",0,NULL};
const PROGMEM  KeyWord K_D_28 = {  3,0  ,"202","╩",0,NULL};
const PROGMEM  KeyWord K_D_29 = {  3,0  ,"203","╦",0,NULL};
const PROGMEM  KeyWord K_D_30 = {  3,0  ,"204","╠",0,NULL};
const PROGMEM  KeyWord K_D_31 = {  3,0  ,"205","═",0,NULL};
const PROGMEM  KeyWord K_D_32 = {  3,0  ,"206","╬",0,NULL};
const PROGMEM  KeyWord K_D_33 = {  3,0  ,"207","╧",0,NULL};
const PROGMEM  KeyWord K_D_34 = {  3,0  ,"208","╨",0,NULL};
const PROGMEM  KeyWord K_D_35 = {  3,0  ,"209","╤",0,NULL};
const PROGMEM  KeyWord K_D_36 = {  3,0  ,"210","╥",0,NULL};
const PROGMEM  KeyWord K_D_37 = {  3,0  ,"211","╙",0,NULL};
const PROGMEM  KeyWord K_D_38 = {  3,0  ,"212","╘",0,NULL};
const PROGMEM  KeyWord K_D_39 = {  3,0  ,"213","╒",0,NULL};
const PROGMEM  KeyWord K_D_40 = {  3,0  ,"214","╓",0,NULL};
const PROGMEM  KeyWord K_D_41 = {  3,0  ,"215","╫",0,NULL};
const PROGMEM  KeyWord K_D_42 = {  3,0  ,"216","╪",0,NULL};
const PROGMEM  KeyWord K_D_43 = {  3,0  ,"217","┘",0,NULL};
const PROGMEM  KeyWord K_D_44 = {  3,0  ,"218","┌",0,NULL};
const PROGMEM  KeyWord K_D_45 = {  3,0  ,"219","█",0,NULL};
const PROGMEM  KeyWord K_D_46 = {  3,0  ,"220","▄",0,NULL};
const PROGMEM  KeyWord K_D_47 = {  3,0  ,"221","▌",0,NULL};
const PROGMEM  KeyWord K_D_48 = {  3,0  ,"222","▐",0,NULL};
const PROGMEM  KeyWord K_D_49 = {  3,0  ,"223","▀",0,NULL};

const PROGMEM  KeyWord K_B_32 = {  3,0  ,"32","",0,NULL};
const PROGMEM  KeyWord K_B_33 = {  3,0  ,"33","",0,NULL};
const PROGMEM  KeyWord K_B_34 = {  3,0  ,"34","",0,NULL};
const PROGMEM  KeyWord K_B_35 = {  3,0  ,"35","",0,NULL};

const PROGMEM  KeyWord K_B_254 = {  3,0  ,"254","",0,NULL};
const PROGMEM  KeyWord K_B_0129 = {  3,0  ,"0129","",0,NULL};
const PROGMEM  KeyWord K_B_127 = {  3,0  ,"127","",0,NULL};
const PROGMEM  KeyWord K_B_0153 = {  3,0  ,"0153","",0,NULL};

// Strings

const PROGMEM  KeyWord K_S_001 = {  2,0  ,"","SELECT ",0,NULL};
const PROGMEM  KeyWord K_S_002 = {  2,0  ,"","* ",0,NULL};
const PROGMEM  KeyWord K_S_003 = {  2,0  ,"","FROM ",0,NULL};
const PROGMEM  KeyWord K_S_004 = {  2,0  ,"","WHERE ",0,NULL};
const PROGMEM  KeyWord K_S_005 = {  2,0  ,"","GROUP BY ",0,NULL};
const PROGMEM  KeyWord K_S_006 = {  2,0  ,"","ORDER BY DESC ",0,NULL};
const PROGMEM  KeyWord K_S_007 = {  2,0  ,"","LEFT JOIN ON ",0,NULL};
const PROGMEM  KeyWord K_S_008 = {  2,0  ,"","UPDATE ",0,NULL};
const PROGMEM  KeyWord K_S_009 = {  2,0  ,"","SET = , ",0,NULL};
const PROGMEM  KeyWord K_S_010 = {  2,0  ,"","INSERT ",0,NULL};
const PROGMEM  KeyWord K_S_011 = {  2,0  ,"","Alexandre ",0,NULL};
const PROGMEM  KeyWord K_S_012 = {  2,0  ,"","Aurélien ",0,NULL};
const PROGMEM  KeyWord K_S_013 = {  2,0  ,"","Arsinoé ",0,NULL};
const PROGMEM  KeyWord K_S_014 = {  2,0  ,"","Aymeric ",0,NULL};
const PROGMEM  KeyWord K_S_015 = {  2,0  ,"","Arthur ",0,NULL};

// limiters

const PROGMEM  KeyWord K_L_1 = {  4,0,"","[]",0,{     &K_A_5B,&K_A_5D,&K_LEFT  }};
const PROGMEM  KeyWord K_L_2 = {  4,0,"","<>",0,{     &K_A_3C,&K_A_3E,&K_LEFT  }};
const PROGMEM  KeyWord K_L_3 = {  4,0,"","()",0,{     &K_A_28,&K_A_29,&K_LEFT  }};
const PROGMEM  KeyWord K_L_4 = {  4,0,"","{}",0,{     &K_A_7B,&K_A_7D,&K_LEFT  }};
const PROGMEM  KeyWord K_L_5 = {  4,0,"","«»",0,{     &K_A_AB,&K_A_BB,&K_LEFT  }};
//const PROGMEM  KeyWord K_L_5 = {4,0,"","/"/"",{ &K_A_AB,&K_A_BB,&K_LEFT}};

// Program

const PROGMEM  KeyWord K_P_000 = {  6,0  ,"","" ,0,NULL} ;  
const PROGMEM  KeyWord K_P_001 = {  6,0  ,"","" ,1,NULL} ;  
const PROGMEM  KeyWord K_P_002 = {  6,0  ,"","" ,2,NULL} ;  
const PROGMEM  KeyWord K_P_003 = {  6,0  ,"","" ,3,NULL} ;  
const PROGMEM  KeyWord K_P_004 = {  6,0  ,"","" ,4,NULL} ;  
const PROGMEM  KeyWord K_P_005 = {  6,0  ,"","" ,5,NULL} ;  
const PROGMEM  KeyWord K_P_006 = {  6,0  ,"","" ,6,NULL} ;  
const PROGMEM  KeyWord K_P_007 = {  6,0  ,"","" ,7,NULL} ;  
const PROGMEM  KeyWord K_P_008 = {  6,0  ,"","" ,8,NULL} ;  
const PROGMEM  KeyWord K_P_009 = {  6,0  ,"","" ,9,NULL} ;  
const PROGMEM  KeyWord K_P_010 = {  6,0  ,"","" ,10,NULL} ;  
const PROGMEM  KeyWord K_P_011 = {  6,0  ,"","" ,11,NULL} ;  
const PROGMEM  KeyWord K_P_012 = {  6,0  ,"","" ,12,NULL} ;  
const PROGMEM  KeyWord K_P_013 = {  6,0  ,"","" ,13,NULL} ;  
const PROGMEM  KeyWord K_P_014 = {  6,0  ,"","" ,14,NULL} ;  
const PROGMEM  KeyWord K_P_015 = {  6,0  ,"","" ,15,NULL} ;  
const PROGMEM  KeyWord K_P_016 = {  6,0  ,"","" ,16,NULL} ;    
const PROGMEM  KeyWord K_P_017 = {  6,0  ,"","" ,17,NULL} ;  
const PROGMEM  KeyWord K_P_018 = {  6,0  ,"","" ,18,NULL} ;  
const PROGMEM  KeyWord K_P_019 = {  6,0  ,"","" ,19,NULL} ;  
const PROGMEM  KeyWord K_P_020 = {  6,0  ,"","" ,20,NULL} ;  
const PROGMEM  KeyWord K_P_021 = {  6,0  ,"","" ,21,NULL} ;  
const PROGMEM  KeyWord K_P_022 = {  6,0  ,"","" ,22,NULL} ;  

const int KEY_QS = KEY_Q + SHIFT_MASK ;
const int KEY_ES = KEY_E + SHIFT_MASK ;
const int KEY_IS = KEY_I + SHIFT_MASK ;
const int KEY_OS = KEY_O + SHIFT_MASK ;
const int KEY_US = KEY_U + SHIFT_MASK ;
const int KEY_CS = KEY_C + SHIFT_MASK ;

// accents tables

static const int nb_accent_a=5;
static const PROGMEM KeyWord* Keys_A[nb_accent_a] = {   &K_A_C2,&K_A_C4,&K_A_C0,&K_A_C3,&K_A_41};
static const PROGMEM KeyWord* Keys_a[nb_accent_a] = {   &K_A_E2,&K_A_E4,&K_A_E0,&K_A_E3,&K_A_61};
static const int nb_accent_e=5;
static const PROGMEM KeyWord* Keys_e[nb_accent_e] = {   &K_A_EB,&K_A_EA,&K_A_E9,&K_A_E8,&K_A_65};
static const PROGMEM KeyWord* Keys_E[nb_accent_e] = {   &K_A_CB,&K_A_CA,&K_A_C9,&K_A_C8,&K_A_45};
static const int nb_accent_i=5;
static const PROGMEM KeyWord* Keys_i[nb_accent_i] = {   &K_A_EE,&K_A_EF,&K_A_EC,&K_A_ED,&K_A_69};
static const PROGMEM KeyWord* Keys_I[nb_accent_i] = {   &K_A_CE,&K_A_CF,&K_A_CC,&K_A_CD,&K_A_49};
static const int nb_accent_o=5;
static const PROGMEM KeyWord* Keys_o[nb_accent_o] = {   &K_A_F4,&K_A_F6,&K_A_F2,&K_A_F5,&K_A_6F};
static const PROGMEM KeyWord* Keys_O[nb_accent_o] = {   &K_A_D4,&K_A_D6,&K_A_D2,&K_A_D5,&K_A_4F};
static const int nb_accent_u=5;
static const PROGMEM KeyWord* Keys_u[nb_accent_u] = {   &K_A_FB,&K_A_FC,&K_A_F9,&K_A_FA,&K_A_75};
static const PROGMEM KeyWord* Keys_U[nb_accent_u] = {   &K_A_DB,&K_A_DC,&K_A_D9,&K_A_DA,&K_A_55};
static const int nb_accent_c=2;
static const PROGMEM KeyWord* Keys_c[nb_accent_c] = {   &K_A_E7,&K_A_63};
static const PROGMEM KeyWord* Keys_C[nb_accent_c] = {   &K_A_C7,&K_A_43};

//===================================================
// RTP page Keys, right thumb panel
//===================================================


static const KeyWord* RTP_keys[] = {
  &K_P_012,
  &K_BACKSPACE,  &K_UP,&K_ESC, &K_P_012,
  &K_RIGHT, &K_DOWN, &K_LEFT, &K_HOME, 
  &K_ENTER, &K_PAGE_UP,  &K_DELETE, &K_END,
  &K_TAB, &K_PAGE_DOWN,  &K_INSERT,&K_P_012,
  &K_M_PREV, &K_M_PLAY, &K_M_NEXT ,&K_M_EJECT, 
  &K_M_INC, &K_M_DEC,&K_P_012, &K_NUMLOCK
};

//===================================================
// LTP page Keys, left thumb panel
//===================================================

static const KeyWord* LTP_keys[] = {
  &K_A___, 
  &K_P_001,&K_P_002,&K_P_007,&K_P_008,&K_P_003,&K_P_012,
  &K_P_004,&K_P_009,&K_P_005,&K_P_006,&K_P_010,&K_P_011,
  &K_P_016,&K_P_017,&K_P_019,&K_P_018,&K_P_020,&K_P_014,
  &K_P_021,&K_P_022,&K_A___,&K_A___,&K_A___,&K_A___
};

//===================================================
// IR page Keys, left thumb panel
//===================================================

static const KeyWord* IR_keys[] = {
  &K_A___, &K_P_020, &K_A___, &K_S_011, &K_S_012,        
  &K_S_013,&K_A___,   &K_S_014,&K_S_015, &K_A___,   
  &K_A___,   &K_A___, &K_A___,   &K_A___,   &K_A___, 
  &K_A___,   &K_A___,   &K_A___,   &K_A___,   &K_A___, 
  &K_A___,   &K_A___,   &K_A___,   &K_A___,   &K_A___,   
  &K_A___,   &K_UP,    &K_A___,      &K_LEFT, &K_A___,   
  &K_RIGHT,     &K_A___,   &K_DOWN,     &K_A___,   &K_A___,   
  &K_A___,   &K_A___,   &K_A___,   &K_A___,   &K_A___,   
  &K_A___,     &K_A___, &K_A___,   &K_A___,   &K_A___,   
  &K_A___,   &K_A___,   &K_A___,   &K_A___,     &K_A___  } ;

//===================================================
//Key pages
//===================================================

static const PROGMEM KeyWord* Keys_NORM[] = {
  &K_A___,&K_A_2D,&K_A_3F,&K_A_2E,&K_A_3A,   &K_A_3B,&K_A_2C,&K_A_21,&K_A___,&K_A___,
  &K_A_62,&K_A_E9,&K_A_70,&K_A_6F,&K_A_E8,   &K_A_7A,&K_A_76,&K_A_64,&K_A_6C,&K_A_6A,
  &K_A_61,&K_A_75,&K_A_69,&K_A_65,&K_A_27,   &K_A_63,&K_A_74,&K_A_73,&K_A_72,&K_A_6E,
  &K_A_E0,&K_A_79,&K_A_78,&K_A_6B,&K_A_77,   &K_A_6D,&K_A_71,&K_A_67,&K_A_68,&K_A_66,
  &K_BACKSPACE, &K_A_A0,    &K_ESC, &K_SPACE  };


//===================================================
static const PROGMEM KeyWord* Keys_MAJ[] = { 
  &K_A___,&K_A_2D,&K_A_3F,&K_A_2E,&K_A_3A,   &K_A_3B,&K_A_2C,&K_A_21,&K_A___,&K_A___,
  &K_A_42,&K_A_C9,&K_A_50,&K_A_4F,&K_A_C8,   &K_A_5A,&K_A_56,&K_A_44,&K_A_4C,&K_A_4A,
  &K_A_41,&K_A_55,&K_A_49,&K_A_45,&K_A_27,   &K_A_43,&K_A_54,&K_A_53,&K_A_52,&K_A_4E,
  &K_A_C0,&K_A_59,&K_A_58,&K_A_4B,&K_A_57,   &K_A_4D,&K_A_51,&K_A_47,&K_A_48,&K_A_46,
  &K_BACKSPACE, &K_A_A0,    &K_ESC, &K_SPACE  };


//=================================================== 
static const PROGMEM KeyWord* Keys_NUM[] = { 
  &K_A_BC,&K_A_BD,&K_A_BE,&K_A_AC,&K_A___,   &K_A___,&K_L_3,&K_A_B3,&K_A_B2, &K_A_B9,
  &K_A_2C,&K_A___,&K_A_D7,&K_A_B1,&K_A___,   &K_A_3D,&K_A_2B, &K_A_2A, &K_A_25, &K_A_2E,
  &K_N_1, &K_N_2, &K_N_3, &K_N_4, &K_N_5,    &K_N_6, &K_N_7, &K_N_8, &K_N_9, &K_N_0,
  &K_A___,&K_A___,&K_A_F7,&K_A_20AC, &K_A_7E,  &K_A_B0,&K_A_2D,&K_A_2F,&K_A_3C,&K_A_3E, 
  &K_BACKSPACE, &K_A_A0,    &K_ESC, &K_SPACE  };

//===================================================
static const PROGMEM KeyWord* Keys_SPE[] = {
  &K_A_AA, &K_A___, &K_A_A4, &K_A___,&K_A_A1,   &K_A___, &K_A___, &K_A___,&K_A___,&K_A___, 
  &K_A_5F, &K_A___,&K_A___,&K_A___, &K_A_B5,   &K_A_A6, &K_A_7C,&K_A___,&K_A_A7, &K_A_23, 
  &K_A_40, &K_A___,&K_A_E6,&K_A_26, &K_A___,   &K_L_2, &K_L_1,&K_L_3,&K_L_4, &K_L_5, 
  &K_A_A5, &K_A_A3,&K_A_24,&K_A_20AC, &K_A_A2,  &K_A_B6, &K_A_2D,&K_A_2F,&K_A_3C, &K_A_3E, 
  &K_BACKSPACE, &K_A_A0,    &K_ESC, &K_SPACE  };

//===================================================  
static const PROGMEM KeyWord* Keys_FN[] = { 
  &K_A___, &K_A___, &K_A___,  &K_A___, &K_A___,    &K_A___, &K_A___, &K_A___, &K_A___, &K_A___, 
  &K_A___, &K_A___, &K_A___,  &K_F11, &K_A___,     &K_A___, &K_F12, &K_A___, &K_A___, &K_A___, 
  &K_F1, &K_F2,&K_F3, &K_F4, &K_F5,                &K_F6, &K_F7, &K_F8, &K_F9, &K_F10,
  &K_A___, &K_A___, &K_A___,  &K_A___, &K_A___,    &K_A___, &K_A___, &K_A___, &K_A___, &K_A___, 
  &K_A___ ,&K_A___,  &K_A___ ,&K_A___ };


//===================================================
static const PROGMEM KeyWord* Keys_MOD0[] = {
  &K_D_22,&K_D_05,&K_D_36,&K_D_41,&K_D_34,   &K_D_33,&K_D_42,&K_D_35,&K_D_12,&K_D_31,
  &K_D_44,&K_D_20,&K_D_17,&K_D_40,&K_D_09,   &K_D_39,&K_D_10,&K_D_27,&K_D_29,&K_D_13,
  &K_D_21,&K_D_23,&K_D_06,&K_D_25,&K_D_08,   &K_D_24,&K_D_07,&K_D_30,&K_D_32,&K_D_11,
  &K_D_18,&K_D_19,&K_D_43,&K_D_37,&K_D_15,   &K_D_38,&K_D_16,&K_D_26,&K_D_28,&K_D_14,
  &K_SPACE  ,&K_D_03,&K_D_02 ,&K_D_04};

//===================================================
static const PROGMEM KeyWord* Keys_MOD1[] = { 
  &K_A___, &K_S_010, &K_A___, &K_A___,&K_A___,    &K_S_009, &K_A_63, &K_A_6D,&K_A_6B, &K_S_008, 
  &K_A_6F, &K_A___,&K_A___, &K_S_007, &K_A_74,    &K_A_71,&K_A_78, &K_S_006, &K_A_70, &K_A___,
  &K_A___, &K_S_005, &K_A_73, &K_A_67,&K_A_79,    &K_S_004, &K_A___, &K_A___,&K_A___, &K_S_003, 
  &K_A_72, &K_A_68,&K_A___, &K_S_002, &K_A_62,    &K_A_77, &K_A___, &K_S_001, &K_A_6E, &K_A_66,
  &K_SPACE ,&K_ENTER,  &K_ESC ,&K_BACKSPACE };

//===================================================
static const PROGMEM KeyWord* Keys_MOD2[] = { 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___ ,&K_A___,  &K_A___ ,&K_A___  };

//===================================================
static const PROGMEM KeyWord* Keys_MOD3[] = { 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___ ,&K_A___,  &K_A___ ,&K_A___  };

//===================================================
static const PROGMEM KeyWord* Keys_MOD4[] = { 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___ ,&K_A___,  &K_A___ ,&K_A___  };

//===================================================
static const PROGMEM KeyWord* Keys_MOD5[] = { 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___ ,&K_A___,  &K_A___ ,&K_A___  };

//===================================================
static const PROGMEM KeyWord* Keys_MOD6[] = { 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___ ,&K_A___,  &K_A___ ,&K_A___  };

//===================================================
static const PROGMEM KeyWord* Keys_MOD7[] = { 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___,&K_A___,&K_A___,&K_A___,&K_A___,    &K_A___,&K_A___,&K_A___,&K_A___,&K_A___, 
  &K_A___ ,&K_A___,  &K_A___ ,&K_A___  };

const KeyWord** KeysPages[] = {
  Keys_NORM, Keys_MAJ, Keys_NUM, Keys_SPE, Keys_FN,
  Keys_MOD0, Keys_MOD1, Keys_MOD2, Keys_MOD3, Keys_MOD4, Keys_MOD5, Keys_MOD6, Keys_MOD7  } ;

char pagesnames[][12] = {
  "NOR" ,"MAJ",
  "NUM","SPE","FN_",
  "MD0" ,"MD1" ,"MD2" ,
  "MD3" ,"MD4" ,"MD5" ,
  "MD6" ,"MD7"  } 
;

//
// tableau des fonction
//

MPV_V cladeonFunctions[24] = { 
    &CladeonKbd::nullaction,        // 00
    &CladeonKbd::switchToPageMaj,   // 01
    &CladeonKbd::switchToPageNum,   // 02   
    &CladeonKbd::switchToPageSpe,   // 03   
    &CladeonKbd::switchToPageNorm,  // 04        
    &CladeonKbd::switchToPageFn,    // 05          
    &CladeonKbd::switchToPageMod,   // 06          
    &CladeonKbd::switchModCtrl,     // 07 
    &CladeonKbd::switchModAlt,      // 08 
    &CladeonKbd::switchModSht,      // 09
    &CladeonKbd::switchModGui,      // 10
    &CladeonKbd::switchModRalt,     // 11
    &CladeonKbd::apply_accent,      // 12
    &CladeonKbd::send_alttab,       // 13
    &CladeonKbd::send_numlock,      // 14
    &CladeonKbd::Supp_1_car,        // 15
    &CladeonKbd::send_copy,         // 16
    &CladeonKbd::send_paste,        // 17
    &CladeonKbd::send_undo,         // 18
    &CladeonKbd::send_cut,          // 19
    &CladeonKbd::send_ctrlaltdel,   // 20
    &CladeonKbd::switchModifierLock, // 21
    &CladeonKbd::testkeys           // 22
  } ;


CladeonKbd::CladeonKbd() {
} 

void CladeonKbd::init(CladeonScreen &scr, CladeonSound &snd){
  cdnscreen = & scr ; 
  cdnsound  = & snd ; 
  debugln("init kbd USB");
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.set_key2(0);
  Keyboard.set_key3(0);
  Keyboard.set_key4(0);
  Keyboard.set_key5(0);
  Keyboard.set_key6(0);
  Keyboard.send_now();
  //  cdnscreen->refresh(pagesnames[PageSelected],pagesnames[PreviousPageSelected],1,0);
  cdnscreen->refresh(pagesnames[PageSelected],pagesnames[PreviousPageSelected],PageLock,keyboard_modifier,modifierLock);
}

void CladeonKbd::emit(int c, int modselector){
  modselected = modselector ; 
  // detect action to do with key code range
  if (c < RTP_CODE_INDEX) {
    LTP_handle(c - LTP_CODE_INDEX ) ;
  } 
  else if (c < MAIN_CODE_INDEX) {      
    RTP_handle(c - RTP_CODE_INDEX );
  } 
  else if (c < (IR_CODE_INDEX)){
    MAIN_handle(c - MAIN_CODE_INDEX);
    switchBackPage();
  } 
  else if (c < (IR_CODE_INDEX+100)){
    IR_handle(c - IR_CODE_INDEX);
  } 
  else  {
    debugln(" unknown action ", c,1);
  } 
  resetModifier();
  cdnscreen->refresh(pagesnames[PageSelected],pagesnames[PreviousPageSelected],PageLock,keyboard_modifier,modifierLock);
  //cdnsound->pageselect();    
} 

void CladeonKbd::send_rawkey( int keyval){ 
  Keyboard.set_key1(keyval);
  Keyboard.send_now();
  Keyboard.set_key1(0);
  Keyboard.send_now();
}

void CladeonKbd::send_composkey(uint8_t modif,int key) {
  Keyboard.set_modifier(modif);
  Keyboard.set_key1(key);
  Keyboard.send_now();
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
}


void CladeonKbd::send_string(const char* c){ 
  Keyboard.print(c); 
}

void CladeonKbd::write_key(uint8_t keyval, int kbd_modif){
  uint8_t modifier=kbd_modif;
  if (keyval & SHIFT_MASK) modifier |= MODIFIERKEY_SHIFT;
  if (keyval & ALTGR_MASK) modifier |= MODIFIERKEY_RIGHT_ALT;
  keyval &= 0x3F;
  if (keyval == KEY_NON_US_100) keyval = 100;
  send_composkey(modifier,keyval);
}

void CladeonKbd::send_alphakey( int keyval, int kbd_modif){ 
  int deadkey = keyval & DEADKEYS_MASK;
  if (deadkey == CIRCUMFLEX_BITS) write_key(DEADKEY_CIRCUMFLEX,0);	
  if (deadkey == DIAERESIS_BITS) write_key(DEADKEY_DIAERESIS,0);
  if (deadkey == GRAVE_ACCENT_BITS) write_key(DEADKEY_GRAVE_ACCENT,0);
  if (deadkey == TILDE_BITS) write_key(DEADKEY_TILDE,0);
  write_key(keyval,kbd_modif);
}

// compose a key with an alt code. not portable though
void CladeonKbd::send_altkey(const char* c){
  // press ALT
  Keyboard.set_modifier(MODIFIERKEY_ALT);
  Keyboard.send_now();
  for (int i=0; i < 4; i++) {
    char code = int(c[i]+40);
    if (code > 87 && code < 98 ) {
      if (code == 88) code = 98;// for 0
      send_rawkey(code);
    }
  }
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
}


//when key is a composition of keys
void CladeonKbd::send_seq(const struct KeyWord* key, int kbd_modif){ 
  for(int i=0;i<KEY_SEQ_LENGTH;i++){ 
    KeyWord * tmpkey = (KeyWord *) pgm_read_word(&key->seq[i] ); 
    send_alpha(tmpkey, kbd_modif );
  }   
}

void CladeonKbd::send_alpha(const struct KeyWord* key, int kbd_modif){ 
  if (key ==NULL) return; 
  switch (pgm_read_word(&key->type )) {
  case 1: // send a caracter
    send_alphakey(pgm_read_word(&key->key),kbd_modif);    
    break;
  case 2: // send a string
    send_string((char *)pgm_read_word(&key->string));
    break;
  case 3: // send an alt key
    send_altkey((char *)pgm_read_word(&key->altval));
    break;
  case 4: // send a sequence
    send_seq(key,kbd_modif);
    break;
  case 5: // send a raw key
    send_rawkey(pgm_read_word(&key->key));
    break;    
  case 6: // call function
    {
      CladeonKbd instance ;
      int prog = pgm_read_word(&key->fctptr) ;
      (this->*cladeonFunctions[prog])();
      break;
    }      
  default: 
    ;
  } 
}  

void CladeonKbd::nullaction() {} ;

// maj, num, ctrl,ctrlaltsuppr
//spe, norm, alt,lock,
//fn, mode,win,altgr

void CladeonKbd::switchToPageMaj()  {  
  CladeonKbd::switchToPage(PAGE_MAJ) ;  
}
void CladeonKbd::switchToPageNum()  {  
  CladeonKbd::switchToPage(PAGE_NUM) ;  
}       
void CladeonKbd::switchToPageSpe()  {  
  CladeonKbd::switchToPage(PAGE_SPE) ;   
}          
void CladeonKbd::switchToPageNorm() {  
  CladeonKbd::switchToPage(PAGE_NORM) ;   
}      
void CladeonKbd::switchToPageFn()   {  
  CladeonKbd::switchToPage(PAGE_FN) ;      
}       
void CladeonKbd::switchToPageMod()  {  
  CladeonKbd::switchToPage(PAGE_MOD0) ;     
}        

void CladeonKbd::switchModCtrl()    {  
  CladeonKbd::switchModifier(MODIFIERKEY_CTRL ); 
}     
void CladeonKbd::switchModAlt()     {  
  CladeonKbd::switchModifier(MODIFIERKEY_ALT);    
}  
void CladeonKbd::switchModSht()     {  
  CladeonKbd::switchModifier(MODIFIERKEY_SHIFT); 
}
void CladeonKbd::switchModGui()     {  
  CladeonKbd::switchModifier(MODIFIERKEY_GUI);    
}  
void CladeonKbd::switchModRalt()    {  
  CladeonKbd::switchModifier(MODIFIERKEY_RIGHT_ALT); 
}




void CladeonKbd::LTP_handle(const int k){
    send_alpha( LTP_keys[k],0); 
}

void CladeonKbd::RTP_handle(const int k){  
    send_alpha( RTP_keys[k],0); 
}




void CladeonKbd::IR_handle(const int k){
  debugln("IR : ", k,1);
  send_alpha( IR_keys[k],0); 
}

void CladeonKbd::MAIN_handle(int c){
  KeyWord * tmpkey = (KeyWord *)pgm_read_word(&KeysPages[PageSelected][c]);
  lastkey = (int)pgm_read_word(&tmpkey->key) ;
  accentiterator = 0 ;
  send_alpha(tmpkey,keyboard_modifier); 
}

void CladeonKbd::switchToPage(int page){
  if ( page >= PAGE_MOD0) 
    page = modselected + PAGE_MOD0 ;
  if (PageSelected == page ) { 
    // uncomment for autolock modes
    // || (PageSelected  >= PAGE_MOD0 && page >= PAGE_MOD0 )) {
    PageLock = 1; 
    debugln("Page locked : ", page,2);
  } 
  else { 
    PreviousPageSelected = PageSelected ;
    PageLock = 0;
    //    if ( page < PAGE_MOD0) { 
    PageSelected = page ;
    debugln("Page selected : ", page,2);      
    //    }
  } 
}

static const KeyWord* ALL_keys[] = { 
  &K_A_1 , &K_A_2 , &K_A_3 , &K_A_4 , &K_A_5 , &K_A_6 , &K_A_7 , &K_A_8 , &K_A_9 , 
  &K_A_A , &K_A_B , &K_A_C , &K_A_D , &K_A_E , &K_A_F , &K_A_10, &K_A_11, &K_A_12 , &K_A_13, &K_A_14, &K_A_15, &K_A_16 
    , &K_A_17, &K_A_18, &K_A_19, &K_A_1A , &K_A_1B, &K_A_1C, &K_A_1D , &K_A_1E , &K_A_1F , &K_A_20 , &K_A_21 , &K_A_22 , 
  &K_A_23 , &K_A_24 , &K_A_25 , &K_A_26 , &K_A_27 , &K_A_28 , &K_A_29 , &K_A_2A , &K_A_2B , &K_A_2C , &K_A_2D , &K_A_2E ,
  &K_A_2F , &K_A_30 , &K_A_31 , &K_A_32 , &K_A_33 , &K_A_34 , &K_A_35 , &K_A_36 , &K_A_37 , &K_A_38 , &K_A_39 , &K_A_3A ,
  &K_A_3B , &K_A_3C , &K_A_3D , &K_A_3E , &K_A_3F , &K_A_40 , &K_A_41 , &K_A_42 , &K_A_43 , &K_A_44 , &K_A_45 , &K_A_46 , 
  &K_A_47 , &K_A_48 , &K_A_49 , &K_A_4A , &K_A_4B , &K_A_4C , &K_A_4D , &K_A_4E , &K_A_4F , &K_A_50 , &K_A_51 , &K_A_52 , 
  &K_A_53 , &K_A_54 , &K_A_55 , &K_A_56 , &K_A_57 , &K_A_58 , &K_A_59 , &K_A_5A , &K_A_5B , &K_A_5C , &K_A_5D , &K_A_5E , 
  &K_A_5F , &K_A_60 , &K_A_61 , &K_A_62 , &K_A_63 , &K_A_64 , &K_A_65 , &K_A_66 , &K_A_67 , &K_A_68 , &K_A_69 , &K_A_6A , 
  &K_A_6B , &K_A_6C , &K_A_6D , &K_A_6E , &K_A_6F , &K_A_70 , &K_A_71 , &K_A_72 , &K_A_73 , &K_A_74 , &K_A_75 , &K_A_76 , 
  &K_A_77 , &K_A_78 , &K_A_79 , &K_A_7A , &K_A_7B , &K_A_7C , &K_A_7D , &K_A_7E , &K_A_7F , &K_A_A0 , &K_A_A1 , &K_A_A2 , 
  &K_A_A3 , &K_A_A4 , &K_A_A5 , &K_A_A6 , &K_A_A7 , &K_A_A8 , &K_A_A9 , &K_A_AA , &K_A_AB , &K_A_AC , &K_A_AD , &K_A_AE , 
  &K_A_AF , &K_A_B0 , &K_A_B1 , &K_A_B2 , &K_A_B3 , &K_A_B4 , &K_A_B5 , &K_A_B6 , &K_A_B7 , &K_A_B8 , &K_A_B9 , &K_A_BA , 
  &K_A_BB , &K_A_BC , &K_A_BD , &K_A_BE , &K_A_BF , &K_A_C0 , &K_A_C1 , &K_A_C2 , &K_A_C3 , &K_A_C4 , &K_A_C5 , &K_A_C6 , 
  &K_A_C7 , &K_A_C8 , &K_A_C9 , &K_A_CA , &K_A_CB , &K_A_CC , &K_A_CD , &K_A_CE , &K_A_CF , &K_A_D0 , &K_A_D1 , &K_A_D2 , 
  &K_A_D3 , &K_A_D4 , &K_A_D5 , &K_A_D6 , &K_A_D7 , &K_A_D8 , &K_A_D9 , &K_A_DA , &K_A_DB , &K_A_DC , &K_A_DD , &K_A_DE , 
  &K_A_DF , &K_A_E0 , &K_A_E1 , &K_A_E2 , &K_A_E3 , &K_A_E4 , &K_A_E5 , &K_A_E6 , &K_A_E7 , &K_A_E8 , &K_A_E9 , &K_A_EA , 
  &K_A_EB , &K_A_EC , &K_A_ED , &K_A_EE , &K_A_EF , &K_A_F0 , &K_A_F1 , &K_A_F2 , &K_A_F3 , &K_A_F4 , &K_A_F5 , &K_A_F6 , 
  &K_A_F7 , &K_A_F8 , &K_A_F9 , &K_A_FA , &K_A_FB , &K_A_FC , &K_A_FD , &K_A_FE , &K_A_FF , &K_A_20AC , &K_M_PREV, &K_M_PLAY,
  &K_M_NEXT, &K_M_DEC , &K_M_INC , &K_M_EJECT, &K_D_01 , &K_D_02 , &K_D_03 , &K_D_04 , &K_D_05 , &K_D_06 , &K_D_07, &K_D_08 ,
  &K_D_09 , &K_D_10 , &K_D_11 , &K_D_12 , &K_D_13 , &K_D_14 , &K_D_15, &K_D_16 , &K_D_17 , &K_D_18 , &K_D_19 , &K_D_20 , &K_D_21 , 
  &K_D_22 , &K_D_23 , &K_D_24 , &K_D_25 , &K_D_26 , &K_D_27 , &K_D_28 , &K_D_29 , &K_D_30 , &K_D_31 , &K_D_32 , &K_D_33 , &K_D_34 ,
  &K_D_35 , &K_D_36 , &K_D_37 , &K_D_38 , &K_D_39 , &K_D_40 , &K_D_41 , &K_D_42 , &K_D_43 , &K_D_44 , &K_D_45 , &K_D_46 , 
  &K_D_47 , &K_D_48 , &K_D_49 , &K_B_32 , &K_B_33 , &K_B_34 , &K_B_35, &K_B_254 ,
  &K_B_0129 , &K_B_127, &K_B_0153  };


void CladeonKbd::testkeys(){
  for (int i = 1; i < 318; i++) {
    Keyboard.print("Key ");
    Keyboard.print(i);
    Keyboard.print(" : ");
    //  send_string((char *)pgm_read_word(&key->string));
    send_string((char *)pgm_read_word(&ALL_keys[i]->string));   
    Keyboard.print(" : ");

    send_alpha( ALL_keys[i],0);
    Keyboard.println(";");
  }
}

void CladeonKbd::switchModifierLock(){
  // faire un xor ?  
  if (modifierLock == 0) modifierLock = 1 ;
  else modifierLock = 0 ;
}

void CladeonKbd::switchModifier(int modif){
  keyboard_modifier = keyboard_modifier ^ modif ;
  //    cdnscreen->welcome("modifier :", itoa(modif,tmpchar,10) );
  cdnsound->switchmodifier();
  Keyboard.set_modifier(keyboard_modifier);
  //  Keyboard.set_key1(keyboard_modifier);
  Keyboard.send_now();

} 



void CladeonKbd::switchBackPage(){
  if (PageLock == 0) { 
    PageSelected =  PreviousPageSelected  ;
    PageLock = 1;
  }
}

void CladeonKbd::resetModifier(){
  if (modifierLock == 0 && keyboard_modifier !=0) { 
    keyboard_modifier = 0 ;
    Keyboard.set_modifier(keyboard_modifier);
    Keyboard.send_now();
  }
}


void CladeonKbd::apply_accent(){ 
  debugln("Accent : ", 0,2);
  switch ( lastkey ) {
  case 0:  
    break; 
  case KEY_Q:
    Supp_1_car();
    send_alpha((KeyWord *)pgm_read_word(&Keys_a[accentiterator%nb_accent_a]),keyboard_modifier);
    break;
  case KEY_QS : 
    Supp_1_car();
    send_alpha((KeyWord *)pgm_read_word(&Keys_A[accentiterator%nb_accent_a]),keyboard_modifier);
    break; 
  case KEY_E:
    Supp_1_car();
    send_alpha((KeyWord *)pgm_read_word(&Keys_e[accentiterator%nb_accent_e]),keyboard_modifier);
    break;    
  case KEY_ES  :
    Supp_1_car();
    send_alpha((KeyWord *)pgm_read_word(&Keys_E[accentiterator%nb_accent_e]),keyboard_modifier);
    break;
  case KEY_I:
    Supp_1_car();
    send_alpha((KeyWord *)pgm_read_word(&Keys_i[accentiterator%nb_accent_i]),keyboard_modifier);
    break;    
  case KEY_IS:
    Supp_1_car();
    send_alpha((KeyWord *)pgm_read_word(&Keys_I[accentiterator%nb_accent_i]),keyboard_modifier);
    break;
  case KEY_O:
    Supp_1_car();
    send_alpha((KeyWord *)pgm_read_word(&Keys_o[accentiterator%nb_accent_o]),keyboard_modifier);
    break;   
  case KEY_OS:
    Supp_1_car();
    send_alpha((KeyWord *)pgm_read_word(&Keys_O[accentiterator%nb_accent_o]),keyboard_modifier);
    break; 
  case KEY_U:
    Supp_1_car();
    send_alpha((KeyWord *)pgm_read_word(&Keys_u[accentiterator%nb_accent_u]),keyboard_modifier);
    break;
  case KEY_US:
    Supp_1_car();
    send_alpha((KeyWord *)pgm_read_word(&Keys_U[accentiterator%nb_accent_u]),keyboard_modifier);
    break;
  case KEY_C:
    Supp_1_car();
    send_alpha((KeyWord *)pgm_read_word(&Keys_c[accentiterator%nb_accent_c]),keyboard_modifier);
    break;
  case KEY_CS:
    Supp_1_car();
    send_alpha((KeyWord *)pgm_read_word(&Keys_C[accentiterator%nb_accent_c]),keyboard_modifier);
    break;
  } 
  accentiterator += 1 ;
}

void CladeonKbd::send_copy() { 
  send_composkey(MODIFIERKEY_CTRL,KEY_C) ; 
}

void CladeonKbd::send_paste() { 
  send_composkey(MODIFIERKEY_CTRL,KEY_V) ; 
}

void CladeonKbd::send_undo() { 
  send_composkey(MODIFIERKEY_CTRL,KEY_Z) ; 
}

void CladeonKbd::send_cut() { 
  send_composkey(MODIFIERKEY_CTRL,KEY_X) ; 
}

void CladeonKbd::send_ctrlaltdel() { 
  send_composkey(MODIFIERKEY_CTRL| MODIFIERKEY_ALT,KEY_DELETE) ; 
}

void  CladeonKbd::Supp_1_car(){ 
  send_rawkey(KEY_BACKSPACE); 
}

void CladeonKbd::send_numlock() { 
  send_alpha(&K_NUMLOCK,0); 
}

void CladeonKbd::send_alttab() { 
  send_composkey(MODIFIERKEY_ALT,KEY_TAB) ; 
}



