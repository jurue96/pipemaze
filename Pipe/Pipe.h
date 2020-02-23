#ifndef PIPE_H
#define PIPE_H

//pipe type
#define TWO_WAY   0
#define TWO_WAY_CORNER 1
#define THREE_WAY 2
#define FOUR_WAY  3

//orientation
// need to start from  1 otherwise cannot distinguish 0 and 270
#define ZERO        1 
#define NINETY      2
#define ONE_EIGHTY  3
#define TWO_SEVENTY 4

//placement type
#define BUFFER  0
#define REGULAR 1

#if ARDUINO >= 100
 #include "Arduino.h"
#endif

class Pipe {
  private:
    byte pos_x;
    byte pos_y;
    byte zone_type;
    byte pipe_type;
    byte orientation;

  public: 
    Pipe();
    void print_pipe();
    void rotate();
    void change_pos();
    // setters
    void set_coordinate(byte x, byte y);
    void set_orientation(byte ot);
    void set_pipetype(byte ptype);
    byte get_orientation();
    byte get_locationX();
    byte get_locationY();
    byte get_pipeType();

};

#endif