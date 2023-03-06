#include <ESP_CapSense.h>

/*** Define the pins used on Feather board here ***/
const int sendPin = 13; // pin 13
const int readPin = 26; // pin 26 (aka A0)

/**************************************************/

CapacitiveSensor cap_sensor = CapacitiveSensor(sendPin, readPin);        // resistor between pins 4 (A5) & 33, pin 33 is read pin
int numberOfSamples = 30;

void setup()
{
  cap_sensor.set_CS_AutocaL_Millis(0xFFFFFFFF);  // turns off autocalibrate

  Serial.begin(9600);
}

void loop()                    
{
  // Taking capacitive readings 50 times (50 being the number of samples defined at the top of file)
  long total =  cap_sensor.capacitiveSensor(numberOfSamples);

  Serial.println(total);

  delay(10);  // slowing down output by waiting for 10 ms each time
}