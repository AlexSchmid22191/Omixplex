#include <Arduino.h>
#include <ArduinoModbus.h>

const byte numCoils = 16;

// Pin definition
const byte relay_pins[numCoils] = {5, 9, A4, A0, 4, 8, A5, A1, 3, 7, A6, A2, 2, 6, A7, A3};

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
  for(byte coil = 0; coil<numCoils; coil++)
  {
    bool coilValue = (bool)ModbusRTUServer.coilRead(coil);
    digitalWrite(relay_pins[coil], coilValue);
  }
}