#include <OneWire.h> 
#include <DallasTemperature.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP280.h>

#define ONE_WIRE_BUS 2 

Adafruit_BMP280 bmp;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); 

LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  Serial.begin(9600);
   sensors.begin();

   lcd.begin();

    lcd.backlight();
    lcd.clear();

   if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

}

void loop() {
  // TEMPERATUUR BINNEN
  sensors.requestTemperatures();
  Serial.print("Temperature inside: "); 
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(" *C");

  lcd.setCursor(0, 0);
  lcd.print("Inside: ");
  lcd.setCursor(8, 0);
  lcd.print(sensors.getTempCByIndex(0));
  lcd.setCursor(14, 0);

  Serial.println();

  // TEMPERATUUR BUITEN
  Serial.print(F("Temperature outside: "));
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

  lcd.setCursor(0, 1);
  lcd.print("Outside: ");
  lcd.setCursor(9, 1);
  lcd.print(bmp.readTemperature());
  lcd.setCursor(14, 1);

  delay(500);

}
