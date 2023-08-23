void drawlivesandlevel() {
  for (int i = 0; i < lives; i++) {  // Draw lives
    // ((WIDTH - LIFE_SIZE - (lives-1) * LIFE_SPACING) / 2) + LIFE_SPACING * i)
    Sprites::drawOverwrite((WIDTH - LIFE_SIZE) / 2 - (lives - 1) * (LIFE_SPACING / 2) + LIFE_SPACING * i, (HEIGHT - LIFE_SIZE) / 2, Life, 0);
  }

  arduboy.setCursor(WIDTH / 2 - 4 * CHAR_WIDTH, HEIGHT / 4 * 3 - CHAR_HEIGHT / 2);
  arduboy.print("LEVEL: ");
  arduboy.print(stage.num);
}

void drawpoints() {
  arduboy.setCursor(WIDTH / 2 - 24 - (GetNumberOfDigits(stagebonus) + 1) * CHAR_WIDTH / 2, HEIGHT / 2 - CHAR_HEIGHT / 2);
  arduboy.print("+");
  arduboy.print(stagebonus);
  arduboy.setCursor(WIDTH / 2 + 24 - (GetNumberOfDigits(timebonus) + 1) * CHAR_WIDTH / 2, HEIGHT / 2 - CHAR_HEIGHT / 2);
  arduboy.print("+");
  arduboy.print(timebonus);

  arduboy.setCursor(WIDTH / 2 - 4 * CHAR_WIDTH, HEIGHT / 4 * 3 - CHAR_HEIGHT / 2);
  arduboy.print("SCORE: ");
  arduboy.print(score);
}

void drawhighscore() {
  arduboy.setCursor(WIDTH / 2 - 6 * CHAR_WIDTH, HEIGHT / 2 - CHAR_HEIGHT / 2);
  arduboy.print("SCORE: ");
  arduboy.print(score);

  arduboy.setCursor(WIDTH / 2 - 9 * CHAR_WIDTH, HEIGHT / 4 * 3 - CHAR_HEIGHT / 2);
  arduboy.print("HI SCORE: ");
  arduboy.print(topscore);
}


void setupstatus(int event) {
  if (event == GAMEOVER || event == CONGRATS) {
    proceedwithA = true;
  } else {
    proceedwithA = false;
  }

  status = event;
  statustimer = 240;
  statustimermax = 240;
  gamestate = GAME_STATUS;
}

void gamestatus() {
  if (status == MISS) {
    arduboy.digitalWriteRGB(RGB_ON, RGB_OFF, RGB_OFF);
    arduboy.setCursor(WIDTH / 2 - 2 * CHAR_WIDTH, HEIGHT / 4 - CHAR_HEIGHT / 2);
    arduboy.print("MISS");
  } else if (status == GOAL) {
    arduboy.digitalWriteRGB(RGB_OFF, RGB_ON, RGB_OFF);
    arduboy.setCursor(WIDTH / 2 - 2 * CHAR_WIDTH, HEIGHT / 4 - CHAR_HEIGHT / 2);
    arduboy.print("GOAL");
  } else if (status == START) {
    arduboy.digitalWriteRGB(RGB_OFF, RGB_ON, RGB_OFF);
    arduboy.setCursor(WIDTH / 2 - 3 * CHAR_WIDTH, HEIGHT / 4 - CHAR_HEIGHT / 2);
    arduboy.print("START!");
  } else if (status == GAMEOVER) {
    arduboy.digitalWriteRGB(RGB_ON, RGB_OFF, RGB_ON);
    arduboy.setCursor(WIDTH / 2 - 5 * CHAR_WIDTH, HEIGHT / 4 - CHAR_HEIGHT / 2);
    arduboy.print("GAME OVER!");
  } else if (status == CONGRATS) {
    arduboy.digitalWriteRGB(RGB_ON, RGB_ON, RGB_OFF);
    arduboy.setCursor(WIDTH / 2 - 8 * CHAR_WIDTH, HEIGHT / 4 - CHAR_HEIGHT / 2);
    arduboy.print("CONGRATULATIONS!");
  }

  if (statustimer > statustimermax / 2) {  // 1st half
    if (status == START || status == MISS) {
      drawlivesandlevel();
    } else if (status == GOAL) {
      drawpoints();
    } else if (status == CONGRATS) {
      drawpoints();
    } else if (status == GAMEOVER) {
      drawhighscore();
    }
  } else {  // 2nd half
    if (status == START || status == MISS || status == GOAL) {
      drawlivesandlevel();
    } else if (status == GAMEOVER || status == CONGRATS) {
      drawhighscore();
    }
  }

  if (arduboy.justPressed(A_BUTTON)) {  // Just for testing?
    statustimer = 0;
  }



  if (proceedwithA) {
    if (arduboy.justPressed(A_BUTTON)) {
      arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
      gamestate = GAME_TITLE;
    }
  } else if (statustimer <= 0) {
    arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
    if (stage.num <= 25) {
      gamestate = GAME_PLAY;
    }
  }

  if (statustimer > 0) {
    statustimer--;
  }
}
