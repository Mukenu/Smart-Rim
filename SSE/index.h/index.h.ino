const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<style>
.card{
    max-width: 400px;
     min-height: 250px;
     background: #02b875;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
</style>
<body>

<div class="card">
  <h4>The ESP32 Update web page without refresh</h4><br>
  <h1>Sensor Value:<span id=""></span></h1><br>
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
