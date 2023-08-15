unsigned GetNumberOfDigits(unsigned i) {
  return i > 0 ? (int)log10((double)i) + 1 : 1;
}

int ScoreFromFrames(uint16_t frames, int modifier) {
  return modifier * (1200 - frames / 2);
}

// Background maths
int hash(int key)
{
  int c2=0x27d4eb2d; // a prime or an odd constant
  key = (key ^ 61) ^ (key >> 16);
  key = key + (key << 3);
  key = key ^ (key >> 4);
  key = key * c2;
  key = key ^ (key >> 15);
  return key;
}




uint16_t hash(uint16_t pos, uint16_t seed) {
  return hash(pos) ^ seed;
}

int toposition(int x, int y) {
  return (y * (WIDTH / STAR_SIZE) + x);
}