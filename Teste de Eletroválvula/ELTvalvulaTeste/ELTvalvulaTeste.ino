// === Definições de pinos ===
#define SENSOR_UMIDADE_1 A0 // Sensor de umidade do solo 1
#define SENSOR_UMIDADE_2 A1 // Sensor de umidade do solo 2m

#define RELAY_BOMBA 8      // Relé da bomba
#define RELAY_VALVULA_1 9  // Relé da válvula 1
#define RELAY_VALVULA_2 10 // Relé da válvula 2

// === Limite de umidade (ajuste conforme o sensor) ===
#define LIMITE_UMIDADE 400  

// Variáveis de leitura
int umidade_1, umidade_2;

void setup() {
  pinMode(RELAY_BOMBA, OUTPUT);
  pinMode(RELAY_VALVULA_1, OUTPUT);
  pinMode(RELAY_VALVULA_2, OUTPUT);

  // Inicializa todos desligados
  digitalWrite(RELAY_BOMBA, LOW);
  digitalWrite(RELAY_VALVULA_1, LOW);
  digitalWrite(RELAY_VALVULA_2, LOW);

  Serial.begin(9600);
}

void loop() {
  // === Leitura dos sensores ===
  umidade_1 = analogRead(SENSOR_UMIDADE_1);
  umidade_2 = analogRead(SENSOR_UMIDADE_2);

  // Debug no monitor serial
  Serial.print("Umidade 1: ");
  Serial.println(umidade_1);
  Serial.print("Umidade 2: ");
  Serial.println(umidade_2);

  // === Controle da irrigação ===
  if (umidade_1 < LIMITE_UMIDADE) {
    acionarIrrigacao(1);
  } else {
    desligarIrrigacao(1);
  }

  if (umidade_2 < LIMITE_UMIDADE) {
    acionarIrrigacao(2);
  } else {
    desligarIrrigacao(2);
  }

  delay(1000); // Espera 1s
}

// === Funções auxiliares ===
void acionarIrrigacao(int mangueira) {
  digitalWrite(RELAY_BOMBA, HIGH); // Liga a bomba

  if (mangueira == 1) {
    digitalWrite(RELAY_VALVULA_1, HIGH); // Abre válvula 1
  } else if (mangueira == 2) {
    digitalWrite(RELAY_VALVULA_2, HIGH); // Abre válvula 2
  }
}

void desligarIrrigacao(int mangueira) {
  if (mangueira == 1) {
    digitalWrite(RELAY_VALVULA_1, LOW);
  } else if (mangueira == 2) {
    digitalWrite(RELAY_VALVULA_2, LOW);
  }

  // Se ambas as válvulas estiverem fechadas → desliga bomba
  if (digitalRead(RELAY_VALVULA_1) == LOW && digitalRead(RELAY_VALVULA_2) == LOW) {
    digitalWrite(RELAY_BOMBA, LOW);
  }
}