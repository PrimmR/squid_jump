// PrimmR 2023
// Squid Jump

#include <Arduboy2.h>
Arduboy2 arduboy;

// Game states
#define GAME_TITLE 0
#define GAME_PLAY 1
#define GAME_OVER 2
int gamestate = GAME_PLAY;

// Graphics
#define PLAYER_SIZE 15
const uint8_t PROGMEM Player[] = {
  15,
  15,
  0xc0,
  0xe0,
  0xf0,
  0x78,
  0xbc,
  0x3e,
  0x3f,
  0x7f,
  0x3f,
  0x3e,
  0xbc,
  0x78,
  0xf0,
  0xe0,
  0xc0,
  0x00,
  0x00,
  0x01,
  0x7c,
  0x3b,
  0x7a,
  0x3a,
  0x1d,
  0x3a,
  0x7a,
  0x3b,
  0x7c,
  0x01,
  0x00,
  0x00,
};

const uint8_t PROGMEM Player_Mask[] = {
  0xc0,
  0xe0,
  0xf0,
  0xf8,
  0xfc,
  0xfe,
  0xff,
  0xff,
  0xff,
  0xfe,
  0xfc,
  0xf8,
  0xf0,
  0xe0,
  0xc0,
  0x00,
  0x00,
  0x01,
  0x7f,
  0x3f,
  0x7f,
  0x3f,
  0x1f,
  0x3f,
  0x7f,
  0x3f,
  0x7f,
  0x01,
  0x00,
  0x00,
};

#define BLOCK_SIZE 8
const uint8_t PROGMEM Block[] = {
  8,
  8,
  0x7e,
  0xc9,
  0x81,
  0x91,
  0xc1,
  0x83,
  0xa7,
  0x7e,
};

// Instances
struct Player {
  float x;
  float y;
  Rect box;
  float velocity;  // Up is +
  bool falling;
  int charge;

  void setX(float newX) {  // When x accelleration added
    x = newX;
    box.x = newX;
  }
  void setY(float newY) {
    y = newY;
    box.y = newY;
  }
};

struct Player player = { WIDTH / 2, HEIGHT / 2, Rect(WIDTH / 2, HEIGHT / 2, PLAYER_SIZE, PLAYER_SIZE), 0, true, 0 };

Rect ground = Rect(0, HEIGHT - 2 * BLOCK_SIZE, WIDTH, BLOCK_SIZE);

Rect platform = Rect(16, 16, 6 * BLOCK_SIZE, BLOCK_SIZE);

// Camera
#define CAM_UPPER_BOUNDARY 16 // Positions for which the camera starts to follow
#define CAM_LOWER_BOUNDARY 40

int camerapos = 0;  // + moves screen up
int cameratick = 0;


// FUNCTIONS


void titlescreen() {
  arduboy.print("title");
}

void gameinput() {
  if (arduboy.pressed(LEFT_BUTTON) && player.falling) {
    player.box.x--;
  }
  if (arduboy.pressed(RIGHT_BUTTON) && player.falling) {
    player.box.x++;
  }
  if (arduboy.pressed(A_BUTTON)) {
    if (player.charge < 120) {
      player.charge++;
    }
  }
  if (arduboy.justReleased(A_BUTTON)) {
    if (!player.falling && player.charge >= 15) {
      player.velocity = static_cast<float>(player.charge) / 30;
      player.falling = true;
    }
    player.charge = 0;
  }

  arduboy.print(player.charge);
  arduboy.print(" ");

  if (player.box.x < 0) {
    player.box.x = 0;
  } else if (player.box.x + PLAYER_SIZE > WIDTH) {
    player.box.x = WIDTH - PLAYER_SIZE;
  }
}

// Calculates whether platform would be hit next frame
bool collision(Rect platform) {  // Assume that it's always called by player
  if (player.velocity < 0) {
    Rect ray = Rect(player.box.x, player.box.y + PLAYER_SIZE, player.box.width, -1 * ceil(player.velocity));
    Rect platformtop = Rect(platform.x, platform.y, platform.width, 1);
    // arduboy.fillRect(player.box.x, player.box.y + PLAYER_SIZE, player.box.width, -1 * ceil(player.velocity)); // Visual
    return Arduboy2::collide(ray, platformtop);
  }
  return false;
}

void physics() {
  if (player.falling) {
    player.setY(player.box.y - player.velocity);
    player.velocity -= 0.1;
  }
  if (collision(ground)) {
    player.setY(ground.y - PLAYER_SIZE);
    player.falling = false;
  } else if (collision(platform)) {
    player.setY(platform.y - PLAYER_SIZE);
    player.falling = false;
  }
  // arduboy.print(player.velocity);
  // arduboy.print(player.y);
}

void movecamera() {
  // PLayer location on screen player.box.y + camerapos
  // camerapos = (-1 * player.y) + 40;
  if (player.box.y + camerapos < CAM_UPPER_BOUNDARY) {
    camerapos = -player.box.y + CAM_UPPER_BOUNDARY;
  } else if (player.box.y + camerapos > CAM_LOWER_BOUNDARY) {
    camerapos = -player.box.y + CAM_LOWER_BOUNDARY;
  }

  arduboy.print(camerapos);
}

void drawgame() {
  // ground
  for (int i = 0; i < ground.width; i++) {
    Sprites::drawOverwrite(ground.x + i * BLOCK_SIZE, ground.y + camerapos, Block, 0);
  }
  // Regular platform
  for (int i = 0; i < platform.width / BLOCK_SIZE; i++) {
    Sprites::drawOverwrite(platform.x + i * BLOCK_SIZE, platform.y + camerapos, Block, 0);
  }
  // Draw player
  Sprites::drawExternalMask(player.box.x, player.box.y + camerapos, Player, Player_Mask, 0, 0);
}

void gameplay() {
  gameinput();
  physics();
  movecamera();
  drawgame();
}

void gameoverscreen() {
  arduboy.print("game over");
}

void gameloop() {
  switch (gamestate) {
    case GAME_TITLE:
      titlescreen();
      break;

    case GAME_PLAY:
      gameplay();
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