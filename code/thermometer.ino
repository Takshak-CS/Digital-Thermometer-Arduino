#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 2
// DHT11 sensor
#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10) 
Adafruit_BMP280 bmp(BMP_CS); // use hardware SPI
// LCD I2C (Address 0x27 might differ)
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup(void)

{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
  dht.begin();
    if (!bmp.begin()) {
    Serial.println("Could not find BMP280 sensor!");
    while (1);
  }

  lcd.init();
  lcd.backlight();
}

void loop(void){ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  float humDHT = dht.readHumidity();
  float presBMP = bmp.readPressure();
  float tempC = sensors.getTempCByIndex(0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(tempC, 1);
  lcd.print("C H:");
  lcd.print(humDHT, 0);
  lcd.print("%");

  // Set the cursor for the second line to display pressure
  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print(presBMP);  // Display pressure in Pa
  lcd.print("Pa");
  
  
  delay(1000);
}