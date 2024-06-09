const int buzzerPin = 11;
int entry_no = 0;

int soundDuration, silenceDuration, finishDuration;
String soundString;

void setup()
{
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  while(entry_no < 2){
    if(entry_no == 0){
      Serial.print("PLEASE ENTER SOUND DURATION (MS): ");
      entry_no++;
    }
    if(entry_no == 1){
      if (Serial.available() > 0){
        soundDuration = Serial.parseInt();
        if(soundDuration == 0){
          Serial.println("\nSOUND DURATION SHOULD NOT BE 0!");
          Serial.print("PLEASE ENTER SOUND DURATION (MS): ");
        }
        else{
          Serial.println(soundDuration);
          entry_no++;
        }
      }
    }
  }
  while(entry_no < 4){
    if(entry_no == 2){
      Serial.print("PLEASE ENTER SILENCE DURATION (MS): ");
      entry_no++;
    }
    if(entry_no == 3){
      if (Serial.available() > 0){
        silenceDuration = Serial.parseInt();
        Serial.println(silenceDuration);
        entry_no++;
      }
    }
  }
  while(entry_no < 6){
    if(entry_no == 4){
      Serial.print("PLEASE ENTER FINISH DURATION (MS): ");
      entry_no++;
    }
    if(entry_no == 5){
      if (Serial.available() > 0){
        finishDuration = Serial.parseInt();
        Serial.println(finishDuration);
        entry_no++;
      }
    }
  }
  while(entry_no < 8){
    if(entry_no == 6){
      Serial.print("PLEASE ENTER SOUND STRING : ");
      entry_no++;
    }
    if(entry_no == 7){
      if (Serial.available() > 0){
        soundString = Serial.readString();
        Serial.println(soundString);
        entry_no++;
      }
    }
  }
  
  for(int i = 0; i < soundString.length(); i++){
    
    if(soundString[i] == '1'){
      tone(buzzerPin, 494, soundDuration); // 494-si
      delay(soundDuration);
      noTone(buzzerPin);
      if(i != soundString.length()-1){
        delay(silenceDuration);
      }
      else{
        delay(finishDuration);
      }
    }
    else if(soundString[i] == '0')
      delay(soundDuration);
    
    
  
  }
}
