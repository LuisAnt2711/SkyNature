/*
PROJETE 2025
EQUIPE MT1503
HORTA VERTICAL
CÓDIGO PARA TESTE DE LCD COM MÚLTIPLOS SENSORES E BOTÃO DE SELEÇÃO
2 RECIPIENTES
IRRIGAÇÃO AUTOMÁTICA COM 2 BOMBAS E 2 RELÉS
*/

//Configura o Display LCD e as bibliotecas
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Dá nome ás entradas
const int sensorP1 = A15;   //Umidade (Sensor)
const int sensorP2 = A10;   //Umidade (Sensor)
const int lm35pin = A0;   //Temperatura (LM35)
const int botaoselect = 2;   //Botão de seleção
const int rele1 = 8;  // Relé da bomba 1
const int rele2 = 9;  // Relé da bomba 2

// Variáveis de seleção
int selected;  //Recipiente selecionado pelo botão
float umidLCD;  //Valor de umidade mostrado no LCD

// Limites dos sensores de umidade
const int umidade_minima = 30;

//Configuração dos pinos do sensor de nível d'água
int sensornivel = 3;  //pino do sensor
int pino_led_cheio = 6;  //led vermelho (vazio)
int pino_led_vazio = 7;  //led verde (cheio)

void setup() {

//Configuração do botão
  pinMode(botaoselect,INPUT);
  selected = 1;
//Configuração dos relés
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);

  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);

//Configuração do sensor de nível d'água
  pinMode(sensornivel, INPUT);
  pinMode(pino_led_cheio, OUTPUT);
  pinMode(pino_led_vazio, OUTPUT);
// Inicializa o LCD
  lcd.init();
  lcd.backlight();
  
// Mensagem de inicialização
  lcd.setCursor(0, 0);
  lcd.print("   SKY NATURE");
  lcd.setCursor(0, 1);
  lcd.print("     MT1503");
  delay(3000);
  lcd.clear();

}

void loop() {

// Atribui uma variável ao sensor de nível d'água
  int estado = digitalRead(sensornivel);

// Atribui uma variável para cada entrada
  int valorA0 = analogRead(lm35pin);   //Temperatura
  delay(150);
  int valorA15 = analogRead(sensorP1);   //Umidade
  delay(150);
  int valorA10 = analogRead(sensorP2);   //Umidade
  delay(150);
  int valorB2 = digitalRead(botaoselect);  //Botão de seleção

//Caucula o valor de cada um dos sensores
  float tempC = ((valorA0 * (5.0 / 1023.0)) / 0.01)-5.63;   //Temperatura
  float umidP1 = (((valorA15 * 100.0) / 1023.0) - 100.0)*(-1.0);         //Umidade
  float umidP2 = (((valorA10 * 100.0) / 1023.0) - 100.0)*(-1.0);

//Determina o estado do nível d'água
  if(estado == 1){
    digitalWrite(pino_led_vazio, HIGH);
    digitalWrite(pino_led_cheio, LOW);
  }
  else{
    digitalWrite(pino_led_vazio, LOW);
    digitalWrite(pino_led_cheio, HIGH);
  }

//Determina a plantação selecionada
  if(valorB2 == HIGH){
    switch(selected){
      case 1:
        selected = 2;
        break;
      case 2:
        selected = 1;
        break;
      default:
        break;
    }
  }

//Determina os valores que devem ser mostrados
  switch(selected) {
    case 1:
      umidLCD = umidP1;
      break;
    case 2:
      umidLCD = umidP2;
      break;
    default:
      break;
  }

// Verifica umidade e ativa bombas se necessário
  if (umidP1 < umidade_minima) {  //Solo 1 está seco
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Plantacao 1 seca");
    lcd.setCursor(0, 1);
    lcd.print("Ativando bomba 1");
    digitalWrite(rele1, HIGH);
    delay(5000);
    digitalWrite(rele1, LOW);
    lcd.clear();
  }

  if (umidP2 < umidade_minima) {  //Solo 2 está seco
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Plantacao 2 seca");
    lcd.setCursor(0, 1);
    lcd.print("Ativando bomba 2");
    digitalWrite(rele2, HIGH);
    delay(5000);
    digitalWrite(rele2, LOW);
    lcd.clear();
  }

//Mostra os valores no Display LCD
  lcd.setCursor(14, 0);   //Mostra a plantação selecionada
  lcd.print("P");
  lcd.print(selected);

  lcd.setCursor(0, 0);   //Mostra a temperatura ambiente
  lcd.print("Temp: ");
  lcd.print(tempC, 1);
  lcd.print((char)223); 
  lcd.print("C ");

  lcd.setCursor(0, 1);   //Mostra a umidade da plantação
  lcd.print("Umidade: ");
  lcd.print(umidLCD, 2);
  lcd.print("%  ");

  delay(50);

}
/*

000000  000000  000000  000000  000000  000000  000000          000000  000000  000000  000000
000000  000000  000000  000000  000000  000000  000000          000000  000000  000000  000000
00  00  00  00  00  00     000  000       00    000                000  00  00     000  000    
000000  000000  00  00     000  000000    00    000000          000000  00  00  000000  000000
000     0000    00  00  0  000  000       00    000             000     00  00  000        000
000     00  00  000000  000000  000000    00    000000          000000  000000  000000  000000

*/