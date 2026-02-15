#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SENSOR_CO A0
#define SENSOR_GAS A1
#define RELAY 7
#define BUZZER 8

LiquidCrystal_I2C lcd(0x27, 16, 2);

int umbralCO = 400;
int umbralGAS = 300;

void setup() {
  Wire.begin();
  lcd.init();
  lcd.backlight();

  pinMode(SENSOR_CO, INPUT);
  pinMode(SENSOR_GAS, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sistema listo");
  delay(1000);
  lcd.clear();
}

void loop() {

  int valorCO = analogRead(SENSOR_CO);
  int valorGAS = analogRead(SENSOR_GAS);

  Serial.print("CO: ");
  Serial.print(valorCO);
  Serial.print(" | GAS: ");
  Serial.println(valorGAS);

  bool peligro = false;

  if (valorCO > umbralCO || valorGAS > umbralGAS) {
    peligro = true;
  }

  if (peligro) {

    digitalWrite(RELAY, HIGH);
    delay(200);
    digitalWrite(BUZZER, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("!PELIGRO DETECT!");

    lcd.setCursor(0, 1);

    if (valorCO > umbralCO)
      lcd.print("CO ALTO");
    else
      lcd.print("GAS ALTO");

  } else {

    digitalWrite(RELAY, LOW);
    digitalWrite(BUZZER, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Todo en orden :D");
  }

  delay(1000);
}
