const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en" class="js-focus-visible">

<title>Bird Cage</title>

  <style>
    table {
      position: relative;
      width:100%;
      border-spacing: 0px;
    }
    tr {
      border: 1px solid white;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
    }
    th {
      height: 20px;
      padding: 3px 15px;
      background-color: #343a40;
      color: #FFFFFF !important;
      }
    td {
      height: 20px;
       padding: 3px 15px;
    }
    .tabledata {
      font-size: 24px;
      position: relative;
      padding-left: 5px;
      padding-top: 5px;
      height:   25px;
      border-radius: 5px;
      color: #FFFFFF;
      line-height: 20px;
      transition: all 200ms ease-in-out;
      background-color: #00AA00;
    }
    .fanrpmslider {
      width: 30%;
      height: 55px;
      outline: none;
      height: 25px;
    }
    .bodytext {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 24px;
      text-align: left;
      font-weight: light;
      border-radius: 5px;
      display:inline;
    }
    .navbar {
      width: 100%;
      height: 50px;
      margin: 0;
      padding: 10px 0px;
      background-color: #FFF;
      color: #000000;
      border-bottom: 5px solid #293578;
    }
    .fixed-top {
      position: fixed;
      top: 0;
      right: 0;
      left: 0;
      z-index: 1030;
    }
    .navtitle {
      float: left;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 50px;
      font-weight: bold;
      line-height: 50px;
      padding-left: 20px;
    }
   .navheading {
     position: fixed;
     left: 60%;
     height: 50px;
     font-family: "Verdana", "Arial", sans-serif;
     font-size: 20px;
     font-weight: bold;
     line-height: 20px;
     padding-right: 20px;
   }
   .navdata {
      justify-content: flex-end;
      position: fixed;
      left: 70%;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      font-weight: bold;
      line-height: 20px;
      padding-right: 20px;
   }
    .category {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: bold;
      font-size: 32px;
      line-height: 50px;
      padding: 20px 10px 0px 10px;
      color: #000000;
    }
    .heading {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: normal;
      font-size: 28px;
      text-align: left;
    }
  
    .btn {
      background-color: #444444;
      border: none;
      color: white;
      padding: 10px 20px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
    }
    .foot {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      position: relative;
      height:   30px;
      text-align: center;   
      color: #AAAAAA;
      line-height: 20px;
    }
    .container {
      max-width: 1800px;
      margin: 0 auto;
    }
    table tr:first-child th:first-child {
      border-top-left-radius: 5px;
    }
    table tr:first-child th:last-child {
      border-top-right-radius: 5px;
    }
    table tr:last-child td:first-child {
      border-bottom-left-radius: 5px;
    }
    table tr:last-child td:last-child {
      border-bottom-right-radius: 5px;
    }
    
  </style>

  <body style="background-color: #efefef" onload="process()">
  
    <header>
      <div class="navbar fixed-top">
          <div class="container">
            <div class="navtitle">Sensor Monitor</div>
            <div class="navdata" id = "date">mm/dd/yyyy</div>
            <div class="navheading">DATE</div><br>
            <div class="navdata" id = "time">00:00:00</div>
            <div class="navheading">TIME</div>
            
          </div>
      </div>
    </header>
  
    <main class="container" style="margin-top:70px">
      <div class="category">Sensor Readings</div>
      <div style="border-radius: 10px !important;">
      <table style="width:50%">
      <colgroup>
        <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
        <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
        <col span="1" style="background-color:rgb(180,180,180); width: 15%; color:#000000 ;">
      </colgroup>
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">

    </div>
    <br>
    <div class="category">Sensor Controls</div>
    <br>
    <div class="bodytext">in_light </div>
    <button type="button" class = "btn" id = "in_light" onclick="in_light()">Toggle</button>
    </div>
    <br>
    <div class="bodytext">out_light</div>
    <button type="button" class = "btn" id = "out_light" onclick="out_light()">Toggle</button>
    </div>
    <br>
    <div class="bodytext">generator</div>
    <button type="button" class = "btn" id = "generator" onclick="generator()">Toggle</button>
    </div>
    <br>
    <div class="bodytext">collector</div>
    <button type="button" class = "btn" id = "collector" onclick="collector()">Toggle</button>
    </div>
    <br>
    <div class="bodytext">fan</div>
    <button type="button" class = "btn" id = "fan" onclick="fan()">Toggle</button>
    </div>
    <br>
    <div class="bodytext">water</div>
    <button type="button" class = "btn" id = "water" onclick="water()">Toggle</button>
    </div>
    <br>
    <div class="bodytext">heater</div>
    <button type="button" class = "btn" id = "heater" onclick="heater()">Toggle</button>
    </div>
    <br>
    <div class="bodytext">food</div>
    <button type="button" class = "btn" id = "food" onclick="food()">Toggle</button>
    </div>
    <br>
    <br>
  </main>

  <footer div class="foot" id = "temp" >A start of something great insh</div></footer>
  
  </body>


  <script type = "text/javascript">
  
    // global variable visible to all java functions
    var xmlHttp=createXmlHttpObject();

    // function to create XML object
    function createXmlHttpObject(){
      if(window.XMLHttpRequest){
        xmlHttp=new XMLHttpRequest();
      }
      else{
        xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
      }
      return xmlHttp;
    }


    function in_light() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      xhttp.open("PUT", "in_light", false);
      xhttp.send();
    }

    function out_light() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      xhttp.open("PUT", "out_light", false);
      xhttp.send();
    }
    function collector() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      xhttp.open("PUT", "collector", false);
      xhttp.send();
    }

    function generator() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      xhttp.open("PUT", "generator", false);
      xhttp.send();
    }

    function heater() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      xhttp.open("PUT", "heater", false);
      xhttp.send();
    }

    function food() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      xhttp.open("PUT", "food", false);
      xhttp.send();
    }

    function water() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      xhttp.open("PUT", "water", false);
      xhttp.send();
    }

    function fan() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      xhttp.open("PUT", "fan", false);
      xhttp.send();
    }

    // function to handle the response from the ESP
    function response(){
      var message;
      var barwidth;
      var currentsensor;
      var xmlResponse;
      var xmldoc;
      var dt = new Date();
      var color = "#e8e8e8";
     
      // get the xml stream
      xmlResponse=xmlHttp.responseXML;
  
      // get host date and time
      document.getElementById("time").innerHTML = dt.toLocaleTimeString();
      document.getElementById("date").innerHTML = dt.toLocaleDateString();
  
      
  //inlight
      xmldoc_inlight = xmlResponse.getElementsByTagName("in_light");
      message = xmldoc_inlight[0].firstChild.nodeValue;
  
      if (message == 0){
        document.getElementById("in_light").innerHTML="Turn ON";
      }
      else{
        document.getElementById("in_light").innerHTML="Turn OFF";
      }
  //outlight 
      xmldoc_outlight = xmlResponse.getElementsByTagName("out_light");
      message = xmldoc_outlight[0].firstChild.nodeValue;
  
      if (message == 0){
        document.getElementById("out_light").innerHTML="Turn ON";
      }
      else{
        document.getElementById("out_light").innerHTML="Turn OFF";
      }
//generator
      xmldoc_generator = xmlResponse.getElementsByTagName("generator");
      message = xmldoc_generator[0].firstChild.nodeValue;
  
      if (message == 0){
        document.getElementById("generator").innerHTML="Turn ON";
      }
      else{
        document.getElementById("generator").innerHTML="Turn OFF";
      }

//collector
      xmldoc_collector = xmlResponse.getElementsByTagName("collector");
      message = xmldoc_collector[0].firstChild.nodeValue;
  
      if (message == 0){
        document.getElementById("collector").innerHTML="Turn ON";
      }
      else{
        document.getElementById("collector").innerHTML="Turn OFF";
      }

//water
      xmldoc_water = xmlResponse.getElementsByTagName("water");
      message = xmldoc_water[0].firstChild.nodeValue;
  
      if (message == 0){
        document.getElementById("water").innerHTML="Turn ON";
      }
      else{
        document.getElementById("water").innerHTML="Turn OFF";
      }

//food 
      xmldoc_food = xmlResponse.getElementsByTagName("food");
      message = xmldoc_food[0].firstChild.nodeValue;
  
      if (message == 0){
        document.getElementById("food").innerHTML="Turn ON";
      }
      else{
        document.getElementById("food").innerHTML="Turn OFF";
      }

//fan 
      xmldoc_fan = xmlResponse.getElementsByTagName("fan");
      message = xmldoc_fan[0].firstChild.nodeValue;
  
      if (message == 0){
        document.getElementById("fan").innerHTML="Turn ON";
      }
      else{
        document.getElementById("fan").innerHTML="Turn OFF";
      }

//heater 
      xmldoc_heater = xmlResponse.getElementsByTagName("heater");
      message = xmldoc_heater[0].firstChild.nodeValue;
  
      if (message == 0){
        document.getElementById("heater").innerHTML="Turn ON";
      }
      else{
        document.getElementById("heater").innerHTML="Turn OFF";
      }



    // general processing code for the web page to ask for an XML steam
    // this is actually why you need to keep sending data to the page to 
    // force this call with stuff like this
    // server.on("/xml", SendXML);
    // otherwise the page will not request XML from the ESP, and updates will not happen
    function process(){
     
     if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {
        xmlHttp.open("PUT","xml",true);
        xmlHttp.onreadystatechange=response;
        xmlHttp.send(null);
      }       
        // you may have to play with this value, big pages need more porcessing time, and hence
        // a longer timeout
        setTimeout("process()",300);
    }
  
  
  </script>

</html>



)=====";