#ifndef cladeon_kbd_h
#define cladeon_kbd_h

#include "WProgram.h"
#include "cladeonsound.h"
#include "cladeonscreen.h"
#define KEY_SEQ_LENGTH 10

//
//page numbers
//
#define PAGE_NORM 0
#define PAGE_MAJ 1
#define PAGE_NUM 2
#define PAGE_SPE 3
#define PAGE_FN 4
#define PAGE_MOD0 5
#define PAGE_MOD1 6
#define PAGE_MOD2 7
#define PAGE_MOD3 8
#define PAGE_MOD4 9
#define PAGE_MOD5 10
#define PAGE_MOD6 11
#define PAGE_MOD7 12

//
// Key range
//
#define RTP_CODE_INDEX       200
#define LTP_CODE_INDEX     100
#define MAIN_CODE_INDEX  300
#define IR_CODE_INDEX  400
//400 programmable

typedef struct KeyWord KeyWord;

class CladeonKbd ;

//
// pointer to CladeonKbd member function
// used in keywords
//

typedef void (CladeonKbd::*MPV_V)() ;

//
//
//
class CladeonKbd {
  public:
    CladeonKbd() ; 
    void init(CladeonScreen &scr, CladeonSound &snd);
    void emit(int c, int modselector);
    void apply_accent() ;
    void send_rawkey( int keyval);
    void send_composkey(uint8_t modif,int key); 
    void send_string(const char* c);
    void write_key(uint8_t keyval, int kbd_modif);
    void send_alphakey( int keyval, int kbd_modif);
    void send_altkey(const char* c);
    void send_seq(const struct KeyWord* key, int kbd_modif);
    void send_alpha(const struct KeyWord* key, int kbd_modif);
    void RTP_handle(int c);
    void LTP_handle(int c);
    void IR_handle(int c);
    void MAIN_handle(int c);
    void switchToPage(int page);
    void switchModifier(int modif);
    void switchBackPage();
    void resetModifier();
    
    // function called by keywords
    
    void nullaction();
    void send_copy();
    void send_paste();
    void send_undo();
    void send_cut();
    void send_ctrlaltdel();
    void send_alttab();  
    void Supp_1_car();
    void send_numlock(); 
    void testkeys(); 
    void switchToPageMaj();  
    void switchToPageNum();        
    void switchToPageSpe() ;             
    void switchToPageNorm();         
    void switchToPageFn() ;             
    void switchToPageMod() ;             
    void switchModCtrl() ;     
    void switchModAlt()  ;      
    void switchModSht()  ; 
    void switchModGui()  ;      
    void switchModRalt() ;
    void switchModifierLock();
    
  private:
    CladeonScreen*  cdnscreen;
    CladeonSound*   cdnsound; 
    int sndpin ;
    int scnpin ;
} ;

//
// Keyword définition
// TODO was not able to use member pointer directly included in a struct in PROGMEM
// type :
//   1 : send a caracter 
//   2 : send string
//   3 : send ALT code 
//   4 : sequence call
//   5 : send a raw key
//   6 : function call 
//

struct KeyWord  {
 int type ;
 int key ;
 char* altval ;
 char* string ;
 int fctptr ;
 const struct KeyWord* seq[KEY_SEQ_LENGTH] ;
//   MPV_V fctptr ;

} ;



#endif

