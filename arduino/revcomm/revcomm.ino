#include <Servo.h>

Servo servo1;

// Constants
const int ACK  = 0x01;
const int INIT = 0x55;

void setup()
{
  Serial.begin(115200);
  servo1.attach(9);
  init_comm();
}

void init_comm()
{
  while(!Serial.available())
  {
    int init_val = Serial.read();
    if(init_val == INIT)
    {
      Serial.write(ACK);
      break;
    }
  }
}

void loop()
{
  if(Serial.available())
  {
    int new_pos = Serial.read();
    servo1.write(new_pos);
    Serial.write(ACK);
  }
}
