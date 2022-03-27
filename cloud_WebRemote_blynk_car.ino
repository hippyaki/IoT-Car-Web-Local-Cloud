#define BLYNK_TEMPLATE_ID           "TMPLxxxxxx"     //Template ID from https://blynk.cloud/dashboard > New Device > Device Info > Firmware Configuration
#define BLYNK_DEVICE_NAME           "Device"         //Device Name from https://blynk.cloud/dashboard > New Device > Device Info > Firmware Configuration
#define BLYNK_AUTH_TOKEN            "YourAuthToken"  //Auth Token from https://blynk.cloud/dashboard > New Device > Device Info > Firmware Configuration

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32_SSL.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

BlynkTimer timer;

int LeftA=13;  //D8
int LeftB=12;  //D7
int RightA=27; //D6
int RightB=14; //D5


void setup() {  

  pinMode(LeftA,OUTPUT);
  pinMode(LeftB,OUTPUT);
  pinMode(RightA,OUTPUT);
  pinMode(RightB,OUTPUT);
  pinMode(2, OUTPUT);

  Serial.begin(9600);
  
  Serial.println("WiFi connected");  
  
  Blynk.begin(auth, ssid, pass);
  digitalWrite(2,HIGH);

}

BLYNK_WRITE(V0)
{ 
  int pinValue = param.asInt();
  if (pinValue == 1){
    forward();
  }
  else{
    continue;
  }
  Serial.println("Forward");
}

BLYNK_WRITE(V1)
{  
  int pinValue = param.asInt();
  if (pinValue == 1){
    backward();
  }
  else{
    continue;
  }
  Serial.println("Backward");
}

BLYNK_WRITE(V2)
{  
  int pinValue = param.asInt();
  if (pinValue == 1){
    halt();
  }
  else{
    continue;
  }
  Serial.println("Stop");
}

BLYNK_WRITE(V3)
{  
  int pinValue = param.asInt();
  if (pinValue == 1){
    right();
  }
  else{
    continue;
  }
  Serial.println("Right");
}

BLYNK_WRITE(V4)
{  
  int pinValue = param.asInt();
  if (pinValue == 1){
    left();
  }
  else{
    continue;
  }  
  Serial.println("Left");
}

void loop(){
  Blynk.run();
}

void left() {
  digitalWrite(LeftA,LOW);
  digitalWrite(LeftB,HIGH);
  digitalWrite(RightA,HIGH);
  digitalWrite(RightB,LOW);
}

void right() {
  digitalWrite(LeftA,HIGH);
  digitalWrite(LeftB,LOW);
  digitalWrite(RightA,LOW);
  digitalWrite(RightB,HIGH);
}

void forward() {
  digitalWrite(LeftA,HIGH);
  digitalWrite(LeftB,LOW);
  digitalWrite(RightA,HIGH);
  digitalWrite(RightB,LOW);
}

void backward() {
  digitalWrite(LeftA,LOW);
  digitalWrite(LeftB,HIGH);
  digitalWrite(RightA,LOW);
  digitalWrite(RightB,HIGH);
}

void halt() {
  digitalWrite(LeftA,LOW);
  digitalWrite(LeftB,LOW);
  digitalWrite(RightA,LOW);
  digitalWrite(RightB,LOW);
}
