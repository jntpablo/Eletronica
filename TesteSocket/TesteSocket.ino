
/*
  Created: Nov 11, 2017 Pablo Oliveira (http://github.com/jntpablo)
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
// Wi-Fi Settings
const char* ssid = "GVT-E931"; // your wireless network name (SSID)
const char* password = "6867006150"; // your Wi-Fi network password
const int buttonPin = 5;
String idCard = "BD 31 15 2B";
String idDispensador = "d7c384d9-55c8-47ae-a0ce-e5e02115d4a5";
//String host = "192.168.0.102:8080/historico";
String host = "192.168.25.3:3000/connection";
float statusDispensador = 100;
WiFiClient client;

const int postingInterval = 5 * 1000; // post data every 20 seconds
// variables will change:
int buttonState = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(115200);
  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    Serial.print(".");
  }
  //  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

String getStatus() {
  statusDispensador -= 0.5;
  return String(statusDispensador);
}

void post() {
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    http.begin("http://" + host);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST("idcard=" + idCard + "&iddispensador=" + idDispensador + "&status=" + getStatus());
    http.writeToStream(&Serial);
    http.end();

    Serial.println(httpCode);   //Print HTTP return code

  } else {
    Serial.println("Error in WiFi connection");
  }
  client.stop();
  delay(postingInterval);
}
void old_post() {
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    http.begin("http://" + host);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    //    int httpCode = http.POST("idcard=BD 31 15 2B&iddispensador=d7c384d9-55c8-47ae-a0ce-e5e02115d4a5&datahora=17/11/2017 11:48:57.705&status=99.7");
    int httpCode = http.POST("idcard=" + idCard + "&iddispensador=" + idDispensador + "&status=" + getStatus());
    http.writeToStream(&Serial);
    http.end();

    Serial.println(httpCode);   //Print HTTP return code

  } else {
    Serial.println("Error in WiFi connection");
  }
  client.stop();
  delay(postingInterval);
}
void loop() {

//  buttonState = digitalRead(buttonPin);
//  if (buttonState == HIGH) {
//    //    while (buttonState == HIGH) {}
//    // turn LED on:
//    digitalWrite(LED_BUILTIN, HIGH);
    post();
    delay(1000);
//  } else {
//    // turn LED off:
//    digitalWrite(LED_BUILTIN, LOW);
//  }
}
