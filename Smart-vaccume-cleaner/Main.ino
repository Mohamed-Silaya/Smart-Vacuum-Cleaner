#include <IRremote.h>

//Millis
int period1 = 375;//45 degrees
int period2 = 500;//60 degrees
int period3 = 750;//90 degrees 
int period4 = 1000;//120 degrees
int period5 = 1500;//180 degrees
unsigned long time_now = 0;

//H-bridge
#define in1 14//set pin 14:17 for H-bridge
#define in2 15
#define in3 16
#define in4 17
#define enA 19
#define enB 20

//Front sweepers & Suction
#define relayPin 18

//LED
#define StopButton 52//set pin 20 for Stop Button 
#define StartButton 53//set pin 20 for Start Button
int buttonstate_Start = 0;
int buttonstate_Stop = 0;

//IR Sensor
#define IRSensor 0 // connect ir sensor to arduino pin 0
int distance = 0;

//IR Receiver
#define IRReceiver 1 //connect IR Receiver to arduino pin 1
IRrecv irrecv(IRReceiver); 
decode_results results; // decode_results class is defined in IRremote.h
double Rval = 0;

//LimitSwitch
#define Lswitch1 2//set pins 2:5 for limit switches
#define Lswitch2 3
#define Lswitch3 4
#define Lswitch4 5

//Battery Level Indication
int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R1 = 100000;
float R2 = 10000;
int value = 0;


void setup() {
  Serial.begin(9600);
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  
  pinMode(Lswitch1, INPUT);
  pinMode(Lswitch2, INPUT);
  pinMode(Lswitch3, INPUT);
  pinMode(Lswitch4, INPUT);
  
  pinMode(relayPin, OUTPUT);
  
  pinMode(IRSensor, INPUT); // sensor pin INPUT
  
  pinMode(IRReceiver, INPUT); // Receiver pin INPUT
  
  pinMode(StopButton, INPUT);
  pinMode(StartButton, INPUT);
  
}

void loop() {
  time_now = millis ();
  
  buttonstate_Start = digitalRead(StartButton);
  buttonstate_Stop = digitalRead(StopButton);
  
  if (buttonstate_Start == LOW){
    WAKE_UP ();
  }

  if (buttonstate_Start == HIGH){
    Sleep ();
  }

  //IRSENSOR
  int statusSensor = digitalRead (IRSensor);
  distance = analogRead(IRSensor);
    if (distance > 8);
    {
      Stop ();
      Right ();
      while (millis() <= time_now + period5){}
      Stop ();
      Forward ();
    }

    //IR Reveicer
    Rval = analogRead(IRReceiver);       // reads the value of the sharp sensor
    
  //LIMIT SWITCHES
  if (digitalRead(Lswitch1) == LOW)/*Left LS*/{
    Stop ();
    Right ();
    while (millis() <= time_now + period3){}
    Stop ();
    Forward ();
  }
  if (digitalRead(Lswitch2) == LOW)/*Front Left LS*/{
    Stop ();
    Right ();
    while (millis() <= time_now + period3){}
    Stop ();
    Forward ();
  }
  if (digitalRead(Lswitch3) == LOW)/*Front Right LS*/{
    Stop ();
    Left ();
    while (millis() <= time_now + period3){}
    Stop ();
    Forward ();
  }
  if (digitalRead(Lswitch4) == LOW)/*Right LS*/{
    Stop ();
    Left ();
    while (millis() <= time_now + period3){}
    Stop ();
    Forward ();
  }


  //BATTERY LEVEL INDICATION
  /*if(vin>40%) {//must be adjusted
    LEDGR_Start();
    }*/

    
   if(vin<11.37) {//must be adjusted
     GO_HOME ();
    }
}


void Forward (){
  while (millis() <= time_now + period2){}
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enA, 150);
  analogWrite(enB, 150);
}

void Backward (){
  while (millis() <= time_now + period2){}
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(enA, 150);
  analogWrite(enB, 150);
}

void Right (){
  while (millis() <= time_now + period2){}
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(enA, 150);
  analogWrite(enB, 150);
}

void Left (){
  while (millis() <= time_now + period2){}
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enA, 150);
  analogWrite(enB, 150);
}

void Stop (){
  while (millis() <= time_now + period2){}
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  while (millis() <= time_now + period2){}
}

void SS_ON (){
  while (millis() <= time_now + period2){}
  digitalWrite(relayPin,HIGH);
}

void SS_OFF (){
  while (millis() <= time_now + period2){}
  digitalWrite(relayPin,LOW);
}

/*float Battery_Indication (){
  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024;
  vin = vout / (R2/(R1+R2));
}

/*void LEDGR_Start {
  digitalWrite(LED_GR,High);
}*/

/*void LEDR_Stop () {
  digitalWrite(LED_R,HIGH);
}*/

void WAKE_UP (){
    Forward ();
}

void Sleep (){
    GO_HOME ();
}

void GO_HOME () {
  //irrecv.enableIRIn(); // Start the receiver
  Stop ();
  /*SS_OFF ();
  while (Rval == 0){
      Right ();
      Reverse ();
      Rval = analogRead(IRReceiver);       // reads the value of the sharp sensor
    }
    if (Rval > 0){
      ZIGZAG ();
    }*/
}

/*void Reverse () {
  if (millis() > (time_now + period5)){
    Left ();
  }
}

void ZIGZAG () {
  while (vin =! 12.75){
    Right ();
    while (millis() <= time_now + period1){}
    Stop ();
    Left ();
    while (millis() <= time_now + period1){}
    Stop ();
    Charge ();
  }
}

void Charge (){
  if ( vin = 12.6 ){
    delay (3600000);
  }
}*/
