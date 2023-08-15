struct Player {
  double x;
  double y;
  float velocity;   // Up is +
  float xvelocity;  // Right is +
  bool falling;
  int charge;
  int lastplatform;

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

#define MAX_PLATFORMS 30  // 'Not in the mood' for dynamic lists
struct Stage {
  int num;
  struct Platform platforms[MAX_PLATFORMS];
  int totalplatforms;
  uint16_t seed;
};

struct Zapfish {
  int y;
};
