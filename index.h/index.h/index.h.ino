#include <SimpleTimer.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "index.h"

const char *ssid = "";
const char *password = "";

AsyncWebServer server(80);

// Create an Event Source on /events
AsyncEventSource events("/events");

int count;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
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
}

void getSensorReadings(){
  count = COUNT();
}
void setup() {
  
  Serial.begin(115200);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send_P(200, "text/html", index_html, processor);
  });

  events.onConnect([](AsyncEventSourceClient *client){
  if(client->lastId()){
    Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
  }
  // send event with message "hello!", id current millis
  // and set reconnect delay to 1 second
  client->send("hello!", NULL, millis(), 10000);
});
server.addHandler(&events);

server.begin();
}


void loop() {
  
  getSensorReadings();
  Serial.println("Count: %d", count);
  events.send("ping",NULL,millis());
  events.send(String(count).c_str(),"count",millis());
  
}
