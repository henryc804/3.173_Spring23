/**
 * Example program reading temperature from fiber
 */

#define PIN_NUMBER  33

#define SERIESRESISTOR  10000

// resistance at 25 degrees C
#define THERMISTORNOMINAL 2000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 4500

// WARNING: The Feather V2 analog read has some error in its readings. Change this number only if you are tring to calibrate the temperature readings to a known thermometer.
//    If you are calibrating, change the number in increments of 0.1 or 0.01.
const float voltageError = 0.14;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_NUMBER, INPUT);
}

void loop() {
  measureTherm();
  delay(100);  
}

void measureTherm() {
  // Taking multiple samples and averaging them to reduce noise
  float avg_reading = 0;  
  for (int cntr = 0; cntr < NUMSAMPLES; cntr++) {
    avg_reading += analogRead(PIN_NUMBER);
  }
  avg_reading /= NUMSAMPLES;
  
  Serial.print("Analog reading "); 
  Serial.println(avg_reading);
  
  // convert the value to resistance
  float nodeVoltage = ((avg_reading/4095) * 3.3) + voltageError;
  float resistance = (nodeVoltage/3.3 * SERIESRESISTOR)/(1 - nodeVoltage/3.3);
  Serial.print("Node voltage "); 
  Serial.println(nodeVoltage);
  Serial.print("Thermistor resistance "); 
  Serial.println(resistance);
 
  float steinhart;
  steinhart = resistance / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert absolute temp to C
  
  Serial.print("Temperature "); 
  Serial.print(steinhart);
  Serial.println(" *C");
  steinhart = (steinhart * 9/5) + 32;
  Serial.print(steinhart);
  Serial.println(" *F");
}
