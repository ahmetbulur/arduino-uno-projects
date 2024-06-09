#include "HX711.h"
#include <LiquidCrystal_I2C.h>

HX711 scale;
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DOUT 2
#define CLK  3

float calibration_factor = -7050;
float gr, kg, lbs;

void setup() {
  Serial.begin(9600);
  scale.begin(DOUT, CLK);
  lcd.begin();
  
  scale.set_scale();
  scale.tare(); // reset scale
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  gr = scale.get_units(); // read weight data
  if (gr < 0) {
    gr *= -1;
  }
  kg = gr;
  lbs = kg * 2.205;

  lcd.setCursor(0,0);
  lcd.print("KG:  "); 
  if(kg > 20)
    lcd.print("OVER LIMIT");
  // print weight on lcd
  else
    lcd.print(kg);
  lcd.setCursor(0,1);
  if(lbs >= 100)
    lcd.print("LB: ");
  else
    lcd.print("LB:  ");  
  lcd.print(lbs);

  // change calibration_factor
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }
}
