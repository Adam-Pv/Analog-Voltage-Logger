/*
  This file was created by Adam Peavey for Chico State Baja SAE
  It logs timestamped, analog voltage measurements to an SD card over 1000/second. 
  It's first use case was measuring and logging the pressure spike in an airshock 
  as a go-cart was dropped from above a crane.
  
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

*/
#include <SPI.h>
#include <SD.h>


const int chipSelect = 10;  // SD Card is hooked up to pin 10 (Ethernet Sheild uses 4)
//unsigned long time;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized."); 

 
  
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  
} 

// the loop routine runs over and over again forever
// each iteration creates a new file
void loop() {
  // creates a new file and gives it a unique/timestamped name
  String fileName = String(millis());
  fileName += ".TXT";
  File dataFile = SD.open(fileName, FILE_WRITE);
  
  // Logs 30000 inputs in a file and saves the file.
  for (int i = 0; i < 30000; i++) {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float voltage = sensorValue * (5.0 / 1023.0);
    // log the value

    dataFile.print(millis());
    dataFile.print(" ");
    dataFile.println(voltage);
    
  }
  // .close() is used to save the file, otherwise we get file corruption.
  dataFile.close();

}
