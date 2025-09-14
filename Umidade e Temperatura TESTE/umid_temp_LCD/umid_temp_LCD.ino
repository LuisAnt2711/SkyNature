#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Dá nome ás entradas
const int trimpot = A7;   //Umidade (Trimpot)
const int lm35pin = A0;   //Temperatura (LM35)

void setup() {

// Inicializa o LCD
  lcd.init();
  lcd.backlight();
  
// Mensagem de inicialização
  lcd.setCursor(0, 0);
  lcd.print("TemperaturaDoAr");
  lcd.setCursor(0, 1);
  lcd.print("UmidadeDoSolo");
  delay(3000);
  lcd.clear();

}

void loop() {

// Atribui uma variável para cada entrada
  int valorA0 = analogRead(lm35pin);   //Temperatura
  int valorA7 = analogRead(trimpot);   //Umidade

//Caucula o valor de cada um dos sensores
  float tempC = (valorA0 * 5.0 * 100.0) / 1023.0;   //Temperatura
  float umidS = (valorA7 * 100.0) / 1023.0;         //Umidade

//Escreve os valores no Serial Monitor a cada 1 segundo
  lcd.setCursor(14, 0);
  lcd.print("P1");

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC, 1);
  lcd.print((char)223); 
  lcd.print("C ");

  lcd.setCursor(0, 1);
  lcd.print("Umidade: ");
  lcd.print(umidS, 1);
  lcd.print("%  ");

  delay(1000);

}
//Por causa de utilizar um trimpot no lugar do Sensor de temperatura, o trimpot pode desrregular o valor emitido pelo LM35
//Então quando for testar algo relacionado ao LM35, deixe o Trimpot zerado no circuito