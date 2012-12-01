#include "debug.h"
#include "WProgram.h"
#define DEBUG 2

// debug function
void debug(const char* str, const int val, const int niv ) {
  #ifdef DEBUG
  if ( niv >= DEBUG ) {
  Serial.print(str);
  Serial.print(val); }
  #endif
}

void debugln(const char* str, const int val, const int niv ) {
  #ifdef DEBUG
    if ( niv >= DEBUG ) {
  Serial.print(str);
  Serial.println(val);
    }
  #endif
}

void debugln(const char* str) {
  #ifdef DEBUG
//    if ( niv > DEBUG ) {
  Serial.println(str);
//    }
  #endif
}
