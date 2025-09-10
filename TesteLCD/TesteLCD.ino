<<<<<<< HEAD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
=======
//EQUIPE 1503 PROJETE 2025
//Código para utilização do Display LCD 16x2 I2C
//Instalar biblioteca: LiquidCrystal_I2C
/*
Pinagem: 
I2C	  Arduino Mega 2560
GND 	GND
VCC	  5V
SDA	  D20
SCL	  D21
*/
>>>>>>> 34d271d043c4e5e2d2cd1aeaf666dc126628df40

// Inicializa o LCD no endereço 0x27 (com 16 colunas e 2 linhas)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pino analógico conectado ao LM35
const int lm35Pin = A0;

void setup() {
  // Inicializa o LCD
  lcd.init();
  lcd.backlight();

  // Mensagem de inicialização
  lcd.setCursor(0, 0);
  lcd.print("Temp do ar");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Leitura analógica do LM35
  int valorAnalogico = analogRead(lm35Pin);

  // Converte a leitura para temperatura (em Celsius)
  float temperaturaC = (valorAnalogico * 5.0 * 100.0) / 1023.0;

  // Exibe no LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperaturaC, 1);  // 1 casa decimal
  lcd.print((char)223);        // Símbolo de grau
  lcd.print("C   ");

  delay(1000);  // Atualiza a cada segundo
}
<<<<<<< HEAD
=======

//Esse código foi feito para testar o LCD

>>>>>>> 34d271d043c4e5e2d2cd1aeaf666dc126628df40
