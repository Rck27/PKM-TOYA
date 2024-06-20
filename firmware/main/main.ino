#define BOARDTYPE 1 // 1 for number, 2 for alphabet, 3 for shape puzzle


#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

//MOSI: 35
//MISO: 37
//SCK: 36
//SS: 34


#define CLK_PIN   36
#define DATA_PIN  35
#define CS_PIN    34

// MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
const byte NUM_LEDS = 16;
const byte LED_PIN = 33;
int position, winCount;
unsigned long lastMillis, currentMillis;
char randomAlphabet, pressedKey;
int mode, score;
char t[100];

Adafruit_NeoPixel pixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

char keys[ROWS][COLS] = {
  {'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L'},
  {'M', 'N', 'O', 'P'},
};


int state[ROWS*COLS] = {0}; // Initialize all to 0

///ESP32 S2
byte colPins[COLS] = {6, 4, 2, 1}; //connect to the column pinouts of the kpd
byte rowPins[ROWS] = {14, 13, 10, 8}; //connect to the row pinouts of the kpd
#define MODE_BUTTON_PIN 5
#define RESET_BUTTON_PIN 7
#define START_PAUSE_BUTTON_PIN 9

int currentGameMode = 0; // 0 = simpleGame, 1 = simonSaysGame
bool gamePaused = false;


//ESP32 S3
//#define MODE_BUTTON_PIN 1
//#define RESET_BUTTON_PIN 2
//#define START_PAUSE_BUTTON_PIN 42
//byte colPins[COLS] = {17, 16, 15, 7};
//byte rowPins[ROWS] = {46, 3, 8, 18};



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

void setLED(int index, int r, int g, int b) {
    if (index >= 0 && index < NUM_LEDS) {
        // Define the new mapping for the snake pattern
        int snakeIndices[] = {0, 1, 2, 3, 7, 6, 5, 4, 8, 9 , 10, 11, 15, 14, 13, 12};
        int mappedIndex = snakeIndices[index];
        pixel.setPixelColor(mappedIndex, pixel.Color(r, g, b));
        pixel.show();
    }
}

void simonSaysGame(char input) {
  static char sequence[5]; // Array to hold the sequence
  static int currentLevel = 1; // Current level (starts at 1)
  static int inputIndex = 0; // Track the current input position
  static bool showSequence = true; // Flag to control sequence display
  static bool gameStarted = false;
  static unsigned long lastTime = 0; // To manage non-blocking delays
  static int sequenceIndex = 0; // Index for showing the sequence

  if (!gameStarted) {
    // Initialize the game
    Serial.println("Simon Says: Watch the sequence and repeat it.");

    // Generate a unique random sequence
    for (int i = 0; i < 5; i++) {
      char newChar;
      bool isUnique;
      do {
        newChar = 'A' + random(16); // Generate a random character
        isUnique = true;

        // Check if the character is already in the sequence
        for (int j = 0; j < i; j++) {
          if (sequence[j] == newChar) {
            isUnique = false;
            break;
          }
        }
      } while (!isUnique);

      sequence[i] = newChar;
      Serial.printf("Generated character %c for position %d\n", newChar, i);
    }
    gameStarted = true;
    showSequence = true;
    sequenceIndex = 0;
    inputIndex = 0;
    lastTime = millis();
  }

  if (showSequence) {
    // Non-blocking display of the current level sequence
    if (millis() - lastTime > 750) { // Adjust the timing as needed
      int index = getKeyIndex(sequence[sequenceIndex]);
      if (index != -1) {
        setLED(index, 0, 0, 255); // Light up the LED in blue for the sequence
        delay(500); // Brief pause to simulate the sequence
        setLED(index, 0, 0, 0); // Turn off the LED
        delay(250); // Short pause between sequence items
      }
      sequenceIndex++;
      lastTime = millis(); // Reset the timer

      if (sequenceIndex >= currentLevel) {
        // Done showing the sequence for this level
        showSequence = false; // Move to player input phase
        sequenceIndex = 0; // Reset sequence index for the next level
        Serial.println("Your turn! Repeat the sequence.");
      }
    }
  } else {
    // Player is inputting the sequence
    if (input != NO_KEY) { // Only process if a valid key is pressed
      if (input == sequence[inputIndex]) {
        // Correct input
        Serial.printf("Correct! Pressed: %c\n", input);
        setLED(getKeyIndex(input), 0, 255, 0); // Green LED for correct input
        delay(200);
        setLED(getKeyIndex(input), 0, 0, 0);
        inputIndex++;
        if (inputIndex == currentLevel) {
          // Completed the current level
          currentLevel++;
          inputIndex = 0;
          showSequence = true; // Show the sequence for the next level
          if (currentLevel > 5) {
            Serial.println("Congratulations! You completed the Simon Says game!");
            for (int i = 0; i < NUM_LEDS; i++) {
              setLED(i, 255, 255, 0); // Celebrate with yellow LED flash
              delay(100);
            }
            // Reset the game
            currentLevel = 1;
            gameStarted = false;
          } else {
            Serial.println("Good job! Get ready for the next level.");
            delay(1000);
          }
        }
      } else {
        // Incorrect input
        Serial.printf("Incorrect! Expected: %c but got: %c\n", sequence[inputIndex], input);
        for (int i = 0; i < NUM_LEDS; i++) {
          setLED(i, 255, 0, 0); // Flash red LEDs for error
        }
        delay(1000);
        // Reset the game
        currentLevel = 1;
        gameStarted = false;
        for (int i = 0; i < NUM_LEDS; i++) setLED(i, 0, 0, 0);
      }
    }
  }
}



void simpleGame(char input) {
  static bool firstRound = true;
  static char targetChar;

  if (firstRound) {
    targetChar = 'A' + random(16);  // Generate a random target
    sprintf(t, "Masukkan huruf: %c", targetChar);
    Serial.println(t);
    
    setLED(getKeyIndex(targetChar), 255, 255, 255); // Highlight the target key in white
    firstRound = false;
  }

  if (input == targetChar) {
    // Correct guess
    for (int i = 0; i < NUM_LEDS; i++) {
      setLED(i, random(255), random(255), random(255)); // Random color flash
      delay(100);
    }
    score++; // Increment the score
    Serial.printf("BENAR! Score: %d\n", score);

    // Generate a new target
    targetChar = 'A' + random(16);
    sprintf(t, "Masukkan huruf: %c", targetChar);
    Serial.println(t);
    setLED(getKeyIndex(targetChar), 255, 255, 255); // Highlight the new target key in white
  } else {
    // Incorrect guess
    int inputIndex = getKeyIndex(input);
    if (inputIndex != -1) {
      setLED(inputIndex, 255, 0, 0); // Flash red on the incorrect key
      delay(100);
      setLED(inputIndex, 0, 0, 0); // Turn off the key after flash
    }
    Serial.printf("Salah! Target was: %c\n", targetChar);
  }

  // Clear all LEDs after feedback
  for (int i = 0; i < NUM_LEDS; i++) setLED(i, 0, 0, 0);

  // Highlight the target key again
  setLED(getKeyIndex(targetChar), 255, 255, 255);
}


void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pixel.begin();
  pixel.clear();  pixel.show();
  randomSeed(analogRead(11));
  randomAlphabet = 'A' + random(16); // Set initial random alphabet
  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);
  pinMode(START_PAUSE_BUTTON_PIN, INPUT_PULLUP);
  P.begin();
  P.setInvert(false);
  // P.setFont(myFont);
  P.setCharSpacing(1);
  P.setIntensity(1);
  P.print("TES");
  P.displayText("Hello", PA_CENTER, P.getSpeed(), 1000, PA_SCROLL_DOWN, PA_SCROLL_DOWN);

  
}




void resetGame() {
  // Reset game-specific variables
  if (currentGameMode == 0) {
    // Reset simpleGame
    // You can reset the score, targetChar, or other variables as needed
  } else if (currentGameMode == 1) {
    // Reset simonSaysGame
    // Reset sequence, current level, or other variables as needed
  }
  // Clear all LEDs
  for (int i = 0; i < NUM_LEDS; i++) setLED(i, 0, 0, 0);
}

void keypadRoutine() {
  if (kpd.getKeys()) {
    bool allPressed = true;

    // Check if all keys are pressed
    for (int i = 0; i < 16; i++) {
      if (kpd.key[i].kstate != PRESSED) {
        allPressed = false;
        break;
      }
    }

    // Determine if we should use PRESSED or RELEASED state based on allPressed
    bool usePressed = !allPressed;

    // Handle key state changes
    for (int i = 0; i < 16; i++) {
      if (kpd.key[i].stateChanged) {
        if ((usePressed && kpd.key[i].kstate == PRESSED) || (!usePressed && kpd.key[i].kstate == RELEASED)) {
          position = getKeyIndex(kpd.key[i].kchar); // Get the index of the key

          if (position != -1) {
            state[position] = !state[position]; // Toggle the state

            if (state[position]) {
              Serial.printf("Button %c at index %d is ON\n", kpd.key[i].kchar, position);

              // Call the appropriate game logic based on the current mode
              if (currentGameMode == 0) {
                simpleGame(kpd.key[i].kchar); // Call the simple game logic
              } else if (currentGameMode == 1) {
                simonSaysGame(kpd.key[i].kchar); // Call the Simon Says game logic
              }
              setLED(position, 255, 255, 0); // Turn on the LED

            } 
          }
        }else if((usePressed && kpd.key[i].kstate == RELEASED) || (!usePressed && kpd.key[i].kstate == PRESSED)){
              setLED(position, 0, 0, 0); // Turn off the LED
              state[position] = 0;
              Serial.printf("Button %c at index %d is OFF\n", kpd.key[i].kchar, position);
            }
      }
    }
  }
}


void checkControlButtons() {
  if (digitalRead(MODE_BUTTON_PIN) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(MODE_BUTTON_PIN) == LOW) {
      // Switch game mode
      currentGameMode = (currentGameMode + 1) % 2;
      Serial.printf("Switched to game mode: %d\n", currentGameMode);
      delay(500); // Avoid rapid toggling
    }
  }

  if (digitalRead(RESET_BUTTON_PIN) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(RESET_BUTTON_PIN) == LOW) {
      // Reset the current game
      Serial.println("Game reset.");
      resetGame();
      delay(500); // Avoid rapid toggling
    }
  }

  if (digitalRead(START_PAUSE_BUTTON_PIN) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(START_PAUSE_BUTTON_PIN) == LOW) {
      // Start or pause the game
      gamePaused = !gamePaused;
      if (gamePaused) {
        Serial.println("Game paused.");
      } else {
        Serial.println("Game resumed.");
      }
      delay(500); // Avoid rapid toggling
    }
  }
}
void loop() {
  checkControlButtons();
  if(!gamePaused) keypadRoutine();
}
