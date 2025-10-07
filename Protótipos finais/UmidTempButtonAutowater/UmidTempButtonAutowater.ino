/* 
PROJETE 2025
EQUIPE MT1503
HORTA VERTICAL
CÓDIGO ATUALIZADO — SISTEMA DE IRRIGAÇÃO AUTOMÁTICA
2 RECIPIENTES COM DUAS BOMBAS 12V CONTROLADAS POR RELÉS
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definição dos pinos
const int sensorP1 = A15;   // Sensor de umidade do recipiente 1
const int sensorP2 = A10;   // Sensor de umidade do recipiente 2
const int lm35pin  = A0;    // Sensor de temperatura LM35
const int botaoselect = 2;  // Botão de seleção no LCD

// Sensor de nível d’água
const int sensornivel = 3;      
const int pino_led_cheio = 6;  
const int pino_led_vazio = 7;  

// Relés das bombas (acionam as bombas 12V) 
const int rele_bomba1 = 8;   // Relé da bomba 1
const int rele_bomba2 = 9;   // Relé da bomba 2

// Variáveis de controle
int selected = 1;          // Plantação selecionada
float umidLCD;             // Umidade exibida no LCD
float limiteBaixo = 40.0;  // Umidade mínima — liga a bomba
float limiteAlto  = 70.0;  // Umidade máxima — desliga a bomba

void setup() {

// Configuração dos pinos
  pinMode(botaoselect, INPUT);
  pinMode(sensornivel, INPUT);
  pinMode(pino_led_cheio, OUTPUT);
  pinMode(pino_led_vazio, OUTPUT);
  pinMode(rele_bomba1, OUTPUT);
  pinMode(rele_bomba2, OUTPUT);

// Relés desligados inicialmente
  digitalWrite(rele_bomba1, HIGH); // Relé inativo (HIGH = desligado em módulos com lógica inversa)
  digitalWrite(rele_bomba2, HIGH);

// Inicializa LCD
  lcd.init();
  lcd.backlight();

// Tela de inicialização
  lcd.setCursor(0, 0);
  lcd.print("   SKY NATURE");
  lcd.setCursor(0, 1);
  lcd.print("     MT1503");
  delay(3000);
  lcd.clear();

}

void loop() {

// Leitura dos sensores
  int estadoNivel = digitalRead(sensornivel);
  delay(50);
  int valorTemp = analogRead(lm35pin);
  delay(50);
  int valorUmidP1 = analogRead(sensorP1);
  delay(50);
  int valorUmidP2 = analogRead(sensorP2);
  delay(50);
  int botao = digitalRead(botaoselect);
  delay(50);

// Conversão de valores
  float tempC = ((valorTemp * (5.0 / 1023.0)) / 0.01) - 14.63;
  float umidP1 = (((valorUmidP1 * 100.0) / 1023.0) - 100.0) * (-1.0);
  float umidP2 = (((valorUmidP2 * 100.0) / 1023.0) - 100.0) * (-1.0);

// LEDs de nível de água
  if (estadoNivel == 1) { // tanque cheio
    digitalWrite(pino_led_vazio, HIGH);
    digitalWrite(pino_led_cheio, LOW);
  } else { // tanque vazio
    digitalWrite(pino_led_vazio, LOW);
    digitalWrite(pino_led_cheio, HIGH);
  }

// Alternância de plantação selecionada
  if (botao == HIGH) {
    selected = (selected == 1) ? 2 : 1;
    delay(250); // debounce
  }

// Determina qual valor de umidade mostrar
  umidLCD = (selected == 1) ? umidP1 : umidP2;

// Controle de irrigação (relés e bombas 12V)
  if (estadoNivel == 1) { // tanque com água disponível

  // Recipiente 1
    if (umidP1 < limiteBaixo) {
      digitalWrite(rele_bomba1, LOW); // Liga bomba 1 (ativo em LOW)
    }
    else if (umidP1 > limiteAlto) {
      digitalWrite(rele_bomba1, HIGH); // Desliga bomba 1
    }


  // Recipiente 2
    if (umidP2 < limiteBaixo) {
      digitalWrite(rele_bomba2, LOW); // Liga bomba 2
    } 
    else if (umidP2 > limiteAlto) {
      digitalWrite(rele_bomba2, HIGH); // Desliga bomba 2
    }

  } 
  else {
  // Tanque vazio → desliga tudo
    digitalWrite(rele_bomba1, HIGH);
    digitalWrite(rele_bomba2, HIGH);
  }

// Exibição no LCD
  lcd.setCursor(14, 0);
  lcd.print("P");
  lcd.print(selected);

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC, 1);
  lcd.print((char)223);
  lcd.print("C ");

  lcd.setCursor(0, 1);
  lcd.print("Umid: ");
  lcd.print(umidLCD, 1);
  lcd.print("%   ");
}
