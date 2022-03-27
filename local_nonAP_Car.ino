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

const char* ssid = " ";  // Enter SSID here
const char* password = " ";  //Enter Password here
const char* secret = " "; //Keep any kind of your own Secret Token - example - 'internetofthings'

WebServer server(80);             
 
void setup() {

// ----- MOVEMENT ------
  pinMode(LeftA,OUTPUT);
  pinMode(LeftB,OUTPUT);
  pinMode(RightA,OUTPUT);
  pinMode(RightB,OUTPUT);
  pinMode(2,OUTPUT);
  

 //------ WiFi Connection ----------
  
  Serial.begin(115200);
  delay(100);
  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());
  digitalWrite(2,HIGH); //Blue LED to display connected WiFi

//---------- Page Endpoints ( Main Control Room ) ----------------

  server.on("/" + secret, handle_OnConnect);

  server.on("/"  + secret + "/left", left);

  server.on("/"  + secret + "/right", right);

  server.on("/"  + secret + "/forward", forward);

  server.on("/"  + secret + "/backward", backward);

  server.on("/"  + secret + "/stop", halt);
 
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
