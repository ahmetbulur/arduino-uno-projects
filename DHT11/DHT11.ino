#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define dhtPin 8  
#define buttonPin 2

DHT dht(dhtPin, DHT11);//you can also use pins 3, 4, 5, 12, 13 or 14
LiquidCrystal_I2C lcd(0x27, 16, 2);

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  dht.begin();// initialize the sensor
  lcd.begin();// initialize lcd
  pinMode(buttonPin, INPUT);
}

void loop() {

  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState == HIGH && lastButtonState == LOW) {
    buttonPushCounter++;
  }
  lastButtonState = buttonState;

  if(buttonPushCounter % 2 == 0){
    lcd.setCursor(14,0);
    lcd.print("TR");
    
    lcd.setCursor(0,0);
    lcd.print("SIC(C):"); 
    if(dht.readTemperature() < 10)
      lcd.print("  ");
    else if(dht.readTemperature() < 100)
      lcd.print(" ");
    lcd.print(dht.readTemperature()); //print the temperature(C)
    lcd.setCursor(10,0);
    lcd.print(",");

    lcd.setCursor(0,1);
    lcd.print("NEM(%): "); 
    lcd.print(dht.readHumidity()); //print the humidity
    lcd.setCursor(10,1);
    lcd.print(",");
  }
  else{
    lcd.setCursor(14,0);
    lcd.print("EN");
    
    lcd.setCursor(0,0);
    lcd.print("TEM(F):"); 
    if(dht.readTemperature()*1.8+32 < 10)
      lcd.print("  ");
    else if(dht.readTemperature()*1.8+32 < 100)
      lcd.print(" ");
    lcd.print(dht.readTemperature()*1.8+32); //print the temperature(F)
    
    lcd.setCursor(0,1);
    lcd.print("HUM(%): "); 
    lcd.print(dht.readHumidity()); //print the humidity
  }
}
