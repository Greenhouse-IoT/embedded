#include "LcdActuator.h"

LcdActuator::LcdActuator(uint8_t addr, CommandHandler* handler)
    : Actuator(0, handler), lcd(addr, 16, 2) {}

void LcdActuator::init() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Iniciando...");
}

void LcdActuator::handle(Command command) {
    if (command.id == LCD_PRINT_COMMAND_ID) {
        LcdData data = command.getData<LcdData>();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(data.line1);
        lcd.setCursor(0, 1);
        lcd.print(data.line2);
    }
}