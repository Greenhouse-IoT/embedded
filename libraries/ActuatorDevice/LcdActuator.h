#ifndef LCD_ACTUATOR_H
#define LCD_ACTUATOR_H

#include "ModestIoT.h"
#include <LiquidCrystal_I2C.h>

struct LcdData {
    String line1;
    String line2;
};

class LcdActuator : public Actuator {
private:
    LiquidCrystal_I2C lcd;

public:
    static const int LCD_PRINT_COMMAND_ID = 201;
    LcdActuator(uint8_t addr, CommandHandler* handler);
    void init() override;
    void handle(Command command) override;
};

#endif