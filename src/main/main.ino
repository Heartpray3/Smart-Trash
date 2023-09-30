#include "lcd.h"

Lcd lcd;
void setup() {
}

void loop() { 
    lcd.casesOutput(OutputTrash::COMPOST);
    delay(1000);
    lcd.casesOutput(OutputTrash::RECYCLABLE);
    delay(1000);
    lcd.casesOutput(OutputTrash::JUNK);
    delay(1000);
}