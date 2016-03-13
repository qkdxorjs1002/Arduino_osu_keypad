/*By Novang*/
#include <Keyboard.h>

#define BAUDRATE    115200  // baudrate for serial communication
#define KP_A        A0      // a key pin number
#define KP_X        A1      // x key pin number
#define KP_FN       A2      // fn key pin number
#define LP_A        9       // a led pin number
#define LP_X        10      // x led pin number
#define LP_FN       11      // fn led pin number
#define PROC_SPD    250       // processing speed (us)
#define LD          255     // led power (0-255)
#define LD_TM       1     // led minus count (0-255)

int V_A = 0;    // for multi-key input processing
int V_X = 0;    // for multi-key input processing
int V_FN = 0;   // for multi-key input processing
int TM_A = LD;    // fading tmp value
int TM_X = LD;    // fading tmp value
int TM_FN = LD;   // fading tmp value
int _ON_A = 0;    // for prevent unnecessory processing
int _ON_X = 0;    // for prevent unnecessory processing
int _ON_FN = 0;   // for prevent unnecessory processing

/* 
 * Init
*/
void setup() {
  Serial.begin(BAUDRATE);
  Serial.print("Arduino based osu keyboard. BY NOVANG! Welcome!\n");
  pinMode(KP_A,INPUT_PULLUP);     // define pinmode
  pinMode(KP_X,INPUT_PULLUP);
  pinMode(KP_FN,INPUT_PULLUP);
  pinMode(LP_A,OUTPUT);
  pinMode(LP_X,OUTPUT);
  pinMode(LP_FN,OUTPUT);
  digitalWrite(LP_A,LD);    // indicate start-up
  digitalWrite(LP_X,LD);
  digitalWrite(LP_FN,LD);
  delay(1000);
}

/* 
 * Debug
*/
void debug() {
  Serial.print("KEY: ");
  Serial.print(digitalRead(KP_A));
  Serial.print(" ");
  Serial.print(digitalRead(KP_X));
  Serial.print(" ");
  Serial.print(digitalRead(KP_FN));
  Serial.print("   ");
  Serial.print("LED: ");
  Serial.print(digitalRead(LP_A));
  Serial.print(" ");
  Serial.print(digitalRead(LP_X));
  Serial.print(" ");
  Serial.print(digitalRead(LP_FN));
  Serial.print("\n");
}

/*
 * Read pin connection value
*/
void READPIN() {
  V_FN = digitalRead(KP_FN);
  V_A = digitalRead(KP_A);
  V_X = digitalRead(KP_X);
}

/*
 * Loop
*/
void loop() {
  delayMicroseconds(PROC_SPD);
  READPIN();
  
  if(V_FN == 0) {
    Keyboard.press('`');    // fn(`) key (replay)
    _ON_FN = 1;
    analogWrite(LP_FN,LD);
    TM_FN = LD;
  }else if(V_FN == 1) {
    if(_ON_FN == 1) {
      Keyboard.release('`');
      _ON_FN = 0;
    }
    if(TM_FN > 0) {
      TM_FN = TM_FN - LD_TM;
      analogWrite(LP_FN, TM_FN);
    }
  }
  
  if(V_A == 0) {
    Keyboard.press('a');    // a key (a)
    _ON_A = 1;
    analogWrite(LP_A,LD);
    TM_A = LD;
  }else if(V_A == 1) {
    if(_ON_A == 1) {
      Keyboard.release('a');
      _ON_A = 0;
    }
    if(TM_A > 0) {
      TM_A = TM_A - LD_TM;
      analogWrite(LP_A, TM_A);
    }
  }

  if(V_X == 0) {
    Keyboard.press('x');    // x key (x)
    _ON_X = 1;
    analogWrite(LP_X,LD);
    TM_X = LD;
  }else if(V_X == 1) {
    if(_ON_X == 1) {
      Keyboard.release('x');
      _ON_X = 0;
    }
    if(TM_X > 0) {
      TM_X = TM_X - LD_TM;
      analogWrite(LP_X, TM_X);
    }
  }
}
