/*
 * Project: Mastermind Game for Arduino
 * File: GameLogic.h
 * Author: Plisz Ksawery (Osoba54)
 * License: MIT
 * Repository: https://github.com/Osoba54/mastermind-arduino
 */

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

enum GameState { PLAYING,
                 WAITING_FOR_RESTART };

class Game {
private:
  GameState currentState = PLAYING;
  unsigned long stateStartTime = 0;
  LiquidCrystal_I2C* lcd;
  const uint8_t POSSIBLE_CHARS_SIZE = 5;
  const char POSSIBLE_CHARS[POSSIBLE_CHARS_SIZE] = { '@', '#', '$', '%', '&' };

  uint8_t cursorX = 0;
  uint8_t cursorY = 3;
  char rightAns[4];
  char playerAns[4];
  uint8_t currentAttempt = 0;
  uint8_t charIndex = 0;

  uint8_t wrongPos = 0;
  uint8_t rightPos = 0;

public:
  Game(LiquidCrystal_I2C* _lcd)
    : lcd(_lcd) {}
  void update();
  void init();
  void updateSelection(long encoderPos);
  void confirmChoice();
  void check();
  void displayRightAns();
  void printStats();
};

#endif