#include <WiFi.h>       // standard library
#include <WebServer.h>  // standard library
#include "SuperMon.h"   // .h file that stores your html page code

#define AP_SSID "TestWebSite"
#define AP_PASS "023456789"

#define pin_in_light 13
#define pin_out_light 12
#define pin_generator 14 
#define pin_heater 27
#define pin_fan 26 
#define pin_food 25 
#define pin_water 33
#define pin_collector 32 

#define pin_sensor_humidity 5 

bool in_light = false; 
bool out_light = false; 
bool generator = false; 
bool heater = false; 
bool fan = false; 
bool food = false; 
bool water = false; 
bool collector = false; 

int humidity = 0; 
int full = 0; 

// the XML array size needs to be bigger that your maximum expected size. 2048 is way too big for this example
char XML[2048];

// just some buffer holder for char operations
char buf[32];

// variable for the IP reported when you connect to your homes intranet (during debug mode)
IPAddress Actual_IP;

// definitions of your desired intranet created by the ESP32
IPAddress PageIP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;

// gotta create a server
WebServer server(80);

void setup() {

  Serial.begin(9600);
  pinMode(pin_in_light, OUTPUT);
  pinMode(pin_out_light, OUTPUT);
  pinMode(pin_generator, OUTPUT);
  pinMode(pin_heater, OUTPUT);
  pinMode(pin_fan, OUTPUT);
  pinMode(pin_food, OUTPUT);
  pinMode(pin_water, OUTPUT);
  pinMode(pin_collector, OUTPUT);

  pinMode(pin_sensor_humidity, INPUT);

    // maybe disable watch dog timer 1 if needed
  disableCore1WDT();

  // just an update to progress
  Serial.println("starting server");

  // if you have this #define USE_INTRANET,  you will connect to your home intranet, again makes debugging easier
#ifdef USE_INTRANET
  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  Actual_IP = WiFi.localIP();
#endif

  // if you don't have #define USE_INTRANET, here's where you will creat and access point
  // an intranet with no internet connection. But Clients can connect to your intranet and see
  // the web page you are about to serve up
#ifndef USE_INTRANET
  WiFi.softAP(AP_SSID, AP_PASS);
  delay(100);
  WiFi.softAPConfig(PageIP, gateway, subnet);
  delay(100);
  Actual_IP = WiFi.softAPIP();
  Serial.print("IP address: "); Serial.println(Actual_IP);
#endif

  printWifiStatus();


  // these calls will handle data coming back from your web page
  // this one is a page request, upon ESP getting / string the web page will be sent
  server.on("/", SendWebsite);

  // upon esp getting /XML string, ESP will build and send the XML, this is how we refresh
  // just parts of the web page
  server.on("/xml", SendXML);

  // upon ESP getting /UPDATE_SLIDER string, ESP will execute the UpdateSlider function
  // same notion for the following .on calls
  // add as many as you need to process incoming strings from your web page
  // as you can imagine you will need to code some javascript in your web page to send such strings
  // this process will be documented in the SuperMon.h web page code
  server.on("/in_light", IN_LIGHT);
  server.on("/out_light", OUT_LIGHT);
  server.on("/generator", GENERATOR);
  server.on("/heater", HEATER);
  server.on("/fan", FAN);
  server.on("/collector", COLLECTOR);
  server.on("/food", FOOD);
  server.on("/water", WATER);

  // finally begin the server
  server.begin();

}

void loop() {
  // no matter what you must call this handleClient repeatidly--otherwise the web page
  // will not get instructions to do something
  server.handleClient();
}


void IN_LIGHT() {

  in_light = !in_light;
  digitalWrite(pin_in_light, in_light);
  Serial.print("The Light inside the cage: "); Serial.println(in_light);
  server.send(200, "text/plain", ""); //Send web page
}

void OUT_LIGHT() {

  out_light = !out_light;
  digitalWrite(pin_in_light, in_light);
  Serial.print("The Light outside: "); Serial.println(out_light);
  server.send(200, "text/plain", ""); //Send web page
}

void GENERATOR() {

  generator = !generator;
  digitalWrite(pin_generator, generator);
  Serial.print("The BioGas energy generation status: "); Serial.println(generator);
  server.send(200, "text/plain", ""); //Send web page
}

void COLLECTOR() {

  collector = !collector;
  digitalWrite(pin_collector, collector);
  Serial.print("Waste collection status: "); Serial.println(collector);
  server.send(200, "text/plain", ""); //Send web page
}

void WATER() {

  water = !water;
  digitalWrite(pin_water, water);
  Serial.print("Water: "); Serial.println(water);
  server.send(200, "text/plain", ""); //Send web page
}

void HEATER() {

  heater = !heater;
  digitalWrite(pin_heater, heater);
  Serial.print("Heat: "); Serial.println(heater);
  server.send(200, "text/plain", ""); //Send web page
}

void FOOD() {

  food = !food;
  digitalWrite(pin_food, food);
  Serial.print("Food: "); Serial.println(food);
  server.send(200, "text/plain", ""); //Send web page
}

void FAN() {

  fan = !fan;
  digitalWrite(pin_fan, fan);
  Serial.print("ventillation: "); Serial.println(collector);
  server.send(200, "text/plain", ""); //Send web page
}


void SendWebsite() {

  Serial.println("sending web page");
  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/html", PAGE_MAIN);

}



void SendXML() {

  // Serial.println("sending xml");

  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

  // show led0 status
  if (in_light) {
    strcat(XML, "<in_light>1</in_light>\n");
  }
  else {
    strcat(XML, "<in_light>0</in_light>\n");
  }

  if (out_light) {
    strcat(XML, "<out_light>1</out_light>\n");
  }
  else {
    strcat(XML, "<out_light>0</out_light>\n");
  }

  if (generator) {
    strcat(XML, "<generator>1</generator>\n");
  }
  else {
    strcat(XML, "<generator>0</generator>\n");
  }

  if (collector) {
    strcat(XML, "<collector>1</collector>\n");
  }
  else {
    strcat(XML, "<collector>0</collector>\n");
  }

  if (water) {
    strcat(XML, "<water>1</water>\n");
  }
  else {
    strcat(XML, "<water>0</water>\n");
  }

  if (heater) {
    strcat(XML, "<heater>1</heater>\n");
  }
  else {
    strcat(XML, "<heater>0</heater>\n");
  }

  if (food) {
    strcat(XML, "<food>1</food>\n");
  }
  else {
    strcat(XML, "<food>0</food>\n");
  }

  if (fan) {
    strcat(XML, "<fan>1</fan>\n");
  }
  else {
    strcat(XML, "<fan>0</fan>\n");
  }





  strcat(XML, "</Data>\n");
  // wanna see what the XML code looks like?
  // actually print it to the serial monitor and use some text editor to get the size
  // then pad and adjust char XML[2048]; above
  Serial.println(XML);

  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/xml", XML);


}

// I think I got this code from the wifi example
void printWifiStatus() {

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("Open http://");
  Serial.println(ip);
}

// end of code






