#include <Servo.h>

Servo servo1;
int margin = 180;
int pos = 1;
int direct = -1;

void setup()
{
  Serial.begin(115200);
  servo1.attach(9);
}

void loop()
{
  pos = (pos + 1) % 180;
  servo1.write(pos);
  servo1.write(180 - pos);
}
