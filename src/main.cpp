#include <Arduino.h>


const byte relay_pins[4][4] = 
{
  {A0, A1, A2, A3},
  {A4, A5, A6, A7},
  {9, 8, 7, 6},
  {5, 4, 3, 2}
};

bool state_array[4][4];

void setup()
{
  for(auto &row:relay_pins)
  {
    for(auto &pin:row)
    {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }
  }
  Serial.begin(9600);
}

void loop()
{

}

void set_pins()
{
  for(byte i = 0; i<4; i++)
  {
    for(byte j = 0; j<4; j++)
    {
      digitalWrite(relay_pins[i][j], state_array[i][j]);
    }
  }
}

void read_serial()
{
  while(Serial.available())
  {
    if(Serial.read() == '#')
    {
      char serial_buffer[20];
      Serial.readBytesUntil(0x0d, serial_buffer, sizeof(serial_buffer-1));
      char* arguments[4];
      char* argument = strtok(serial_buffer, ",");
      while(strtok != nullptr)
      {
        arguments
      }
                




    }
  }
}