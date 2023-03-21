#define LATCH 9
#define CLOCK 10
#define DATA 8
#define SERCLK 4
#define OE 3
#define BUTTON 2

byte block[]                //bytes um einen 2x2 Block von Rechts nach Links laufen zu lassen
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

byte player[]            //bytes um den player Punkt sprung Ablauf
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

byte blockCounter_byte1 = -3;         //Counter fur die drei Schieberegister, da in der Funktion nicht inkrementiert werden kann
byte blockCounter_byte2 = -2;
byte blockCounter_byte3 = -1;
byte playerCounter_byte1 = -3;
byte playerCounter_byte2 = -2;
byte playerCounter_byte3 = -1;
bool jumpFlag = 0;                   //Jump Flag das in der ISR gesetzt wird
bool crash = false;

//Prototypen der Funktionen
void Display(byte byte1, byte byte2, byte byte3, int displayTime);                                                                      //Schiebt drei bytes in die Schieberegister
void jump(volatile int count);                                                                                                          //ISR
void Homescreen();                                                                                                                      //Bei Spielbeginn blinkt die Anzeige und das Programm läuft nicht los
void CrashDetaction(byte blockCounter);                                                                                                //Chrash Detection falls kein Sprung ausgelöst wurde
bool CrashDetection(byte playerCounter_byte3, byte blockCounter_byte3, byte playerCounter_byte1, byte blockCounter_byte1);

void setup()                                                                                                                            //Setup aller Pins und Interrupt und ausführung von Homescreen
{
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(SERCLK, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON), Jump, FALLING);
  Homescreen();
}

void loop() 
{
  blockCounter_byte1 += 3;     
  blockCounter_byte2 += 3;
  blockCounter_byte3 += 3;

  if(jumpFlag == 1)                   //Wenn Interrupt ausgeführt wurde wird der Jump ablauf ausgeführt
  {
    for(byte e=0; e<=7; e++)
    {
      if(crash == true)
      {
        crash = false;
        break;
        break;
      }

      playerCounter_byte1 += 3;
      playerCounter_byte2 += 3;
      playerCounter_byte3 += 3;
      for(byte i=0; i<100; i++)
      {
        Display(player[playerCounter_byte1], player[playerCounter_byte2], player[playerCounter_byte3], 1);
        Display(block[blockCounter_byte1], block[blockCounter_byte2], block[blockCounter_byte3], 1);
      }
      crash = CrashDetection(playerCounter_byte3, blockCounter_byte3, playerCounter_byte1, blockCounter_byte1);
      blockCounter_byte1 += 3;
      blockCounter_byte2 += 3;
      blockCounter_byte3 += 3;

      if(blockCounter_byte3 >= 65)
      {
        blockCounter_byte1 = 0;
        blockCounter_byte2 = 1;
        blockCounter_byte3 = 2;
      }
    }

    playerCounter_byte1 = -3;
    playerCounter_byte2 = -2;
    playerCounter_byte3 = -1;
    jumpFlag = 0;    
    interrupts();
  }

  for(byte i=0; i<=100; i++)
  {
    Display(player[0], player[1], player[2], 1);
    Display(block[blockCounter_byte1], block[blockCounter_byte2], block[blockCounter_byte3], 1);
  }

  ChrashDetection(blockCounter_byte3);
  if(blockCounter_byte3 >= 65)
  {
    blockCounter_byte1 = -3;
    blockCounter_byte2 = -2;
    blockCounter_byte3 = -1;
  }
}