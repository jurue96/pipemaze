#ifndef MAP_H
#define MAP_H

#include "Pipe.h"

#if ARDUINO >= 100
 #include "Arduino.h"
#endif

#define MAP_SIZE 25

class Map {
  private:
    uint8_t pipes_avail [16];
    byte start_index;
    byte end_index;
    Pipe pipes [MAP_SIZE];
    uint16_t index_to_coordinate(byte i);
    uint8_t randNum_generator(uint8_t m, uint8_t start_num);

  public: 
    Map();
    void generate(byte seed);
    Pipe get_pipe(byte index);
    bool connection_completed();
};

#endif
