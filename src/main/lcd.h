#pragma once
#include <LiquidCrystal.h>

enum class OutputTrash {
    COMPOST,
    RECYCLABLE,
    JUNK
};

class Lcd {
    public:
        Lcd();
        Lcd(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
        void setup();
        void casesOutput(OutputTrash output) const;
    private:
        LiquidCrystal lcd_;
};

