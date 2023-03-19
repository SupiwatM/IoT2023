#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int Analog_pin = A0;
int count;
int Enable_pin = 4;  
void setup()
{
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);            
  pinMode(Enable_pin, OUTPUT);
  pinMode(Analog_pin,INPUT); 
  delay(10); 

}

void loop() 
{
lcd.clear();
int ADC_Value = analogRead(Analog_pin);
count++;  
 lcd.setCursor(0,0);
 lcd.print("EV Charger");
 lcd.setCursor(4,1);
 lcd.print("Total ");
 lcd.print(ADC_Value);
 lcd.print(" kW");
 delay(1000);
}
