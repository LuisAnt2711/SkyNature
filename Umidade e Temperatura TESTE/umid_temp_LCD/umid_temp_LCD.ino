/*
PROJETE 2025
EQUIPE MT1503
HORTA VERTICAL
CÓDIGO PARA TESTE DE LCD COM MÚLTIPLOS SENSORES
*/

//Configura o Display LCD e as bibliotecas
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Dá nome ás entradas
const int sensorP1 = A7;   //Umidade (Sensor)
const int sensorP2 = A6;   //Umidade (Sensor)
const int sensorP3 = A5;   //Umidade (Sensor)
const int lm35pin = A0;   //Temperatura (LM35)

void setup() {

// Inicializa o LCD
  lcd.init();
  lcd.backlight();
  
// Mensagem de inicialização
  lcd.setCursor(0, 0);
  lcd.print("Temp.Ambiente");
  lcd.setCursor(0, 1);
  lcd.print("Umidade Do Solo");
  delay(3000);
  lcd.clear();

}

void loop() {

// Atribui uma variável para cada entrada
  int valorA0 = analogRead(lm35pin);   //Temperatura
  int valorA7 = analogRead(sensorP1);   //Umidade
  int valorA6 = analogRead(sensorP2);   //Umidade
  int valorA5 = analogRead(sensorP3);   //Umidade

//Caucula o valor de cada um dos sensores
  float tempC = (valorA0 * 5.0 * 100.0) / 1023.0;   //Temperatura
  float umidP1 = (((valorA7 * 100.0) / 1023.0) - 100.0)*(-1.0);         //Umidade
  float umidP2 = (((valorA6 * 100.0) / 1023.0) - 100.0)*(-1.0);
  float umidP3 = (((valorA5 * 100.0) / 1023.0) - 100.0)*(-1.0);

//Escreve os valores dos três sensore (PLACEHOLDER)
  lcd.setCursor(0,0);
  lcd.print("P1:");
  lcd.print(umidP1,1);
  lcd.print("%");
  lcd.print("P2:");
  lcd.print(umidP2,1);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("P3:");
  lcd.print(umidP3,1);
  lcd.print("%");
  lcd.print("TA:");
  lcd.print(tempC,1);
  lcd.print((char)223);
  lcd.print("C");
  delay(1000);


/*
//Escreve os valores no Serial Monitor a cada 1 segundo
  lcd.setCursor(14, 0);   //Mostra a plantação selecionada
  lcd.print("P1");

  lcd.setCursor(0, 0);   //Mostra a temperatura ambiente
  lcd.print("Temp: ");
  lcd.print(tempC, 1);
  lcd.print((char)223); 
  lcd.print("C ");

  lcd.setCursor(0, 1);   //Mostra a umidade da plantação
  lcd.print("Umidade: ");
  lcd.print(umidS, 1);
  lcd.print("%  ");

  delay(1000);

*/
}
 /*

000000  000000  000000  000000  000000  000000  000000          000000  000000  000000  000000
000000  000000  000000  000000  000000  000000  000000          000000  000000  000000  000000
00  00  00  00  00  00     000  000       00    000                000  00  00     000  000    
000000  000000  00  00     000  000000    00    000000          000000  00  00  000000  000000
000     0000    00  00  0  000  000       00    000             000     00  00  000        000
000     00  00  000000  000000  000000    00    000000          000000  000000  000000  000000


 
*/