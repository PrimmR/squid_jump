struct Player {
  double x;
  double y;
  float velocity;   // Up is +
  float xvelocity;  // Right is +
  bool falling;
  int charge;
  int lastplatform;
  uint16_t poweruptimer;
  byte powerupstate;
  bool jumpcharge;
  float velocitymod;

  int intX() {
    return floor(x);
  }
  int intY() {
    return floor(y);
  }
};

struct Platform {
  int x;
  int y;
  int len;
  int type;
  bool facingright;
  byte sprite;
};

#define POWERUP_TIME 660
struct Powerup {
  int x;
  int y;
  byte type;
  bool hidden;
};

struct Star {
  int x;
  int y;
  byte type;
};

#define MAX_PLATFORMS 30  // 'Not in the mood' for dynamic lists
#define MAX_POWERUPS 8
struct Stage {
  int num;
  struct Platform platforms[MAX_PLATFORMS];
  int totalplatforms;
  struct Powerup powerups[MAX_POWERUPS];
  int totalpowerups;
  byte staroffset;
};

struct Zapfish {
  int y;
};