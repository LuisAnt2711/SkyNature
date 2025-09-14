const int trimpot = A7;
const int lm35pin = A0;

void setup() {

  Serial.begin(9600);
  
}

void loop() {

  int valorA0 = analogRead(lm35pin);
  int valorA7 = analogRead(trimpot);
  float tempC = (valorA0 * 5.0 * 100.0) / 1023.0;
  float umidS = (valorA7 * 100.0) / 1023.0;

  Serial.print("Umidade: ");
  Serial.print(umidS, 1);
  Serial.println("%");
  Serial.print("Temperatura: ");
  Serial.print(tempC);
  Serial.print((char)223);
  Serial.println("C");
  delay(1000);
}
