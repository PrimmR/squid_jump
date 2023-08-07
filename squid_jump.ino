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

#define MAX_X_VELOCITY 1.5
#define X_VELOCITY_DECAY 0.1
#define X_ACCEL 0.1
#define MAX_Y_VELOCITY 12
#define Y_ACCEL 0.1
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
  double x;
  double y;
  float velocity;   // Up is +
  float xvelocity;  // Right is +
  bool falling;
  int charge;

  int intX() {
    return x;
  }
  int intY() {
    return y;
  }
};

struct Player player = { WIDTH / 2, HEIGHT / 2, 0, 0, true, 0 };

struct Platform {
  int x;
  int y;
  int len;
};

#define MAX_PLATFORMS 30  // 'Not in the mood' for dynamic lists

struct Stage {
  int num;
  struct Platform platforms[MAX_PLATFORMS];
  int totalplatforms;
};

struct Stage stage = { 0, {}, 0 };

// Camera
#define CAM_UPPER_BOUNDARY 16  // Positions for which the camera starts to follow
#define CAM_LOWER_BOUNDARY 40

int camerapos = 0;  // + moves screen up

// FUNCTIONS


void titlescreen() {
  arduboy.print("title");
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
    }
    player.charge = 0;
  }

  if (arduboy.justPressed(B_BUTTON)) {
    nextstage();
  }

  // arduboy.print(player.charge);
  // arduboy.print(" ");
}

void nextstage() {
  struct Platform ground = { 0, HEIGHT - 2 * BLOCK_SIZE, WIDTH / BLOCK_SIZE };
  stage.platforms[0] = ground;
  int lastheight = HEIGHT - 2 * BLOCK_SIZE;
  for (int i = 1; i < 20; i++) {
    int len = random(4, 8);
    int x = random(0, (WIDTH / BLOCK_SIZE - len) + 1) * BLOCK_SIZE;
    int y = lastheight - random(5, 10) * BLOCK_SIZE;
    stage.platforms[i] = { x, y, len };
    lastheight = y;
  }

  stage.totalplatforms = 20;

  stage.num++;
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
  // Y
  if (player.falling) {
    player.y -= player.velocity;
    player.velocity -= Y_ACCEL;
  }
  if (player.velocity > MAX_Y_VELOCITY) {
    player.velocity = MAX_Y_VELOCITY;
  }

  // for (auto const& plat : stage.platforms) {
  for (int i = 0; i < stage.totalplatforms; i++) {
    if (!cull(stage.platforms[i])) {
      if (collision(stage.platforms[i])) {
        player.y = stage.platforms[i].y - PLAYER_SIZE;
        player.falling = false;
      }
    }
  }

  // X
  if (player.xvelocity > MAX_X_VELOCITY) {
    player.xvelocity = MAX_X_VELOCITY;
  } else if (player.xvelocity < -MAX_X_VELOCITY) {
    player.xvelocity = -MAX_X_VELOCITY;
  }
  if (player.falling) {
    player.x += player.xvelocity;
  } else {
    player.xvelocity = 0;
  }

  if (player.xvelocity > 0) {
    player.xvelocity -= 0.1;
  } else if (player.xvelocity < 0) {
    player.xvelocity += 0.1;
  }

  // Boundaries
  if (player.intX() < 0) {
    player.x = 0;
  } else if (player.intX() + PLAYER_SIZE > WIDTH) {
    player.x = WIDTH - PLAYER_SIZE;
  }

  arduboy.print(player.xvelocity);
}

void movecamera() {
  // PLayer location on screen player.y + camerapos
  // camerapos = (-1 * player.y) + 40;
  if (player.y + camerapos < CAM_UPPER_BOUNDARY) {
    camerapos = -player.y + CAM_UPPER_BOUNDARY;
  } else if (player.y + camerapos > CAM_LOWER_BOUNDARY) {
    camerapos = -player.y + CAM_LOWER_BOUNDARY;
  }
  // arduboy.print(camerapos);
}

bool cull(struct Platform platform) {
  return platform.y + camerapos + player.velocity > HEIGHT || platform.y + camerapos + BLOCK_SIZE < 0;
}

void drawgame() {
  // for (auto& plat : stage.platforms) {  // For every platform in platforms
  for (int k = 0; k < stage.totalplatforms; k++) {
    if (!cull(stage.platforms[k])) {
      for (int i = 0; i < stage.platforms[k].len; i++) {
        Sprites::drawOverwrite(stage.platforms[k].x + i * BLOCK_SIZE, stage.platforms[k].y + camerapos, Block, 0);
      }
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

  arduboy.print(stage.num);

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

  nextstage();
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