#include <Keyboard.h>
#include <Mouse.h>

int pinw=2;
int pine=3;
int pind=4;
int pinc=5;
int pinx=6;
int pinz=7;
int pina=8;
int pinq=9;

void setup() 
{
  for(int i=pinw; i<=pinq; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }
  return;
}

void loop() 
{
  if (digitalRead(pinw) == HIGH)
  {
    Keyboard.write('W');
    delay(1);
  }
  
  if (digitalRead(pine) == HIGH)
  {
    Keyboard.write('E');
    delay(1);
  }

  if (digitalRead(pind) == HIGH)
  {
    Keyboard.write('D');
    delay(1);
  }

  if (digitalRead(pinc) == HIGH)
  {
    Keyboard.write('C');
    delay(1);
  }

  if (digitalRead(pinx) == HIGH)
  {
    Keyboard.write('X');
    delay(1);
  }

  if (digitalRead(pinz) == HIGH)
  {
    Keyboard.write('Z');
    delay(1);
  }

  if (digitalRead(pina) == HIGH)
  {
    Keyboard.write('A');
    delay(1);
  }

  if (digitalRead(pinq) == HIGH)
  {
    Keyboard.write('Q');
    delay(1);
  }
}
