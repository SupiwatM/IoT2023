#define SLAVE_EN  2
#define SWITCH1   5
#define SWITCH2   7 
#define LED1    6
#define LED2    8
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int EV1 = 20;
int EV2 = 0;  
int R = 100 ;   
String recInput;                                // Variable to store Receive string 
 
void setup() {  
  lcd.init();
  lcd.backlight();
  pinMode(LED1 , OUTPUT);
  pinMode(LED2 , OUTPUT);
  pinMode(SWITCH1 , INPUT_PULLUP);                        // Declare LED pin as output
  pinMode(SWITCH2 , INPUT_PULLUP); 
  pinMode(SLAVE_EN , OUTPUT);                   // Declare Enable pin as output
  Serial.begin(9600);                           // set serial communication baudrate 
  digitalWrite(SLAVE_EN , LOW);                 // Make Enable pin low, Receiving mode ON 
  digitalWrite( LED1 , LOW); 
  digitalWrite( LED2 , LOW); 
}
 
void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("EV Charger");
  lcd.setCursor(4,1);
  lcd.print("Total ");
  lcd.print(recInput);
  lcd.print(" kW");
  delay (60);
  if(digitalRead(SWITCH1) == 0)
  {
    Serial.print("Power = ");
    delay(100);                        // Debouncing for switch
    digitalWrite(SLAVE_EN , HIGH);     // Make Enable pin high to send Data
    delay(5);                           // required minimum delay of 5ms
    Serial.print((EV1*R)/100);     // Send String serially, End String with *
    Serial.flush();                     // wait for transmission of data
    digitalWrite(SLAVE_EN , LOW);      // Receiving mode ON
    Serial.print(" kW\n"); 
    digitalWrite( LED1 , HIGH);    // LED ON
    delay(1000);
    digitalWrite( LED1 , LOW);     // LED OFF
  } 
    if(digitalRead(SWITCH2) == 0)
  {
    delay(100);                        // Debouncing for switch
    digitalWrite(SLAVE_EN , HIGH);     // Make Enable pin high to send Data
    delay(5);                           // required minimum delay of 5ms
    Serial.print(EV2);     // Send String serially, End String with *
    Serial.print(" kW\n"); 
    Serial.flush();                     // wait for transmission of data
    digitalWrite(SLAVE_EN , LOW);      // Receiving mode ON
    digitalWrite( LED2 , HIGH);    // LED ON
    delay(1000);
    digitalWrite( LED2 , LOW);     // LED OFF
  }

  while(Serial.available())                     // If serial data is available then enter into while loop
  {
    recInput = Serial.readStringUntil('*');     // Receive Serial data in Variable
    Serial.print("Balance to "); 
    Serial.print(recInput);
    Serial.print("  %\n"); 
    R = recInput.toInt();                     // Print Data
    Serial.print("Power = ");
    Serial.print((EV1*R)/100);     // Send String serially, End String with *
    Serial.print("\n"); 
    //if(R == 125531)             // Compare Data
    // {
      digitalWrite( (LED1,LED2) , HIGH);    // LED ON
      delay(1000);
      digitalWrite( (LED1,LED2) , LOW);     // LED OFF
    // }
  }
}