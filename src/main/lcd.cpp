#pragma once
#include "lcd.h"

Lcd::Lcd() : lcd_(9,10,4,5,6,7) {
    setup();
}

Lcd::Lcd(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) : 
    lcd_(rs, enable, d4, d5, d6, d7) {
    setup();
}

void Lcd::setup() {
    lcd_.begin(16, 2);
}

void Lcd::casesOutput(OutputTrash output) const {
    lcd_.setCursor(0, 1);
    switch (output)
    {
        case OutputTrash::COMPOST:
        lcd_.print("Composte");
        break;
        case OutputTrash::RECYCLABLE:
        lcd_.print("Recyclable");
        break;
        case OutputTrash::JUNK:
        lcd_.print("Junk");
            break;
    }
}