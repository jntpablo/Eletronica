
int a = 7;
int b = 13;//8
int c = 12;
int d = 11;
int e = 9;
int f = 8;
int g = 10;

void apaga() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void zero(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
}
void um() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
}

void dois() {
  digitalWrite(f, HIGH);
  digitalWrite(a, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(c, HIGH);
}


void tres() {
  digitalWrite(f, HIGH);
  digitalWrite(a, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
}

void quatro() {
  digitalWrite(e, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
}

void cinco(){
  digitalWrite(f, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  
}
void seis(){
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void sete(){
  digitalWrite(b, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(a, HIGH);
}

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}


void oito(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void nove(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
void loop() {

  apaga();
  zero();
  delay(500);

  apaga();
  um();
  delay(500);

  apaga();
  dois();
  delay(500);

  apaga();
  tres();
  delay(500);

  apaga();
  quatro();
  delay(500);

  apaga();
  cinco();
  delay(500);
  
  apaga();
  seis();
  delay(500);

  apaga();
  sete();
  delay(500);
  
  apaga();
  oito();
  delay(500);
  
  apaga();
  nove();
  delay(500);
}
