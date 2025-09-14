// Dá nome ás entradas
const int trimpot = A7;   //Umidade (Trimpot)
const int lm35pin = A0;   //Temperatura (LM35)

void setup() {

  Serial.begin(9600);
  
}

void loop() {

// Atribui uma variável para cada entrada
  int valorA0 = analogRead(lm35pin);   //Temperatura
  int valorA7 = analogRead(trimpot);   //Umidade

//Caucula o valor de cada um dos sensores
  float tempC = (valorA0 * 5.0 * 100.0) / 1023.0;   //Temperatura
  float umidS = (valorA7 * 100.0) / 1023.0;         //Umidade

//Escreve os valores no Serial Monitor a cada 1 segundo
  Serial.print("Umidade: ");
  Serial.print(umidS, 1);
  Serial.println("%");

  Serial.print("Temperatura: ");
  Serial.print(tempC, 1);
  Serial.print("°"); 
  Serial.println("C");

  delay(1000);

}
