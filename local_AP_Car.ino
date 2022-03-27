/*
 * Akshayan Sinha
 * Complete Project Details https://www.hackster.io/akshayansinha
*/
#include <WiFi.h>
#include <WebServer.h>

int LeftA= ;  //IN1
int LeftB= ;  //IN2
int RightA= ; //IN3
int RightB= ; //IN4

const char* ssid = "myESP32device";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);             
 
void setup() {

// ----- MOVEMENT ------
  pinMode(LeftA,OUTPUT);
  pinMode(LeftB,OUTPUT);
  pinMode(RightA,OUTPUT);
  pinMode(RightB,OUTPUT);
  pinMode(2,OUTPUT);
  

 //------ WiFi HOTSPOT Creation ----------
  
  Serial.begin(115200);

  Serial.print("Setting AP (Access Point)…");
  
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password); //IP Address of the Bot - 192.168.1.1
  
  digitalWrite(2,HIGH);

//---------- Page Endpoints ( Main Control Room ) ----------------

  server.on("/asasasasa", handle_OnConnect);
  server.on("/asasasasa/left", left);
  server.on("/asasasasa/right", right);
  server.on("/asasasasa/forward", forward);
  server.on("/asasasasa/backward", backward);
  server.on("/asasasasa/stop", halt);
  server.onNotFound(handle_NotFound);

//---------- SERVER EXECUTION --------------

  server.begin();
  Serial.println("HTTP server started");
  
}
void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML()); 
}

void left() {
  digitalWrite(LeftA,LOW);
  digitalWrite(LeftB,HIGH);
  digitalWrite(RightA,HIGH);
  digitalWrite(RightB,LOW);
  
  server.send(200, "text/html", SendHTML()); 
}

void right() {

  digitalWrite(LeftA,HIGH);
  digitalWrite(LeftB,LOW);
  digitalWrite(RightA,LOW);
  digitalWrite(RightB,HIGH);
  
  server.send(200, "text/html", SendHTML()); 
}

void forward() {

  digitalWrite(LeftA,HIGH);
  digitalWrite(LeftB,LOW);
  digitalWrite(RightA,HIGH);
  digitalWrite(RightB,LOW);
  
  server.send(200, "text/html", SendHTML()); 
}

void backward() {

  digitalWrite(LeftA,LOW);
  digitalWrite(LeftB,HIGH);
  digitalWrite(RightA,LOW);
  digitalWrite(RightB,HIGH);
  
  server.send(200, "text/html", SendHTML()); 
}

void halt() {

  digitalWrite(LeftA,LOW);
  digitalWrite(LeftB,LOW);
  digitalWrite(RightA,LOW);
  digitalWrite(RightB,LOW);
  
  server.send(200, "text/html", SendHTML()); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\">\n";
  ptr +="<title>IoT Gesture Bot</title>\n";
  ptr +="<style>html { font-family: Courier New; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>Enter /command on the URL, or contact Admin for WebRemote</h1>\n";
  ptr +="<p>Available Commands - left,  right,  forward,  stop,  backward, open </p>";
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
