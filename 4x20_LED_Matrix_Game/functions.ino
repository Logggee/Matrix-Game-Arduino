void Display(byte byte1, byte byte2, byte byte3, int displayTime)               //Funktion um drei bytes in die Schieberegister zu schieben
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

void Jump()                 //ISR
{
  noInterrupts();
  jumpFlag = 1;
}

void Homescreen()                                        //Blinckender Startbildschirm
{
  noInterrupts();
  while(digitalRead(BUTTON) == HIGH)
  {
    for(int i=0; i<=500; i++)
    {
      Display(player[0], player[1], player[2], 1);
      Display(block[3], block[4], block[5], 1);
    }

    for(int i=0; i<=1000; i++)
    {
      Display(0xF0, 0x00, 0x00, 1);
    }
  }
  interrupts();
}

void ChrashDetection(byte blockCounter)                                        //Crash Detection falls gar kein Sprung ausgelöst wurde
{
  if(bitRead(player[2], 3) == 1 && bitRead(block[blockCounter], 3) == 1)
  {
    Homescreen();
    blockCounter_byte3 = 65;
  }
}

bool CrashDetection(byte player_Counter_byte3, byte block_Counter_byte3, byte player_Counter_byte1, byte block_Counter_byte1)   //Crash detection wenn ein Sprung ausgelöst wurde
{
  if(bitRead(player[player_Counter_byte3], 3) == 1 && bitRead(block[block_Counter_byte3], 3) == 1)   //Kontrolle ob ein Block in der gleichen Zeile befindet wie der palyer
  {
    if(player[player_Counter_byte1] == 0x70 || player[player_Counter_byte1] == 0xB0)     //Die Beiden möglichkeiten eines Crashes während einer Sprunganimation
    {
      Homescreen();
      blockCounter_byte3 = 65;           //Globale Variable wird geändert
      return true;                       //retur true wenn ein Crash aufgetreten ist
    }
  }
  return false;                          //return false falls kein crash detectet wurde
}