int pin1=9;
int pin2=10;
int pin3=11;
int pin4=12;
int pin5=13;
int increment;
int wait_time;
int i=0;
int entry_no=0;

void setup() {
  Serial.begin(9600);
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
  pinMode(pin5,OUTPUT);
}
void loop() {
 
  while (true && entry_no == 0){

    if(Serial.available()>0){
      increment = Serial.parseInt();

      if(increment >= 1 && increment <= 31){
        entry_no++;
        Serial.print("increment: ");
        Serial.print(increment);
          break;
      }
      else{
        Serial.print("wrong input,please enter increment between 1-31\n");
      }
    }
  }
  while (true && entry_no == 1){

    if(Serial.available()>0){
      wait_time = Serial.parseInt();

      if(wait_time >= 1 && wait_time <= 10000){
        entry_no++;
        Serial.print(", wait_time: ");
        Serial.print(wait_time);
          break;
      }
      else{
        Serial.print("wrong input,please enter wait time between 1-10000\n");
      }
    }
  }

  digitalWrite(pin5,LOW);
  digitalWrite(pin4,LOW);
  digitalWrite(pin3,LOW);
  digitalWrite(pin2,LOW);
  digitalWrite(pin1,LOW);

  i = i + increment;

  if((i % 2) > 0) { digitalWrite(pin1, HIGH); } else { digitalWrite(pin1, LOW); }
  if((i % 4) > 1) { digitalWrite(pin2, HIGH); } else { digitalWrite(pin2, LOW); }
  if((i % 8) > 3) { digitalWrite(pin3, HIGH); } else { digitalWrite(pin3, LOW); }
  if((i % 16) > 7) { digitalWrite(pin4, HIGH); } else { digitalWrite(pin4, LOW); }
  if((i % 32) > 15) { digitalWrite(pin5, HIGH); } else { digitalWrite(pin5, LOW); }

  delay(wait_time);
}
