#define MASTER_EN   14                 // connected to RS485 Enable pin
#define SWITCH 0                // Declare LED pin

#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <TridentTD_LineNotify.h>
#define SSID        "Mos_2.4GHz"   // ชื่อ Wifi
#define PASSWORD    "0853699454"   // รหัส Wifi
#define LINE_TOKEN  "zZP5ePz6pDVy21UJnaeuk6p6gnfY5JlW0FRnlC3TKFV"   // TOKEN

int EV,PR,PW1,PW2,PW3,PW4,PW5,PW6;
String Input;
float PWT = 0;
float Tr = 100;
float Ef = 0;
float Efs = 0; 
float Efb = 0.8;
void setup() {
  pinMode(D0, OUTPUT);
  pinMode(SWITCH , INPUT_PULLUP);     // Declare LED pin as output
  pinMode(MASTER_EN , OUTPUT);        // Declare Enable pin as output
  Serial.begin(9600);                 // set serial communication baudrate 
  digitalWrite(MASTER_EN , LOW);      // Make Enable pin low, Receiving mode ON
  Serial.begin(9600);
  Serial.println(LINE.getVersion());
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting ",  SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
//-----------------------Recieve the data from EV Charger---------------   
  while(Serial.available())                     // If serial data is available then enter into while loop
  {
    Input = Serial.readStringUntil('*');     // Receive Serial data in Variable 
    EV = Input.toInt();
    if(EV == 1)
    { Serial.print("Charger ");
      Serial.print(EV);
      Input = Serial.readStringUntil('*');
      PR = Input.toInt();
      Serial.print(" Plug in\n");
      Serial.print("Power  ");  
      Serial.print(PR);
      Serial.print("  kW\n");
      digitalWrite(D0 ,HIGH); 
      delay(1000);
      digitalWrite(D0 ,LOW);
       PW1=PR;
    } 
    else if(EV == 2)
    { Serial.print("Charger ");
      Serial.print(EV);
      Input = Serial.readStringUntil('*');
      PR = Input.toInt();
      Serial.print(" Plug in\n");
      Serial.print("Power  ");  
      Serial.print(PR);
      Serial.print("  kW\n");
      digitalWrite(D0 ,HIGH); 
      delay(1000);
      digitalWrite(D0 ,LOW);
      PW2=PR;
    }
    else if(EV == 3)
    { Serial.print("Charger ");
      Serial.print(EV);
      Input = Serial.readStringUntil('*');
      PR = Input.toInt();
      Serial.print(" Plug in\n");
      Serial.print("Power  ");  
      Serial.print(PR);
      Serial.print("  kW\n");
      digitalWrite(D0 ,HIGH); 
      delay(1000);
      digitalWrite(D0 ,LOW);
      PW3=PR;
    }
    else if(EV == 4)
    { Serial.print("Charger ");
      Serial.print(EV);
      Input = Serial.readStringUntil('*');
      PR = Input.toInt();
      Serial.print(" Plug in\n");
      Serial.print("Power  ");  
      Serial.print(PR);
      Serial.print("  kW\n");
      digitalWrite(D0 ,HIGH); 
      delay(1000);
      digitalWrite(D0 ,LOW);
      PW4=PR;
    }
    else if(EV == 5)
    { Serial.print("Charger ");
      Serial.print(EV);
      Input = Serial.readStringUntil('*');
      PR = Input.toInt();
      Serial.print(" Plug in\n");
      Serial.print("Power  ");  
      Serial.print(PR);
      Serial.print("  kW\n");
      digitalWrite(D0 ,HIGH); 
      delay(1000);
      digitalWrite(D0 ,LOW);
      PW5=PR;
    }
    else if(EV == 6)
    { Serial.print("Charger ");
      Serial.print(EV);
      Input = Serial.readStringUntil('*');
      PR = Input.toInt();
      Serial.print(" Plug in\n");
      Serial.print("Power  ");  
      Serial.print(PR);
      Serial.print("  kW\n");
      digitalWrite(D0 ,HIGH); 
      delay(1000);
      digitalWrite(D0 ,LOW);
      PW6=PR;
    }  
  // ------------------------------Set total Power------------------------
  PWT = PW1+PW2+PW3+PW4+PW5+PW6;
  Ef = PWT/Tr ;
  Efs = (Efb*Tr)/PWT;
  Serial.print(PWT); 
  Serial.print("\n");
  Serial.print(PW1); 
  Serial.print("\n");  
  Serial.print(PW2); 
  Serial.print("\n"); 
  Serial.print(PW3); 
  Serial.print("\n"); 
  Serial.print(PW4); 
  Serial.print("\n"); 
  Serial.print(PW5); 
  Serial.print("\n");
  Serial.print(PW6); 
  Serial.print("\n");
  Serial.print(Tr); 
  Serial.print("\n"); 
  Serial.print(Ef); 
  Serial.print("\n"); 
  Serial.print(Efb); 
  Serial.print("\n");   
  Serial.print(Efs); 
  Serial.print("\n");

  if(Ef >= Efb && PWT >= (Efb*Tr))
  {
      delay(50); 
      digitalWrite(MASTER_EN , HIGH);       
      delay(50);                           
      Serial.print(Efs*100);
      Serial.print("\n");                    
      Serial.flush();                     
      digitalWrite(MASTER_EN , LOW); 
      delay(50);
      digitalWrite(D0 ,HIGH); 
      delay(1000);
      digitalWrite(D0 ,LOW);

      LINE.setToken(LINE_TOKEN); 
      LINE.notify("Adjust charging power to "+String(Efs,3)+" %");
  }  
  }
}

