

//scl to d1 for nodemcu
//sda to d2 for node
//vin to 3.3v
//gnd to gnd

#include "config.h"
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000
PulseOximeter pox;

uint32_t tsLastReport = 0;

// Callback (registered below) fired when a pulse is detected
void onBeatDetected()
{
    Serial.println("Beat!");
}



// this int will hold the current count for our sketch
int count = 0;
int bpm;
int o2;

// set up the feeds for the cloud
AdafruitIO_Feed *pulse = io.feed("pulse");
AdafruitIO_Feed *oxy = io.feed("oxy");

void setup() {
  Wire.begin(4, 5); 

  // start the serial connection
  Serial.begin(115200);
  Serial.print("Initializing pulse oximeter..");
  if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }



    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
  io.run();

  //pulse oxy
  // Make sure to call update as fast as possible
    pox.update();

    // Asynchronously dump heart rate and oxidation levels to the serial
    // For both, a value of 0 means "invalid"
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
      //bpm=pox.getHeartRate();
      //o2=pox.getSpO2();
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");

        tsLastReport = millis();
    }

  if ( count %90 ==0){ // because i need a delay  only on posting to cloud
  pulse->save(pox.getHeartRate());}
  oxy->save(pox.getSpO2());
 


 // delay(3000);

}
