#include "Particle.h"
#include "SdFat.h"

// PIN CONFIGURATION
const int CHIP_SELECT = S3;  // S3 = D18

SdFat SD;

SYSTEM_MODE(AUTOMATIC);

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 10000); 
  delay(2000);

  Serial.println("Initializing SD card...");

  // Try to initialize at safe speed
  if (!SD.begin(CHIP_SELECT, SD_SCK_MHZ(4))) {
    Serial.println("----------------------------------------");
    Serial.println("FAILURE CAPTURED");
    
    // Print the Error Code to identify the specific problem
    // 0x1 or 0xFF usually means Wiring/Power issues
    // Other codes usually mean Formatting issues
    Serial.print("Error Code: 0x");
    Serial.println(SD.card()->errorCode(), HEX);
    Serial.print("Error Data: 0x");
    Serial.println(SD.card()->errorData(), HEX);
    Serial.println("----------------------------------------");
    return;
  }

  Serial.println("Success! SD Card initialized.");
  
  File myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    myFile.println("It works!");
    myFile.close();
    Serial.println("Written to test.txt");
  }
}

void loop() {
  SD.ls();
}