#include "Map.h"
#include "Entropy.h"

uint8_t map1 [16] = {TWO_WAY, THREE_WAY, TWO_WAY, TWO_WAY_CORNER,
                  TWO_WAY_CORNER, THREE_WAY, FOUR_WAY, TWO_WAY,
                  TWO_WAY, THREE_WAY, TWO_WAY, TWO_WAY_CORNER,
                  TWO_WAY_CORNER, TWO_WAY_CORNER, THREE_WAY, TWO_WAY_CORNER};

uint32_t __attribute__((section(".noinit"))) random_seed;

void __attribute__((naked, section(".init3"))) seed_from_ram()
{
    const uint32_t * const ramstart = (uint32_t *) RAMSTART;
    const uint32_t * const ramend   = (uint32_t *) RAMEND;
    uint32_t seed = 0;
    for (const uint32_t *p = ramstart; p <= ramend; p++)
        seed ^= *p;
    random_seed = seed;
}

Map::Map(){
    //Entropy.initialize();
    srand (random_seed);
}

void Map::generate(byte seed){
  for (int i = 0; i < MAP_SIZE; i++){
      uint16_t coordinate = index_to_coordinate(i);
      byte topleft_x = coordinate >> 8;
      byte topleft_y = coordinate & 0x0000FFFF;
      pipes[i].set_coordinate(topleft_x, topleft_y);
      pipes[i].set_pipetype(randNum_generator(4, 0));
      pipes[i].set_orientation(randNum_generator(4, 1));
  }
}

uint16_t Map::index_to_coordinate(byte i){
    byte origin_x = 2;
    byte origin_y = 2;
    byte side_length = 12;

    byte row = i / 5;
    byte col = i % 5;

    byte y = origin_y + side_length * row;
    byte x = origin_x + side_length * col;

    return (x << 8) | y;
}

Pipe Map::get_pipe(byte index){
  return pipes[index];
}

uint8_t Map::randNum_generator(uint8_t m, uint8_t start_num){
  //uint8_t result = Entropy.random(start_num, start_num + m); // return a 0 or a 1
  uint8_t result = rand() % 4 + start_num;
  return result;
}



