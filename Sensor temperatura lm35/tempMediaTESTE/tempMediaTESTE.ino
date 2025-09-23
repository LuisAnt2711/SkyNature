const int lm35Pin = A0;  // Pino analógico conectado ao LM35
const int numLeituras = 10; // Quantas leituras para calcular a média

void setup() {
  Serial.begin(9600); 
}

void loop() {
  long soma = 0;

  // Faz várias leituras do LM35
  for (int i = 0; i < numLeituras; i++) {
    int leitura = analogRead(lm35Pin); // Valor bruto do ADC (0 a 1023)
    soma += leitura;
    delay(10); // pequeno intervalo para estabilizar
  }

  // Calcula a média
  float media = soma / (float)numLeituras;

  // Converte o valor médio do ADC para temperatura em °C
  float tensao = (media * 5.0) / 1023.0; // Converte para tensão (0–5V)
  float temperatura = tensao * 100.0;    // 10 mV por grau → 1°C = 0,01 V
  float tempfinal = temperatura * 0.5;

  // Exibe no Serial Monitor
  Serial.print("Temperatura media: ");
  Serial.print(tempfinal);
  Serial.println(" °C");

  delay(1000); // atualiza a cada 1 segundo
}
