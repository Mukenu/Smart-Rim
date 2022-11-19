#include <SimpleTimer.h>
#include <WiFi.h>
#include <WebServer.h>
#include "index.h"

const char *ssid = "Nezuko";
const char *password = "NezukoChan542";

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
  
  // // Clears the trigPin
  // digitalWrite(trigPin, LOW);
  // delayMicroseconds(2);
  // // Sets the trigPin on HIGH state for 10 micro seconds
  // digitalWrite(trigPin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin, LOW);
  // // Reads the echoPin, returns the sound wave travel time in microseconds
  // duration = pulseIn(echoPin, HIGH);
  // // Calculating the distance
  // distance = duration * 0.034 / 2;
  // // Prints the distance on the Serial Monitor
  // Serial.print("Distance: ");
  // Serial.println(distance);
  // delay(200);


  // if (distance < 10) {
  //   Count += 1;
  // } else {  // distance <=10
  //   Count;
  // }
  // Serial.print("count: ");
  // Serial.println(Count);

  WiFiClient client;   // listen for incoming clients
  
  server.handleClient();
  delay(1);
//  if (client) {                             // if you get a client,
//    Serial.println("New Client.");           // print a message out the serial port
//    String currentLine = "";                // make a String to hold incoming data from the client
//    while (client.connected()) {            // loop while the client's connected
//      if (client.available()) {             // if there's bytes to read from the client,
//        char c = client.read();             // read a byte, then
//        Serial.write(c);                    // print it out the serial monitor
//        if (c == '\n') {                    // if the byte is a newline character
//
//          // if the current line is blank, you got two newline characters in a row.
//          // that's the end of the client HTTP request, so send a response:
//          if (currentLine.length() == 0) {
//            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
//            // and a content-type so the client knows what's coming, then a blank line:
//            client.println("HTTP/1.1 200 OK");
//            client.println("Content-type:text/html");
//            client.println();
//
//            // the content of the HTTP response follows the header:
//            client.print("Click <a href=\"/H\">here</a> to see the COUNT.<br>");
//            // The HTTP response ends with another blank line:
//            client.println();
//            // break out of the while loop:
//            break;
//          } else {    // if you got a newline, then clear currentLine:
//            currentLine = "";
//          }
//        } else if (c != '\r') {  // if you got anything else but a carriage return character,
//          currentLine += c;      // add it to the end of the currentLine
//        }
//
//        // Check to see if the client request was "GET /H" 
//        if (currentLine.endsWith("GET /H")) 
//        {
//          client.println ("Count: ");
//          client.println(COUNT);
//        }
//        
//      }
//    }
//    // close the connection:
//    client.stop();
//    Serial.println("Client Disconnected.");
//    
//  }
}
