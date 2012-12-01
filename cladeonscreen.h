#ifndef CladeonScreen_h
#define CladeonScreen_h

#include "WProgram.h"

class CladeonScreen {
  public:
    CladeonScreen();
    void begin(int pin);
    void welcome(char* t1, char* t2) ;
    void refresh(char* t1, char* t2,int pagelock,int modif,int modiflock);
    void lockpage(char* t1);
    void resetmodifier();

  private:
    int screenpin ;
    void sep();
    void clearLCD();
    void newLine();
    void cursorHome();
    void cursorSet(int xpos, int ypos);
    void dispText(char* txt);
    void dispInt(int txt);
} ;
#endif
