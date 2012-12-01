#include "ps2kbdraw.h"
#include "debug.h"
#include "cladeonsound.h"
#include "cladeonscreen.h"
#include "cladeonkbd.h"
#include <IRremote.h>
#define DEBUG 4

//=====================================================================
// pin definition for a teensy 2 ++
//=====================================================================
//startup led
const int led_Pin = 6; 
//internal ps2
const int Data_Pin = 20;
const int IRQ_Pin =  19;
//page mode selector
const int modSelector0_Pin =  21;
const int modSelector1_Pin =  22;
const int modSelector2_Pin =  23;
//mouse pins
const int mouseLeft_Pin     =  10;
const int mouseMiddle_Pin   =  9;
const int mouseRight_Pin    = 8 ;
const int mouseJoystick_Pin = 11;
const int mouseX_APin = 1 ; // analogical
const int mouseY_APin = 0 ; // analogical
//scroll pins
const int scrollX_APin = 2 ;  // analogical
const int scrollY_APin = 3 ; // analogical
//IR pins
const int IRrecv_Pin = 18 ; // E6
const int sound_Pin = 43 ; // F5 
const int screen_Pin = 3 ; // Tx pin used by default

//=====================================================================
// variables
//=====================================================================

int loopDelay = 1 ;

// IR variable

// Mouse parametres 
int mouseXTrim = 508 ;
int mouseYTrim = 524  ;
int scrollXTrim = 520 ;
int scrollYTrim = 520 ;

const int mouseXdirection = -1 ;
const int mouseYdirection = -1 ;
//const int mouseResistivity =25;
const int mouseMvtDelay = 25 ;
const int scrollMvtDelay = 500;
const int scrollResistivity = 100 ;
const int scrollDirection = 1 ;
int mouseXresistance = 30 ;  
int mouseYresistance = 30 ;  
unsigned long lastMouseMove ;

const int scrollLim1 = 130 ;
const int scrollLim2 = 180 ;
const int scrollAccel = 3 ;
unsigned long lastScroll ;

//mouse initialisation values
int mouseLeftValue     = 1;
int mouseMiddleValue   = 1;
int mouseRightValue    = 1;
int mouseJoystickValue = 1;




// irvalues
int lastIrVal;
int lastIrDate;
int irDelay = 200 ;

//
//PS2 code transcription
//
static int kbdmap[]={
  0,214,0,209,106,123,107,0,0,202,     // 0
  218,341,101,114,115,0,0,0,0,222,     // 10
  0,113,112,0,0,0,110,124,116,121,     // 20
  120,0,0,102,118,108,105,0,104,0,     // 30
  0,210,323,332,333,324,314,0,0,311,   // 40
  313,330,334,331,310,0,0,0,321,312,   // 50
  320,322,0,0,0,302,300,301,217,203,   // 60
  223,0,0,220,211,219,207,216,215,0,   // 70
  0,304,212,0,208,303,0,0,122,0,       // 80
  201,340,0,206,0,0,0,117,0,0,         // 90
  221,0,205,111,338,317,213,329,339,0, // 100
  0,0,307,336,309,343,326,308,109,319, // 110
  327,0,337,325,315,335,0,0,0,0,       // 120
  0,224,0,0,0,0,0,0,0,0,               // 130
  0,0,0,0,0,0,0,0,0,0,                 // 140
  0,0,0,0,0,0,0,0,0,0,                 // 150
  0,0,0,0,0,0,0,0,0,0,                 // 160
  0,0,0,0,0,0,0,0,0,0,                 // 170
  0,0,0,0,0,0,0,0,0,0,                 // 180
  0,0,0,0,305,0,0,0,0,0,               // 190 
  0,0,0,0,0,0,0,0,0,0,                 // 200
  0,0,0,0,0,0,0,0,0,0,                 // 210
  0,0,0,0,0,0,0,0,0,0,                 // 220
  0,0,306,318,328,0,342,0,0,0,         // 230
  0,119,103,0,0,316};                  // 240

//=====================================================================
// objects
//=====================================================================

PS2Keyboard tki ;
CladeonScreen screen ; 
CladeonSound sound ; 
IRrecv irrecv(IRrecv_Pin);
CladeonKbd kbd ; 

//=====================================================================
// Setup function
//=====================================================================

void setup() {
  Serial.begin(19200);
  delay(200);  
  debugln("init cladeon");
  screen.begin(screen_Pin);
  screen.welcome("demarrage","CLADEON");

  pinMode(mouseLeft_Pin,      INPUT_PULLUP);
  pinMode(mouseMiddle_Pin,    INPUT_PULLUP);
  pinMode(mouseRight_Pin,     INPUT_PULLUP);
  pinMode(mouseJoystick_Pin,  INPUT_PULLUP);
  pinMode(modSelector0_Pin,     INPUT_PULLUP);
  pinMode(modSelector1_Pin,     INPUT_PULLUP);
  pinMode(modSelector2_Pin,     INPUT_PULLUP);
  pinMode(led_Pin, OUTPUT);

  sound.begin(sound_Pin);
  //  sound.welcome();

  for (int i=0; i < 10; i++) {
    digitalWrite(led_Pin, HIGH);
    delay(100);
    digitalWrite(led_Pin, LOW);
    delay(100);   
  }

  // joystick trim initialisation
  mouseXTrim=analogRead(mouseX_APin) ;
  mouseYTrim=analogRead(mouseY_APin) ;
  scrollXTrim = analogRead(scrollX_APin) ;
  scrollYTrim = analogRead(scrollY_APin) ;

  debugln("Mouse X trim : ", mouseXTrim, 3 ) ;
  debugln("Mouse Y trim : ", mouseYTrim, 3 ) ;
  debugln("Scroll X trim : ", scrollXTrim, 3 ) ;
  debugln("Scroll Y trim : ", scrollYTrim, 3 ) ;

  // objects initialisation
  tki.begin(Data_Pin, IRQ_Pin) ;
  kbd.init(screen, sound) ;
  irrecv.enableIRIn();
}

//=====================================================================
// Raw signal handler
//=====================================================================

void kbdHandle(){
  if (tki.available()) {
    int c = tki.read();
    debug("Key : ", c,0);
    debugln("    remap : ",kbdmap[c],0);
    kbd.emit(kbdmap[c],findSelectedMod());
  }
}

int findSelectedMod() {
  return 7 - (digitalRead(modSelector0_Pin)+digitalRead(modSelector1_Pin)*2+digitalRead(modSelector2_Pin)*4 ) ;
}

void irHandle(){
  decode_results results;
  int irval = 0; 
  int temp = 0;
  if (irrecv.decode(&results)) {
    //   if (results.decode_type == NEC  ) { //&& results.value != 0xFFFFFFFF
    if (results.value == 0xFFFFFFFF && (millis() - lastIrDate > irDelay)) {
      irval = lastIrVal ; 
    } 
    else { 
      temp = (results.value & 0b111111111111111 ) ;
      switch(temp) {  
      case 0x629D: 
        irval = 401 ; 
        break ;
      case 0x205F: 
        irval = 402 ; 
        break ;
      case 0x7A85: 
        irval = 403 ; 
        break ;
      case 0x3A45: 
        irval = 404 ; 
        break ;
      case 0x7887: 
        irval = 405 ; 
        break ;
      case 0x3847: 
        irval = 406 ; 
        break ;
      case 0x52AD: 
        irval = 407 ; 
        break ;
      case 0x126D: 
        irval = 408 ; 
        break ;
      case 0x50AF: 
        irval = 409 ; 
        break ;
      case 0x106F: 
        irval = 410 ; 
        break ;
      case 0x5AA5: 
        irval = 411 ; 
        break ;
      case 0x1A65: 
        irval = 412 ; 
        break ;
      case 0x58A7: 
        irval = 413 ; 
        break ;
      case 0x1867: 
        irval = 414 ; 
        break ;
      case 0x728D: 
        irval = 415 ; 
        break ;
      case 0x324D: 
        irval = 416 ; 
        break ;
      case 0x708F: 
        irval = 417 ; 
        break ;
      case 0x304F: 
        irval = 418 ; 
        break ;
      case 0x4AB5: 
        irval = 419 ; 
        break ;
      case 0x0A75: 
        irval = 420 ; 
        break ;
      case 0x48B7: 
        irval = 421 ; 
        break ;
      case 0x0877: 
        irval = 422 ; 
        break ;
      case 0x6A95: 
        irval = 423 ; 
        break ;
      case 0x2A55: 
        irval = 424 ; 
        break ;
      case 0x2857: 
        irval = 425 ; 
        break ;
      case 0x7A05: 
        irval = 426 ; 
        break ;
      case 0x38C7: 
        irval = 427 ; 
        break ;
      case 0x7807: 
        irval = 428 ; 
        break ;
      case 0x6A15: 
        irval = 429 ; 
        break ;
      case 0x28D7: 
        irval = 430 ; 
        break ;
      case 0x6817: 
        irval = 431 ; 
        break ;
      case 0x5A25: 
        irval = 432 ; 
        break ;
      case 0x18E7: 
        irval = 433 ; 
        break ;
      case 0x5827: 
        irval = 434 ; 
        break ;
      case 0x4A35: 
        irval = 435 ; 
        break ;
      case 0xAF5: 
        irval = 436 ; 
        break ;
      case 0x8F7: 
        irval = 437 ; 
        break ;
      case 0x4837: 
        irval = 438 ; 
        break ;
      case 0x720D: 
        irval = 439 ; 
        break ;
      case 0x32CD: 
        irval = 440 ; 
        break ;
      case 0x30CF: 
        irval = 441 ; 
        break ;
      case 0x700F: 
        irval = 442 ; 
        break ;
      case 0x522D: 
        irval = 443 ; 
        break ;
      case 0x12ED: 
        irval = 444 ; 
        break ;
      case 0x10EF: 
        irval = 445 ; 
        break ;
      case 0x502F: 
        irval = 446 ; 
        break ;
      case 0x621D: 
        irval = 447 ; 
        break ;
      case 0x22DD: 
        irval = 448 ; 
        break ;
      case 0x20DF: 
        irval = 449 ; 
        break ;
      case 0x601F: 
        irval = 450 ; 
        break ;
      default:  
        break;
      }
    }
    irrecv.resume(); // Receive the next value
    if (irval > 0) {
      lastIrVal= irval; 
      lastIrDate = millis();
      kbd.emit(irval,findSelectedMod());
    }
  }  
}

//=====================================================================
// main loop
//=====================================================================

void loop() {
  sendMouseButton();
  sendMouseMvt();
  sendScrollMvt();
  delay(loopDelay);
  kbdHandle();
  irHandle();
}

//=====================================================================
// Mouse sender
//=====================================================================

//
// handle mouse joystick
// TODO linear/exponential increment

void sendMouseMvt(){  
  int mouseXposition=analogRead(mouseX_APin)-mouseXTrim ;
  int mouseYposition=analogRead(mouseY_APin)-mouseYTrim ;

  if (  (millis() - lastMouseMove > mouseMvtDelay)) { 
    lastMouseMove = millis() ; 
    Mouse.move(mouseXdirection*mouseXposition/mouseXresistance,mouseYdirection*mouseYposition/mouseYresistance );
    debug("Mouse X : ", mouseXposition, 2 );
    debugln("  Move X : ", mouseXdirection*mouseXposition/mouseXresistance , 0 );
    debug("Mouse Y : ", mouseYposition,2 );
    debugln("  Move Y : ", mouseYdirection*mouseYposition/mouseXresistance,0 ); 
  } 
}

//
// handle scroll joystick
// TODO X scroll
//

void  sendScrollMvt(){   
  int val=analogRead(scrollY_APin) - scrollYTrim ;
  if ( abs(val) > scrollLim1 && ( (millis() - lastScroll) > scrollMvtDelay )) {
    lastScroll = millis() ;
    int dir = scrollDirection * scrollResistivity ;
    if ( abs(val) > scrollLim2 ) {
      dir = dir / scrollAccel ;
    } 
    debug("Scroll position : ", val ,2 );
    debugln("  Scroll Move : ", val/dir ,2 ); 
    Mouse.scroll(val/dir );
  }
}
//
// Send clic on mouse buttons
//
void sendMouseButton(){
  int LeftValue   =  digitalRead(mouseLeft_Pin)*digitalRead(mouseJoystick_Pin);
  int MiddleValue =  digitalRead(mouseMiddle_Pin);
  int RightValue  =  digitalRead(mouseRight_Pin);
  if ( LeftValue - mouseLeftValue + MiddleValue  - mouseMiddleValue + RightValue - mouseRightValue != 0 ) {
    Mouse.set_buttons(1-LeftValue ,1-MiddleValue,1-RightValue );
    mouseLeftValue   = LeftValue ;
    mouseMiddleValue = MiddleValue ;
    mouseRightValue  = RightValue ;
  }
}


