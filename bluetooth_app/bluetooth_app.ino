
//#include <OneButton.h>
#include <FastLED.h>
#define NUM_LEDS 60
#define LED_PIN  4
//#define BTN_PIN 26
CRGB leds[NUM_LEDS];
#define BLENDING LINEARBLEND
#include "BluetoothSerial.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"

#define SECONDS_PER_PALETTE 15



#include "ledgfx.h"
#include "fire.h"


byte Huevalue = 0;
int Nappivalue = 0;
int Nappi = 26;
int LED = 32;
int value = 255;
int varikyllaisyys = 255;
int hue = 0;
String color = "BLUE";
int moodi = 0;
String  DATA;
byte dothue = 0;
uint8_t gHue = 0;
uint8_t gCurrentPaletteNumber = 0;
int g_Brightness = 255; 


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
void printDeviceAddress() {


const uint8_t* point = esp_bt_dev_get_address();

for (int i = 0; i < 6; i++) {
   char str[3];
   sprintf(str, "%02X", (int)point[i]);
   Serial.print(str);
   if (i < 5){
   Serial.print(":");}
}
Serial.println();
}

void setup()
{
DATA = "";

Serial.begin(9600);

  SerialBT.begin("ESP32_C3");
  printDeviceAddress();
  pinMode(Nappi, INPUT);
  pinMode(LED, OUTPUT);
 
 FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
 fill_solid(leds, NUM_LEDS, CRGB(0,0,0));       
 FastLED.show();

 
 //btn.attachClick(DATA == "SPARK");
}

extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
extern const uint8_t gGradientPaletteCount;

// Current palette number from the 'playlist' of color palettes


CRGBPalette16 gCurrentPalette( CRGB::Black);
CRGBPalette16 gTargetPalette( gGradientPalettes[0] );

void loop()
{
    if (SerialBT.available()) {
      DATA = (SerialBT.readString());
      Serial.println("NEW DATA");
      Serial.println(DATA);
      if (DATA == "OFF") {
        moodi = 0;
      } 
      if (DATA == "SOLID") {
        moodi = 1;
      }
      if (DATA == "WAVE") {
        moodi = 2;
      }
      if (DATA == "SPARK") {
        moodi = 3;
      }      
      if (DATA == "PARTY") {
        moodi = 4;
      }
      if (DATA == "ALAS") {
        moodi = 5;
      } 
      if (DATA == "YLOS") {
        moodi = 6;
      }
      if (DATA == "SPEEDY"){
        moodi = 7;
      } 
      if (DATA == "RED") {
        color = "Red";
      }
      if (DATA == "GREEN") {
        color = "Green";
      }
      if (DATA == "BLUE") {
        color = "Blue";
      }
      if (DATA == "YELLOW") {
        color = "Yellow";
      }
      if (DATA == "PINK") {
        color = "Pink";
      }
      if (DATA == "CYAN") {
        color = "Cyan";
      }
      if (DATA == "VIOLET") {
        color = "Violet";
      }
      if (DATA == "WHITE") {
        color = "White";
      } 
      if (DATA == "RAINBOW") {
        color = "Rainbow";
      }
      if (DATA == "COLORWAVE") {
        moodi = 8;
      }
      if (DATA == "CYLON") {
        moodi = 9;
      }
      if (DATA == "FIRE") {
        moodi = 10;
      }
      
    }
   //Pois päältä
   if (moodi == 0){
      fadeToBlackBy(leds, NUM_LEDS, 10);       
      FastLED.show();
    }
  //SOLID
   if (moodi == 1){
      
      if(color == "Green"){
        fill_solid(leds, NUM_LEDS, CRGB(0,255,0));
        }
      if(color == "Cyan"){
        fill_solid(leds, NUM_LEDS, CRGB(0,255,255));
        }
      if(color == "Violet"){
        fill_solid(leds, NUM_LEDS, CRGB(93,0,255));
        }  
      if(color == "White"){
        fill_solid(leds, NUM_LEDS, CRGB(155,155,155));
        }
      if(color == "Blue"){
        fill_solid(leds, NUM_LEDS, CRGB(0,0,255));
        }
       if(color == "Yellow"){
        fill_solid(leds, NUM_LEDS, CRGB::Yellow);
        }
      if(color == "Red"){
        fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
        }
      if(color == "Pink"){
        fill_solid(leds, NUM_LEDS, CRGB(255,0,64));
      }
      if(color == "Rainbow"){
        fill_rainbow( leds, NUM_LEDS, 0, 1);
        }       
       FastLED.show();
     }
     if (moodi==2){
    //Aja SinBeat
    //Serial.println("Todettiin mode = 1");
    uint16_t sinBeat = beatsin16(20, 0, NUM_LEDS - 1, 255, 0);
    if(color == "Green"){
      leds[sinBeat] = CRGB::Green;
      }
    if(color == "Cyan"){
      leds[sinBeat] = CRGB::Cyan;
      } 
    if(color == "Pink"){
      leds[sinBeat] = CRGB(255,0,64);
      }
    if(color == "White"){
      leds[sinBeat] = CRGB::White;
      }
    if(color == "Red"){
      leds[sinBeat] = CRGB::Red;
      }
    if(color == "Blue"){
      leds[sinBeat] = CRGB::Blue;
      }
    if(color == "Yellow"){
      leds[sinBeat] = CRGB::Yellow;
      }  
    if(color == "Violet"){
      leds[sinBeat] = CRGB(93,0,255);
      }   
    if(color == "Rainbow"){
      leds[sinBeat] = CHSV(hue++,255,255);
      }
    fadeToBlackBy(leds, NUM_LEDS, 10);
    FastLED.show();
   }
    
if (moodi == 3){
    //tuikku
   fadeToBlackBy( leds, NUM_LEDS, 10);
   int pos = random16(NUM_LEDS);
    if(color == "Green"){
      leds[pos] +=  CRGB::Green;
      }
    if(color == "Cyan"){
      leds[pos] +=  CRGB::Cyan;
      } 
    if(color == "Pink"){
      leds[pos] +=  CRGB(255,0,64);
      }
    if(color == "White"){
      leds[pos] +=  CRGB::White;
      }
    if(color == "Red"){
      leds[pos] +=  CRGB::Red;
      }
    if(color == "Blue"){
      leds[pos] +=  CRGB::Blue;
      }
    if(color == "Yellow"){
      leds[pos] +=  CRGB::Yellow;
      }  
    if(color == "Violet"){
      leds[pos] +=  CRGB(93,0,255);
      }   
    if(color == "Rainbow"){
      leds[pos] +=  CHSV(hue++,255,255);
      }
   FastLED.show();
  }
//PARTY
  if (moodi==4){
    fadeToBlackBy( leds, NUM_LEDS, 20);
    for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+9, 0, NUM_LEDS-1 )] |= CHSV(dothue, varikyllaisyys, value);
    
    if(color == "Green"){
      dothue =  85;
      }
    if(color == "Cyan"){
      dothue =  122;
      } 
    if(color == "Pink"){
      dothue =  237;
      }
    if (color == "White"){
      varikyllaisyys = 0;
    }
    else{
      varikyllaisyys = 255;
    }
    if(color == "Red"){
      dothue =  255;
      }
    if(color == "Blue"){
      dothue =  165;
      }
    if(color == "Yellow"){
      dothue =  43;
      }  
    if(color == "Violet"){
      dothue =  205;
      }   
    if(color == "Rainbow"){
      dothue += 32;
      }
     }
  }
   if (moodi==8){
    
      colorwaves( leds, NUM_LEDS, gCurrentPalette);
      FastLED.show();
    }
   
   if(moodi == 9){
    
   
 static uint8_t hue = 0;
  // First slide the led in one direction

  // Now go in the other direction.  
  for(int i = (NUM_LEDS/2)-1; i >= 0; i--) {
    // Set the i'th led to red     
    if(color == "Green"){
      leds[i] +=  CRGB::Green;
      }
    if(color == "Cyan"){
      leds[i] +=  CRGB::Cyan;
      } 
    if(color == "Pink"){
      leds[i] +=  CRGB(255,0,64);
      }
    if(color == "White"){
      leds[i] +=  CRGB::White;
      }
    if(color == "Red"){
      leds[i] +=  CRGB::Red;
      }
    if(color == "Blue"){
      leds[i] +=  CRGB::Blue;
      }
    if(color == "Yellow"){
      leds[i] +=  CRGB::Yellow;
      }  
    if(color == "Violet"){
      leds[i] +=  CRGB(93,0,255);
      }   
    if(color == "Rainbow"){
      leds[i] +=  CHSV(hue++,255,255);
      }
    // Show the leds
    for(int i=0 ; i<NUM_LEDS/2; i++)
{
    leds[NUM_LEDS-i-1]=leds[i];
}
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    
    delay(20);
    FastLED.show();
    fadeToBlackBy(leds, NUM_LEDS, 30);
  }
 }
 
   if(moodi == 10){

    bool bLED = 0;

    ClassicFireEffect fire(NUM_LEDS, 30, 200 ,6 , 5, false, true);
    
  while (true)
  {
    FastLED.clear();
    fire.DrawFire();
    FastLED.show(g_Brightness);                          //  Show and delay
    delay(33);
  }
      
    
   }
      EVERY_N_SECONDS( SECONDS_PER_PALETTE ) {
        gCurrentPaletteNumber = addmod8( gCurrentPaletteNumber, 1, gGradientPaletteCount);
        gTargetPalette = gGradientPalettes[ gCurrentPaletteNumber ];
      }
    
      EVERY_N_MILLISECONDS(40) {
        nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 16);
      }
}





DEFINE_GRADIENT_PALETTE( es_pinksplash_08_gp ) {
    0, 126, 11,255,
  127, 197,  1, 22,
  175, 210,157,172,
  221, 157,  3,112,
  255, 157,  3,112};

void colorwaves( CRGB* ledarray, uint16_t numleds, CRGBPalette16& palette) {
  
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 300, 1500);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < numleds; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
    uint16_t h16_128 = hue16 >> 7;
    if( h16_128 & 0x100) {
      hue8 = 255 - (h16_128 >> 1);
    } else {
      hue8 = h16_128 >> 1;
    }

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    uint8_t index = hue8;
    //index = triwave8( index);
    index = scale8( index, 240);

    CRGB newcolor = ColorFromPalette( palette, index, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (numleds-1) - pixelnumber;
    
    nblend( ledarray[pixelnumber], newcolor, 128);
  }
}
const TProgmemRGBGradientPalettePtr gGradientPalettes[] = { 
  es_pinksplash_08_gp
 };
 
const uint8_t gGradientPaletteCount = 
  sizeof( gGradientPalettes) / sizeof( TProgmemRGBGradientPalettePtr );
