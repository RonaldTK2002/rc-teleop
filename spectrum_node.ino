#include "SpektrumSatellite.h"

SpektrumSatellite<uint16_t> satellite(Serial2); // Assing satellite to Serial (use Serial1 or Serial2 if available!)
int rxPin = 3; // pin for receiving data from serial1
int counter = 0;

void setup() {
  Serial2.begin(SPEKTRUM_SATELLITE_BPS);
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");

  // Activate the loggin to the console only if SpektrumSatellite is not using Serial
  satellite.setLog(Serial);
  // we can define the requested binding mode
  satellite.setBindingMode(External_DSMx_22ms);

  // //scale the values from 0 to 180 degrees for PWM
  // satellite.setChannelValueRange(0, 180);

  // wait forever for data
  satellite.waitForData();

  
}

void loop() {
  if (satellite.getFrame()) {   

    if(counter % 10 == 0){
      for (int j=0;j<12; j++){
          Channel ch = static_cast<Channel>(j);   
          long value = satellite.getChannelValue(ch);
          Serial.print(j);
          Serial.print(":");
          Serial.print(value);
          Serial.print("\t");
        }        
        Serial.println("");
    }

    counter++;
    
  }   

}