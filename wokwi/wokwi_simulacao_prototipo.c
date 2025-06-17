#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define LDR_SENSOR 9
#define LDR_PLACA 8

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  sensors.begin();
  pinMode(LDR_SENSOR, INPUT);
  pinMode(LDR_PLACA, INPUT);
}

void loop() {
  int ldrSensor = digitalRead(LDR_SENSOR);
  int ldrPlaca = digitalRead(LDR_PLACA);

  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  lcd.clear();

  if (ldrSensor != ldrPlaca) {
    lcd.setCursor(0, 0);
    lcd.print("Alerta: perda de");
    lcd.setCursor(0, 1);
    lcd.print("eficiencia solar");
  } else if (ldrSensor == LOW && ldrPlaca == LOW) {
    lcd.setCursor(0, 0);
    lcd.print("Painel eficiente");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(tempC);
    lcd.print(" C");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Baixa geracao");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(tempC);
    lcd.print(" C");
  }

  delay(2000);
}
