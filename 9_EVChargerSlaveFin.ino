//-----------------------Modbus pin-------------------------
#define SLAVE_EN  2
String Input;
//-----------------------LCD Show---------------------------
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//------------------------Switch----------------------------
#define SWITCH1   5 //SW Send data Plug in
#define SWITCH2   6 //SW send data Plug out
#define SWITCH3   7 //SW send data full
#define SWITCH4   12 //SW Change EVcharger Up
#define SWITCH5   13 //SW Change EVcharger Down
//-------------------------LED------------------------------
#define LED1    8  //LED send data Plug in
#define LED2    9  //LED send data Plug out
#define LED3    10  //LED send data full
#define LED4    11  //LED receive data
//-----------------------Variable----------------------------
int LCD = 0;
int EV = 1;
float PW = 20;
float PO = 0;
int F = 0;
float Ef = 100;

void setup() {
//--------------------------Set Serial-------------------------
  Serial.begin(9600);  
//---------------------------LCD setup-------------------------
  lcd.init();
  lcd.backlight();
//--------------------------Switch setup-----------------------
  pinMode(SWITCH1 , INPUT_PULLUP);                       
  pinMode(SWITCH2 , INPUT_PULLUP);
  pinMode(SWITCH3 , INPUT_PULLUP);
  pinMode(SWITCH4 , INPUT_PULLUP);                       
  pinMode(SWITCH5 , INPUT_PULLUP);
//---------------------------LED setup-------------------------
  digitalWrite(LED1 , LOW); 
  digitalWrite(LED2 , LOW);
  digitalWrite(LED3 , LOW); 
  digitalWrite(LED4 , LOW);
//-----------------------Modbus pin setup----------------------
  pinMode(SLAVE_EN , OUTPUT);     
  digitalWrite(SLAVE_EN , LOW); 
}

void loop() {
//-----------------------LCD Show to select Charger---------------------------
  if(digitalRead(SWITCH4) == 0) //Charger Up
  { 
    if(LCD == 0) {EV = 2; LCD = 1; PW = ((25*Ef)/100); delay (100); }
    else if(LCD == 1) {EV = 3; LCD = 2; PW = ((30*Ef)/100); delay (100);}
    else if(LCD == 2) {EV = 4; LCD = 3; PW = ((27*Ef)/100); delay (100);}
    else if(LCD == 3) {EV = 5; LCD = 4; PW = ((33*Ef)/100); delay (100);}
    else if(LCD == 4) {EV = 6; LCD = 5; PW = ((15*Ef)/100); delay (100);}
    else if(LCD == 5) {EV = 1; LCD = 0; PW = ((20*Ef)/100); delay (100);}
    Serial.print("Charger ");
    Serial.print(EV);
    Serial.print("\n");
    Serial.print("Power ");
    Serial.print(PW);
    Serial.print(" kW\n");
  }
  if(digitalRead(SWITCH5) == 0) //Charger Down
  { 
    if(LCD == 0) {EV = 6; LCD = 5; PW = ((15*Ef)/100); delay (100); }
    else if(LCD == 1) {EV = 1; LCD = 0; PW = ((20*Ef)/100); delay (100);}
    else if(LCD == 2) {EV = 2; LCD = 1; PW = ((25*Ef)/100); delay (100);}
    else if(LCD == 3) {EV = 3; LCD = 2; PW = ((30*Ef)/100); delay (100);}
    else if(LCD == 4) {EV = 4; LCD = 3; PW = ((27*Ef)/100); delay (100);}
    else if(LCD == 5) {EV = 5; LCD = 4; PW = ((33*Ef)/100); delay (100);}
    Serial.print("Charger ");
    Serial.print(EV);
    Serial.print("\n");
    Serial.print("Power ");
    Serial.print(PW);
    Serial.print(" kW\n");
  }

//--------------------Send the data of Charger Plug in--------------------- 
  if(digitalRead(SWITCH1) == 0)
  {
    Serial.print("EVCharger = ");
    delay(50); 
    digitalWrite(SLAVE_EN , HIGH);       
    delay(100);                           
    Serial.print(EV);                   
    Serial.flush();                     
    digitalWrite(SLAVE_EN , LOW); 
    delay(1000);
    Serial.print("\nPower = ");
    delay(50);                              
    digitalWrite(SLAVE_EN , HIGH);       
    delay(50);                           
    Serial.print(PW*1000);                   
    Serial.flush();                     
    digitalWrite(SLAVE_EN , LOW);      
    Serial.print(" W\n"); 

    digitalWrite( LED1 , HIGH);    // LED ON
    delay(1000);
    digitalWrite( LED1 , LOW);     // LED OFF
  } 
//--------------------Send the data of Charger Plug out--------------------- 
  if(digitalRead(SWITCH2) == 0)
  {
    Serial.print("EVCharger = ");
    delay(50); 
    digitalWrite(SLAVE_EN , HIGH);       
    delay(50);                           
    Serial.print(EV);                   
    Serial.flush();                     
    digitalWrite(SLAVE_EN , LOW); 
    delay(1000);
    Serial.print("\nPower = ");
    delay(50);                              
    digitalWrite(SLAVE_EN , HIGH);       
    delay(50);                           
    Serial.print(PO);                   
    Serial.flush();                     
    digitalWrite(SLAVE_EN , LOW);      
    Serial.print(" kW Plug Out!\n"); 

    digitalWrite( LED2 , HIGH);    // LED ON
    delay(1000);
    digitalWrite( LED2 , LOW);     // LED OFF
  } 
//--------------------Send the data of Charger Full Charge--------------------- 
  if(digitalRead(SWITCH3) == 0)
  {
    delay(50);  
    digitalWrite(SLAVE_EN , HIGH);       
    delay(50);                           
    Serial.print(EV);                   
    Serial.flush();                     
    digitalWrite(SLAVE_EN , LOW); 
    delay(1000);
    Serial.print("Power = ");
    delay(50);                            
    digitalWrite(SLAVE_EN , HIGH); 
    delay(50);
    Serial.print(PO);
    Serial.flush(); 
    digitalWrite(SLAVE_EN , LOW);
    Serial.print(" = Full\n"); 

    digitalWrite( LED3 , HIGH);    // LED ON
    delay(1000);
    digitalWrite( LED3 , LOW);     // LED OFF
  }
  while(Serial.available())                     // If serial data is available then enter into while loop
  {
    Input = Serial.readStringUntil('*');     // Receive Serial data in Variable 
    Ef = Input.toInt();
    Ef = Ef/1000;
    Serial.print(Ef);
    Serial.print(" %\n");

    digitalWrite(LED4 , HIGH);    // LED ON
    delay(1000);
    digitalWrite(LED4 , LOW);     // LED OFF
  }

//-----------------------LCD Display---------------------------
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("EV Charger");
  lcd.setCursor(11,0);
  lcd.print(EV);
  lcd.setCursor(2,1);
  lcd.print("Power ");
  lcd.print(PW);
  lcd.print(" kW");
  delay (60);
  }
