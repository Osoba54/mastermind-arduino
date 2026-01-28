/*
 * Project: Mastermind Game for Arduino
 * File: GameLogic.cpp
 * Author: Plisz Ksawery (Osoba54)
 * License: MIT
 * Repository: https://github.com/Osoba54/mastermind-arduino
 */

#include "GameLogic.h"

void Game::init() {
  uint8_t char_wrong[8] = { 0x0, 0x0, 0xE, 0x11, 0x11, 0x11, 0xE, 0x0 };
  uint8_t char_right[8] = { 0x0, 0x0, 0xE, 0x1F, 0x1F, 0x1F, 0xE, 0x0 };

  lcd->createChar(0, char_wrong);
  lcd->createChar(1, char_right);
  lcd->clear();

  cursorX = 0;
  cursorY = 3;

  randomSeed(analogRead(A0));
  for (int i = 0; i < 4; i++) {
    rightAns[i] = POSSIBLE_CHARS[random(0, POSSIBLE_CHARS_SIZE)];
  }

  lcd->setCursor(cursorX, cursorY);
  lcd->print(POSSIBLE_CHARS[0]);
}

void Game::updateSelection(long encoderPos) {
  uint8_t newIdx = (encoderPos % POSSIBLE_CHARS_SIZE + POSSIBLE_CHARS_SIZE) % POSSIBLE_CHARS_SIZE;
  if (newIdx != charIndex) {
    charIndex = newIdx;
    lcd->setCursor(cursorX, cursorY);
    lcd->print(POSSIBLE_CHARS[charIndex]);
  }
}

void Game::confirmChoice() {
  playerAns[3 - cursorY] = POSSIBLE_CHARS[charIndex];

  if (cursorY > 0) {
    cursorY--;
    lcd->setCursor(cursorX, cursorY);
    lcd->print(POSSIBLE_CHARS[charIndex]);
  } else {
    check();
    printStats();

    cursorX += 2;
    cursorY = 3;
    if (cursorX < 20) {
      lcd->setCursor(cursorX, cursorY);
      lcd->print(POSSIBLE_CHARS[charIndex]);
    }
  }
}

void Game::check() {
  rightPos = 0;
  wrongPos = 0;
  bool matchedRight[4] = { false };
  bool matchedPlayer[4] = { false };

  for (int i = 0; i < 4; i++) {
    if (playerAns[i] == rightAns[i]) {
      rightPos++;
      matchedRight[i] = true;
      matchedPlayer[i] = true;
    }
  }

  for (int i = 0; i < 4; i++) {
    if (!matchedPlayer[i]) {
      for (int j = 0; j < 4; j++) {
        if (!matchedRight[j] && playerAns[i] == rightAns[j]) {
          wrongPos++;
          matchedRight[j] = true;
          break;
        }
      }
    }
  }


if (rightPos == 4 || cursorX >= 16) {
    if (cursorX >= 16 && rightPos < 4) displayRightAns();
    currentState = WAITING_FOR_RESTART;
    stateStartTime = millis(); 
  }
}

void Game::update() {
  if (currentState == WAITING_FOR_RESTART) {
    if (millis() - stateStartTime >= 5000) {
      init();
      currentState = PLAYING;
    }
  }
}

void Game::displayRightAns() {
  uint8_t revealX = 19;
  for (int i = 0; i < 4; i++) {
    lcd->setCursor(revealX, 3 - i);
    lcd->print(rightAns[i]);
  }
}


void Game::printStats() {
  uint8_t statX = cursorX + 1;
  uint8_t statY = 3;

  for (int i = 0; i < rightPos; i++) {
    lcd->setCursor(statX, statY--);
    lcd->write(1);
  }
  for (int i = 0; i < wrongPos; i++) {
    lcd->setCursor(statX, statY--);
    lcd->write(0);
  }
}