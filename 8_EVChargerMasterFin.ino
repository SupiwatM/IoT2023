#define MASTER_EN   14          // connected to RS485 Enable pin
#define SWITCH 0                // Declare LED pin

#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
//---------------------------Code Top--------------------------------
#include <PubSubClient.h> 
#include <ESP8266WebServer.h> 
const char* ssid = "Mos_2.4GHz" ;  
const char* password = "0853699454" ; 

const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "8316fea3-5b3e-4686-b02f-3fdf278c3af2"; 
const char* mqtt_username = "YxDqYsjA4F29VH4GNomWJHqKXhXi6zeK";
const char* mqtt_password = "8wiPAqxm_6*v_8NO_W1t_Pqrf_jz-Ldc";
//---------------------------Code Top--------------------------------

#include <TridentTD_LineNotify.h>
//#define SSID        "Mos_2.4GHz"   
//#define PASSWORD    "0853699454"   
#define LINE_TOKEN  "fPl3iitvwUzhsokqKXR3zDwle9PIadARm8G4m5hHg4s"   // TOKEN

int EV;
int T=0;
String Input;
float Tr = 100;
float Ef = 0;
float Efs = 1; 
float Efb = 0.8;
float PW1,PW2,PW3,PW4,PW5,PW6,PWT,PR;

//---------------------------Code Top--------------------------------
WiFiClient espClient;  
PubSubClient client(espClient);


#define ldr A0
/*float ADC_value = 0.0048828125;*/
char msg[150]; 

void reconnect() { 
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection…"); 
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("@msg/test2");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}
//---------------------------Code Top--------------------------------


void setup() {
  pinMode(D0, OUTPUT);
  pinMode(SWITCH , INPUT_PULLUP);     // Declare LED pin as output
  pinMode(MASTER_EN , OUTPUT);        // Declare Enable pin as output
  Serial.begin(9600);                 // set serial communication baudrate 
  digitalWrite(MASTER_EN , LOW);      // Make Enable pin low, Receiving mode ON
  Serial.println(LINE.getVersion());
//WiFi.begin(SSID, PASSWORD);
 //---------------------------Code Top--------------------------------
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  pinMode(ldr, INPUT);
  }
//---------------------------Code Top--------------------------------
/*
  Serial.printf("WiFi connecting ",  SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
}*/


void loop() {
//---------------------------Code Top--------------------------------
if (!client.connected()) { 
    reconnect();
  }
  client.loop();
//---------------------------Code Top--------------------------------

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
      Serial.print("  W\n");
      digitalWrite(D0 ,HIGH); 
      delay(1000);
      digitalWrite(D0 ,LOW);
      PW1=PR/1000;
    } 
    else if(EV == 2)
    { Serial.print("Charger ");
      Serial.print(EV);
      Input = Serial.readStringUntil('*');
      PR = Input.toInt();
      Serial.print(" Plug in\n");
      Serial.print("Power  ");  
      Serial.print(PR);
      Serial.print("  W\n");
      digitalWrite(D0 ,HIGH); 
      delay(1000);
      digitalWrite(D0 ,LOW);
      PW2=PR/1000;
    }
    else if(EV == 3)
    { Serial.print("Charger ");
      Serial.print(EV);
      Input = Serial.readStringUntil('*');
      PR = Input.toInt();
      Serial.print(" Plug in\n");
      Serial.print("Power  ");  
      Serial.print(PR);
      Serial.print("  W\n");
      digitalWrite(D0 ,HIGH); 
      delay(1000);
      digitalWrite(D0 ,LOW);
      PW3=PR/1000;
    }
    else if(EV == 4)
    { Serial.print("Charger ");
      Serial.print(EV);
      Input = Serial.readStringUntil('*');
      PR = Input.toInt();
      Serial.print(" Plug in\n");
      Serial.print("Power  ");  
      Serial.print(PR);
      Serial.print("  W\n");
      digitalWrite(D0 ,HIGH); 
      delay(1000);
      digitalWrite(D0 ,LOW);
      PW4=PR/1000;
    }
    else if(EV == 5)
    { Serial.print("Charger ");
      Serial.print(EV);
      Input = Serial.readStringUntil('*');
      PR = Input.toInt();
      Serial.print(" Plug in\n");
      Serial.print("Power  ");  
      Serial.print(PR);
      Serial.print("  W\n");
      digitalWrite(D0 ,HIGH); 
      delay(1000);
      digitalWrite(D0 ,LOW);
      PW5=PR/1000;
    }
    else if(EV == 6)
    { Serial.print("Charger ");
      Serial.print(EV);
      Input = Serial.readStringUntil('*');
      PR = Input.toInt();
      Serial.print(" Plug in\n");
      Serial.print("Power  ");  
      Serial.print(PR);
      Serial.print("  W\n");
      digitalWrite(D0 ,HIGH); 
      delay(1000);
      digitalWrite(D0 ,LOW);
      PW6=PR/1000;
    }
  PW1 = PW1/(Efs);
  PW2 = PW2/(Efs);
  PW3 = PW3/(Efs);
  PW4 = PW4/(Efs);
  PW5 = PW5/(Efs);
  PW6 = PW6/(Efs);
  PWT = PW1+PW2+PW3+PW4+PW5+PW6;
  Serial.print("PWTInitial = ");
  Serial.print(PWT);
  Serial.print("\n"); 
  if(PWT >= (Efb*Tr))
  {
    delay(50); 
    Efs = 1-((PWT-(Efb*Tr))/PWT); // % Balance
    PW1 = PW1*Efs;
    PW2 = PW2*Efs;
    PW3 = PW3*Efs;
    PW4 = PW4*Efs;
    PW5 = PW5*Efs;
    PW6 = PW6*Efs;
    Efs = Efs*1000;
    delay(200);  
    digitalWrite(MASTER_EN , HIGH);       
    delay(50);                           
    Serial.print(Efs*100);
    Serial.print("\n");                    
    Serial.flush();                     
    digitalWrite(MASTER_EN , LOW);
    Efs = Efs/1000; 
    delay(50);
    digitalWrite(D0 ,HIGH); 
    delay(1000);
    digitalWrite(D0 ,LOW);
    LINE.setToken(LINE_TOKEN); 
    LINE.notify("Adjust charging power to "+String(Efs*100,3)+" %");

  }
  // ------------------------------Set total Power------------------------
  PWT = PW1+PW2+PW3+PW4+PW5+PW6;
  Ef = PWT/Tr ;  
  if(Ef <= (Efb-0.01) && Efs != 1)
  { 
    Efs = 1;
    Efs = Efs*1000;
    delay(200);  
    digitalWrite(MASTER_EN , HIGH);       
    delay(50);                           
    Serial.print(Efs*100);
    Serial.print("\n");                    
    Serial.flush();                     
    digitalWrite(MASTER_EN , LOW);
    Efs = Efs/1000; 
    delay(50);
    digitalWrite(D0 ,HIGH); 
    delay(1000);
    digitalWrite(D0 ,LOW);
  }
  // ------------------------------Set total Power------------------------
  PWT = PW1+PW2+PW3+PW4+PW5+PW6;
  Ef = PWT/Tr ;
  Serial.print("PWT = ");  
  Serial.print(PWT); 
  Serial.print("\nPW1 = ");
  Serial.print(PW1); 
  Serial.print("\nPW2 = ");  
  Serial.print(PW2); 
  Serial.print("\nPW3 = "); 
  Serial.print(PW3); 
  Serial.print("\nPW4 = "); 
  Serial.print(PW4); 
  Serial.print("\nPW5 = "); 
  Serial.print(PW5); 
  Serial.print("\nPW6 = ");
  Serial.print(PW6); 
  Serial.print("\nTr = ");
  Serial.print(Tr); 
  Serial.print("\nEf = "); 
  Serial.print(Ef); 
  Serial.print("\nEfb = "); 
  Serial.print(Efb); 
  Serial.print("\nEfs = ");   
  Serial.print(Efs*100); 
  Serial.print("\n-------------------------------------------------\n");
  }
  delay(10);
  T=T+1;
//---------------------------Code Top--------------------------------
  if (T == 1000)
  {
    Serial.print(T);
    Serial.print("\n"); 
    String data = "{\"data\": {\"Power1\":" + String(PW1) + ",\"Power2\":" + String(PW2) + ",\"Power3\":" + String(PW3) + ",\"Power4\":" + String(PW4) + ",\"Power5\":" + String(PW5) + ",\"Power6\":" + String(PW6) + ",\"PowerT\":" + String(PWT) + "}}";
    Serial.println(data);
    data.toCharArray(msg, (data.length() + 1));
    client.publish("@shadow/data/update", msg);
    delay(100);
    T=0;
  }
}

