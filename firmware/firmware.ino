#include <HID-Project.h>

#define arraySize 3
#define Sync 0xff

#define CIRCLE 3
#define CROSS 2
#define SQUARE 1
#define TRIANGLE 4
#define OPTION 10

#define CIRCLE_PIN 6
#define CROSS_PIN 5
#define SQUARE_PIN 4
#define TRIANGLE_PIN 3
#define START_PIN 2

#define led1 21  // BUTTON LED TRIANGLE
#define led2 20  // BUTTON LED SQUARE
#define led3 19  // BUTTON LED CROSS
#define led4 18  // BUTTON LED CIRCLE

#define led_R1 14  // LEFT PARTITION LED PED
#define led_G1 15  // LEFT PARTITION LED GREEN
#define led_B1 16  // LEFT PARTITION LED BLUE

#define led_R2 8  // RIGHT PARTITION LED PED
#define led_G2 7 // RIGHT PARTITION LED GREEN
#define led_B2 9 // RIGHT PARTITION LED BLUE

uint8_t iteration = 0;
uint8_t inData[arraySize];

#define BUTTON_NUM 5

const unsigned char button_direct_table[8] = {
  TRIANGLE, SQUARE, CROSS, CIRCLE, OPTION, 0, 0, 0
};

const unsigned char button_direct_logic = 0b11111110;

const int button_direct_pin_table[BUTTON_NUM] = {
  TRIANGLE_PIN, SQUARE_PIN, CROSS_PIN, CIRCLE_PIN, START_PIN
};

unsigned char button_data_byte = 0;

unsigned char readDirectlyConnectedButtons(int *pin_table, unsigned char pin_logic);
void addHIDreportFromTable(unsigned char serial_data_byte, unsigned char *button_table, int contents_of_table_num);

void setup(void) {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led_R1, OUTPUT);
  pinMode(led_G1, OUTPUT);
  pinMode(led_B1, OUTPUT);
  pinMode(led_R2, OUTPUT);
  pinMode(led_G2, OUTPUT);
  pinMode(led_B2, OUTPUT);
  for(int i = 0; i < BUTTON_NUM; i++) {
    pinMode(button_direct_pin_table[i], INPUT_PULLUP);
  }
  Gamepad.begin();
}

void loop(void) {
  button_data_byte = readDirectlyConnectedButtons(button_direct_pin_table, button_direct_logic);
  addHIDreportFromTable(button_data_byte, button_direct_table, BUTTON_NUM);
  Gamepad.write();
  if(Serial.available()){
      inData[iteration] = Serial.read();
      iteration++;
      if(iteration>2) 
        Update();
      if(inData[0] != Sync) 
        Clear();
  }
}

unsigned char readDirectlyConnectedButtons(int *pin_table, unsigned char pin_logic) {
  unsigned char result = 0;
  for(int i = 0; i < BUTTON_NUM; i++) {
    result |= (digitalRead(pin_table[i]) << (7 - i));
  }
  return result ^ pin_logic;
}

void addHIDreportFromTable(unsigned char serial_data_byte, unsigned char *button_table, int contents_of_table_num) {
  for(int i = 0; i < contents_of_table_num; i++)
    serial_data_byte >> (7 - i) & 0x01 ? Gamepad.press(button_table[i]) : Gamepad.release(button_table[i]);
}

void Update() {
//BUTTONS 

      bitRead(inData[1],0) ? digitalWrite(led1, HIGH) : digitalWrite(led1, LOW);
      bitRead(inData[1],1) ? digitalWrite(led2, HIGH) : digitalWrite(led2, LOW);
      bitRead(inData[1],2) ? digitalWrite(led3, HIGH) : digitalWrite(led3, LOW);
      bitRead(inData[1],3) ? digitalWrite(led4, HIGH) : digitalWrite(led4, LOW);

//SIDES
      bitRead(inData[2],0) ? digitalWrite(led_R1, HIGH) : digitalWrite(led_R1, LOW);
      bitRead(inData[2],1) ? digitalWrite(led_G1, HIGH) : digitalWrite(led_G1, LOW);
      bitRead(inData[2],2) ? digitalWrite(led_B1, HIGH) : digitalWrite(led_B1, LOW);
      bitRead(inData[2],3) ? digitalWrite(led_R2, HIGH) : digitalWrite(led_R2, LOW);
      bitRead(inData[2],4) ? digitalWrite(led_G2, HIGH) : digitalWrite(led_G2, LOW);
      bitRead(inData[2],5) ? digitalWrite(led_B2, HIGH) : digitalWrite(led_B2, LOW);
      
      Clear();
}
    
void Clear() {
      iteration = 0;
      inData[0] = 0;
      inData[1] = 0;
      inData[2] = 0;
}
