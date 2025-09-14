#include <Wire.h>
#include <LiquidCrystal_I2C.h>

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
  lcd.print("C");

  delay(1000);  // Atualiza a cada segundo
}
