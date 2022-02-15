#include <Arduino.h>
#include <ArduinoRS485.h>
#include <ArduinoModbus.h>

const int numCoils = 3;

// Pin definition
const byte relay_pins[16] = {A0, A1, A2, A3, A4, A5, A6, A7, 9, 8, 7, 6, 5, 4, 3, 2};

void setup()
{
  for (auto &pin : relay_pins)
  {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  
  Serial.begin(9600);
  while (!Serial);
  if (!ModbusRTUServer.begin(1, 9600))
  {
    Serial.println("Failed to start Modbus RTU Server!");
    while (1);
  }
  ModbusRTUServer.configureCoils(0x00, numCoils);

}

void loop()
{
  ModbusRTUServer.poll();
  for(byte coil = 0; coil<16; coil++)
  {
    bool coilValue = ModbusRTUServer.coilRead(coil);
    digitalWrite(relay_pins[coil], coilValue);
  }
}