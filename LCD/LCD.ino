#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String text0, text1;
String scr_stat0, scr_stat1, scr_direction0, scr_direction1;
int scr_speed0, scr_speed1;
int i = 0;
int k = 0;
int entry_no = 0;
unsigned long time0, time1;

void setup() {
  lcd.begin();
  Serial.begin(9600);
  Serial.print(" STATUS SCREEN\nLCD ROW 0 (UP)\n1 – TEXT : ");
  Serial.println(text0);
  Serial.print("2 – SCROLLING STATUS : ");
  Serial.println(scr_stat0);
  Serial.print("3 – SCROLLING DIRECTION : ");
  Serial.println(scr_direction0);
  Serial.print("4 – SCROLLING SPEED (MS): ");
  Serial.println(scr_speed0);
  Serial.print("LCD ROW 1 (DOWN)\n5 – TEXT : ");
  Serial.println(text1);
  Serial.print("6 – SCROLLING STATUS : ");
  Serial.println(scr_stat1);
  Serial.print("7 – SCROLLING DIRECTION : ");
  Serial.println(scr_direction1);
  Serial.print("8 – SCROLLING SPEED (MS): ");
  Serial.println(scr_speed1);
}
void loop() {

    while(entry_no == 0){
      if (Serial.available() > 0){
          
          Serial.print("\nROW 0 - TEXT: ");
          text0 = Serial.readString();
          Serial.println(text0);
          entry_no++;
      }
    }
    while(entry_no == 1){
      if (Serial.available() > 0){
          
          String scr_no = Serial.readString();
          if(scr_no == "d"){
            scr_stat0 = "DISABLED";
            Serial.println("ROW 0 - SCROLLING: DISABLED");
          }
          else if(scr_no == "e"){
            scr_stat0 = "ENABLED";
            Serial.println("ROW 0 - SCROLLING: ENABLED");
          }
          entry_no++;
      }
    }
    while(entry_no == 2){
      if (Serial.available() > 0){
        
        String dir_no = Serial.readString();
        if(dir_no == "l"){
          scr_direction0 = "LEFT";
          Serial.println("ROW 0 - SCROLLING DIRECTION: LEFT");
        }
        else if(dir_no == "r"){
          scr_direction0 = "RIGHT";
          Serial.println("ROW 0 - SCROLLING DIRECTION: RIGHT");
        }
        entry_no++;
      }
    }
    while(entry_no == 3){
      if (Serial.available() > 0){
          Serial.print("ROW 0 - SCROLLING SPEED (MS): ");
          String speed = Serial.readString();
          scr_speed0 = speed.toInt();
          Serial.println(scr_speed0);
          entry_no++;
      }
    }
    while(entry_no == 4){
      if (Serial.available() > 0){
          
          Serial.print("ROW 1 - TEXT: ");
          text1 = Serial.readString();
          Serial.println(text1);
          entry_no++;
      }
    }
    while(entry_no == 5){
      if (Serial.available() > 0){
          
          String scr_no = Serial.readString();
          if(scr_no == "d"){
            scr_stat1 = "DISABLED";
            Serial.println("ROW 1 - SCROLLING: DISABLED");
          }
          else if(scr_no == "e"){
            scr_stat1 = "ENABLED";
            Serial.println("ROW 1 - SCROLLING: ENABLED");
          }
          entry_no++;
      }
    }
    while(entry_no == 6){
      if (Serial.available() > 0){
        
        String dir_no = Serial.readString();
        if(dir_no == "l"){
          scr_direction1 = "LEFT";
          Serial.println("ROW 1 - SCROLLING DIRECTION: LEFT");
        }
        else if(dir_no == "r"){
          scr_direction1 = "RIGHT";
          Serial.println("ROW 1 - SCROLLING DIRECTION: RIGHT");
        }
        entry_no++;
      }
    }
    while(entry_no == 7){
      if (Serial.available() > 0){
          Serial.print("ROW 1 - SCROLLING SPEED (MS): ");
          String speed = Serial.readString();
          scr_speed1 = speed.toInt();
          Serial.println(scr_speed1);
          entry_no++;
      }
    }
    while(entry_no == 8){
      Serial.print("\nSTATUS SCREEN\nLCD ROW 0 (UP)\n1 – TEXT : ");
      Serial.println(text0);
      Serial.print("2 – SCROLLING STATUS : ");
      Serial.println(scr_stat0);
      Serial.print("3 – SCROLLING DIRECTION : ");
      Serial.println(scr_direction0);
      Serial.print("4 – SCROLLING SPEED (MS): ");
      Serial.println(scr_speed0);
      Serial.print("LCD ROW 1 (DOWN)\n5 – TEXT : ");
      Serial.println(text1);
      Serial.print("6 – SCROLLING STATUS : ");
      Serial.println(scr_stat1);
      Serial.print("7 – SCROLLING DIRECTION : ");
      Serial.println(scr_direction1);
      Serial.print("8 – SCROLLING SPEED (MS): ");
      Serial.println(scr_speed1);
      
      time0 = millis();
      time1 = millis();
      entry_no++;
    }

  //---------------------------------------------------------------------------------------------------------------------------------

  if(scr_stat0 == "DISABLED"){ // no scrolling
    lcd.setCursor(0, 0);
    lcd.print(text0);
  }
  else{
    if(scr_direction0 == "LEFT"){ //row 0 - scroll left
      for(int j = 0; j < 16; j++){
        lcd.setCursor(j, 0);
        lcd.print(text0[(i+j)%text0.length()]);
      }
    }
    else{ //row 0 - scroll right
      for(int j = 0; j < 16; j++){
        lcd.setCursor(j, 0);
        lcd.print(text0[(text0.length()+j-(i%text0.length()))%text0.length()]);
      }
    }
  }
  if(scr_stat1 == "DISABLED"){ // no scrolling
    lcd.setCursor(0, 1);
    lcd.print(text1);
  }
  else{
    if(scr_direction1 == "LEFT"){ //row 1 - scroll left
      for(int j = 0; j < 16; j++){
        lcd.setCursor(j, 1);
        lcd.print(text1[(k+j)%text1.length()]);
      }
    }
    else{ //row 1 - scroll right
      for(int j = 0; j < 16; j++){
        lcd.setCursor(j, 1);
        lcd.print(text1[(text1.length()+j-(k%text1.length()))%text1.length()]);
      }
    }
  }
  
  if(millis() - time0 >= scr_speed0){
    time0 = millis();
    i++;
    lcd.clear();
  }
  if(millis() - time1 >= scr_speed1){
    time1 = millis();
    k++;
    lcd.clear();
  }
  
}
