/*
PROJETE 2025
EQUIPE MT1503
HORTA VERTICAL
CÓDIGO PARA TESTE DE LCD COM MÚLTIPLOS SENSORES E BOTÃO DE SELEÇÃO
*/

//Configura o Display LCD e as bibliotecas
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Dá nome ás entradas
const int sensorP1 = A15;   //Umidade (Sensor)
const int sensorP2 = A10;   //Umidade (Sensor)
const int sensorP3 = A8;   //Umidade (Sensor)
const int lm35pin = A0;   //Temperatura (LM35)
const int botaoselect = 2;   //Botão de seleção
int selected;
float umidLCD;
float soma;

//variável
const int numLeituras = 10; // Quantas leituras para calcular a média

//Cpnfiguração dos pinos do sensor de nível d'água
int sensornivel = 3;  //pino do sensor
int pino_led_cheio = 6;  //led vermelho (vazio)
int pino_led_vazio = 7;  //led verde (cheio)

void setup() {

//Configuração do botão
  pinMode(2,INPUT);

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
  int valorA15 = analogRead(sensorP1);   //Umidade
  int valorA10 = analogRead(sensorP2);   //Umidade
  int valorA8 = analogRead(sensorP3);   //Umidade
  int valorB2 = digitalRead(botaoselect);  //Botão de seleção

//Caucula o valor de cada um dos sensores de umidade
  float umidP1 = (((valorA15 * 100.0) / 1023.0) - 100.0)*(-1.0);         //Umidade
  float umidP2 = (((valorA10 * 100.0) / 1023.0) - 100.0)*(-1.0);
  float umidP3 = (((valorA8 * 100.0) / 1023.0) - 100.0)*(-1.0);

// Faz várias leituras do LM35
  for (int i = 0; i < numLeituras; i++) {
    int leitura = analogRead(lm35pin); // Valor bruto do ADC (0 a 1023)
    soma += leitura;
    delay(10); // pequeno intervalo para estabilizar
  }

//Calcula a média
  float media = soma / (float)numLeituras;

  // Converte o valor médio do ADC para temperatura em °C
  float tensao = (media * 5.0) / 1023.0; // Converte para tensão (0–5V)
  float temperatura = tensao * 100.0;    // 10 mV por grau → 1°C = 0,01 V
  float tempfinal = (temperatura * 0.5)/1000.0;

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
  if(selected == 0){
    selected = 1;
  }
  if(valorB2 == 1){
    selected = selected+1;
    
    if(selected > 3){
      selected = 1;
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
    case 3:
      umidLCD = umidP3;
      break;
    defauil:
      break;
  }

//Mostra os valores no Display LCD
  lcd.setCursor(14, 0);   //Mostra a plantação selecionada
  lcd.print("P");
  lcd.print(selected);

  lcd.setCursor(0, 0);   //Mostra a temperatura ambiente
  lcd.print("Temp: ");
  lcd.print(tempfinal, 1);
  lcd.print((char)223); 
  lcd.print("C ");

  lcd.setCursor(0, 1);   //Mostra a umidade da plantação
  lcd.print("Umidade: ");
  lcd.print(umidLCD, 2);
  lcd.print("%  ");

  delay(500);

}
/*

000000  000000  000000  000000  000000  000000  000000          000000  000000  000000  000000
000000  000000  000000  000000  000000  000000  000000          000000  000000  000000  000000
00  00  00  00  00  00     000  000       00    000                000  00  00     000  000    
000000  000000  00  00     000  000000    00    000000          000000  00  00  000000  000000
000     0000    00  00  0  000  000       00    000             000     00  00  000        000
000     00  00  000000  000000  000000    00    000000          000000  000000  000000  000000

*/