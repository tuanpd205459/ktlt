#include "DHT.h"

#define DHTPIN 8     // what pin we're connected to
#include <LiquidCrystal.h>

#define DHTTYPE DHT11   // DHT 11 

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


DHT dht(DHTPIN, DHTTYPE);

const int LED_PIN = 13;

void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
 lcd.begin(16, 2);
  dht.begin();
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
 
  float h = dht.readHumidity();
  float t = dht.readTemperature();

 if (Serial.available()) {
    char receivedData = Serial.read(); // Đọc byte dữ liệu từ cổng serial

    // Kiểm tra nếu nhận được giá trị "1"
    if (receivedData == '1') {
      Serial.print(receivedData);
      digitalWrite(LED_PIN, HIGH); // Bật đèn LED
    }
    if (receivedData == '0') {
      Serial.print(receivedData);
      digitalWrite(LED_PIN, LOW); // Bật đèn LED
    }
 }


  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  }
 

  Serial.println(t);
  Serial.println(h);

  
  delay(100);
}
