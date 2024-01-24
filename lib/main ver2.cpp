// +-------------------------------------------------------------
//
// Equipment:
// ESP32, OLED SSD1306
//
// File: main.cpp
//
// Description:
//
// main file to engage all char array graphics, whether they be
// non-animated or animated on the ESP 32 platform
//
// History:     1-Nov-2023     Scarecrow1965   Created
//
// +-------------------------------------------------------------

// CONFIRMED: WORKS ON ESP32 AND OLED SCREEN

// install ibraries
#include <Arduino.h>
#include <U8g2lib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// This will enable for the OLED screen to display information
// definition of OLED display SSD1306 for Arduino Mega SCA & SDL
#define OLED_CLOCK 17 // SCA pin on Display = SCL on ESP32
#define OLED_DATA 20  // SDL pin on display = SDA on ESP32

// U8G2 SSD1306 Driver here to run OLED Screen
// built constructor for the OLED function
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, OLED_CLOCK, OLED_DATA, U8X8_PIN_NONE); // This works but according to the function, it shouldn't
static int oled_LineH = 0;

// #define LED_BUILTIN 2 // pin for onboard LED or use LED_BUILTIN as the default location
static bool bLED = LOW;

// ADAFRUIT SSD1306 Driver here to run animation
// NOTE: confirmed by I2C Scanner address for SSD1306 is 0x3c
// NOTE: const int SSD1306_addr = 0x3c;
// to initialilze the address of the OLED display
#define SCREEN_I2C_ADDR 0x3C // or 0x3C
#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels
#define OLED_RST_PIN -1      // Reset pin (-1 if not available)

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RST_PIN);

#include "charArrayNonAnim.h"
#include "charArrayAnim.h"

charArrayNonAnim charNoAnimation;
charArrayAnim charAnimation;

// ==================================
// ONE TIME MANDATORY FUNCTION - DO NOT REMOVE
// ==================================
void setup(void)
{
    pinMode(LED_BUILTIN, OUTPUT); // relying on GPIO2 LED to light up on MB

    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial.println("Starting setup");

    // for U8G2 library setup
    u8g2.begin();
    u8g2.clear();
    u8g2.setFont(u8g2_font_profont10_tf);
    oled_LineH = u8g2.getFontAscent() + u8g2.getFontAscent();

    // for Adafruit library setup
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR);
    display.clearDisplay();

    Serial.println("Setup complete");
} // end setup function

// ==================================
// REPETITIVE MANDATORY FUNCTION - DO NOT REMOVE
// ==================================
void loop(void)
{

    Serial.println("Starting non-Animations");
    // calling the function from charArrayNonAnim.h
    // this one cycles through all the char array non-animations
    // charArray_NonAnim(); // this works when not in a class
    charNoAnimation.charArray_NonAnim(); // this works when in a class

    Serial.println("Starting Animations");
    // calling the function from charArrayAnim.h
    // this one cycles through all the char array animations
    // charArray_Anim(); // this works when not in a class
    charAnimation.charArray_Anim(); // this works when in a class

    Serial.println("Starting an individual Non-Animation");
    // CPLUSPLUSLogo(); // this works not in a class
    charNoAnimation.CPLUSPLUSLogo(); // this works when in a class
    delay(1000);                     // used for single graphics display

    Serial.println("Starting an individual Animation");
    // download_ANIMATION(); // this works when not in a class
    charAnimation.download_ANIMATION(); // this works when in a class

} // end loop function

// =========================================================
// END OF PROGRAM
// =========================================================
