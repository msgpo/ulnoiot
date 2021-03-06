// Example for an i2c connector to communicate with ulnoiot-node via i2c
//
// Author: ulno (http://ulno.net)
// Created: 2017-10-20
//


#include <UlnoiotI2c.h>


void myreceive( char *msg, int len ) {
    Serial.print("Received a message of length: ");
    Serial.println(len);
    Serial.print("Message:");
    Serial.println(msg); // is properly 0 terminated - but len can used to
}

UlnoiotI2c ui2c(1000,myreceive);

void setup() {
  Serial.begin(115200); // start serial for debug output
  Serial.println("Starting.");
}

int counter = 0;

void loop() {
  char mystr[20];
  ui2c.suspend(100);
  snprintf(mystr, 19, "%d", counter);
  ui2c.write(mystr);
  Serial.println(mystr);
  delay(1000);
  counter += 1;
}


