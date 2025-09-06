//Código para utilização do Display LCD 16x2 I2C
//Instalar biblioteca: LiquidCrystal_I2C
/*
Pinagem: 
I2C	  Arduino UNO
GND 	GND
VCC	  5V
SDA	  A4
SCL	  A5
*/

#include <Wire.h> 	//Biblioteca que permite a comunicação via I2C
#include <LiquidCrystal_I2C.h>	//Biblioteca do I2C

// Endereço I2C do display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  lcd.init();                      // Inicializa o LCD
  lcd.backlight();                 // Liga a luz de fundo

}

void loop() {
  
  // lcd.clear();
  // lcd.setCursor(2, 0);             // Define posição coluna 0 - 16, linha 0 - 1
  // lcd.print("PROJETE 2025");       // Escreve na primeira linha e inicia na primeira coluna
  // lcd.setCursor(1, 1);             // Define posição coluna 1, linha 1
  // lcd.print("EQUIPE: MT1503");     // Escreve na segunda linha
  // delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);             
  lcd.print("ProjetoSKYNATURE");       
  lcd.setCursor(1, 1);             
  lcd.print("HORTA VERTICAL");      
  delay(3000);

}
