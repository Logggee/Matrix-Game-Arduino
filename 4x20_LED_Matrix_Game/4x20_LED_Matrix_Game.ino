#define LATCH 9
#define CLOCK 10
#define DATA 8
#define SERCLK 3
#define OE 2

byte block[]
{
  0x38, 0x00, 0x00,
  0x3C, 0x00, 0x00,
  0x36, 0x00, 0x00,
  0x33, 0x00, 0x00,
  0x31, 0x80, 0x00,
  0x30, 0xC0, 0x00,
  0x30, 0x60, 0x00,
  0x30, 0x30, 0x00,
  0x30, 0x18, 0x00,
  0x30, 0x0C, 0x00,
  0x30, 0x06, 0x00,
  0x30, 0x03, 0x00,
  0x30, 0x01, 0x80,
  0x30, 0x00, 0xC0,
  0x30, 0x00, 0x60,
  0x30, 0x00, 0x30,
  0x30, 0x00, 0x18,
  0x30, 0x00, 0x0C,
  0x30, 0x00, 0x06,
  0x30, 0x00, 0x03,
  0x30, 0x00, 0x01,
  0x30, 0x00, 0x00,
};

byte counter_byte1 = 0;
byte counter_byte2 = 1;
byte counter_byte3 = 2;

void setup() 
{
  pinMode(LATCH,OUTPUT);
  pinMode(CLOCK,OUTPUT);
  pinMode(DATA,OUTPUT);
  pinMode(SERCLK,OUTPUT);
  pinMode(OE,OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  Display(block[counter_byte1], block[counter_byte2], block[counter_byte3], 1000);
  counter_byte1 += 3;
  counter_byte2 += 3;
  counter_byte3 += 3;
  if(counter_byte3 == 65)
  {
    counter_byte1 = 0;
    counter_byte2 = 1;
    counter_byte3 = 2;
  }
}

void Display(byte byte1, byte byte2, byte byte3, int displayTime)
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