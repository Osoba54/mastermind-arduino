/*
 * Project: Mastermind Game for Arduino
 * File: mastermind.ino
 * Author: Plisz Ksawery (Osoba54)
 * License: MIT
 * Repository: https://github.com/Osoba54/mastermind-arduino
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "EncoderHandler.h"
#include "GameLogic.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);

EncoderHandler encoder(2, 3, 4);
Game game(&lcd);

void encoderISR() {
  encoder.handleInterrupt();
}

void setup() {
  lcd.init();
  lcd.backlight();
  encoder.begin(encoderISR);
  game.init();
}

void loop() {
  long pos = encoder.getPosition();
  game.updateSelection(pos);

  if(encoder.isButtonPressed()){
    game.confirmChoice();
  }
  game.update();
}