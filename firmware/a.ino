#define LOM 2 //lead off Plus pin
#define LOP 3 //lead offf Min Pin (high when lead is disconected)
///////////////////////////////////////////

#include <Arduino.h>
#if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <FirebaseClient.h>
#include <WiFiClientSecure.h>

#define WIFI_SSID "ini  wifii"
#define WIFI_PASSWORD "12345678"

#define DATABASE_URL "https://savergowes-default-rtdb.asia-southeast1.firebasedatabase.app/"
String name;
WiFiClientSecure ssl;
DefaultNetwork network;
AsyncClientClass client(ssl, getNetwork(network));

FirebaseApp app;
RealtimeDatabase Database;
AsyncResult result;
NoAuth noAuth;

void printError(int code, const String &msg)
{
    Firebase.printf("Error, msg: %s, code: %d\n", msg.c_str(), code);
}

//////////////////////////////////////////
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);
String wifiText = "ini_wifii 12345678";
////////////////////////////////////////////
unsigned long waktu, waktuS, waktuT;
int speedKmh, bpm, bpm2;
////////////////////////////////////////////


///////////////////////////////////////////


#define HALL_SENSOR_PIN 2  // Pin where the Hall effect sensor is connected

unsigned long pulseCount = 0;  // To store pulse count
unsigned long lastCalculationTime = 0;  // To track the last RPM calculation time
unsigned long lastPulseTime = 0;  // To track the last pulse time
bool lastSensorState = LOW;  // To track the last sensor state

const float tireDiameter = 0.7;  // Tire diameter in meters
const float tireCircumference = tireDiameter * PI;  // Calculate tire circumference
const unsigned long intervalMs = 1000;  // Interval for RPM calculation in milliseconds

float readRPM() {
    unsigned long currentTime = millis();
    if (currentTime - lastCalculationTime >= intervalMs) {
        unsigned long pulses = pulseCount;  // Copy the pulse count
        pulseCount = 0;  // Reset pulse count

        lastCalculationTime = currentTime;  // Update last calculation time
        return (pulses * 60000.0) / intervalMs;  // Calculate RPM
    }
    return 0;  // Return 0 RPM if interval hasn't passed
}

float calculateSpeed(float rpm) {
    return (rpm * tireCircumference * 3.6) / 60.0;  // Convert RPM to KM/H
}



////////////////////////////////////////////
void initwifi() {
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  lcd.setCursor(0,0);
  int index = 0;
  while (WiFi.status() != WL_CONNECTED) {
    if(index <= 19) lcd.print(wifiText[index]+wifiText[index+1]);
    index += 2;
    delay(500);
  }
    WiFi.setSleep(false);
  Serial.print(WiFi.localIP());
}

void setup() {
  Wire.begin(0, 1);
  Wire.beginTransmission(0x27);
  Serial.begin(115200);
  pinMode(HALL_SENSOR_PIN, INPUT_PULLUP);
  analogReadResolution(10);
  lcd.begin(16,2);
  lcd.setBacklight(255);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Saver Gowesser");
  delay(1000);
  initwifi();
  Firebase.printf("Firebase Client v%s\n", FIREBASE_CLIENT_VERSION);
  ssl.setInsecure();
  initializeApp(client, app, getAuth(noAuth));
  // Binding the authentication handler with your Database class object.
  app.getApp<RealtimeDatabase>(Database);
  // Set your database URL
  Database.url(DATABASE_URL);
  // In sync functions, we have to set the operating result for the client that works with the function.
  client.setAsyncResult(result);
  screenRoutine();

}


void screenRoutine() {
    lcd.clear();
    char s[16];
    sprinf(s, "%d KMH->%d BPM->%d BPM",speedKmh, bpm, bpm2 );
    lcd.print(s);
}

void loop() {
  unsigned long waktu = millis();

  bool currentSensorState = digitalRead(HALL_SENSOR_PIN);
  if (currentSensorState == HIGH && lastSensorState == LOW) {
    pulseCount++;  // Increment pulse count
    lastPulseTime = currentTime;  // Update the last pulse time
  }
  lastSensorState = currentSensorState;

  // Calculate RPM and speed if the interval has passed
  float rpm = readRPM();
  if (rpm > 0) {
      float speedKmh = calculateSpeed(rpm);
  }

  if(waktu  - waktuS >= 2000UL){
    Database.set<int>(client, "/Speed", speedKmh);
    Database.set<int>(client, "/Speed", bpm);
    WaktuS = waktu;
  }
  if(waktu - waktuT >= 100UL){
    if(!(digitalRead(LOM) && digitalRead(LOP))) bpm = analogRead(PINMonitor);
    waktuT = waktu;
  }
    screenRoutine();

} 
