const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  setInterval(function() {
  getData();
  }, 1000);

  function getData() {
    var GetDataRequest = new XMLHttpRequest();
    GetDataRequest.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) 
      {
        document.GetelementByID("Count").innerHTML = 
        this.responseText;  
      }
    };
    GetDataRequest.open("GET", "readCount", true);
    GetDataRequest.send();  
  }
</html>
)=====";
