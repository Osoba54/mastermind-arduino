/*
 * Project: Mastermind Game for Arduino
 * File: EncoderHandler.h
 * Author: Plisz Ksawery (Osoba54)
 * License: MIT
 * Repository: https://github.com/Osoba54/mastermind-arduino
 */

#ifndef ENCODER_HANDLER_H
#define ENCODER_HANDLER_H

#include <Arduino.h>

class EncoderHandler {
private:
    uint8_t pinA, pinB, pinSW;
    volatile int32_t position;
    volatile uint8_t lastStateA;
    unsigned long lastDebounceTime;

public:
    EncoderHandler(uint8_t a, uint8_t b, uint8_t sw);
    void begin(void (*ISR_callback)());
    void handleInterrupt();
    bool isButtonPressed();
    long getPosition();
    void resetPosition();
};

#endif