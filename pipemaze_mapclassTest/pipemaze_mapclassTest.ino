#include <Map.h>
#include <RGBmatrixPanel.h>

#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
#define PIXEL_NUM 64

// Function signatures
void two_way_v(byte x, byte y);
void two_way_h(byte x, byte y);
void two_way_0(byte x, byte y);
void two_way_90(byte x, byte y);
void two_way_180(byte x, byte y);
void two_way_270(byte x, byte y);
void three_way_0(byte x, byte y);
void three_way_90(byte x, byte y);
void three_way_180(byte x, byte y);
void three_way_270(byte x, byte y);
void four_way(byte x, byte y);

//Global variables
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, PIXEL_NUM);
Map first_map;

void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  //first_map.generate(0);
  //print_map(first_map);
}

void loop() {
  // put your main code here, to run repeatedly
  first_map.generate(0);
  print_map(first_map);
}

void print_map(Map m){     
    //Serial.begin(9600);    
    for (byte i = 0; i < MAP_SIZE; i++){
        Pipe cur_pipe = m.get_pipe(i);
        byte degree = cur_pipe.get_orientation();
        byte cur_x = cur_pipe.get_locationX();
        byte cur_y = cur_pipe.get_locationY();
        byte pipe_type = cur_pipe.get_pipeType();
        
        //cur_pipe.print_pipe();
        switch(pipe_type){
        case TWO_WAY:
            
            if (degree == ZERO || degree == ONE_EIGHTY){
            two_way_h(cur_x, cur_y);
            //Serial.println("Two way degree 0");
            }

            if (degree == NINETY || degree == TWO_SEVENTY)
            two_way_v(cur_x, cur_y);
            break;
        case THREE_WAY:
            if (degree == ZERO)
            three_way_0(cur_x, cur_y);
            if (degree == NINETY)
            three_way_90(cur_x, cur_y);
            if (degree == ONE_EIGHTY)
            three_way_180(cur_x, cur_y);
            if (degree == TWO_SEVENTY)
            three_way_270(cur_x, cur_y);
            break;
        case FOUR_WAY:
            four_way(cur_x, cur_y);
        }
    }
}

void two_way_v(byte x, byte y){
  //filling pipe rectangle
  matrix.fillRect(x, y, 12, 12, matrix.Color444(1, 0, 5));
  //rectangle on bottom side
  matrix.drawRect(x + 3, y, 6, 3, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 4, y + 1, 4, 1, matrix.Color444(0,0,0));
  //middle rectangle
  matrix.drawRect(x + 4, y + 2, 4, 8, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 5, y + 3, 2, 6, matrix.Color444(0,0,0));
  //rectangle on top side
  matrix.drawRect(x + 3, y + 9, 6, 3, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 4, y + 10, 4, 1, matrix.Color444(0, 0, 0));
}

void two_way_h(byte x, byte y){
  //filling pipe rectangle
  matrix.fillRect(x, y, 12, 12, matrix.Color444(1, 0, 5));
  //rectangle on right side
  matrix.drawRect(x, y + 3, 3, 6, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 1, y + 4, 1, 4, matrix.Color444(0,0,0));
  //middle rectangle
  matrix.drawRect(x + 2, y + 4, 8, 4, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 3, y + 5, 6, 2, matrix.Color444(0,0,0));
  //rectangle on left side
  matrix.drawRect(x + 9, y + 3, 3, 6, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 10, y + 4, 1, 4, matrix.Color444(0, 0, 0));
}

void two_way_0(byte x, byte y){
  //Corner pipe - up + right
  //filling pipe rectangle
  matrix.fillRect(x, y, 12, 12, matrix.Color444(1, 0, 5));
  //rectangle on up side
  matrix.drawRect(x + 3, y, 6, 3, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 4, y + 1, 4, 1, matrix.Color444(0,0,0));
  //rectangle on right side
  matrix.drawRect(x + 9, y + 3, 3, 6, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 10, y + 4, 1, 4, matrix.Color444(0, 0, 0));
  //connecting rectangle(s)
  //outer trace
  matrix.fillRect(x + 4, y + 3, 4, 5, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 8, y + 4, 1, 4, matrix.Color444(4, 4, 4));
  //inner fill
  matrix.fillRect(x + 5, y + 3, 2, 4, matrix.Color444(0, 0, 0));
  matrix.fillRect(x + 7, y + 5, 2, 2, matrix.Color444(0, 0, 0));
}

void two_way_90(byte x, byte y){
  //corner pipe - down + right
  //filling pipe rectangle
  matrix.fillRect(x, y, 12, 12, matrix.Color444(1, 0, 5));
  //rectangle on down side
  matrix.drawRect(x + 3, y + 9, 6, 3, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 4, y + 10, 4, 1, matrix.Color444(0, 0, 0));
  //rectangle on right side
  matrix.drawRect(x + 9, y + 3, 3, 6, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 10, y + 4, 1, 4, matrix.Color444(0, 0, 0));
  //connecting rectangle(s)
  //outer trace
  matrix.fillRect(x + 4, y + 4, 4, 5, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 8, y + 4, 1, 4, matrix.Color444(4, 4, 4));
  //inner fill
  matrix.fillRect(x + 5, y + 5, 2, 4, matrix.Color444(0, 0, 0));
  matrix.fillRect(x + 7, y + 5, 2, 2, matrix.Color444(0, 0, 0));
}

void two_way_180(byte x, byte y){
 //corner pipe - down + left
  //filling pipe rectangle
  matrix.fillRect(x, y, 12, 12, matrix.Color444(1, 0, 5));
  //rectangle on down side
  matrix.drawRect(x + 3, y + 9, 6, 3, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 4, y + 10, 4, 1, matrix.Color444(0, 0, 0));
  //rectangle on left side
  matrix.drawRect(x, y + 3, 3, 6, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 1, y + 4, 1, 4, matrix.Color444(0,0,0));
  //connecting rectangle(s)
  //outer trace
  matrix.fillRect(x + 4, y + 4, 4, 5, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 3, y + 4, 1, 4, matrix.Color444(4, 4, 4));
  //inner fill
  matrix.fillRect(x + 5, y + 5, 2, 4, matrix.Color444(0, 0, 0));
  matrix.fillRect(x + 3, y + 5, 2, 2, matrix.Color444(0, 0, 0));
}

void two_way_270(byte x, byte y){
 //corner pipe - up + left
  //filling pipe rectangle
  matrix.fillRect(x, y, 12, 12, matrix.Color444(1, 0, 5));
  //rectangle on top side
  matrix.drawRect(x + 3, y, 6, 3, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 4, y + 1, 4, 1, matrix.Color444(0,0,0));
  //rectangle on left side
  matrix.drawRect(x, y + 3, 3, 6, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 1, y + 4, 1, 4, matrix.Color444(0,0,0));
  //connecting rectangle(s)
  //outer trace
  matrix.fillRect(x + 3, y + 4, 5, 4, matrix.Color444(4, 4, 4));
  matrix.fillRect(x + 4, y + 3, 4, 1, matrix.Color444(4, 4, 4));
  //inner fill
  matrix.fillRect(x + 5, y + 3, 2, 4, matrix.Color444(0, 0, 0));
  matrix.fillRect(x + 3, y + 5, 2, 2, matrix.Color444(0, 0, 0));
}

void three_way_0(byte x, byte y){ // up
  matrix.fillRect(x + 3, y, 6, 3, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.drawRect(x + 3, y, 6, 3, matrix.Color444(0x3a,0x3b,0x39));
  matrix.fillRect(x + 0, y + 3, 3, 6, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.drawRect(x + 0, y + 3, 3, 6, matrix.Color444(0x3a,0x3b,0x39));
  matrix.fillRect(x + 9, y + 3, 3, 6, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.drawRect(x + 9, y + 3, 3, 6, matrix.Color444(0x3a,0x3b,0x39));
  matrix.drawRect(x + 4, y + 2, 4, 6, matrix.Color444(0x3a,0x3b,0x39));
  matrix.drawRect(x + 2, y + 4, 8, 4, matrix.Color444(0x3a,0x3b,0x39));
  matrix.fillRect(x + 5, y + 3, 2, 4, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.fillRect(x + 3, y + 5, 6, 2, matrix.Color444(0xb0, 0xd9, 0xbb));
  
}

void three_way_90(byte x, byte y){ // right
  matrix.fillRect(x + 3, y + 0, 6, 3, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.drawRect(x + 3, y + 0, 6, 3, matrix.Color444(0x3a,0x3b,0x39));
  matrix.fillRect(x + 3, y + 9, 6, 3, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.drawRect(x + 3, y + 9, 6, 3, matrix.Color444(0x3a,0x3b,0x39));
  matrix.fillRect(x + 0, y + 3, 3, 6, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.drawRect(x + 0, y + 3, 3, 6, matrix.Color444(0x3a,0x3b,0x39));
  matrix.drawRect(x + 4, y + 2, 4, 8, matrix.Color444(0x3a,0x3b,0x39));
  matrix.drawRect(x + 2, y + 4, 6, 4, matrix.Color444(0x3a,0x3b,0x39));
  matrix.fillRect(x + 5, y + 3, 2, 6, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.fillRect(x + 3, y + 5, 4, 2, matrix.Color444(0xb0, 0xd9, 0xbb));
}

void three_way_180(byte x, byte y){ // down
  matrix.fillRect(x + 3, y + 9, 6, 3, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.drawRect(x + 3, y + 9, 6, 3, matrix.Color444(0x3a,0x3b,0x39));
  matrix.fillRect(x + 0, y + 3, 3, 6, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.drawRect(x + 0, y + 3, 3, 6, matrix.Color444(0x3a,0x3b,0x39));
  matrix.fillRect(x + 9, y + 3, 3, 6, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.drawRect(x + 9, y + 3, 3, 6, matrix.Color444(0x3a,0x3b,0x39));
  matrix.drawRect(x + 4, y + 4, 4, 6, matrix.Color444(0x3a,0x3b,0x39));
  matrix.drawRect(x + 2, y + 4, 8, 4, matrix.Color444(0x3a,0x3b,0x39));
  matrix.fillRect(x + 5, y + 5, 2, 4, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.fillRect(x + 3, y + 5, 6, 2, matrix.Color444(0xb0, 0xd9, 0xbb));
  
}

void three_way_270(byte x, byte y){ // left
  matrix.fillRect(x + 3, y + 0, 6, 3, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.drawRect(x + 3, y + 0, 6, 3, matrix.Color444(0x3a,0x3b,0x39));
  matrix.fillRect(x + 9, y + 3, 3, 6, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.drawRect(x + 9, y + 3, 3, 6, matrix.Color444(0x3a,0x3b,0x39));
  matrix.fillRect(x + 3, y + 9, 6, 3, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.drawRect(x + 3, y + 9, 6, 3, matrix.Color444(0x3a,0x3b,0x39));
  matrix.drawRect(x + 4, y + 2, 4, 8, matrix.Color444(0x3a,0x3b,0x39));
  matrix.drawRect(x + 4, y + 4, 6, 4, matrix.Color444(0x3a,0x3b,0x39));
  matrix.fillRect(x + 5, y + 3, 2, 6, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.fillRect(x + 5, y + 5, 4, 2, matrix.Color444(0xb0, 0xd9, 0xbb));
}

void four_way(byte x, byte y){
  matrix.fillRect(x + 0, y + 0, 12, 12, matrix.Color444(0xa8, 0x7c, 0xa0));
  matrix.fillRect(x + 3, y + 0, 6, 3, matrix.Color444(0x55, 0x55, 0x55));
  matrix.drawRect(x + 3, y + 0, 6, 3, matrix.Color444(0x55,0x55,0x55));
  matrix.fillRect(x + 3, y + 9, 6, 3, matrix.Color444(0x55, 0x55, 0x55));
  matrix.drawRect(x + 3, y + 9, 6, 3, matrix.Color444(0x55,0x55,0x55));
  matrix.fillRect(x + 0, y + 3, 3, 6, matrix.Color444(0x55, 0x55, 0x55));
  matrix.drawRect(x + 0, y + 3, 3, 6, matrix.Color444(0x55,0x55,0x55));
  matrix.fillRect(x + 9, y + 3, 3, 6, matrix.Color444(0xb0, 0xd9, 0xbb));
  matrix.drawRect(x + 9, y + 3, 3, 6, matrix.Color444(0x55,0x55,0x55));
  matrix.drawRect(x + 4, y + 2, 4, 8, matrix.Color444(0x55,0x55,0x55));
  matrix.drawRect(x + 2, y + 4, 8, 4, matrix.Color444(0x55,0x55,0x55));
  matrix.fillRect(x + 5, y + 3, 2, 6, matrix.Color444(0x55, 0x55, 0x55));
  matrix.fillRect(x + 3, y + 5, 6, 2, matrix.Color444(0x55, 0x55, 0x55));
}
