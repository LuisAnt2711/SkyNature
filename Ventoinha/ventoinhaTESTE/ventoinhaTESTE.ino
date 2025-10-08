// Controle de ventoinha com LM35
// Função: Liga ventoinha se temperatura > limite, desliga se < limite - histerese

const int lm35Pin = A0;      // Entrada analógica do LM35
const int fanPin = 5;        // Saída digital para o relé ou transistor

const float tempLimite = 30.0;    // Temperatura limite em °C
const float histerese = 2.0;      // Diferença para desligar (evita oscilações)

bool fanLigado = false;  // Estado atual da ventoinha

void setup() {
  Serial.begin(9600);
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW); // Ventoinha inicialmente desligada
}

void loop() {
  // Leitura do LM35 (10mV por °C → 1°C = 0.01V)
  int leitura = analogRead(lm35Pin);
  float tensao = leitura * (5.0 / 1023.0);
  float temperatura = tensao / 0.01;

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  // Controle com histerese
  if (!fanLigado && temperatura >= tempLimite) {
    digitalWrite(fanPin, HIGH); // Liga ventoinha
    fanLigado = true;
    Serial.println("Ventoinha LIGADA");
  } 
  else if (fanLigado && temperatura <= (tempLimite - histerese)) {
    digitalWrite(fanPin, LOW); // Desliga ventoinha
    fanLigado = false;
    Serial.println("Ventoinha DESLIGADA");
  }

  delay(1000); // Atualiza a cada 1 segundo
}
