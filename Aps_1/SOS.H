/* 
  Song of storms - Legend of Zelda 
  Connect a piezo buzzer or speaker to pin 11 or select a new pin.
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
*/

#ifndef SOS_H
#define SOS_H

#include "notes.h"

#define name3 "Song Storms"

// change this to make the song slower or faster
#define tempo3 148

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody3[] = {
  
  // Song of storms - The Legend of Zelda Ocarina of Time. 
  // Score available at https://musescore.com/user/4957541/scores/1545401
  
  NOTE_D4,4, NOTE_A4,4, NOTE_A4,4,
  REST,8, NOTE_E4,8, NOTE_B4,2,
  NOTE_F4,4, NOTE_C5,4, NOTE_C5,4,
  REST,8, NOTE_E4,8, NOTE_B4,2,
  NOTE_D4,4, NOTE_A4,4, NOTE_A4,4,
  REST,8, NOTE_E4,8, NOTE_B4,2,
  NOTE_F4,4, NOTE_C5,4, NOTE_C5,4,
  REST,8, NOTE_E4,8, NOTE_B4,2,
  NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,
  
  NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,
  NOTE_E5,-4, NOTE_F5,8, NOTE_E5,8, NOTE_E5,8,
  NOTE_E5,8, NOTE_C5,8, NOTE_A4,2,
  NOTE_A4,4, NOTE_D4,4, NOTE_F4,8, NOTE_G4,8,
  NOTE_A4,-2,
  NOTE_A4,4, NOTE_D4,4, NOTE_F4,8, NOTE_G4,8,
  NOTE_E4,-2,
  NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,
  NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,

  NOTE_E5,-4, NOTE_F5,8, NOTE_E5,8, NOTE_E5,8,
  NOTE_E5,8, NOTE_C5,8, NOTE_A4,2,
  NOTE_A4,4, NOTE_D4,4, NOTE_F4,8, NOTE_G4,8,
  NOTE_A4,2, NOTE_A4,4,
  NOTE_D4,1,
};

#endif /* MII_H */