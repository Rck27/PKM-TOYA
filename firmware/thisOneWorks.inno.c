/* @file MultiKey.ino
|| @version 1.0
|| @author Mark Stanley
|| @contact mstanley@technologist.com
||
|| @description
|| | The latest version, 3.0, of the keypad library supports up to 10
|| | active keys all being pressed at the same time. This sketch is an
|| | example of how you can get multiple key presses from a keypad or
|| | keyboard.
|| #
*/

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'0', '1', '2', '3'},
  {'4', '5', '6', '7'},
  {'8', '9', 'x', '-'},
  {'n', '/', '+', 'n'},
};


byte colPins[4] = {6, 2, 1, 9}; //connect to the column pinouts of the kpd
byte rowPins[4] = {11, 7, 5, 3}; //connect to the row pi

//byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the kpd
//byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the kpd

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTime;
String msg;


void setup() {
    Serial.begin(115200);
    loopCount = 0;
    startTime = millis();
    msg = "";
}

void executeTask(){
  Serial.println("game is executed");
}

char lastTriggered;
void loop() {
//    loopCount++;
//    if ( (millis()-startTime)>5000 ) {
//        Serial.print("Average loops per second = ");
//        Serial.println(loopCount/5);
//        startTime = millis();
//        loopCount = 0;
//    }

    // Fills kpd.key[] array with up to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys()) {
        bool allKeysPressed = true;
        bool taskExecuted = false;
        int counter = 0;
        for(int i = 0; i<LIST_MAX; i++){
          if (kpd.key[i].kstate == HOLD) {
                counter+=1;
                Serial.print(kpd.key[i].kchar);
            }
//           else allKeysPressed = true;
        }
        Serial.println("");
        allKeysPressed = counter >= (4*4)/2 -1  ? true : false;

        for (int i = 0; i < LIST_MAX; i++) {// Scan the whole key list.
          taskExecuted = false;
            if (kpd.key[i].stateChanged) { // Only find keys that have changed state.
              if(kpd.key[i].kstate == HOLD){
                 msg = " HOLD.";
                        if (!taskExecuted && !allKeysPressed) {
                          if( kpd.key[i].kchar != lastTriggered) {
           
                            // Serial.println(msg);
                            // executeTask();
                            Serial.printf(" %c is trig pressed \n", kpd.key[i].kchar);
                            taskExecuted = true;
                            lastTriggered = kpd.key[i].kchar;}
                            else Serial.printf(" %c is trig pressed before \n", kpd.key[i].kchar);

                        }
              }
              if(kpd.key[i].kstate == RELEASED){
                msg = " RELEASED.";
                        if (!taskExecuted && allKeysPressed){
                          if( kpd.key[i].kchar != lastTriggered) {
           
                            // Serial.println(msg);
                            // executeTask();
                            Serial.printf(" %c is trig released \n", kpd.key[i].kchar);
                            taskExecuted = true;
                            lastTriggered = kpd.key[i].kchar;}
                            else Serial.printf(" %c is trig released before \n", kpd.key[i].kchar);

                        }
              }
                Serial.print("Key ");
                Serial.print(kpd.key[i].kchar);
                Serial.print(allKeysPressed ? " ALL ": " NOT ALL ");
                Serial.print(counter);
                Serial.println(msg);
            }

            // Check if any key is not pressed
            
        }

        // Reset taskExecuted flag if no task was executed
        if (!taskExecuted) {
        }
    }
}  // End 