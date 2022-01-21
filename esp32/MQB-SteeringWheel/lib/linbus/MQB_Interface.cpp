
#include "MQB_Interface.hpp"

void MQB_Interface::setup(void)
{
  LinBus.baud = 19200;
  LinBus.pin_rx = LIN_RX;
  LinBus.pin_tx = LIN_TX;
  LinBus.verboseMode = -1;
}

void MQB_Interface::loop(void)
{
  lastKeyPressed = MQB_NONE;
  readLinData(0x0E);
  readLinData(0x0F);

  if (lastKeyPressed == MQB_UP)
  {
    Serial.printf("Value : %d \n", lightValue);
    lightValue = lightValue + 10;
  }
  if (lastKeyPressed == MQB_DOWN)
  {
    Serial.printf("Value : %d \n", lightValue);
    lightValue = lightValue - 10;
  }

  // Send Lin Data:
  LinBus.LinMessage[0] = lightValue;
  LinBus.LinMessage[1] = 0xFF;
  LinBus.LinMessage[2] = 0xDC;
  LinBus.LinMessage[3] = 0x7F;
  LinBus.writeFrame(0x0D, 4);
}
void MQB_Interface::dumpBuffer()
{
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.printf("%02X ", LinBus.LinMessage[i]);
  }
  Serial.println();
  delay(1000);
}
void MQB_Interface::readLinData(uint8_t frameId)
{
  bool chkSumValid = LinBus.readFrame(frameId);
  if (chkSumValid)
  {
    //dumpBuffer();
    if (frameId == 0x0E && LinBus.LinMessage[1] != 0x00)
    {
      uint8_t linMessage = LinBus.LinMessage[1];
      //Serial.printf("Valid Message1 : %02X \n", linMessage);
      for (uint8_t i = 0; i < sizeof(MQBKeyCodes); i++)
      {
        if (linMessage == MQBKeyCodes[i])
        {
          MQBKeys key = MQBKeys(i);
          lastKeyPressed = key;
          //keyQueue.push(key);
        }
      }
    }
    if (frameId == 0x0F && LinBus.LinMessage[2] != 0x80)
    {
      uint8_t linMessage = LinBus.LinMessage[2];
      //Serial.printf("Valid Message2 : %02X \n", linMessage);

      for (uint8_t i = 0; i < sizeof(MQBKeyCodes); i++)
      {
        if (linMessage == MQBKeyCodes[i])
        {
          MQBKeys key = MQBKeys(i);
          lastKeyPressed = key;
          //keyQueue.push(key);
        }
      }
    }
    // Special Treatment of On/Off Key:
    if (frameId == 0x0F && LinBus.LinMessage[3] == 0x2A)
    {
      lastKeyPressed = MQB_ONOFF;
    }
    // Special Treatment of Horn Key:
    if (frameId == 0x0E && LinBus.LinMessage[7] == 0x02)
    {
      lastKeyPressed = MQB_HORN;
    }
  }
}
bool MQB_Interface::hasKeysPressed()
{
  return lastKeyPressed == MQB_NONE ? false : true;
}

byte MQB_Interface::getLastKey()
{
  return lastKeyPressed;
}

String MQB_Interface::getKeyName(byte key)
{
  String name = MQBKeyNames[key];
  return name;
}