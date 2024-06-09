int a=2;
int b=3;
int c=4;
int d=5;
int e=6;
int f=7;
int g=8;
int dp=9;

int led = 13;
int pir = 12;
int pirState;

int time = 20;

int hexadec[16] = {0b1111110, 0b0110000, 0b1101101, 0b1111001,
                   0b0110011, 0b1011011, 0b1011111, 0b1110000,
                   0b1111111, 0b1111011, 0b1110111, 0b0011111,
                   0b1001110, 0b0111101, 0b1001111, 0b1000111};

void setup()
{
  Serial.begin(9600);
  
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);
  
  pinMode(led, OUTPUT);
  pinMode(pir,INPUT);
}

void loop()
{
  pirState = digitalRead(pir);
  Serial.print(pirState);
  if (pirState == HIGH)
  {
    Serial.print("hareket ");
    if(time > 0)
      digitalWrite(led, HIGH);
    counter(time);
    digitalWrite(led, LOW);
  }
}
int counter(int time){
  while(time > 16){
    for(int pin = a; pin < g; pin++){
      digitalWrite((pin-2+5)%6+2,0);
      digitalWrite(pin, 1);
      delay(1000);
      --time;
      if(time <= 16)
        break;
    }
  }
  for(int i = time-1; i >= 0; i--){
    for(int pin = a; pin <= g; pin++)
      digitalWrite(pin, bitRead(hexadec[i], g-a-pin+2));
    delay(1000);
    --time;
  }
  for(int pin = a; pin < g; pin++)
    digitalWrite(pin, 0);
}
