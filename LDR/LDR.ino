int ldrPin = A0;
int ledPin = 7;
String ledStatus;
unsigned long time;

int LED_ACTIVATION_VALUE = 500;
int SERIAL_OUTPUT_FREQUENCY = 500;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  int ldrValue = analogRead(ldrPin);
  
  if(ldrValue <= LED_ACTIVATION_VALUE){
    digitalWrite(ledPin, HIGH);
    ledStatus = "ON";
  }
  else{
    digitalWrite(ledPin, LOW);
    ledStatus = "OFF";
  }
  if(millis() - time >= SERIAL_OUTPUT_FREQUENCY){
    time = millis();
    Serial.println((String)"LIGHT SENSOR: " + ldrValue);
    Serial.println("LED STATUS: " + ledStatus);
  }
  
}
