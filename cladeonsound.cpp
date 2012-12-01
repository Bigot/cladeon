#include "cladeonsound.h"
#include "debug.h"
#include "WProgram.h"


// notes in the melody:
int melody[] = {NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4, 8, 8, 4,4,4,4,4 };

int shortbeep = 30 ;
int longbeep = 60 ;

CladeonSound::CladeonSound() { }

void CladeonSound::begin(int pin) {
  soundpin = pin ;
  debugln("init sound");
}

void CladeonSound::welcome() {
   for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(soundpin, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
 //   noTone(soundpin);
  }
}

void CladeonSound::pagelock() {
  tone(soundpin, NOTE_A1 , longbeep);
 // noTone(soundpin);    
}

void CladeonSound::pageselect() {
  tone(soundpin, NOTE_A1 , shortbeep);
 // noTone(soundpin);    
}

void CladeonSound::switchmodifier() {
  tone(soundpin, NOTE_B0 , shortbeep);
 // noTone(soundpin);  
}
