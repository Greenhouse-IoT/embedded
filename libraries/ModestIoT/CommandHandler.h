/**
 * @file CommandHandler.h
 * @brief Defines the Command structure and CommandHandler interface.
 * @author Angel Velasquez / ModestIoT Copilot
 * @date July 01, 2025
 */
#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

// --- CORRECCIÓN AQUÍ ---
// Se añade la librería principal de Arduino para que reconozca 'Serial'
#include <Arduino.h>
#include <any>

struct Command {
    int id;
    std::any data;

    explicit Command(int commandId) : id(commandId) {}

    template<typename T>
    void setData(T value) {
        data = value;
    }

    template<typename T>
    T getData() const {
        try {
            return std::any_cast<T>(data);
        } catch (const std::bad_any_cast& e) {
            // Ahora 'Serial' será reconocido gracias al #include <Arduino.h>
            Serial.printf("Error de casting en Comando ID %d: %s\n", id, e.what());
            return T{};
        }
    }
};

class CommandHandler {
public:
    virtual void handle(Command command) = 0;
    virtual ~CommandHandler() = default;
};

#endif // COMMAND_HANDLER_H