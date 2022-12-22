#include <SimpleTimer.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <WiFi.h>
#include <WiFiAP.h>

const char *ssid = "NW_GA-Call_EXT";
const char *password = "CGitonga@123";

AsyncWebServer server(80);

// Create an Event Source on /events
AsyncEventSource events("/events");

unsigned long lastTime = 0;  
unsigned long timerDelay = 3000;

int count = 0;
int Count = 0;

int Distance(){
  long duration;
  int distance;

  const int trigPin = 2;
  const int echoPin = 15;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
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
  return (distance);
}
int dist = Distance();

int COUNT()
{
  if (dist < 10) {
    Count += 1;
  } else {  // distance >=10
    Count;
  }
  return (Count);
  println("Scored: %d", Count); 
}

void getSensorReadings(){
  count = COUNT();
}

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

String processor(const String& var){
  getSensorReadings();
  //Serial.println(var);
  if(var == "count"){
    return String(count);
  }
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    p { font-size: 1.2rem;}
    body {  margin: 0;}
    .topnav { overflow: hidden; background-color: #50B8B4; color: white; font-size: 1rem; }
    .content { padding: 20px; }
    .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); }
    .cards { max-width: 800px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); }
    .reading { font-size: 1.4rem; }
  </style>
</head>
<body>
  <div class="topnav">
    <h1>SMART RIM (SSE)</h1>
  </div>
  <div class="content">
    <div class="cards">
      <div class="card">
        <p>COUNT</p><p><span class="reading"><span id="count">%COUNT%</span> scored</span></p>
      </div>
    </div>
  </div>
<script>
if (!!window.EventSource)
{
  var source = new EventSource('/events');

  source.addEventListner('open', function(e){
    console.log("Events Disconnected");
  }, false);
  source.addEventListener('error', function(e) {
  if (e.target.readyState != EventSource.OPEN) {
    console.log("Events Disconnected");
  }
 }, false);

 source.addEventListener('message', function(e) {
  console.log("message", e.data);
 }, false);
 
 source.addEventListener('count', function(e) {
  console.log("count", e.data);
  document.getElementById("count").innerHTML = e.data;
 }, false);
}
</script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  initWiFi();
  COUNT();
  
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
 if ((millis() - lastTime) > timerDelay){
  delay(200);
  getSensorReadings();
//  Serial.println("Count: %d", count);
  events.send("ping",NULL,millis());
  events.send(String(count).c_str(),"count",millis());
  
  lastTime = millis();
 }
}
