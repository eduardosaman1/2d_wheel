#include <FastLED.h>  // LEDs Strip Library
#include <ezButton.h> // Button Library

#define BUTTON_PIN 2  // LEDs Button INPUT PINS 
#define LED_PIN_1 4   // LEDs 1 INPUT PINS 
#define LED_PIN_2 5   // LEDs 2 INPUT PINS 
#define LED_PIN_3 6   // LEDs 3 INPUT PINS 
#define LED_PIN_4 7   // LEDs 4 INPUT PINS 
#define LED_PIN_5 8   // LEDs 5 INPUT PINS 
#define LED_PIN_6 9   // LEDs 6 INPUT PINS 
#define LED_PIN_7 10  // LEDs 7 INPUT PINS 
#define switchPin 3   // Switch PIN //////////////////////////////////////////////////

#define NUM_STRIPS 7          // Number of STRIPS
#define NUM_LEDS_PER_STRIP 21 // Number of LEDs per STRIP


int NUM = 0;
int DELAY_1 = 200; // Delay time delay (200 ms)
int DELAY_2 = 500; // Delay time delay (500 ms)
int DELAY_3 = 2500; // Delay time delay (2500 ms)
const int waitTime = 2000; // Delay time delay (2000 ms)

int NUM_TRIALS = 7; // Define number of iterations per event
bool INIT_EVENT = false;
 
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP]; // Array to control color of LEDs in strip
ezButton button(BUTTON_PIN); // Create a button instance on pin 2


void setup() {

  Serial.begin(9600); // Prepare serial interface
  button.setDebounceTime(50); // set debounce time to 50 milliseconds

  FastLED.addLeds<WS2813, LED_PIN_1>(leds[0], NUM_LEDS_PER_STRIP); // tell FastLED there's 30 NEOPIXEL leds on pin 4
  FastLED.addLeds<WS2813, LED_PIN_2>(leds[1], NUM_LEDS_PER_STRIP); // tell FastLED there's 30 NEOPIXEL leds on pin 5
  FastLED.addLeds<WS2813, LED_PIN_3>(leds[2], NUM_LEDS_PER_STRIP); // tell FastLED there's 30 NEOPIXEL leds on pin 6
  FastLED.addLeds<WS2813, LED_PIN_4>(leds[3], NUM_LEDS_PER_STRIP); // tell FastLED there's 30 NEOPIXEL leds on pin 7
  FastLED.addLeds<WS2813, LED_PIN_5>(leds[4], NUM_LEDS_PER_STRIP); // tell FastLED there's 30 NEOPIXEL leds on pin 8
  FastLED.addLeds<WS2813, LED_PIN_6>(leds[5], NUM_LEDS_PER_STRIP); // tell FastLED there's 30 NEOPIXEL leds on pin 9
  FastLED.addLeds<WS2813, LED_PIN_7>(leds[6], NUM_LEDS_PER_STRIP); // tell FastLED there's 30 NEOPIXEL leds on pin 10

  FastLED.clear();
  FastLED.show();
  pinMode(switchPin, INPUT_PULLUP); // pin del interruptor como entrada pull-up  

}

void loop() {
  button.loop(); // MUST call the loop() function first
  int b = checkButton(); // Get button event and act accordingly
  
  
  if (b == 0) {
    Initialization();
    delay(2000);
    FastLED.show();
  }

  else if (b == 1) { // Call for Speed 1 (NORMAL) Parameters for LEDs illumination
    FastLED.clear();
    Serial.print("Modo ");
    Serial.println(b);
      DELAY_1 = 200;
      DELAY_2 = 500;
      DELAY_3 = 2500;
      Event_Indicator(b);
      for (int n = 0; n < NUM_TRIALS; n = n + 1) {
        if (digitalRead(switchPin) == HIGH) {
            NUM = random(1, 7);
            Serial.println(NUM);
          }
        else {NUM = n;
          Serial.println(NUM);
        } 
        Serial.print("LED ");
        Serial.println(NUM);
        Event_StripFlash();
      }
    Initialization();
    delay(2000);
    FastLED.show();
  }
  else if (b == 2) { // Call for Speed 2 (FASTER) Parameters for LEDs illumination
    FastLED.clear();
    Serial.print("Modo ");
    Serial.println(b);
      DELAY_1=120;
      DELAY_2=300;
      DELAY_3=1700;
      Event_Indicator(b);

      for (int n = 0; n < NUM_TRIALS; n = n + 1) {
        if (digitalRead(switchPin) == HIGH) {
            NUM = random(1, 7);
            Serial.println(NUM);
          }
        else {NUM = n;
        Serial.println(NUM);
        }
        Serial.print("LED ");
        Serial.println(NUM);      
        Event_StripFlash();
      }
    Initialization();
    delay(2000);
    FastLED.show();
  }

  else if (b == 3) { // Call of all the LEDs to be turned OFF including board
    Serial.print(b);
    TurnOff();
    asm volatile("jmp 0");
  }
}

void Initialization() { // Turn ON Event: Turns ON <GREEN> the LEDs sequentially
  for (int x = 2; x < NUM_LEDS_PER_STRIP; x = x + 1) { 
    leds[0][x] =  CRGB(100,0,0);
    FastLED.show(); 
    leds[1][x] =  CRGB(100,0,0);
    FastLED.show(); 
    leds[2][x] =  CRGB(100,0,0);
    FastLED.show(); 
    leds[3][x] =  CRGB(100,0,0);
    FastLED.show(); 
    leds[4][x] =  CRGB(100,0,0);
    FastLED.show(); 
    leds[5][x] =  CRGB(100,0,0);
    FastLED.show();
    leds[6][x] =  CRGB(100,0,0);
    FastLED.show(); 
  }
}

void Event_StripFlash() { // Strip Flashing Event: Turns ON <GREEN> and OFF <BLACK> the LEDs sequentially
    for (int x = 2; x < NUM_LEDS_PER_STRIP; x = x + 1) {
      // Turn on the led
      leds[NUM][x] =  CRGB(100,0,0);
      FastLED.show(); 
      delay(DELAY_1);
    }
  delay(DELAY_2);
    for (int x = NUM_LEDS_PER_STRIP-1; x >= 0; x = x - 1) {
      // Turn off the led
      leds[NUM][x] =  CRGB(0,0,0);
      FastLED.show();
      delay(DELAY_1);
    }
  delay(DELAY_3);
}

void TurnOff() {  // Turn Off Event: Turns off <BLACK> all the LEDs from all the STRIPS
  for (int x = NUM_LEDS_PER_STRIP-1; x >= 0; x = x - 1) {
      leds[0][x] =  CRGB(0,0,0);
      FastLED.show();
      leds[1][x] =  CRGB(0,0,0);
      FastLED.show();
      leds[2][x] =  CRGB(0,0,0);
      FastLED.show();
      leds[3][x] =  CRGB(0,0,0);
      FastLED.show();
      leds[4][x] =  CRGB(0,0,0);
      FastLED.show();
      leds[5][x] =  CRGB(0,0,0);
      FastLED.show();
      leds[6][x] =  CRGB(0,0,0);
      FastLED.show();
    }
}

void Event_Indicator(int event_mode){
  for (int j = 0; j < NUM_STRIPS; j++ ){
    leds[j][1] = CRGB(0,0,100);
    leds[j][event_mode] = CRGB(0,0,100);
    FastLED.show();
  }
  delay(5000);
  FastLED.clear();
  FastLED.show();
}

long Release1 = 0; // Debounce period to prevent flickering when pressing or releasing the button
long Press1 = 0; // Time the button was pressed down

int checkButton() {
  int event = -1;
  int stat = button.getState();
  Serial.print (stat);
  Serial.println (INIT_EVENT);
  if (button.isReleased()  && !INIT_EVENT ){
    event = 0;
    INIT_EVENT = true;
    button.resetCount();
  }
  else if (button.isReleased() && INIT_EVENT ) {
    Press1 = millis();
    button.resetCount();
    while (millis() - Press1 < waitTime){
      button.loop();
      Serial.println(button.getCount());
    	if (button.getCount() == 1) { 
    	  event  = 2;
    	}
    	else if (button.getCount() == 2) { 
    	  event = 3;
    	}
      else{
        event = 1;
      }
    }
  }
  return event;
  
}
