#define MASTER_EN   14                 // connected to RS485 Enable pin
#define SWITCH 0                // Declare LED pin
int b;
String recInput;

void setup() {
  pinMode(D0, OUTPUT);
  pinMode(SWITCH , INPUT_PULLUP);     // Declare LED pin as output
  pinMode(MASTER_EN , OUTPUT);        // Declare Enable pin as output
  Serial.begin(9600);                 // set serial communication baudrate 
  digitalWrite(MASTER_EN , LOW);      // Make Enable pin low, Receiving mode ON 
}
 
void loop() {
  //MASTER send the data to slave
  if(digitalRead(SWITCH) == 0)
  { 
    Serial.print("Balance to "); 
    delay(100);                       // Debouncing for switch
    digitalWrite(MASTER_EN , HIGH);     // Make Enable pin high to send Data
    delay(5);                          // required minimum delay of 5ms
    Serial.print(80);               // Send String serially, End String with * 
    Serial.flush();                     // wait for transmission of data
    digitalWrite(MASTER_EN , LOW);      // Receiving mode ON
    Serial.print(" %\n"); 
    digitalWrite(D0 ,HIGH); 
    delay(1000);
    digitalWrite(D0 ,LOW); 
  }

  //MASTER receive the data to slave
  while(Serial.available())                     // If serial data is available then enter into while loop
  {
    recInput = Serial.readStringUntil('*');     // Receive Serial data in Variable 
    b = recInput.toInt();
    if(b == 20)             // Compare Data
      {
      digitalWrite(D0 ,HIGH); 
      delay(1000);
      digitalWrite(D0 ,LOW);
      Serial.print("Plug in\n");
      Serial.print("Power  ");  
      Serial.print(b);
      Serial.print("  kW\n");
      } 
    else
      {
      Serial.print("Plug out\n");
      Serial.print("OK !");
      Serial.print("\n");
      }
  }
}

