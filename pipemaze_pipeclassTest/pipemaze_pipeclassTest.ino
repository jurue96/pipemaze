#include <Pipe.h>

boolean game_start = false;
void generate_map(int seed);
boolean check_connection();


Pipe first_pipe;
void setup() {
  first_pipe.set(0, 0, TWO_WAY, NINETY);
}

void loop() {
  // put your main code here, to run repeatedly:
  first_pipe.print_pipe();
  first_pipe.rotate();
  delay(1000);
}
