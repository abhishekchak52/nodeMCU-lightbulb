#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define LED 16

const char* ssid = "Redmi";
const char* password = "password";



void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);     // Initialize the LED_BUILTIN pin as an output

  
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://light-switch-toggle.herokuapp.com/state");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code

      StaticJsonBuffer<200> jsonBuffer; // Set up a JSON buffer to perform associations
      String payload = http.getString();   //Get the request response payload
      JsonObject& response = jsonBuffer.parseObject(payload);
      String lightbulb_status = response["state"];
      if (lightbulb_status == "on")
      {
        digitalWrite(LED, LOW);           // Active low LED
        Serial.println("ON");                     //Print the response payload
      }
      else if (lightbulb_status == "off")
      {
        digitalWrite(LED, HIGH);          // Active low LED
        Serial.println("OFF");                     //Print the response payload
      }
      
      
 
    }
 
    http.end();   //Close connection
 
  }
 
  delay(2000);    //Send a request every 30 seconds

}
