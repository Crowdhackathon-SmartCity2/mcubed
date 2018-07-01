

#include "config.h"
#include <Servo.h>


// digital pin 5
#define servoPin 5
Servo Servo1;


// set up the 'digital' feed
AdafruitIO_Feed *digital = io.feed("digital");

void setup() {
Servo1.attach(servoPin);
  // set led pin as a digital output
 // pinMode(LED_PIN, OUTPUT);

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'digital' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  digital->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  digital->get();

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  delay(2000);

}


void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  //Serial.print(data->toPinLevel());
//  Serial.print(data);
//  Serial.print(&data);
 // Serial.print(*data);
  

  if(data->toPinLevel() == HIGH){
    Serial.println("HIGH");
    Servo1.write(180);}
  else{
    Serial.println("LOW");
    Servo1.write(0);}



}

