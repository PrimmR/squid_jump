#define REGULAR 0
#define CHARGE_2 1
#define CHARGE_3 2
#define CHARGE_4 3
#define CHARGE_NUM 3

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

#define REGULAR_PLATFORM 0
#define ICE_PLATFORM 1
#define JELLYFISH_PLATFORM 2
#define CONVEYOR_PLATFORM 4

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

  // Jellyfish L
  0x1e,
  0x5f,
  0xbb,
  0x5f,
  0xbb,
  0x5f,
  0xbf,
  0x1e,

  // Jellyfish R
  0x1e,
  0xbf,
  0x5f,
  0xbb,
  0x5f,
  0xbb,
  0x5f,
  0x1e,

  // Conveyor 0
  0x66,
  0x42,
  0x00,
  0x99,
  0x99,
  0x99,
  0x00,
  0x42,

  // Conveyor 1
  0x42,
  0x00,
  0x99,
  0x99,
  0x99,
  0x00,
  0x42,
  0x66,

  // Conveyor 2
  0x00,
  0x99,
  0x99,
  0x99,
  0x00,
  0x42,
  0x66,
  0x42,

  // Conveyor 3
  0x99,
  0x99,
  0x99,
  0x00,
  0x42,
  0x66,
  0x42,
  0x00,

  // Conveyor 4
  0x99,
  0x99,
  0x00,
  0x42,
  0x66,
  0x42,
  0x00,
  0x99,

  // Conveyor 5
  0x99,
  0x00,
  0x42,
  0x66,
  0x42,
  0x00,
  0x99,
  0x99,

  // Conveyor 6
  0x00,
  0x42,
  0x66,
  0x42,
  0x00,
  0x99,
  0x99,
  0x99,

  // Conveyor 7
  0x42,
  0x66,
  0x42,
  0x00,
  0x99,
  0x99,
  0x99,
  0x00,
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

#define LIFE_SIZE 8
const uint8_t PROGMEM Life[] = {
  8,
  8,
  0x18,
  0xfc,
  0x5e,
  0x7f,
  0x5e,
  0xfc,
  0x18,
  0x00,
};

#define NUM_STARS 8
#define STAR_SIZE 5
const uint8_t PROGMEM Star[] = {
  5,
  5,
  0x02,
  0x0e,
  0x07,
  0x04,
  0x00,

  0x00,
  0x0e,
  0x11,
  0x00,
  0x00,

  0x00,
  0x04,
  0x0e,
  0x04,
  0x00,

  0x08,
  0x04,
  0x04,
  0x02,
  0x00,

  0x00,
  0x04,
  0x0a,
  0x04,
  0x00,

  0x00,
  0x01,
  0x0e,
  0x10,
  0x00,

  0x08,
  0x00,
  0x15,
  0x00,
  0x04,

  0x04,
  0x00,
  0x15,
  0x00,
  0x04,
};