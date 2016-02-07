/*written by novang*/
#include <Keyboard.h>
#include <EEPROM.h>

#define BAUDRATE    115200    // Baudrate for serial communication
#define KEYPIN_A    A0        // A Key pin number
#define KEYPIN_X    A1        // X Key pin number
#define KEYPIN_FN   A2        // FN Key pin number
#define LEDPIN_A    9         // A LED pin number
#define LEDPIN_X    10        // X LED pin number
#define LEDPIN_FN   11        // FN LED pin number
#define PROCESS_SPD 1         // Process speed (ms)

int LED_DV = 127;   // Default LED Bri. value
int VALUE_A = 0;    // For Multi-key Input processing
int VALUE_X = 0;    // For Multi-key Input processing
int VALUE_FN = 0;   // For Multi-key Input processing

/* 
 * Init
 */
void setup() {
  Serial.begin(BAUDRATE);
  Serial.print("Arduino based osu keyboard. BY NOVANG! Welcome!\n");
  pinMode(KEYPIN_A,INPUT_PULLUP);
  pinMode(KEYPIN_X,INPUT_PULLUP);
  pinMode(KEYPIN_FN,INPUT_PULLUP);
  pinMode(LEDPIN_A,OUTPUT);
  pinMode(LEDPIN_X,OUTPUT);
  pinMode(LEDPIN_FN,OUTPUT);
  analogWrite(LEDPIN_A,LED_DV);
  analogWrite(LEDPIN_X,LED_DV);
  analogWrite(LEDPIN_FN,LED_DV);
  LED_DV = EEPROM.read(1);    // Read saved LED Bri. value from EEPROM
  delay(1000);
  analogWrite(LEDPIN_A,0);
  analogWrite(LEDPIN_X,0);
  analogWrite(LEDPIN_FN,0);
  Keyboard.begin();
}

/* 
 * Debug
*/
void debug() {
  Serial.print("KEY: ");
  Serial.print(digitalRead(KEYPIN_A));
  Serial.print(" ");
  Serial.print(digitalRead(KEYPIN_X));
  Serial.print(" ");
  Serial.print(digitalRead(KEYPIN_FN));
  Serial.print("   ");
  Serial.print("LED: ");
  Serial.print(LED_DV);
  Serial.print(" ");
  Serial.print(digitalRead(LEDPIN_A));
  Serial.print(" ");
  Serial.print(digitalRead(LEDPIN_X));
  Serial.print(" ");
  Serial.print(digitalRead(LEDPIN_FN));
  Serial.print("\n");
}

/*
 * Loop
 */
void loop() {
  //debug();
  
  // For Limited response speed
  delay(PROCESS_SPD);
  
  //For Multi-key Input processing
  VALUE_A = digitalRead(KEYPIN_A);
  VALUE_X = digitalRead(KEYPIN_X);
  VALUE_FN = digitalRead(KEYPIN_FN);
  
  // FN key: FN+A(LED Bri. set), FN+X(Save Bri. value to EEPROM)
  if(VALUE_FN == 0){
    analogWrite(LEDPIN_FN,LED_DV);
    
    // FN+A(LED Bri. set)
    if(VALUE_A == 0){
      analogWrite(LEDPIN_A,LED_DV);
      if(VALUE_X == 0){
        delay(3000);
        analogWrite(LEDPIN_X,LED_DV);
        if(LED_DV == EEPROM.read(1)){
          // Blank
        }else{
          analogWrite(LEDPIN_A,0);
          analogWrite(LEDPIN_X,0);
          analogWrite(LEDPIN_FN,LED_DV);
          EEPROM.write(1, LED_DV);
          delay(2000);
          analogWrite(LEDPIN_A,LED_DV);
          analogWrite(LEDPIN_X,LED_DV);
          analogWrite(LEDPIN_FN,LED_DV);
        }
      }
      if(LED_DV == 0){
        LED_DV = 51;
      }else if(LED_DV == 51){
        LED_DV = 102;
      }else if(LED_DV == 102){
        LED_DV = 153;
      }else if(LED_DV == 153){
        LED_DV = 204;
      }else if(LED_DV == 204){
        LED_DV = 255;
      }else if(LED_DV == 255){
        LED_DV = 0;
      }
      analogWrite(LEDPIN_A,LED_DV);
      analogWrite(LEDPIN_FN,LED_DV);
      delay(500);
    }
    
    // FN+X(Save Bri. value to EEPROM)
    if(VALUE_X == 0){
        delay(3000);
        analogWrite(LEDPIN_X,LED_DV);
        if(LED_DV == EEPROM.read(1)){
          // Blank
        }else{
          analogWrite(LEDPIN_A,0);
          analogWrite(LEDPIN_X,0);
          analogWrite(LEDPIN_FN,LED_DV);
          EEPROM.write(1, LED_DV);
          delay(2000);
          analogWrite(LEDPIN_A,LED_DV);
          analogWrite(LEDPIN_X,LED_DV);
          analogWrite(LEDPIN_FN,LED_DV);
        }
      }
  }else if(VALUE_FN == 1){
    analogWrite(LEDPIN_FN,0);
  }
  
  // A Key
  if(VALUE_A == 0){
    Keyboard.press('a');
    analogWrite(LEDPIN_A,LED_DV);
  }else if(VALUE_A == 1){
    Keyboard.release('a');
    analogWrite(LEDPIN_A,0);
  }
  
  // X Key
  if(VALUE_X == 0){
    Keyboard.press('x');
    analogWrite(LEDPIN_X,LED_DV);
  }else if(VALUE_X == 1) {
    Keyboard.release('x');
    analogWrite(LEDPIN_X,0);
  }
}
