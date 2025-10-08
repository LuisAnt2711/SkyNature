// Pinos dos relés conectados ao Arduino
const int rele1 = 8;  // Relé da bomba 1
const int rele2 = 9;  // Relé da bomba 2

// Sensores de umidade do solo
const int sensor1 = A15;  // Sensor 1 controla bomba 1
const int sensor2 = A10;  // Sensor 2 controla bomba 2

// Limites do sensor (ajuste conforme seu sensor)
const int sensorSeco = 1023;  // Valor lido quando o solo está seco
const int sensorMolhado = 300; // Valor lido quando o solo está totalmente úmido

// Limiar de umidade em percentual para acionar a bomba
const int umidadeMinimaPercentual = 30;  // Aciona bomba se umidade < 30%

void setup() {
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);

  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);

  Serial.begin(9600);
}

void loop() {
  // Lê os sensores
  int leitura1 = analogRead(sensor1);
  int leitura2 = analogRead(sensor2);

  // Converte para percentual (100% úmido, 0% seco)
  int umidade1 = map(leitura1, sensorSeco, sensorMolhado, 0, 100);
  int umidade2 = map(leitura2, sensorSeco, sensorMolhado, 0, 100);

  // Limita os valores entre 0 e 100
  umidade1 = constrain(umidade1, 0, 100);
  umidade2 = constrain(umidade2, 0, 100);

  // Mostra no monitor serial
  Serial.print("Umidade 1: ");
  Serial.print(umidade1);
  Serial.print("%  |  Umidade 2: ");
  Serial.print(umidade2);
  Serial.println("%");

  // Verifica umidade e ativa bombas se necessário
  if (umidade1 < umidadeMinimaPercentual) {
    Serial.println("Solo seco no sensor 1. Ativando bomba 1.");
    digitalWrite(rele1, HIGH);
    delay(5000);
    digitalWrite(rele1, LOW);
  }

  if (umidade2 < umidadeMinimaPercentual) {
    Serial.println("Solo seco no sensor 2. Ativando bomba 2.");
    digitalWrite(rele2, HIGH);
    delay(5000);
    digitalWrite(rele2, LOW);
  }

  delay(2000); // Tempo entre leituras
}