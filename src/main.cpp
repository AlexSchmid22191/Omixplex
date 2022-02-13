#include <Arduino.h>

// Pin definition
const byte relay_pins[4][4] =
    {
        {A0, A1, A2, A3},
        {A4, A5, A6, A7},
        {9, 8, 7, 6},
        {5, 4, 3, 2}};

void setup()
{
  for (auto &row : relay_pins)
  {
    for (auto &pin : row)
    {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }
  }
  Serial.begin(9600);
}

void loop()
{
  while (Serial.available())
  {
    if (Serial.read() == '#')
    {
      char serial_buffer[25];
      Serial.readBytesUntil(0x0d, serial_buffer, sizeof(serial_buffer - 1));

      //TODO: Refactor string tokening
      if (strtok(serial_buffer, ",") == nullptr)
        Serial.println("Invalid command!");
      else
      {
        //*******************************************************************************************
        // Sets a single relay
        //*******************************************************************************************
        if (!strncmp(serial_buffer, "set", 3))
        {
          byte args[3];
          // Validate that args were parsed successfull
          if (!args_to_bytes(args, 3))
            Serial.println("Invalid command!");
          // Validate that arg values are within range
          if (args[0] < 1 || args[0] > 4 || args[1] < 1 || args[1] > 4 || args[3] < 0 || args[0] > 1)
            Serial.println("Invalid command!");
          digitalWrite(relay_pins[args[0]][args[1]], args[2]);
          Serial.println("ack");
        }

        //*******************************************************************************************
        // Gets the state of a single relay
        //*******************************************************************************************
        if (!strncmp(serial_buffer, "get", 3))
        {
          byte args[3];
          // Validate that args were parsed successfull
          if (!args_to_bytes(args, 3))
            Serial.println("Invalid command!");
          // Validate that arg values are within range
          if (args[0] < 1 || args[0] > 4 || args[1] < 1 || args[1] > 4 || args[3] < 0 || args[0] > 1)
            Serial.println("Invalid command!");
          Serial.println(digitalRead(relay_pins[args[0]][args[1]]));
          return;
        }

        //*******************************************************************************************
        // Set all relays
        //*******************************************************************************************
        if (!strncmp(serial_buffer, "aset", 4))
        {
          byte args[16];
          // Validate that args were parsed successfull
          if (!args_to_bytes(args, 16))
            Serial.println("Invalid command!");
          // Validate that arg values are within range
          for (byte i = 0; i < 16; i++)
          {
            if (args[i] < 0 || args[i] > 1)
              Serial.println("Invalid command!");
          }
          for (byte i = 0; i < 4; i++)
          {
            for (byte j = 0; j < 4; j++)
            {
              digitalWrite(relay_pins[j][i], args[4 * j + i]);
            }
          }
          Serial.println("ack");
          return;
        }

        //*******************************************************************************************
        // get the state of all relays
        //*******************************************************************************************
        if (!strncmp(serial_buffer, "aget", 4))
        {
          for (byte i = 0; i < 4; i++)
          {
            for (byte j = 0; j < 4; j++)
            {
              Serial.print(digitalRead(relay_pins[j][i]));
              Serial.print(",");
            }
          }
          Serial.print("\n");
          return;
        }
      }
    }
  }
}

bool args_to_bytes(byte *arg_vals, byte argc)
{
  // TODO: Refactor this so that it calls strtol first with the args argument
  for (byte i = 0; i < argc; i++)
  {
    char *arg = strtok(nullptr, ",");
    if (arg == nullptr)
      return false;
    char *p_end;
    arg_vals[i] = (byte)strtol(arg, &p_end, 10);
    if (p_end == nullptr)
      return false;
  }
  return true;
}