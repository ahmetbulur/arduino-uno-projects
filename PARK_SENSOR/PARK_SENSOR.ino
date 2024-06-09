#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long time1,time2,time3;
int echoPin=2; // Sensörün üzerindeki alıcı(echo) mikrofon pini
int trigPin=3; // Sensörün üzerindeki verici(trig) ses hoparlör pini
int buzzerPin=4; // Engele yaklaştığında öten buzzer pini
int ledPin=5;

float Buzzer_LED_Freq_Max = 1000;
float Buzzer_LED_Freq_Min = 10;

float Dist_Max = 100;
float Dist_Min = 10;

float Current_Dist = 50;
float Current_Freq = 0;

int Update_Freq = 500;
int Update_LCD = 200;

float time,distance;  //sure ve mesafe değişkenlerini float(kesirli sayı) veri tipinde tanımlıyoruz.

float freqUpdate(int CurrentDist){
  float current = 0;
  current = ((CurrentDist - Dist_Min) / (Dist_Max - Dist_Min) * (Buzzer_LED_Freq_Max - Buzzer_LED_Freq_Min))+Buzzer_LED_Freq_Min;
  return current;
}

void setup() {
  pinMode(trigPin, OUTPUT); // Giriş ve çıkış pinlerini ayarlıyoruz.
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin,OUTPUT); 
  lcd.begin();
  Serial.begin(9600);  //Seri monitörü başlatmak için gerekli parametreyi giriyoruz.
}

void alarm1(int time){
  tone(buzzerPin, 400); // 15 hertzlik sinyal gönderiyoruz.
  digitalWrite(ledPin, HIGH);
  delay(time);           // 100 msde bir
  noTone(buzzerPin);    // sinyali kapatıyoruz
  digitalWrite(ledPin, LOW);
  delay(time);  
}

void alarm2(){
  tone(buzzerPin, 400); // 15 hertzlik sinyal gönderiyoruz.
  digitalWrite(ledPin, HIGH);
  //delay(50);           // 50 msde bir
}

void loop() 
{  
  digitalWrite(trigPin,LOW);//Trig pinini kapatır.
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);// Sensörün Trig pininden uygulanan sinyal 40 kHz frekansında ultrasonik bir ses yayılmasını sağlar.
  delayMicroseconds(5);
  digitalWrite(trigPin , LOW);//Trig pinini kapatır.
  time = pulseIn(echoPin, HIGH);//Bu ses dalgası herhangi bir cisme çarpıp sensöre geri döndüğünde, Echo pini aktif hale gelir.
  Current_Dist = (time / 29.1) /2; //Echo pininden alınan değer yani "süre" değeri işlemden geçiriliyor.
  
  if(millis() - time1 >= Update_Freq){
    time1 = millis();
    Current_Freq = (Current_Dist - Dist_Min) * (Buzzer_LED_Freq_Max - Buzzer_LED_Freq_Min) / (Dist_Max - Dist_Min) + Buzzer_LED_Freq_Min;
    if(Current_Freq < 0)
      Current_Freq = 0;
  }
  if(millis() - time2 >= Update_LCD){
    time2 = millis();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DISTANCE :      ");
    if(Current_Dist < 10)
      lcd.setCursor(15, 0);
    if(Current_Dist >= 10 || Current_Dist < 100)
      lcd.setCursor(14, 0);
    if(Current_Dist >= 100)
      lcd.setCursor(13, 0);
    lcd.print(Current_Dist);
    lcd.setCursor(0, 1);
    lcd.print("FREQUENCY :     ");
    if(Current_Freq < 10)
      lcd.setCursor(15, 1);
    if(Current_Freq >= 10 || Current_Freq < 100)
      lcd.setCursor(14, 1);
    if(Current_Freq >= 100 || Current_Freq < 1000)
      lcd.setCursor(13, 1);
    if(Current_Freq >= 1000)
      lcd.setCursor(12, 1);
    lcd.print(Current_Freq);
  }
  if(millis() - time3 >= Current_Freq){
    time3 = millis();
    if (Current_Dist > Dist_Min && Current_Dist <= Dist_Max ){
     alarm1(Current_Freq);
    }
    else if(Current_Dist > 0 && Current_Dist <= Dist_Min){
     alarm2();
    }
  }
}
