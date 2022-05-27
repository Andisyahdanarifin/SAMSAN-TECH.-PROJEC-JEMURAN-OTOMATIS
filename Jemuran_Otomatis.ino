#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define LIMIT_LDR 200 // nilai batas intensitas cahaya pada LDR
#define LIMIT_RAIN 1000 // nilai batas air pada sensor
#define LIMIT_MOTOR 100 // nilai batas waktu putaran motor
#define LIMIT_SPEED 100 // nilai kecepatan motor

byte hold1 = 0; // tahan putara motor jemur
byte hold2 = 0; // tahan putara motor balik
byte Stop = 0;

const byte en1 = 2;
const byte en2 = 3;
const byte speedMotor = 9;


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2); 

void jemur();
void kembali();
void berhenti();

void setup()
{
  pinMode(A0, INPUT_PULLUP); // set sebagai output
  pinMode(A1, INPUT_PULLUP); // set sebagai output
lcd.begin();
  lcd.backlight();
  lcd.print("Jemuran Otomatis");
  delay(2000);
  lcd.clear();
}

void loop()
{
  int s_ldr = analogRead(A0);
  int s_rain = analogRead(A1);
  lcd.clear();
  /*lcd.setCursor(0,0);
  lcd.print("L: ");
  lcd.print(s_ldr);
  lcd.print("  R: ");
  lcd.print(s_rain);
 */  if ( s_ldr < LIMIT_LDR && s_rain > LIMIT_RAIN){ // TERANG ATAU TIDAK HUJAN
    lcd.setCursor(0,1);
    lcd.print("Jemur Pakaian");
     if ( hold1 == 0){
        lcd.setCursor(0,0);
        lcd.print("Motor Jalan");
        jemur(); 
     }
     if ( Stop == 1){
        lcd.setCursor(0,0);
        lcd.print("Motor Stop");
     }
     
  }
  if ( s_ldr > LIMIT_LDR || s_rain < LIMIT_RAIN){ // GELAP ATAU HUJAN
    lcd.setCursor(0,1);
    lcd.print("Pakaian Kembali");
    if ( hold2 == 0){
        lcd.setCursor(0,0);
        lcd.print("Motor Jalan");
        kembali(); 
     }
     if ( Stop == 1){
        lcd.setCursor(0,0);
        lcd.print("Motor Stop");
     }
  }

  delay(250);
  
}


void jemur(){
  Stop = 0;
  for ( int i = 0; i < LIMIT_MOTOR; i++){
    analogWrite(speedMotor, LIMIT_SPEED);
    digitalWrite(en1, LOW);
    digitalWrite(en2, HIGH);
    delay(100);
    if ( i == LIMIT_MOTOR - 1){
      hold1 = 1;
      hold2 = 0;
      berhenti();
    }
  }
}

void kembali(){
  Stop = 0;
   for ( int i = 0; i < LIMIT_MOTOR; i++){
    analogWrite(speedMotor, LIMIT_SPEED);
    digitalWrite(en1, HIGH);
    digitalWrite(en2, LOW);
    delay(100);
     if ( i == LIMIT_MOTOR - 1){
      hold1 = 0;
      hold2 = 1;
      berhenti();
    }
  }
}

void berhenti(){
    analogWrite(speedMotor, 0);
    digitalWrite(en1, LOW);
    digitalWrite(en2, HIGH);
    Stop = 1;
    delay(100);
}
