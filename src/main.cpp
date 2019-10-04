#include <Arduino.h>
#include <SD.h>
#include <MFRC522.h>
#include "vs1053_ext.h"
#include "pinout.h"


MFRC522 mfrc522(MFRC522_CS, MFRC522_RST);  // Create MFRC522 instance
VS1053 player(VS1053_CS, VS1053_DCS, VS1053_DREQ);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(200);

  SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI);			// Im Originalcode fehlen die Parameter! Daher hat auch das Ändern deiner Pinout.h nix gebracht.

  if (SD.begin(SDCARD_CS)) 
  {
     Serial.println("SD opened!");
  }    
  else
  {
    Serial.println("SD FAIL!");
  }

	mfrc522.PCD_Init();		// Init MFRC522
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details

  Serial.print("MFRC522 Selftest:");
  if (mfrc522.PCD_PerformSelfTest())
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("fail");
  }
  mfrc522.PCD_Init();		 // again! Otherwise the reader will not read


  pinMode(VS1053_ENABLE, OUTPUT);
  digitalWrite(VS1053_ENABLE, true);

  
  Serial.print("player init:");
  player.begin();
  player.setVolume(0);    
  player.printVersion();
}

void loop() {
  // put your main code here, to run repeatedly:
}