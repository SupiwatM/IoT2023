#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define SWITCH3   12
#define SWITCH4   13 
int LCD = 0;
int EV = 1;
int PW = 20;
void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(SWITCH3 , INPUT_PULLUP);                        // Declare LED pin as output
  pinMode(SWITCH4 , INPUT_PULLUP);
}

void loop() {
  if(digitalRead(SWITCH3) == 0)
  { 
    if(LCD == 0) {EV = 2; LCD = 1; PW = 25; delay (100); }
    else if(LCD == 1) {EV = 3; LCD = 2; PW = 30; delay (100);}
    else if(LCD == 2) {EV = 4; LCD = 3; PW = 20; delay (100);}
    else if(LCD == 3) {EV = 5; LCD = 4; PW = 32; delay (100);}
    else if(LCD == 4) {EV = 6; LCD = 5; PW = 15; delay (100);}
    else if(LCD == 5) {EV = 1; LCD = 0; PW = 20; delay (100);}
  }
  if(digitalRead(SWITCH4) == 0)
  { 
    if(LCD == 0) {EV = 6; LCD = 5; PW = 15; delay (100); }
    else if(LCD == 1) {EV = 1; LCD = 0; PW = 20; delay (100);}
    else if(LCD == 2) {EV = 2; LCD = 1; PW = 25; delay (100);}
    else if(LCD == 3) {EV = 3; LCD = 2; PW = 30; delay (100);}
    else if(LCD == 4) {EV = 4; LCD = 3; PW = 20; delay (100);}
    else if(LCD == 5) {EV = 5; LCD = 4; PW = 32; delay (100);}
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("EV Charger");
  lcd.setCursor(11,0);
  lcd.print(EV);
  lcd.setCursor(4,1);
  lcd.print("Power ");
  lcd.print(PW);
  lcd.print(" kW");
  delay (60);
}
