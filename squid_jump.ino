// PrimmR 2023
// Squid Jump

#include <Arduboy2.h>
#include <ArduboyTones.h>
Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

#include "Sprites.hpp"
#include "Structs.hpp"
#include "Sounds.hpp"
#include "Sums.hpp"

#define CHAR_WIDTH 6
#define CHAR_HEIGHT 8

// Game states
#define GAME_TITLE 0
#define GAME_PLAY 1
#define GAME_OVER 2
#define GAME_STATUS 3
int gamestate = GAME_TITLE;

// Graphics
int sprite = REGULAR;  // Default

#define MAX_X_VELOCITY 1.5
#define X_VELOCITY_DECAY 0.01
#define X_ACCEL 0.1
#define MAX_Y_VELOCITY 12
#define Y_ACCEL 0.1
#define MAX_CHARGE 80

float poisonheight = 128;
#define LEEWAY 8
#define POISON_SPEED 0.25

#define ZAP_UP 86

#define LIFE_SPACING 10

struct Player player = { (WIDTH - PLAYER_SIZE) / 2, HEIGHT / 2, 0, 0, true, 0, 0 };

struct Stage stage = { 1, {}, 0 };

struct Zapfish zapfish {
  0
};

// Camera
#define CAM_UPPER_BOUNDARY 20  // Positions for which the camera starts to follow
#define CAM_LOWER_BOUNDARY 40

int camerapos = 0;  // + moves screen up

// Status
byte lives = 3;
#define EXTRA_LIFE 10000
uint32_t score = 0;
int stagebonus = 0;
int timebonus = 0;
#define MISS 0
#define GOAL 1
#define START 2
int status = 0;
int statustimer = 0;
int statustimermax = 0;

uint16_t currentstagetimer = 0;

bool showtextblink = true;


// FUNCTIONS


void titlescreen() {
  arduboy.setCursor(WIDTH / 2 - 5 * CHAR_WIDTH, HEIGHT / 4 - CHAR_HEIGHT / 2);
  arduboy.print("SQUID JUMP");

  arduboy.setCursor((WIDTH - 16 * CHAR_WIDTH) / 2, HEIGHT / 4 * 3 - CHAR_HEIGHT / 2);
  arduboy.print("PRESS");

  if (showtextblink) {
    arduboy.print(" A ");
  }

  arduboy.setCursor((WIDTH) / 2, HEIGHT / 4 * 3 - CHAR_HEIGHT / 2);
  arduboy.print("TO START");



  if (arduboy.everyXFrames(30)) {
    showtextblink = !showtextblink;
  }


  if (arduboy.justPressed(A_BUTTON)) {
    startgame();
  }
}

void startgame() {
  lives = 3;
  score = 0;
  stagebonus = 0;
  timebonus = 0;
  stage.num = 1;

  resetstage();
  setupstatus(START);
}

void gameinput() {
  if (arduboy.pressed(LEFT_BUTTON) && player.falling) {
    player.xvelocity -= X_ACCEL + X_VELOCITY_DECAY;
  }
  if (arduboy.pressed(RIGHT_BUTTON) && player.falling) {
    player.xvelocity += X_ACCEL + X_VELOCITY_DECAY;
  }
  if (arduboy.pressed(A_BUTTON)) {
    if (player.charge < MAX_CHARGE) {
      player.charge++;
    }
  }
  if (arduboy.justReleased(A_BUTTON)) {
    if (!player.falling && player.charge >= MAX_CHARGE / CHARGE_NUM) {
      player.velocity = static_cast<float>(player.charge) / 20;
      player.falling = true;

      sound.tones(jump_sound);
    }
    player.charge = 0;
  }

  if (arduboy.justPressed(B_BUTTON)) {
    if (arduboy.pressed(UP_BUTTON)) {
      lives++;
    } else if (arduboy.pressed(DOWN_BUTTON)) {
      lives--;
    }
  }

  // arduboy.print(player.charge);
  // arduboy.print(" ");
}

void resetstage() {
  // Set up stage
  stage.totalplatforms = 16;

  struct Platform ground = { 0, HEIGHT - 2 * BLOCK_SIZE, WIDTH / BLOCK_SIZE };
  stage.platforms[0] = ground;
  int lastheight = HEIGHT - 2 * BLOCK_SIZE;
  for (int i = 1; i < stage.totalplatforms; i++) {
    int len = random(4, 8);
    int x = random(0, (WIDTH / BLOCK_SIZE - len) + 1) * BLOCK_SIZE;
    int y = lastheight - random(5, 10) * BLOCK_SIZE;
    int type = random(0, 3);
      
    int facingright = (type == JELLYFISH_PLATFORM) ? random(0, 2) : false;

    stage.platforms[i] = { x, y, len, type, facingright };
    lastheight = y;
  }

  zapfish = { lastheight - ZAP_UP - ZAP_SIZE };

  // Reset states
  player = { (WIDTH - PLAYER_SIZE) / 2, HEIGHT / 2, 0, 0, true, 0, 0 };
  camerapos = 0;
  poisonheight = 128;
}

// Calculates whether platform would be hit next frame (may fail if collision boxes both 1px)
bool collision(Platform platform, int height) {  // Assume that it's always called by player
  if (player.velocity <= 0) {
    Rect ray = Rect(player.intX(), player.intY() + PLAYER_SIZE + camerapos, PLAYER_SIZE, height);
    Rect platformtop = Rect(platform.x, platform.y + camerapos, platform.len * BLOCK_SIZE, 2);
    // arduboy.fillRect(player.x, player.y + PLAYER_SIZE + camerapos, PLAYER_SIZE, -1 * height); // Visual
    // arduboy.fillRect(platform.x, platform.y + camerapos, platform.len * BLOCK_SIZE, 2); // Visual
    return Arduboy2::collide(ray, platformtop);
  }
  return false;
}

void physics() {
  // Y
  if (player.falling) {
    player.y -= player.velocity;
    player.velocity -= Y_ACCEL;
  } else {
    player.velocity = 0;
  }
  if (player.velocity < -MAX_Y_VELOCITY) {
    player.velocity = -MAX_Y_VELOCITY;
  }

  // for (auto const& plat : stage.platforms) {
  for (int i = 0; i < stage.totalplatforms; i++) {
    if (player.falling) {
      if (!cull(stage.platforms[i])) {
        if (collision(stage.platforms[i], -ceil(player.velocity))) {
          player.y = stage.platforms[i].y - PLAYER_SIZE;
          player.falling = false;
          player.lastplatform = i;
        }
      }
    } else {
      if (!collision(stage.platforms[player.lastplatform], BLOCK_SIZE)) {  // If player has been pushed off the platform
        player.falling = true;
      }
    }
  }

  // X
  if (player.xvelocity > MAX_X_VELOCITY) {  // X Velocity Limits
    player.xvelocity = MAX_X_VELOCITY;
  } else if (player.xvelocity < -MAX_X_VELOCITY) {
    player.xvelocity = -MAX_X_VELOCITY;
  }
  if (player.falling || stage.platforms[player.lastplatform].type == ICE_PLATFORM) {  // Set to 0 when on solid ground
    player.x += player.xvelocity;
  } else {
    player.xvelocity = 0;
  }

  if (player.xvelocity > 0) {  // Decay
    player.xvelocity -= X_VELOCITY_DECAY;
  } else if (player.xvelocity < 0) {
    player.xvelocity += X_VELOCITY_DECAY;
  }

  if (abs(player.xvelocity) < X_VELOCITY_DECAY) {  // Stops tiny pixel movement
    player.xvelocity = 0;
  }

  // Check for player push
  if (!player.falling && stage.platforms[player.lastplatform].type == JELLYFISH_PLATFORM) {
    if (stage.platforms[player.lastplatform].facingright) {
      player.x++;
    } else {
      player.x--;
    }
  }

  // Boundaries
  if (player.intX() < 0) {
    player.x = 0;
  } else if (player.intX() + PLAYER_SIZE > WIDTH) {
    player.x = WIDTH - PLAYER_SIZE;
  }

  // Platform movement
  for (int k = 0; k < stage.totalplatforms; k++) {
    if (stage.platforms[k].type == JELLYFISH_PLATFORM) {
      if (stage.platforms[k].facingright) {
        stage.platforms[k].x++;
      } else {
        stage.platforms[k].x--;
      }

      if (stage.platforms[k].x < 0 + BLOCK_SIZE) {
        stage.platforms[k].facingright = true;
      } else if (stage.platforms[k].x + stage.platforms[k].len * BLOCK_SIZE > WIDTH - BLOCK_SIZE) {
        stage.platforms[k].facingright = false;
      }
    }
  }
}

void poison() {
  poisonheight -= POISON_SPEED;

  if (player.y + PLAYER_SIZE > poisonheight + LEEWAY) {
    if (lives > 0) {
      lives--;
      resetstage();
      setupstatus(MISS);
    } else {
      gamestate = GAME_OVER;
      showtextblink = true;
    }
  }
}

void zap() {
  if (!cullzap(zapfish)) {
    Rect playerbox = Rect(player.intX(), player.intY(), PLAYER_SIZE, PLAYER_SIZE);
    Rect zapbox = Rect((WIDTH - ZAP_SIZE) / 2, zapfish.y, ZAP_SIZE, ZAP_SIZE);
    if (Arduboy2::collide(playerbox, zapbox)) {
      nextlevel();
    }
  }
}

void nextlevel() {
  int timemodifier;
  if (stage.num < 11) {
    stagebonus = 300;
    timemodifier = 1;
  } else if (stage.num < 21) {
    stagebonus = 600;
    timemodifier = 2;
  } else {
    stagebonus = 1000;
    timemodifier = 3;
  }

  if (currentstagetimer < 2400) {
    timebonus = ScoreFromFrames(currentstagetimer, timemodifier);
  } else {
    timebonus = 0;
  }

  int prevscorelife = score / EXTRA_LIFE;

  score += stagebonus + timebonus;

  int scorelife = score / EXTRA_LIFE;

  if (scorelife > prevscorelife && lives < 5) {
    lives++;
  }

  stage.num++;
  resetstage();
  setupstatus(GOAL);
}

void movecamera() {
  // PLayer location on screen player.y + camerapos
  // camerapos = (-1 * player.y) + 40;
  if (player.intY() + camerapos < CAM_UPPER_BOUNDARY) {
    camerapos = -player.intY() + CAM_UPPER_BOUNDARY;
  } else if (player.intY() + camerapos > CAM_LOWER_BOUNDARY) {
    camerapos = -player.intY() + CAM_LOWER_BOUNDARY;
  }
  // arduboy.print(camerapos);
  // arduboy.print(player.y);
}

bool cull(struct Platform platform) {
  return platform.y + camerapos + player.velocity > HEIGHT || platform.y + camerapos + BLOCK_SIZE < 0;
}

bool cullzap(struct Zapfish zapfish) {
  return zapfish.y + camerapos + player.velocity > HEIGHT || zapfish.y + camerapos + ZAP_SIZE < 0;
}

void drawgame() {
  // for (auto& plat : stage.platforms) {  // For every platform in platforms
  for (int k = 0; k < stage.totalplatforms; k++) {
    if (!cull(stage.platforms[k])) {
      for (int i = 0; i < stage.platforms[k].len; i++) {
        Sprites::drawOverwrite(stage.platforms[k].x + i * BLOCK_SIZE, stage.platforms[k].y + camerapos, Block, stage.platforms[k].type + stage.platforms[k].facingright);
      }
    }
  }

  if (!cullzap(zapfish)) {
    Sprites::drawOverwrite((WIDTH - ZAP_SIZE) / 2, zapfish.y + camerapos, Zap, 0);
  }

  if (poisonheight + camerapos <= HEIGHT) {
    Sprites::drawSelfMasked(0, poisonheight + camerapos, Poison, 0);
  }

  if (player.charge == MAX_CHARGE) {
    sprite = CHARGE_4;
  } else if (player.charge >= MAX_CHARGE / CHARGE_NUM * 2) {
    sprite = CHARGE_3;
  } else if (player.charge >= MAX_CHARGE / CHARGE_NUM * 1) {
    sprite = CHARGE_2;
  } else {
    sprite = REGULAR;
  }


  // Draw player
  Sprites::drawExternalMask(player.x, player.y + camerapos, Player, Player_Mask, sprite, sprite);
}

void gameplay() {
  currentstagetimer++;

  gameinput();
  poison();
  zap();
  physics();
  movecamera();
  if (gamestate == GAME_PLAY) {  // Prevents flashes when going to status screen
    drawgame();
  }
}

void setupstatus(int event) {
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
  }

  if (statustimer <= statustimermax / 2 || status != GOAL) {
    for (int i = 0; i < lives; i++) {  // Draw lives
      // ((WIDTH - LIFE_SIZE - (lives-1) * LIFE_SPACING) / 2) + LIFE_SPACING * i)
      Sprites::drawOverwrite((WIDTH - LIFE_SIZE) / 2 - (lives - 1) * (LIFE_SPACING / 2) + LIFE_SPACING * i, (HEIGHT - LIFE_SIZE) / 2, Life, 0);
    }

    arduboy.setCursor(WIDTH / 2 - 4 * CHAR_WIDTH, HEIGHT / 4 * 3 - CHAR_HEIGHT / 2);
    arduboy.print("LEVEL: ");
    arduboy.print(stage.num);
  } else {
    arduboy.setCursor(WIDTH / 2 - 4 * CHAR_WIDTH, HEIGHT / 4 * 3 - CHAR_HEIGHT / 2);
    arduboy.print("SCORE: ");
    arduboy.print(score);

    if (status == GOAL) {
      arduboy.setCursor(WIDTH / 2 - 24 - (GetNumberOfDigits(stagebonus) + 1) * CHAR_WIDTH / 2, HEIGHT / 2 - CHAR_HEIGHT / 2);
      arduboy.print("+");
      arduboy.print(stagebonus);
      arduboy.setCursor(WIDTH / 2 + 24 - (GetNumberOfDigits(timebonus) + 1) * CHAR_WIDTH / 2, HEIGHT / 2 - CHAR_HEIGHT / 2);
      arduboy.print("+");
      arduboy.print(timebonus);
    }
  }

  if (arduboy.justPressed(A_BUTTON)) {  // Just for testing?
    statustimer = 0;
  }


  if (statustimer <= 0) {
    if (status != MISS) {  // Reset timer unless MISS
      currentstagetimer = 0;
    }

    arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
    gamestate = GAME_PLAY;

  } else {
    statustimer--;
  }
}

void gameoverscreen() {
  arduboy.setCursor(WIDTH / 2 - 5 * CHAR_WIDTH, HEIGHT / 4 - CHAR_HEIGHT / 2);
  arduboy.print("GAME OVER!");

  arduboy.setCursor(WIDTH / 2 - 6 * CHAR_WIDTH, HEIGHT / 2 - CHAR_HEIGHT / 2);
  arduboy.print("SCORE: ");
  arduboy.print(score);



  arduboy.setCursor((WIDTH - 19 * CHAR_WIDTH) / 2, HEIGHT / 4 * 3 - CHAR_HEIGHT / 2);
  arduboy.print("PRESS");

  if (showtextblink) {
    arduboy.print(" A ");
  }

  arduboy.setCursor((WIDTH - 3 * CHAR_WIDTH) / 2, HEIGHT / 4 * 3 - CHAR_HEIGHT / 2);
  arduboy.print("TO CONTINUE");


  if (arduboy.everyXFrames(30)) {
    showtextblink = !showtextblink;
  }

  if (arduboy.justPressed(A_BUTTON)) {
    gamestate = GAME_TITLE;
  }
}

void gameloop() {
  switch (gamestate) {
    case GAME_TITLE:
      titlescreen();
      break;

    case GAME_PLAY:
      gameplay();
      break;

    case GAME_STATUS:
      gamestatus();
      break;

    case GAME_OVER:
      gameoverscreen();
      break;
  }
}

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.display();
  arduboy.initRandomSeed();
  arduboy.clear();

  //startgame();  // For testing only
}

void loop() {
  if (!(arduboy.nextFrame())) {
    return;
  }

  arduboy.setCursor(0, 0);
  arduboy.pollButtons();
  arduboy.clear();

  gameloop();

  arduboy.display();
}