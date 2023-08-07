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
#define REGULAR 0
#define CHARGE_1 1  // Unused?
#define CHARGE_2 2
#define CHARGE_3 3
#define CHARGE_4 4
#define CHARGE_NUM 3
int sprite = REGULAR;  // Default

#define MAX_CHARGE 80

#define PLAYER_SIZE 15
const uint8_t PROGMEM Player[] = {
  // Regular
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

  // Charge 1
  0xc0,
  0xe0,
  0xf0,
  0x78,
  0xbc,
  0x7e,
  0xff,
  0xff,
  0xff,
  0x7e,
  0xbc,
  0x78,
  0xf0,
  0xe0,
  0xc0,
  0x00,
  0x40,
  0x41,
  0x7c,
  0x3b,
  0x7a,
  0x3a,
  0x1d,
  0x3a,
  0x7a,
  0x3b,
  0x7c,
  0x41,
  0x40,
  0x00,

  // Charge 2
  0xc0,
  0xc0,
  0xe0,
  0xe0,
  0x70,
  0xf8,
  0xfc,
  0xfc,
  0xfc,
  0xf8,
  0x70,
  0xe0,
  0xe8,
  0xc0,
  0xc0,
  0x09,
  0x41,
  0x63,
  0x78,
  0x37,
  0x74,
  0x35,
  0x1b,
  0x35,
  0x74,
  0x37,
  0x78,
  0x63,
  0x41,
  0x01,

  // Charge 3
  0x00,
  0x10,
  0x80,
  0xc0,
  0xc0,
  0xe0,
  0xe0,
  0xe0,
  0xe0,
  0xe0,
  0xc0,
  0xc0,
  0x80,
  0x40,
  0x00,
  0x03,
  0x47,
  0x6f,
  0x31,
  0x6e,
  0x29,
  0x2b,
  0x37,
  0x2b,
  0x29,
  0x6e,
  0x31,
  0x6f,
  0x47,
  0x03,

  // Charge 4
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x30,
  0x38,
  0x7c,
  0x62,
  0x5c,
  0x53,
  0x57,
  0x6f,
  0x57,
  0x53,
  0x5c,
  0x62,
  0x7c,
  0x38,
  0x30,
};

const uint8_t PROGMEM Player_Mask[] = {
  // Regular
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

  // Charge 1
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
  0x40,
  0x41,
  0x7f,
  0x3f,
  0x7f,
  0x3f,
  0x1f,
  0x3f,
  0x7f,
  0x3f,
  0x7f,
  0x41,
  0x40,
  0x00,

  // Charge 2
  0xc0,
  0xc0,
  0xe0,
  0xe0,
  0xf0,
  0xf8,
  0xfc,
  0xfc,
  0xfc,
  0xf8,
  0xf0,
  0xe0,
  0xe8,
  0xc0,
  0xc0,
  0x09,
  0x41,
  0x63,
  0x7f,
  0x3f,
  0x7f,
  0x3f,
  0x1f,
  0x3f,
  0x7f,
  0x3f,
  0x7f,
  0x63,
  0x41,
  0x01,

  // Charge 3
  0x00,
  0x10,
  0x80,
  0xc0,
  0xc0,
  0xe0,
  0xe0,
  0xe0,
  0xe0,
  0xe0,
  0xc0,
  0xc0,
  0x80,
  0x40,
  0x00,
  0x03,
  0x47,
  0x6f,
  0x7f,
  0x7f,
  0x7f,
  0x3f,
  0x3f,
  0x3f,
  0x7f,
  0x7f,
  0x7f,
  0x6f,
  0x47,
  0x03,

  // Charge 4
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x30,
  0x78,
  0x7c,
  0x7e,
  0x7e,
  0x7f,
  0x7f,
  0x7f,
  0x7f,
  0x7f,
  0x7e,
  0x7e,
  0x7c,
  0x78,
  0x30,
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
  float velocity;  // Up is +
  bool falling;
  int charge;

  int intX() {
    return x;
  }
  int intY() {
    return y;
  }
};

struct Player player = { WIDTH / 2, HEIGHT / 2, 0, true, 0 };

struct Platform {
  int x;
  int y;
  int len;
};

// Rect ground = Rect(0, HEIGHT - 2 * BLOCK_SIZE, WIDTH, BLOCK_SIZE);

struct Platform ground = { 0, HEIGHT - 2 * BLOCK_SIZE, WIDTH / BLOCK_SIZE };

struct Platform platform = { 16, 16, 6 };

struct Platform platforms[3] = { ground, platform, {0,-20,7} };

// Camera
#define CAM_UPPER_BOUNDARY 16  // Positions for which the camera starts to follow
#define CAM_LOWER_BOUNDARY 40

int camerapos = 0;  // + moves screen up
int cameratick = 0;


// FUNCTIONS


void titlescreen() {
  arduboy.print("title");
}

void gameinput() {
  if (arduboy.pressed(LEFT_BUTTON) && player.falling) {
    player.x--;
  }
  if (arduboy.pressed(RIGHT_BUTTON) && player.falling) {
    player.x++;
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
    }
    player.charge = 0;
  }

  // arduboy.print(player.charge);
  // arduboy.print(" ");

  if (player.x < 0) {
    player.x = 0;
  } else if (player.x + PLAYER_SIZE > WIDTH) {
    player.x = WIDTH - PLAYER_SIZE;
  }
}

// Calculates whether platform would be hit next frame (may fail if collision boxes both 1px)
bool collision(Platform platform) {  // Assume that it's always called by player
  if (player.velocity < 0) {
    Rect ray = Rect(player.x, player.y + PLAYER_SIZE + camerapos, PLAYER_SIZE, -ceil(player.velocity));
    Rect platformtop = Rect(platform.x, platform.y + camerapos, platform.len * BLOCK_SIZE, 2);
    // arduboy.fillRect(player.x, player.y + PLAYER_SIZE + camerapos, PLAYER_SIZE, -1 * ceil(player.velocity)); // Visual
    // arduboy.fillRect(platform.x, platform.y + camerapos, platform.len * BLOCK_SIZE, 2); // Visual
    return Arduboy2::collide(ray, platformtop);
  }
  return false;
}

void physics() {
  if (player.falling) {
    player.y -= player.velocity;
    player.velocity -= 0.1;
  }
  for (auto const& plat : platforms) {
    if (collision(plat)) {
      player.y = plat.y - PLAYER_SIZE;
    player.falling = false;
    }
  }
}

void movecamera() {
  // PLayer location on screen player.box.y + camerapos
  // camerapos = (-1 * player.y) + 40;
  if (player.y + camerapos < CAM_UPPER_BOUNDARY) {
    camerapos = -player.y + CAM_UPPER_BOUNDARY;
  } else if (player.y + camerapos > CAM_LOWER_BOUNDARY) {
    camerapos = -player.y + CAM_LOWER_BOUNDARY;
  }

  // arduboy.print(camerapos);
}

void drawgame() {
  for (auto const& plat : platforms) { // For every platform in platforms
    for (int i = 0; i < plat.len; i++) {
      Sprites::drawOverwrite(plat.x + i * BLOCK_SIZE, plat.y + camerapos, Block, 0);
    }
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