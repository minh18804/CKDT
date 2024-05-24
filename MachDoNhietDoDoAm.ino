#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

#define DHT_PIN 9
#define DHT_TYPE DHT11
#define SMS_VCC 10
#define SMS_SIGNAL A3

LiquidCrystal_I2C lcd(0x27,20,4); 
DHT dht(DHT_PIN, DHT_TYPE);
byte degree[8] = { 
  0B01110, 
  0B01010, 
  0B01110, 
  0B00000, 
  0B00000, 
  0B00000, 
  0B00000, 
  0B00000 
};

void setup() {
  pinMode(SMS_SIGNAL, INPUT);
  pinMode(SMS_VCC, OUTPUT);
  lcd.init();
  lcd.backlight(); 
  lcd.print("Nhiet do: "); 
  lcd.setCursor(0,1); 
  lcd.print("Do am: "); 
  lcd.createChar(1, degree); 
  dht.begin();
  lcd.setCursor(0,2);
  lcd.print("Do am dat: ");
  delay(300);
} 
void loop() { 
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); 
  digitalWrite(SMS_VCC, HIGH);
  delay(1000);
  float sms = (1023-analogRead(SMS_SIGNAL))/1023.0*100;
  digitalWrite(SMS_VCC, LOW);
  if (isnan(t) || isnan(h)){}
  else { 
    lcd.setCursor(0,3);
    lcd.print("                    ");
    lcd.setCursor(10,0); 
    lcd.print(round(t)); 
    lcd.print(" "); 
    lcd.write(1); 
    lcd.print("C");
    lcd.setCursor(10,1); 
    lcd.print(round(h)); 
    lcd.print(" %");
    lcd.setCursor(11,2);
    lcd.print(round(sms));
    lcd.print(" %");
    lcd.setCursor(0,3);
    if(sms <= 35) {
      lcd.print("Can tuoi nuoc!");
    }
    else if(sms <= 80) {
      lcd.print("Cay du nuoc");
    }
    else {
      lcd.print("Tuoi qua nhieu nuoc");
    }
    delay(300);
  } 
} 