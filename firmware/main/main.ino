#define BOARDTYPE 2 // 1 for number, 2 for alphabet, 3 for shape puzzle
bool REV = 1; // rev 0 for  the non inverted led matrix, rev 1 for the  inverted one , will  alter the led setup below
//pin 10 is used to alter the value, HIGH for 1
bool debug = true;//////////////DEBUG FOR DISABLE THE GAME, ONLY  CHECKING THE BASIC FUNCTION OF THE BOARD
//pin  12 is used to alter the value on boot, HIGH for true



#if BOARDTYPE != 2
//if the board type is not huruf, that means the cols and rows would be the same, that means these settings didnt change(like the last version)
//there's an additional Word variable that store the String that should be printed on the lcd, other than board 2, the value is different (nuber and shape)\
//thus we made it different, and make the lcd print the correct character accordingly
//but we still need the keys variable to check the generated word and the inputted word, int this case we made 1 and 3 the same, doesnt care about the symbol on the angka mode
// and also the indonesianWords variable need to be different, and need to be placed in this line to save space
byte colPins[COLS] = {6, 2, 1, 9}; //connect to the column pinouts of the kpd
int snakeIndices[] = {0, 1, 2, 3, 7, 6, 5, 4, 8, 9 , 10, 11, 15, 14, 13, 12};
const byte COLS = 4; //four columnsv
const char* indonesianWords[] = {"ABDI","ABEN","ABID","ABOI","ABON","ACIK","ADEH","ADEM","ADIB","ADIK","ADIL","ADON","AFEK","AGEN","AGIH","AGIL","AGIO","AGON","AHLI","AJEK","AKEO","AKIL","AKLI","ALEM","ALIF","ALIH","ALIK","ALIM","ALIN","ALIP","ALOI","ALON","AMBI","AMEN","AMIL","AMIN","AMKO","AMOI","AMPE","AMPO","ANEH","ANIL","ANOM","APEK","APEL","APIK","APOK","BACO","BADE","BADI","BAGI","BAID","BAIK","BAIN","BAJI","BAKH","BAKI","BAKO","BANG","BANI","BANK","BEDA","BEDO","BEGA","BEGO","BEHA","BEKA","BELA","BELI","BELO","BEMO","BENA","BENI","BEOL","BIAH","BIAK","BIDA","BIDO","BIJA","BILA","BINA","BLEK","BLOG","BLOK","BODI","BOGA","BOGI","BOLA","BONG","CABE","CABO","CAEM","CAHI","CAKI","CAKO","CALO","CANG","CAPE","CEKI","CELA","CELI","CEMA","CENA","CENG","CEPO","CIAK","CIAP","CIKA","CINA","CING","COAK","COBA","COLI","DAGE","DAGI","DAHI","DAIF","DAIM","DAKI","DAME","DAMI","DANG","DEMI","DEMO","DENA","DEPA","DEPO","DIAM","DIAN","DILA","DINA","DOBI","DONG","DONI","EBAM","EBAN","EDAN","EGAH","EGOL","EJAN","EKAD","EKON","ELAK","ELAN","ELOK","ELON","EMOH","EMOL","EMPO","ENAK","ENAM","ENAP","ENOM","EPAK","EPIK","EPOK","FAIL","FANI","FEKO","FILM","FILO","FLOP","FOLI","GACO","GADO","GAEK","GAIB","GAIL","GAIN","GAJI","GALI","GANI","GAOK","GEDI","GELA","GELI","GELO","GEMA","GEMI","GENA","GIAL","GIAM","GILA","GOAK","GOBA","GODA","GOEL","GOLF","GONI","HAID","HAIK","HAIL","HAJI","HALO","HANG","HELA","HELM","HENG","HIFA","HINA","HOBI","HOKI","HOLI","IBAN","IDAH","IDAM","IDAP","IDEM","IDEP","IFAH","IGAL","IGLO","IJAB","IJON","IKAB","IKAL","IKAN","IKON","ILAH","ILAK","IMAK","IMAN","IMLA","INAP","INCA","INFO","INGA","IPON","JADI","JAGO","JAHE","JAIL","JALI","JANI","JEDA","JELA","JELI","JENG","JEPA","JIKA","JILA","JOKI","JOLI","KACI","KACO","KADE","KADI","KADO","KAFE","KAFI","KAIL","KAIN","KAJI","KALI","KALO","KAMI","KAMP","KANE","KANG","KANO","KAON","KAPI","KEBO","KECI","KEDI","KEJI","KELI","KELP","KEMI","KENA","KENG","KIAH","KIAL","KIAM","KIAN","KIAP","KILA","KILN","KILO","KIMA","KIMO","KINA","KIPA","KLAN","KLEM","KLEN","KLEP","KLIN","KLIP","KLON","KLOP","KNOP","KOCI","KODA","KODE","KODI","KOIL","KOIN","KOJA","KOLA","KOLI","KOMA","KOPI","LACI","LADI","LAGI","LAGO","LAIF","LAIK","LAIN","LAKI","LANG","LAPO","LEAK","LECI","LECO","LEFA","LEGA","LEGI","LEGO","LEJA","LEKA","LEMA","LEMO","LENA","LENG","LEPA","LIAN","LIFO","LIGA","LIMA","LING","LOAK","LOBA","LOBI","LOHA","LOJI","LOKA","LOKI","LONG","MACE","MADI","MADO","MAGI","MAIN","MAKI","MALE","MANG","MANI","MBAH","MBAK","MBOK","MEGA","MEJA","MEKO","MENA","MENI","MIAK","MIAP","MIKA","MINA","MIOP","MODE","MOGA","MOKA","MOKE","MOLA","MOLE","MONG","NABI","NADI","NAFI","NAHI","NAIB","NAIF","NAIK","NAIM","NALI","NEKA","NEKO","NICA","NILA","NODA","NOEM","NOJA","OCEH","OGAH","OGAM","OGEL","OJEG","OJEK","OLAH","OLAK","OLEH","OLEK","OLIA","OMEL","ONAK","ONCE","OPAK","OPAL","OPEN","PACE","PADI","PAGI","PAIL","PALE","PALI","PECI","PEDA","PEGO","PEKA","PELO","PENA","PENI","PEOK","PIAH","PIAK","PIAL","PICA","PICO","PIKA","PIKE","PION","PLAN","PLOI","POAL","POCI","POIN","POLA","POMA","PONI"
  };
char keys[ROWS][COLS] = {
  {'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L'},
  {'M', 'N', 'O', 'P'}
};
#endif


#if BOARDTYPE == 1
#include "numFont.h"
String word[ROWS][COLS]= {
  {'0', '1', '2', '3'},
  {'4', '5', '6', '7'},
  {'8', '9', 'x', '-'},
  {'\0', '/', '+', '\0'}
}

#elif BOARDTYPE == 2
#include "charFont.h"
int snakeIndices[] = {0, 1, 2, 3, 7, 6, 5, 4, 8, 9 ,10, 11, 12, 16, 15, 14, 13, 17, 18, 19, 20, 24, 23, 22, 21, 25, 26};
byte colPins[COLS] = {6, 2, 1, 9, 38 ,39, 40}; //connect to the column pinouts of the kpd
const byte COLS = 7; //four columnsv
const char* indonesianWords[] = {

};// dont forget to add the different word for the different board type

char keys[ROWS][COLS] = {
  {'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L'},
  {'M', 'N', 'O', 'P'},
  {'Q', 'R', 'S', 'T'},
  {'U', 'V', 'W', 'X'},
  {'\0', 'Y', 'Z', '\0'}
};

#elif BOARDTYPE == 3
#include "shapeFont.h"
String word[ROWS][COLS] = {
  {"PERSEGI", "PERSEGI PANJANG", "LINGKARAN", "TRAPESIUM"},
  {"SEGITIGA", "SEGI ENAM", "SEGITIGA SAMA KAKI", "SEGI LIMA"},
  {"JAJAR GENJANG", "LAYANG LAYANG", "1/2 LINGKARAN", "3/4 LINGKARAN"},
  {"SEGI BANYAK", "BINTANG", "SEGITIGA SEMBARANG", "SEGI DELAPAN"}
};
#endif


#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
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
//MOSI: 35
//MISO: 37
//SCK: 36
//SS: 34




byte rowPins[ROWS] = {11, 7, 5, 3}; //connect to the row pinouts of the kpd
const byte ROWS = 4; //four rows
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


const byte NUM_LEDS = 16;
const byte LED_PIN = 4;
int position, winCount;
unsigned long lastMillis, currentMillis;
char randomAlphabet, pressedKey;
int mode, score;
char t[100];
int index;

Adafruit_NeoPixel pixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

/////////////////////variables for the game
  static char sequence[6]; // Array to hold the sequence
  static int currentLevel = 1; // Current level (starts at 1)
  static int inputIndex = 0; // Track the current input position
  static bool gameStarted = false;
  static unsigned long lastTime = 0; // To manage non-blocking delays
  static int sequenceIndex = 0; // Index for showing the sequence
  static int wrongCount = 0;
  int state[ROWS*COLS] = {0}; // Initialize all to 0
  

/////


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
          setLED(i, 0, 0 , 0);{
            delay(100);
          }
        }
}

char getCharToDisplay(int index) {
    int row = index / COLS;
    int col = index % COLS;

    if (BOARDTYPE == 2) {
        // For BOARDTYPE 2, use the keys array
        return keys[row][col];
    } else if (BOARDTYPE == 1 || BOARDTYPE == 3) {
        // For BOARDTYPE 1 or 3, use the word array
        return word[row][col][0]; // Assuming word stores strings and we want the first character
    }

    return ' '; // Default return value in case of an unexpected BOARDTYPE
}

void upScreenLED(char input, char target, bool isCorrect){
  String text = isCorrect ? "Correct," : "Wrong,";
  char sign = isCorrect ? '^' : '*';
  Serial.printf("%s your input is %c\n",text, input);

  
  sprintf(t, "%c %c", inputToDisplay(getKeyIndex(input)), sign);
  #if BOARDTYPE == 2
  P.setTextEffect(PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  #elif BOARDTYPE != 2
  P.setTextEffect(NO_EFFECT, NO_EFFECT);
  #endif

  P.print(t);
  if(isCorrect){setLED(getKeyIndex(input), 0, 45, 0);
  }
  else {
    setLED(getKeyIndex(input), 45, 0, 0);
    setLED(getKeyIndex(target), 0, 45, 0);
    }
  delay(SHORTDELAY);
  flashLED( 0, 0, 0);
}
void simonSaysGame(char input) {
  static bool changed = true;
  if (!gameStarted) {
    // Initialize the game
    Serial.println("Simon Says: Watch the sequence and repeat it.");
    P.displayText("Amati,Tirukan", PA_CENTER, 25, 2000, PA_SCROLL_LEFT, PA_SCROLL_LEFT)
    delay(SHORTDELAY);
    P.print("");

    flashLED(0,0,0); //turn all led off to make sure clean start
    // Generate a unique random sequence of characters from Indonesian words
    int randomIndex = random(0, MAX_WORDS);
    for (int i = 0; i <  WORD_LENGTH ; i++) {
      sequence[i] = indonesianWords[randomIndex][i];
      Serial.printf("Generated character %c for position %d\n", sequence[i], i);
      // Immediately display the sequence character on the LED
      int ledIndex = getKeyIndex(sequence[i]);
      P.print(String(sequence));
      if (ledIndex != -1) {
        setLED(ledIndex, 0, 0, 45); // Blue LED
        delay(SHORTDELAY); // Display each character for half a second
        setLED(ledIndex, 0, 0, 0); // Turn off the LED
        delay(SHORTDELAY); // Short pause between characters
      }
    }
    flashLED(0, 45, 0); // Flash green to indicate the game has started
    gameStarted = true;
    inputIndex = 0;
    lastTime = millis();
    P.print("");
  }

  if (input != NO_KEY) { // Only process if a valid key is pressed
    setLED(getKeyIndex(sequence[inputIndex]), 0, 0, 0);
    changed = true;
/////////////////////////////////////////////////////////////////////////////////////////////////////
    if (input == sequence[inputIndex]) {
      // Correct input
      upScreenLED(input,sequence[inputIndex], true);
      inputIndex++;
      setLED(getKeyIndex(sequence[inputIndex]), 55, 16, 90);

      if (inputIndex >= 4) {
        // Completed the current level
        currentLevel++;
        inputIndex = 0;
        Serial.println("Congratulations! You completed the Simon Says game!");
        P.print(":D");
        for (int i = 0; i < NUM_LEDS; i++) {
          setLED(i, random(0, 45), random(0, 45), random(0,45)); // Celebrate with yellow LED flash
          delay(200);
          // Reset the game
        }
        gameStarted = false;
        simonSaysGame(NO_KEY); // Call again to show the sequence for the next level

      }
    } else {
      // Incorrect input
      upScreenLED(input,sequence[inputIndex], false);
      wrongCount+=1;
      if(wrongCount >= 3){  
        // Reset the game
        currentLevel = 1;
        gameStarted = false;
        for (int i = 0; i < NUM_LEDS; i++) setLED(i, 45, 0, 0);
          simonSaysGame(NO_KEY); // Call again to show the sequence for the next level

        }
      setLED(getKeyIndex(sequence[inputIndex]), 55, 16, 90);

    }
    P.print("");
  }
  else{
    setLED(getKeyIndex(sequence[inputIndex]), 55, 16, 90);
  
}}

// void startCheck(){
//   Serial.println("Test check");
//   P.print("Test Started");
//   for(int i =  0; i < 16; i ++){
//     setLED(i, 0, 0, 45);
//     delay
//   }
// }

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(REV_PIN, INPUT);
  pinMode(DEBUG_PIN, INPUT);
  pixel.begin();
  pixel.clear();  pixel.show();
  debug = digitalRead(DEBUG_PIN) ? 1 : 0;
  REV = digitalRead(REV_PIN) ? 1 : 0;

  randomSeed(analogRead(11));
  randomAlphabet = 'A' + random(16); // Set initial random alphabet
  P.begin();
  P.setInvert(false);
  // P.setFont(myFont);

  if(REV)
  for(int i = 0; i <MAX_DEVICES; i++){
    P.setZoneEffect(i, true, PA_FLIP_UD);
    P.setZoneEffect(i, true, PA_FLIP_LR);
    }


  P.setTextAlignment(PA_CENTER);
  P.setCharSpacing(1);
  P.setIntensity(1);
  P.print("TES");
  // P.displayText("Hello", PA_RIGHT, P.getSpeed(), 1000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  delay(LONGDELAY);
  P.print("");
  simonSaysGame(NO_KEY);
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
    for (int i = 0; i < MAX_KEY; i++) {
      if (kpd.key[i].stateChanged) {
        if ((usePressed && kpd.key[i].kstate == PRESSED) || (!usePressed && kpd.key[i].kstate == RELEASED)) {
          position = getKeyIndex(kpd.key[i].kchar); // Get the index of the key

          if (position != -1) {
            state[position] = !state[position]; // Toggle the state

            if (state[position]) {
              P.print(kpd.key[i].kchar);
              Serial.printf("Button %c at index %d is ON\n", kpd.key[i].kchar, position);
              // simonSaysGame(kpd.key[i].kchar); // Call the Simon Says game logic
              if(debug) setLED(getKeyIndex(kpd.key[i].kchar), 45, 0, 0);
              if(!debug)simonSaysGame(kpd.key[i].kchar); // Call the Simon Says game logic
            } 
          }
        }else if((usePressed && kpd.key[i].kstate == RELEASED) || (!usePressed && kpd.key[i].kstate == PRESSED)){
              setLED(position, 0, 0, 0); // Turn off the LED
              state[position] = 0;
              P.print("");
              Serial.printf("Button %c at index %d is OFF\n", kpd.key[i].kchar, position);
            }
      }
    }
  }
}


void loop() {
  keypadRoutine();
}
