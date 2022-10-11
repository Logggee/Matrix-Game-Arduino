#define LATCH 9
#define CLOCK 10
#define DATA 8
#define SERCLK 3
#define OE 2
#define BUTTON 4

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

byte player[]
{
  0x70, 0x00, 0x08,
  0xB0, 0x00, 0x08,
  0xD0, 0x00, 0x08,
  0xE0, 0x00, 0x08,
  0xE0, 0x00, 0x08,
  0xD0, 0x00, 0x08,
  0xB0, 0x00, 0x08,
  0x70, 0x00, 0x08,
};

byte counter_byte1 = -3;
byte counter_byte2 = -2;
byte counter_byte3 = -1;
byte displayByte1;
byte displayByte2;
byte displayByte3;

void setup() 
{
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(SERCLK, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() 
{
  if(digitalRead(BUTTON) == LOW)                                                                        //Display of player jump
  {
    for(byte i=0; i<8; i++)
    {
      counter_byte1 += 3;
      counter_byte2 += 3;
      counter_byte3 += 3;

      Display(player[counter_byte1], player[counter_byte2], player[counter_byte3], 200);

      if(counter_byte1 == 18)
      {
        counter_byte1 = -3;
        counter_byte2 = -2;
        counter_byte3 = -1;
      } 
    }
  }

  else                                                                                                  //Display of the block
  {
    counter_byte1 += 3;
    counter_byte2 += 3;
    counter_byte3 += 3;

    displayByte1 = block[counter_byte1] | 0x70;
    displayByte2 = block[counter_byte2] | 0x00;
    displayByte3 = block[counter_byte3] | 0x08;
    
    Display(displayByte1, displayByte2, displayByte3, 200);

    if(counter_byte3 == 65)
    {
      counter_byte1 = -3;
      counter_byte2 = -2;
      counter_byte3 = -1;
    }
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