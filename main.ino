#include "pitches.h"

// INPUTS
const int BTN_C = 2;
const int BTN_D = 3;
const int BTN_E = 4;
const int BTN_F = 5;
const int BTN_G = 6;
const int BTN_A = 7;
const int BTN_B = 8;

// OUTPUTS
const int SPKR = 9;
const int LED1 = 10;
const int LED2 = 11;
const int LED3 = 12;

// KEYBOARD ARRAY
int KYBRD[] = {
  BTN_C, BTN_D, BTN_E, BTN_F, BTN_G, BTN_A, BTN_B
};

// TONE ARRAY
int NOTES[] = {
  NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3, // SCALE 1
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, // SCALE 2
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5,  // SCALE 3
};

int val_key = 0; // KYBRD BUTTON READ VALUE
int val_oct_L = 0; // OCTAVE LEFT BUTTON READ VALUE
int val_oct_R = 0; // OCTAVE RIGHT BUTTON READ VALUE
int oct = 7; // OCTAVE SWITCH COEFFICIENT

void setup()
{
  // INPUTS
  pinMode(A0, INPUT); // LEFT BUTTON
  pinMode(A1, INPUT); // RIGHT BUTTON
  pinMode(BTN_C, INPUT); // DO
  pinMode(BTN_D, INPUT); // RE
  pinMode(BTN_E, INPUT); // MI
  pinMode(BTN_F, INPUT); // FA
  pinMode(BTN_G, INPUT); // SOL
  pinMode(BTN_A, INPUT); // LA
  pinMode(BTN_B, INPUT); // SI
  
  // OUTPUTS
  pinMode(SPKR, OUTPUT); // PIEZO SPEAKER
  pinMode(LED1, OUTPUT); // LED 1
  pinMode(LED2, OUTPUT); // LED 2
  pinMode(LED3, OUTPUT); // LED 3
  
  // REMOVE GARBAGE FROM KEYBOARD BUTTONS
  for(int i=0; i<7; i++) {
    digitalWrite(KYBRD[i],LOW);
  }
  
  // REMOVE GARBAGE FROM OCTAVE BUTTONS
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  
  Serial.begin(9600);
}

void loop()
{
  // OCTAVE SWITCH READING
  val_oct_L = digitalRead(A0);
  val_oct_R = digitalRead(A1);
  
  // If the left button is pressed,
  // and octave is not close to minimums:
  if(val_oct_L == 1 && oct >= 7) {
    oct = oct-7;
    delay(200);
  }
  
  // If the right button is pressed,
  // and octave is not close to maximums:
  if(val_oct_R == 1 && oct <= 7) {
    oct = oct+7;
    delay(200);
  }
  // END OCTAVE SWITCH READING
  
  // SHOW USER WHICH MODE IS SELECTED
  switch(oct) {
    case 0:
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    break;
    
    case 7:
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    break;
    
    case 14:
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
  }
  // END USER MODE
   
  // KEYBOARD FEATURES
  for (int thisButton=0; thisButton<7; thisButton++) {    
    val_key = digitalRead(KYBRD[thisButton]);
  // if the button is pressed:
    if (val_key == 1) {
      // play the note corresponding to this button:
      tone(SPKR, NOTES[thisButton+oct], 200);
    }
  }
  // END KEYBOARD FEATURES
}
