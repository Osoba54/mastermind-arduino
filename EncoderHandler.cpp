/*
 * Project: Mastermind Game for Arduino
 * File: EncoderHandler.cpp
 * Author: Plisz Ksawery (Osoba54)
 * License: MIT
 * Repository: https://github.com/Osoba54/mastermind-arduino
 */

#include "EncoderHandler.h"

EncoderHandler::EncoderHandler(uint8_t a, uint8_t b, uint8_t sw) 
  : pinA(a), pinB(b), pinSW(sw), position(0), lastDebounceTime(0) {}

void EncoderHandler::begin(void (*ISR_callback)()) {
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  pinMode(pinSW, INPUT_PULLUP);
  lastStateA = digitalRead(pinA);
  
  attachInterrupt(digitalPinToInterrupt(pinA), ISR_callback, CHANGE);
}

void EncoderHandler::handleInterrupt() {
  uint8_t stateA = digitalRead(pinA);
  if (stateA != lastStateA) {
    if (digitalRead(pinB) != stateA) {
      position++;
    } else {
      position--;
    }
  }
  lastStateA = stateA;
}

bool EncoderHandler::isButtonPressed() {
  if (digitalRead(pinSW) == LOW) {
    if (millis() - lastDebounceTime > 200) {
      lastDebounceTime = millis();
      return true;
    }
  }
  return false;
}

long EncoderHandler::getPosition() { return position / 2; }
void EncoderHandler::resetPosition() { position = 0; }