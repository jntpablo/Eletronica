
/*
  Created: Jun 26, 2018 Pablo Oliveira (http://github.com/jntpablo)
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define MAX_VALUE 100
String valores[MAX_VALUE];

// Wi-Fi Settings
const char* ssid = "GVT-E931"; // your wireless network name (SSID)
const char* password = "6867006150"; // your Wi-Fi network password
const int alertPin = 5; //IO21
//String host = "172.20.10.6/alert";
String host = "192.168.25.3/alert";
WiFiClient client;

const int postingInterval = 5 * 1000; // post data every 20 seconds
// variables will change:
int state = 0;

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println("Iniciando...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
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
void assembly(String texto) {
  int aux = 0;

  while (texto.length() > 0) {
    int indiceSeparador = texto.indexOf(";");
    if (indiceSeparador > -1) {
      valores[aux] = texto.substring(0, indiceSeparador);
      aux++;
      // Serial.println(texto.substring(0, indiceSeparador));
      delay(1000);
      texto.remove(0, indiceSeparador + 1);
    } else {
      valores[aux] = texto.substring(0, texto.length());
      //Serial.println(texto.substring(0, texto.length()));
      texto.remove(0, texto.length());
    }
  }
  state = valores[0].toInt();
}

void imprimeVariaveis() {
  Serial.println("Valores[0] = " + valores[0]);
}

String leStringSerial() {
  String conteudo = "";
  char caractere;

  // Enquanto receber algo pela serial
  while (Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n') {
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
  return conteudo;
}

void post() {
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    http.begin("http://" + host);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String msg = "state=" + (String) state;
    Serial.println("Valor a ser enviado: " + msg);
    int httpCode = http.POST(msg);
    http.writeToStream(&Serial);
    http.end();

    Serial.println(httpCode);   //Print HTTP return code

  } else {
    Serial.println("Error in WiFi connection");
  }
  client.stop();
}

void loop() {
  if (Serial.available() > 0) {
    String recebido = leStringSerial();
    assembly(recebido);
    imprimeVariaveis();
    post();
  }
}
