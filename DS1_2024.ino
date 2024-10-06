#include "MIDIUSB.h"
#include "Wire.h"

void setup()
{
  Serial.begin(115200); // Open USB Midi port
  Wire.begin(0x08); // Open I2C port at address 8
  Wire.setClock(400000UL); // Set speed to 400kHz (max
  Wire.onReceive(receiveEvent); // Watch for inbound data on I2C
}

void loop()
{
}

void receiveEvent(int bytecount)
{
  byte byteArray[4];
  while (Wire.available())
  {
    for (int i=0;i<4; i++)
    {
      byteArray[i] = Wire.read()-0;
    }

    switch (byteArray[0])
    {
      case 0:
        noteOn(byteArray[1], byteArray[2], byteArray[3]);
        break;
      case 1:
        noteOff(byteArray[1], byteArray[2], byteArray[3]);
        break;
      case 2:
        controlChange(byteArray[1], byteArray[2], byteArray[3]);
        break;
    }
    MidiUSB.flush();
  }
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = { 0x09, 0x90 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = { 0x08, 0x80 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = { 0x08, 0xB0 | channel, control, value };
  MidiUSB.sendMIDI(event);
}
