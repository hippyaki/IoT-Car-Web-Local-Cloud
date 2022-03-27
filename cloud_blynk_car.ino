/*
 * Akshayan Sinha
 * Complete Project Details https://www.hackster.io/akshayansinha
*/

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

int LeftA= ;  //IN1
int LeftB= ;  //IN2
int RightA= ; //IN3
int RightB= ; //IN4

char auth[] = " ";       // You should get Auth Token in the Blynk App.
char ssid[] = " ";       // Your Wi-Fi Credentials
char pass[] = " ";

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
  forward();
  Serial.println("Forward");
}
BLYNK_WRITE(V1)
{  
  backward();
  Serial.println("Backward");
}
BLYNK_WRITE(V2)
{  
  halt();
  Serial.println("Stop");
}
BLYNK_WRITE(V3)
{  
  right();
  Serial.println("Right");
}
BLYNK_WRITE(V4)
{  
  left();
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
