#define LATCH 9
#define CLOCK 10
#define DATA 8
#define SERCLK 3
#define OE 2

void setup() 
{
  pinMode(LATCH,OUTPUT);
  pinMode(CLOCK,OUTPUT);
  pinMode(DATA,OUTPUT);
  pinMode(SERCLK,OUTPUT);
  pinMode(OE,OUTPUT);
}

void loop() 
{
  Display(0x3C, 0x00, 0x00, 1000);
}

void Display(byte byte1, byte byte2, byte byte3, byte displayTime)
{
  digitalWrite(SERCLK,HIGH);
  digitalWrite(OE,HIGH);
  digitalWrite(LATCH,LOW);
  shiftOut(DATA,CLOCK,MSBFIRST,byte1);
  shiftOut(DATA,CLOCK,MSBFIRST,byte2);
  shiftOut(DATA,CLOCK,MSBFIRST,byte3);
  digitalWrite(LATCH,HIGH);
  digitalWrite(OE,LOW);
  delay(displayTime);
  digitalWrite(SERCLK,LOW);
  digitalWrite(LATCH,LOW);
  digitalWrite(LATCH,HIGH);
}