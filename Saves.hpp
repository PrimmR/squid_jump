#include <EEPROM.h>
#define EEPROM_START_CHECK 500
#define EEPROM_START_LEVEL EEPROM_START_CHECK + 2
#define EEPROM_START_SCORE EEPROM_START_LEVEL + 1

byte toplevel = 1;
uint32_t topscore = 0;

void saveEEPROM() {
  EEPROM.update(EEPROM_START_LEVEL, toplevel);
  EEPROM.put(EEPROM_START_SCORE, topscore);
}

void initEEPROM() {
  byte c1 = EEPROM.read(EEPROM_START_CHECK);
  byte c2 = EEPROM.read(EEPROM_START_CHECK + 1);

  if (c1 == 0x20 && c2 == 0x82) {
    toplevel = EEPROM.read(EEPROM_START_LEVEL);
    EEPROM.get(EEPROM_START_SCORE, topscore);

  } else {
    EEPROM.update(EEPROM_START_CHECK, 0x20);
    EEPROM.update(EEPROM_START_CHECK + 1, 0x82);
    saveEEPROM();
  }
}