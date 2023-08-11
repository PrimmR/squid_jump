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
#define X_VELOCITY_DECAY 0.01
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

  // Regular
  0x7e,
  0xc9,
  0x81,
  0x91,
  0xc1,
  0x83,
  0xa7,
  0x7e,

  // Ice
  0x7f,
  0xf1,
  0xb9,
  0xdd,
  0xaf,
  0xd7,
  0xeb,
  0xff,
};

const uint8_t PROGMEM Poison[] = {
  128,
  64,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xab,
  0x56,
  0xac,
  0x58,
  0xb8,
  0x5c,
  0xae,
  0x57,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
  0xaa,
  0x55,
};

float poisonheight = 128;
#define LEEWAY 8

#define ZAP_UP 42
#define ZAP_SIZE 18
const uint8_t PROGMEM Zap[] = {
  18,
  18,
  0x00,
  0x00,
  0xf0,
  0x0c,
  0x02,
  0x02,
  0x61,
  0xf9,
  0x99,
  0x99,
  0x79,
  0x71,
  0x99,
  0x9a,
  0x72,
  0x0c,
  0xf0,
  0x00,
  0x0c,
  0x12,
  0x2d,
  0xea,
  0x14,
  0x30,
  0x10,
  0x00,
  0x23,
  0x7e,
  0x7c,
  0xfc,
  0xa4,
  0x42,
  0x31,
  0x16,
  0x0b,
  0x04,
  0x00,
  0x00,
  0x00,
  0x00,
  0x01,
  0x01,
  0x01,
  0x01,
  0x01,
  0x01,
  0x01,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
};

// Instances
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

struct Player player = { WIDTH / 2, HEIGHT / 2, 0, 0, true, 0, 0 };

struct Platform {
  int x;
  int y;
  int len;
  int type;
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

struct Zapfish {
  int y;
};

struct Zapfish zapfish {
  0
};

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
  // Set up stage
  struct Platform ground = { 0, HEIGHT - 2 * BLOCK_SIZE, WIDTH / BLOCK_SIZE };
  stage.platforms[0] = ground;
  int lastheight = HEIGHT - 2 * BLOCK_SIZE;
  for (int i = 1; i < 20; i++) {
    int len = random(4, 8);
    int x = random(0, (WIDTH / BLOCK_SIZE - len) + 1) * BLOCK_SIZE;
    int y = lastheight - random(5, 10) * BLOCK_SIZE;
    int type = random(0, 2);
    stage.platforms[i] = { x, y, len, type };
    lastheight = y;
  }

  zapfish = { lastheight - ZAP_UP - ZAP_SIZE };

  stage.totalplatforms = 20;

  stage.num++;

  // Reset states
  player = { WIDTH / 2, HEIGHT / 2, 0, 0, true, 0, 0 };
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

  // arduboy.print(player.falling);
  // arduboy.print(player.lastplatform);

  // X
  if (player.xvelocity > MAX_X_VELOCITY) {  // X Velocity Limits
    player.xvelocity = MAX_X_VELOCITY;
  } else if (player.xvelocity < -MAX_X_VELOCITY) {
    player.xvelocity = -MAX_X_VELOCITY;
  }
  if (player.falling || stage.platforms[player.lastplatform].type == 1) {  // Set to 0 when on solid ground
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

  // Boundaries
  if (player.intX() < 0) {
    player.x = 0;
  } else if (player.intX() + PLAYER_SIZE > WIDTH) {
    player.x = WIDTH - PLAYER_SIZE;
  }

  // arduboy.print(player.xvelocity);
}

void poison() {
  poisonheight -= 0.25;

  if (player.y + PLAYER_SIZE > poisonheight + LEEWAY) {
    gamestate = GAME_OVER;
  }
}

void zap() {
  if (!cullzap(zapfish)) {
    Rect playerbox = Rect(player.intX(), player.intY(), PLAYER_SIZE, PLAYER_SIZE);
    Rect zapbox = Rect((WIDTH - ZAP_SIZE) / 2, zapfish.y, ZAP_SIZE, ZAP_SIZE);
    if (Arduboy2::collide(playerbox, zapbox)) {
      nextstage();
    }
  }
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
        Sprites::drawOverwrite(stage.platforms[k].x + i * BLOCK_SIZE, stage.platforms[k].y + camerapos, Block, stage.platforms[k].type);
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
  gameinput();
  poison();
  zap();
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