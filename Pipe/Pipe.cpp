#include "Pipe.h"
 
// default constructor
Pipe::Pipe(){
}

void Pipe::set_coordinate(byte x, byte y){
  pos_x = x;
  pos_y = y;
}

void Pipe::set_pipetype(byte ptype){
  pipe_type = ptype;
}

void Pipe::set_orientation(byte ot){
  orientation = ot;
}

void Pipe::rotate(){
  byte current_rot = this->orientation % 4;
  this->orientation = (current_rot == 0) ? 1 : (this->orientation + 1); 
}

/** print out member varaibles for debgging **/
void Pipe::print_pipe(){
  Serial.begin(9600);
  Serial.print("X position: ");
  Serial.println(this->pos_x);
  Serial.print("Y position: ");
  Serial.println(this->pos_y);
  Serial.print("Pipe type: ");
  Serial.println(this->pipe_type);
  Serial.print("Orientation: ");
  Serial.println(this->orientation);
  Serial.end();
}

byte Pipe::get_orientation(){
  return this->orientation;
}
byte Pipe::get_locationX(){
  return this->pos_x;
}
byte Pipe::get_locationY(){
  return this->pos_y;
}
byte Pipe::get_pipeType(){
  return this->pipe_type;
}