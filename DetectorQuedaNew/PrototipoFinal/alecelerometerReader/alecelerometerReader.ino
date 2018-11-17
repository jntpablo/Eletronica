/**
   Projeto....: Detector de Quedas
   Criado em..: 21/05/2018, 00:02:00
   Arquivo....: Prototipo.ino

   @author Pablo Oliveira (jntpablo)
   Aplicativo para simulação
*/
#include <Wire.h>

#define Register_ID 0
#define Register_2D 0x2D
#define Register_X0 0x32
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37

// Endereco I2C do sensor : 83 em decimal ou 0x53
int ADXAddress = 0x53;  // the default 7-bit slave address
int reading = 0;
int val = 0;
int X0, X1, X_out;
int Y0, Y1, Y_out;
int Z1, Z0, Z_out;
int alert = 0;
double Xg, Yg, Zg;
double angle;
String state = "0";

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Iniciando.....");
  delay(100);
  // enable to measute g data
  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_2D);
  Wire.write(8);                //measuring enable
  Wire.endTransmission();     // stop transmitting
  pinMode(7, OUTPUT);
}


void readAngle() {
  //--------------X
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_X0);
  Wire.write(Register_X1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress, 2);
  if (Wire.available() <= 2)
  {
    X0 = Wire.read();
    X1 = Wire.read();
    X1 = X1 << 8;
    X_out = X0 + X1;
  }

  //------------------Y
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_Y0);
  Wire.write(Register_Y1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress, 2);
  if (Wire.available() <= 2)
  {
    Y0 = Wire.read();
    Y1 = Wire.read();
    Y1 = Y1 << 8;
    Y_out = Y0 + Y1;
  }
  //------------------Z
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_Z0);
  Wire.write(Register_Z1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress, 2);
  if (Wire.available() <= 2)
  {
    Z0 = Wire.read();
    Z1 = Wire.read();
    Z1 = Z1 << 8;
    Z_out = Z0 + Z1;
  }
  //
  Xg = X_out; //256.0;
  Yg = Y_out; //256.0;
  Zg = Z_out; //256.0;

}

void printValues() {
  Serial.print("X= ");
  Serial.print(Xg);
  Serial.print("       ");
  Serial.print("A= ");
  Serial.print(angle);
  Serial.print("       ");
  Serial.print("Y= ");
  Serial.print(Yg);
  Serial.print("       ");
  Serial.print("Z= ");
  Serial.print(Zg);
  Serial.println("  ");
}

void setAngule(int axisReference) {
  if (axisReference > 0) {
    angle = map(axisReference, 0, 256, 90, 180);
  } else {
    angle = map(axisReference, -1, -256, 90, 10);
  }
}


void verifyAndSendAlert() {
  String currentState;
  if (angle > 135 || angle < 45) {
    currentState = "1";
    digitalWrite(7, HIGH);
  } else {
    currentState = "0";
    digitalWrite(7, LOW);
  }

  if (!state.equals(currentState)) {
    state = currentState;
    Serial.println(state);
  }
}
void loop() {
  readAngle();
  setAngule(Zg);
  printValues();
  //verifyAndSendAlert();
  delay(50);
}
