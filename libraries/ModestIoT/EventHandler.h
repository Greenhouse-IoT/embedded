/**
 * @file EventHandler.h
 * @brief Defines the Event structure and EventHandler interface.
 * @author Angel Velasquez / ModestIoT Copilot
 * @date July 01, 2025
 */
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

// --- CORRECCIÓN AQUÍ ---
// Se añade la librería principal de Arduino para que reconozca 'Serial'
#include <Arduino.h>
#include <any>

struct Event {
    int id;
    std::any data;

    explicit Event(int eventId) : id(eventId) {}

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
            Serial.printf("Error de casting en Evento ID %d: %s\n", id, e.what());
            return T{}; 
        }
    }
};

class EventHandler {
public:
    virtual void on(Event event) = 0;
    virtual ~EventHandler() = default;
};

#endif // EVENT_HANDLER_H