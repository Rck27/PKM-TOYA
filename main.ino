#include <Keypad.h>
#include <Adafruit_NeoPixel.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
const byte NUM_LEDS = 16;
const byte LED_PIN = 15;
int position, winCount;
unsigned long lastMillis, currentMillis;
char randomAlphabet;
int mode = 0;


Adafruit_NeoPixel pixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

char keys[ROWS][COLS] = {
  {'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L'},
  {'M', 'N', 'O', 'P'},
};

int state[ROWS*COLS] = {0}; // Initialize all to 0

byte colPins[COLS] = {19, 21, 22, 23}; //connect to the column pinouts of the kpd
byte rowPins[ROWS] = {2, 4, 5,  18}; //connect to the row pinouts of the kpd

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Function to get the index of the key in the keys array
int getKeyIndex(char key){
  for(int r = 0; r < ROWS; r++){
    for(int c = 0; c < COLS; c++){
      if(keys[r][c] == key) {
        return r * COLS + c; // Calculate the index
      }
    }
  }
  return -1; // Return -1 if the key is not found
}

// Function to turn on/off the LED at the given index
// void setLED(int index, int r, int g, int b){
//   if(index >= 0 && index < NUM_LEDS){
//     pixel.setPixelColor(index, pixel.Color(r, g, b));
//     pixel.show();
//   }
// }



void setLED(int index, int r, int g, int b) {
    if (index >= 0 && index < NUM_LEDS) {
        // Define the new mapping for the snake pattern
        int snakeIndices[] = {0, 1, 2, 3, 7, 6, 5, 4, 8, 9 , 10, 11, 15, 14, 13, 12};
        int mappedIndex = snakeIndices[index];
        pixel.setPixelColor(mappedIndex, pixel.Color(r, g, b));
        pixel.show();
    }
}


void simpleGame(char input) {
  static bool firstRound = true;
  static bool correctGuess = false;
  if (firstRound || correctGuess) {
    Serial.printf("Masukkan huruf : %c \n", randomAlphabet);
    firstRound = false;
  }

  if (input == randomAlphabet) {
    randomAlphabet = 'A' + random(16);
    for (int i = 0; i <= 15; i++){ 
        setLED(i, random(255), random(255), random(255));
        delay(150);
        }
    correctGuess = true;
  } else {
    for (int i = 16; i >= 0; i--) {setLED(i, 255, 0, 0); delay(100);};
    correctGuess = false;
  }
  for (int i = 0; i <= 15; i++) setLED(i, 0, 0, 0);

  // Handle individual LED behavior here based on correctGuess
  // (turn on corresponding LED briefly if correct, otherwise handle wrong guess)
}


void keypadRoutine(){
  if (kpd.getKeys()) {
    for (int i=0; i<16; i++) {
      if (kpd.key[i].stateChanged) {
        switch (kpd.key[i].kstate) {
          case PRESSED:
            position = getKeyIndex(kpd.key[i].kchar); // Get the index of the pressed key
            if(position != -1 && state[position] == 0){
              state[position] = 1; // Set the state to 1
              setLED(position, 255, 255, 0); // Turn the LED on
                switch(mode){
                    case 0:simpleGame(kpd.key[i].kchar); break;
                }
            //   simpleGame(kpd.key[i].kchar);
              Serial.printf("button %c at index %d is pressed, state is now ON\n", kpd.key[i].kchar, position);
            }
            break;
          case RELEASED:
            position = getKeyIndex(kpd.key[i].kchar); // Get the index of the released key
            if(position != -1 && state[position] == 1){
              state[position] = 0; // Set the state to 0
              setLED(position, 0, 0, 0); // Turn the LED off
              Serial.printf("button %c at index %d is released, state is now OFF\n", kpd.key[i].kchar, position);
            }
            break;
        }
      }
    }
  }
}


void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pixel.begin();
  pixel.clear();  pixel.show();
  randomSeed(analogRead(11));
    randomAlphabet = 'A' + random(16); // Set initial random alphabet

}
void loop() {

  keypadRoutine();


}
