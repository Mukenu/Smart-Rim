#include <SimpleTimer.h>
#include <WiFi.h>
#include <WebServer.h>
#include "index.h"

const char *ssid = "";
const char *password = "";

WebServer server(80);

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
  
void COUNT(){
  long duration;
  int distance;
  int Count;
  const int trigPin = 2;
  const int echoPin = 15;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Count = 0;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(200);

  if (distance < 10) {
    Count += 1;
  } else {  // distance <=10
    Count;
  }
  Serial.print("count: ");
  Serial.println(Count);
  String Num = String(Count);
  server.send(200, "text/plane",  Num);
}

void setup() {
  
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
//  WiFi.mode(WIFI_AP); //ACCESS POINT MODE
//  WiFi.softAP(ssid, password);
//  IPAddress myIP = WiFi.softAPIP();
//  Serial.print("AP IP address: ");
//  Serial.println(myIP);
//  server.begin();

  WiFi.mode(WIFI_STA); //Connectto your wifi
  WiFi.begin(ssid, password);

  Serial.println("Connecting to ");
  Serial.print(ssid);

  //Wait for WiFi to connect
  while(WiFi.waitForConnectResult() != WL_CONNECTED){      
      Serial.print(".");
    }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
//----------------------------------------------------------------
  
  Serial.println("Server started");
  COUNT();
  
  server.on("/", handleRoot);      //This is display page
  server.on("/readADC", COUNT);

  server.begin();
  Serial.println("HTTP server started");
}


void loop() {
  
  server.handleClient();
  delay(1);

}
