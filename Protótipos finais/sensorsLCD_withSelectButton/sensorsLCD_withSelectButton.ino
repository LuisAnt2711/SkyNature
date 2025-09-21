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


void setup() {

//Configuração do botão
  pinMode(2,INPUT);

// Inicializa o LCD
  lcd.init();
  lcd.backlight();
  
// Mensagem de inicialização
  lcd.setCursor(0, 0);
  lcd.print("TESTE SENSORES");
  lcd.setCursor(0, 1);
  lcd.print("PLACEHOLDER");
  delay(3000);
  lcd.clear();

}

void loop() {

// Atribui uma variável para cada entrada
  int valorA0 = analogRead(lm35pin);   //Temperatura
  int valorA15 = analogRead(sensorP1);   //Umidade
  int valorA10 = analogRead(sensorP2);   //Umidade
  int valorA8 = analogRead(sensorP3);   //Umidade
  int valorB2 = digitalRead(botaoselect);  //Botão de seleção

//Caucula o valor de cada um dos sensores
  float tempC = (valorA0 * 5.0 * 100.0) / 1023.0;   //Temperatura
  float umidP1 = (((valorA15 * 100.0) / 1023.0) - 100.0)*(-1.0);         //Umidade
  float umidP2 = (((valorA10 * 100.0) / 1023.0) - 100.0)*(-1.0);
  float umidP3 = (((valorA8 * 100.0) / 1023.0) - 100.0)*(-1.0);

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
  lcd.print(tempC, 1);
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