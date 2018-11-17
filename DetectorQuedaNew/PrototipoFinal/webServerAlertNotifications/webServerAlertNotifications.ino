#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "GVT-E931"; // your wireless network name (SSID)
const char* password = "6867006150"; // your Wi-Fi network password

ESP8266WebServer server(80);

const int led = 13;
const int alertPIn = 2;

void handleAlert() {
  String armts = (String) server.args();
  Serial.println("RequestRecebido - " + armts + " - ");
  
  String message = "Number of args received:";
  message += server.args();
  
  for (int i = 0; i < server.args(); i++) {
    message += "Arg nº" + (String) i + "->";
    message += server.argName(i) + ": ";
    message += server.arg(i) + "\n";
    Serial.println(message);
  }

  String state = server.arg("state");
  if (state == "1") {
    Serial.println("Socorro");
    digitalWrite(alertPIn, HIGH);
  } else if (state == "0") {
    Serial.println("OK");
    digitalWrite(alertPIn, LOW);
  }
  server.send(200, "text/plain", "Alert is " + state);
}

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  pinMode(alertPIn, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  Serial.println("Iniciando...");
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/alert", handleAlert);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
