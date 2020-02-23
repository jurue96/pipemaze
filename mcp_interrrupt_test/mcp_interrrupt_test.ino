#include <Wire.h>
#include <Adafruit_MCP23017.h>

#define BUTTON_NUM 16
#define ATTACH_INTERRUPT attachInterrupt(digitalPinToInterrupt(arduinoIntPin),isr_button,RISING)

/* --- Begin global variables --- */
Adafruit_MCP23017 button_mcp;

byte ledPin=5; // pin in arduino
byte arduinoIntPin=3;
/* ---- End global variables ---- */

/* --- Begin function declaration --- */
void init_button_mcp();
void enable_button_interrupt();
void isr_button();

/* ---- End function declaration ---- */

void setup() {
  Serial.begin(9600);
  pinMode(arduinoIntPin,INPUT);
  pinMode(ledPin, OUTPUT);  // use the p13 LED as debugging

  init_button_mcp();
  enable_button_interrupt();
  
  ATTACH_INTERRUPT; 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("int pin: ");
  Serial.print(digitalRead(arduinoIntPin));
  Serial.print(" ");
  Serial.print(button_mcp.getLastInterruptPin());
  Serial.println("");
  delay(1000);
}

void init_button_mcp(){
  button_mcp.begin();      // use default address 0

  // configure all 16 buttons to be input with pull-up enabled
  for (int i = 0; i < BUTTON_NUM; i++){
    button_mcp.pinMode(i, INPUT);
    button_mcp.pullUp(i, HIGH);
  }
}

void enable_button_interrupt(){
  // configure button_mcp23017 for interrupt (mirroring = true, opendrain = false, output = active high)
  button_mcp.setupInterrupts(true,false,HIGH); 

  for (int i = 0; i < BUTTON_NUM; i++){
    button_mcp.setupInterruptPin(i, CHANGE); // int pin goes high whenever pin input changes 
  }

  // clear previous interrupt stuff
  button_mcp.readGPIOAB();
}

/* Interrupt Service Routine when button is pressed/released */
void isr_button(){
  static bool pressed = false;
  static uint8_t pressed_pin = -1;
  
  noInterrupts();
  delayMicroseconds(1000);
  detachInterrupt(digitalPinToInterrupt(arduinoIntPin));
  interrupts();

  // --- Begin actual code ---
  uint8_t pin = button_mcp.getLastInterruptPin();
  uint8_t val = button_mcp.getLastInterruptPinValue();

  if (!pressed && val){ //pressed
    Serial.println("pressed");
    pressed = true;
    pressed_pin = pin; // save the first button pressed
  }
  else if (pressed && !val && (pressed_pin == pin)){ //released
    Serial.println("released");
    pressed = false;
    pressed_pin = -1;
  }

  Serial.println(pressed_pin);
  // --- End actual code ---
  
  ATTACH_INTERRUPT; 
}
