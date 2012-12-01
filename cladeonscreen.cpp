
#include "cladeonscreen.h"
#include "debug.h"
#include "WProgram.h"

HardwareSerial cladeonscreen ;

CladeonScreen::CladeonScreen() { }

void CladeonScreen::begin(int pin) {
  cladeonscreen = HardwareSerial() ;
  cladeonscreen.begin(19200);
  cladeonscreen.print(160, BYTE); // init display
  delay(100);
//  cladeonscreen.print(163, BYTE); // remove curser
//  cladeonscreen.print(14, BYTE); // remove curser
//  delay(100);
  debugln("init screen");
}

void CladeonScreen::sep(){   dispText("#"); }

void CladeonScreen::welcome(char* t1, char* t2) {
  clearLCD();
  dispText(t1);
  cursorSet(0,2);              // start a new line
  dispText(t2); 
}

void CladeonScreen::refresh(char* mod1, char* mod2, int pagelock,int modif,int modiflock) {
  clearLCD();
  //first line
  // selected page
  dispText(mod1);
  sep();

  // modifier, > befor if selected  
  int tempmodif =  modif & 0x7FFF ;

if (modiflock==0 ) { dispText("*C*A*S*G*R"); } else {

  if (MODIFIERKEY_CTRL & tempmodif  ) { dispText(">C"); } else { dispText(" C"); }
     debugln("CTRL", MODIFIERKEY_CTRL & tempmodif   ,3);
  if (MODIFIERKEY_ALT  & tempmodif   ) { dispText(">A"); } else { dispText(" A"); }
       debugln("ALT", MODIFIERKEY_ALT & tempmodif  ,3);
  if (MODIFIERKEY_SHIFT  & tempmodif ) { dispText(">S"); } else { dispText(" S"); }
       debugln("SHIFT", MODIFIERKEY_SHIFT & tempmodif ,3);
  if (MODIFIERKEY_GUI  & tempmodif  ) { dispText(">G"); } else { dispText(" G"); }
       debugln("RALT", MODIFIERKEY_RIGHT_ALT & tempmodif ,3);
  if (MODIFIERKEY_RIGHT_ALT  & tempmodif ) { dispText(">R"); } else { dispText(" R"); }
  
}
  //second line
  cursorSet(0,2);
  
  // return page if present not locked
  if (pagelock == 0) { dispText(mod2); } else {  dispText("###"); }
  sep();

}


void CladeonScreen::clearLCD(){
  cladeonscreen.print(163, BYTE);
  cladeonscreen.print(1, BYTE);
  cursorSet(0,1);
}

// move the cursor to the home position
void CladeonScreen::cursorHome(){
  cladeonscreen.print(161, BYTE); 
  cladeonscreen.print("0");
  cladeonscreen.print("0");
}

void CladeonScreen::cursorSet(int xpos, int ypos){  
  cladeonscreen.print(161, BYTE);               
  cladeonscreen.print(xpos); 
  cladeonscreen.print(ypos);
} 

void CladeonScreen::dispText(char* txt){  
  cladeonscreen.print(162, BYTE);               
  cladeonscreen.print(txt);   
  cladeonscreen.print(0, BYTE);
} 

void CladeonScreen::dispInt(int val){  
  cladeonscreen.print(162, BYTE);               
  cladeonscreen.print(val);   
  cladeonscreen.print(0, BYTE);
}

 
