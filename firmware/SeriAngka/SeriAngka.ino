#include <Arduino.h>
#define useLCD 0
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'0', '1', '2', '3'},
  {'4', '5', '6', '7'},
  {'8', '9', '*', '-'},
  {'n', '/', '+', 'n'},
};

int snakeIndices[] = {0, 1, 2, 3, 7, 6, 5, 4, 8, 9 ,10, 11,15, 14,  13, 12, 16, 17, 18, 19, 23, 22, 21, 20, 24, 25};
char t[100];
#include <Adafruit_NeoPixel.h>

#if useLCD

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

#endif

#define MAX_DEVICES 4
#define DEBUG_PIN 12
#define REV_PIN 10
#define SHORTDELAY 500
#define LONGDELAY 1000
#define MAX_WORDS  100
#define WORD_LENGTH 4
#define CLK_PIN   36
#define DATA_PIN  35
#define CS_PIN    34
#define MAX_KEY COLS * ROWS
#define NUM_LEDS COLS * ROWS
//MOSI: 35
//MISO: 37
//SCK: 36
//SS: 34

#define LED_PIN 15

char lastTriggered;

byte colPins[COLS] = {19, 21, 22, 23}; //connect to the column pinouts of the kpd
byte rowPins[ROWS] = {2, 4, 5,  18};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Adafruit_NeoPixel pixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long loopCount;
unsigned long startTime;

bool gameStarted = false;
char sequence[6]; //to hold X+Y=Z
bool getRandom;
int counter, indexCounter;
String msg;
int result;

int getKeyIndex(char key){// Function to get led index of the key in the keys array
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
        int mappedIndex = snakeIndices[index];
        pixel.setPixelColor(mappedIndex, pixel.Color(r, g, b));
        pixel.show();
    }
}

void flashLED(int r, int g, int b){
    for (int i = 0; i < NUM_LEDS; i++) {
        setLED(i, r, g, b);
        delay(100);
    }
    delay(SHORTDELAY);
    for(int i = NUM_LEDS; i >=0; i--){
        setLED(i, 0, 0 , 0);
        delay(100);
    }
}

void upScreenLED(char input, char target, bool isCorrect){
    String text = isCorrect ? "Correct," : "Wrong,";
    char sign = isCorrect ? '^' : '*';
    Serial.printf("%s your input is %c\n",text.c_str(), input);
    sprintf(t, "%s %c", text.c_str(), sign);

    #if useLCD
        P.print("");
        P.displayText(t, PA_LEFT, 80, 1000, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
        while (!P.displayAnimate()) { /* do animation empty loop */ };
    #endif

    if(isCorrect){
        setLED(getKeyIndex(input), 0, 45, 0);
    }
    else {
        setLED(getKeyIndex(input), 45, 0, 0);
        setLED(getKeyIndex(target), 0, 45, 0);
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("TESTANG");
    loopCount = 0;
    pinMode(LED_PIN, OUTPUT);
    pixel.begin();
    pixel.clear();
    pixel.show();
    startTime = millis();
    msg = "";
    randomSeed(analogRead(11));

    #if useLCD
        P.begin();
        P.setInvert(false);
        P.setIntensity(1);
        P.displayText("FUNTOYA", PA_LEFT, 100, 1000, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
        while (!P.displayAnimate()) { /* do animation empty loop */ };
        P.print("");
    #endif
    mathGame(NO_KEY);
}

void mathGame(char input) {
    if (!gameStarted) { // New game started
        indexCounter = 0;
        do {
            sequence[0] = random(0, 10);
            do {
                sequence[2] = random(0, 9);
            } while (sequence[0] == sequence[2]);
            sequence[1] = random(0, 4); // Generate random operator, + - * /
            switch (sequence[1]) {
                case 0: result = sequence[0] + sequence[2];
                    sequence[1] = '+';
                    break;
                case 1: result = sequence[0] - sequence[2];
                    sequence[1] = '-';
                    break;
                case 2: result = sequence[0] * sequence[2];
                    sequence[1] = '*';
                    break;
                case 3: result = sequence[0] / sequence[2];
                    sequence[1] = '/';
                    break;
            }
            getRandom = result >= 10 || result < 0;
        } while (getRandom);

        Serial.printf("Generated number %d %c %d = %d\n", sequence[0], sequence[1], sequence[2], result);
        counter = 0;
        gameStarted = true;
        indexCounter = 0;
        sprintf(t, "%d %c %d = %d", sequence[0], sequence[1], sequence[2], result);
        Serial.println(t);

#if useLCD
        P.displayText(t, PA_LEFT, 80, 1000, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
        while (!P.displayAnimate()) { /* do animation empty loop */ };
#endif
        // Turn target LED white
        int targetIndex = (indexCounter == 1) ? sequence[1] : sequence[indexCounter] + '0';
        setLED(getKeyIndex(targetIndex), 255, 255, 255);
    }

    if (input != NO_KEY) {
        // Turn LED blue for button pressed
        setLED(getKeyIndex(input), 0, 0, 255);

        Serial.printf("index %d target is %d %c %d input is %c \n", indexCounter, sequence[0], sequence[1], sequence[2], input);
        if ((indexCounter == 1 && input == sequence[1]) || (input == '0' + sequence[indexCounter])) { // Handle operator and number input
            Serial.printf("input %c is correct \n", input);
            upScreenLED(input, input, true);
            setLED(getKeyIndex(input), 0, 255, 0); // Turn LED green for correct input
            delay(500);
            indexCounter += 1;
        } else {
            upScreenLED(input, indexCounter == 1 ? sequence[1] : sequence[indexCounter] + '0', false); // Handle operator and number input
            Serial.printf("input %c is wrong \n", input);
            setLED(getKeyIndex(input), 255, 0, 0); // Turn LED red for wrong input
            delay(500);
        }

        // Turn off target LED
        setLED(getKeyIndex(input), 0, 0, 0);

        if (indexCounter >= 3) {
            Serial.println("Congratulations");
            for(int i = 0; i <16 ;i++){
              setLED(i, random(0,255), random(0, 255), random(0, 255));
              delay(250);
            }
            for(int i = 16; i >= 0; i--){
              delay(250);
              setLED(i, 0, 0, 0);
            }
            gameStarted = false;
            delay(2000); // Add a delay before starting the new game
            mathGame(NO_KEY);
        } else {
            // Turn next target LED white
            int nextTargetIndex = (indexCounter == 1) ? sequence[1] : sequence[indexCounter] + '0';
            setLED(getKeyIndex(nextTargetIndex), 255, 255, 255);
        }
    }
}

void loop() {
    loopCount++;
    if ((millis() - startTime) > 5000) {
        Serial.print("Average loops per second = ");
        Serial.println(loopCount / 5);
        startTime = millis();
        loopCount = 0;
    }

    if (kpd.getKeys()) {
        bool allKeysPressed = true;
        bool taskExecuted = false;
        int counter = 0;
        for (int i = 0; i < LIST_MAX; i++) {
            if (kpd.key[i].kstate == PRESSED) {
                counter += 1;
                Serial.print(kpd.key[i].kchar);
                setLED(getKeyIndex(kpd.key[i].kchar), 0, 0, 255); // Turn LED blue for button pressed
            }
        }
        Serial.println("");
        allKeysPressed = counter >= (4 * 4) / 2 - 1 ? true : false;

        for (int i = 0; i < LIST_MAX; i++) { // Scan the whole key list
            taskExecuted = false;
            if (kpd.key[i].stateChanged) { // Only find keys that have changed state
                if (kpd.key[i].kstate == PRESSED) {
                    msg = " HOLD.";
                    if (!taskExecuted && !allKeysPressed) {
                        if (kpd.key[i].kchar != lastTriggered) {
                            Serial.printf(" %c is trig pressed \n", kpd.key[i].kchar);
                            mathGame(kpd.key[i].kchar);
                            taskExecuted = true;
                            lastTriggered = kpd.key[i].kchar;
                        } else {
                            Serial.printf(" %c is trig pressed before \n", kpd.key[i].kchar);
                        }
                    }
                }
                if (kpd.key[i].kstate == RELEASED) {
                    msg = " RELEASED.";
                    if (!taskExecuted && allKeysPressed) {
                        if (kpd.key[i].kchar != lastTriggered) {
                            Serial.printf(" %c is trig released \n", kpd.key[i].kchar);
                            mathGame(kpd.key[i].kchar);
                            taskExecuted = true;
                            lastTriggered = kpd.key[i].kchar;
                        } else {
                            Serial.printf(" %c is trig released before \n", kpd.key[i].kchar);
                        }
                    }
                }
                Serial.print("Key ");
                Serial.print(kpd.key[i].kchar);
                Serial.print(allKeysPressed ? " ALL " : " NOT ALL ");
                Serial.print(counter);
                Serial.println(msg);
            }
        }
    }
}