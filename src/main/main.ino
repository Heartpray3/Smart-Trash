#include "lcd.h"
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN     9     // Configurable, see typical pin layout above
#define SS_PIN      10    // Configurable, see typical pin layout above

#define RECYCLE     0xB5
#define TRASH       0x7E

#define LED_RECYCLE 6
#define LED_TRASH   8
#define NB_CYCLES   30

int cycle = 0;

//Method definitions 
void blink(int ledPos);

Servo myservo;

int isRecyclable = 0;
int isTrash = 0;
int pos = 0;

MFRC522 mfrc522(SS_PIN, RST_PIN);

#define NEW_UID {0xDE, 0xAD, 0xBE, 0xEF}

MFRC522::MIFARE_Key key;
Lcd lcd(0,1,2,3,4,5);

void setup() {
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  myservo.attach(7);
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  pinMode(8, OUTPUT);
}

void loop() {
  if (isRecyclable > 0){
    if (isRecyclable == NB_CYCLES){
      lcd.casesOutput(OutputTrash::RECYCLABLE);
      digitalWrite(LED_RECYCLE, HIGH);
    digitalWrite(LED_TRASH, LOW);

      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
      delay(1000); 
    }

    
    isRecyclable--;
  }
  else if (isTrash > 0){
    if (isTrash == NB_CYCLES){
      lcd.casesOutput(OutputTrash::JUNK);
      cycle = 30;
    }
    digitalWrite(LED_RECYCLE, LOW);
    digitalWrite(LED_TRASH, HIGH);
    isTrash--;
  }
  else {
    digitalWrite(LED_RECYCLE, LOW);
    digitalWrite(LED_TRASH, LOW);
    lcd.casesOutput(OutputTrash::EMPTY);
    myservo.write(0);
  }
  
  // Look for new cards, and select one if present
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }
  
  // Dump UID
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  } 
  if (mfrc522.uid.uidByte[0] == RECYCLE){
    isRecyclable = NB_CYCLES;
    isTrash = 0;
  }
  else if (mfrc522.uid.uidByte[0] == TRASH){
    isRecyclable = 0;
    isTrash = NB_CYCLES;
  }
  else{
    digitalWrite(LED_RECYCLE, HIGH);
  }
  Serial.println();
  
  delay(15);
}

