/*
  DCS-BIOS Monitor - Simple Version (No IRQ)
*/

#define DCSBIOS_DEFAULT_SERIAL
#include "DcsBios.h"

// Rotary Encoder - ALT BARO ADJ
#define PIN_ENCODER_CLK 2
#define PIN_ENCODER_DT 3


#define PIN_ARM 4
#define PIN_SAFE 5

#define PIN_SELECT_SAFE 6
#define PIN_SELECT_FIRE_TO_CLEAR 7
#define PIN_FIRE_NORM 8

// Panel Lights
#define PIN_GENERATOR_CUT 10
#define PIN_XMSN_OIL_PRESS 11
#define PIN_ENGINE_OUT 12

// State variables
bool onBatteryPower = false;
unsigned long lastFlipFlopTime = 0;
bool flipFlopState = false;

// DCS-BIOS callback to detect battery power switch
void onBattPwrChange(unsigned int newValue) {
  onBatteryPower = (newValue == 0);  // 0 = BATT position (0=BATT, 1=OFF, 2=EXT)
}
DcsBios::IntegerBuffer battPwrBuffer(0x8c00, 0x0060, 5, onBattPwrChange);

// Rotary Encoder for Altimeter Barometric Adjustment
// OH-6A BARO_ALT control
DcsBios::RotaryEncoder baroAlt("BARO_ALT", "-320", "+320", PIN_ENCODER_DT, PIN_ENCODER_CLK);

// Pin 4, 5: Weapon Arm
DcsBios::Switch2Pos weaponArm("WEAPON_ARM", PIN_SAFE);
// Pins 6, 7, 8: Weapon mode Switch (OFF/CLEAR/FIRE) - 3 position selector
// Array order: [0]=OFF (SAFE), [1]=CLEAR (FIRE TO CLEAR), [2]=FIRE (FIRE NORM)
const byte weaponModes[3] = {PIN_SELECT_SAFE, PIN_SELECT_FIRE_TO_CLEAR, PIN_FIRE_NORM};
DcsBios::SwitchMultiPos weaponMode("WEAPON_MODE", weaponModes, 3);

void setup() {
  // Initialize LED pins as outputs
  pinMode(PIN_GENERATOR_CUT, OUTPUT);
  pinMode(PIN_XMSN_OIL_PRESS, OUTPUT);
  pinMode(PIN_ENGINE_OUT, OUTPUT);

  // Initialize encoder pins as inputs with pullups
  pinMode(PIN_ENCODER_CLK, INPUT_PULLUP);
  pinMode(PIN_ENCODER_DT, INPUT_PULLUP);

  // Initialize all LEDs off
  digitalWrite(PIN_GENERATOR_CUT, LOW);
  digitalWrite(PIN_XMSN_OIL_PRESS, LOW);
  digitalWrite(PIN_ENGINE_OUT, LOW);

  DcsBios::setup();
}

void loop() {
  DcsBios::loop();

  // Handle BATT power mode LEDs
  if (onBatteryPower) {
    // Turn on GENERATOR CUT LED
    digitalWrite(PIN_GENERATOR_CUT, HIGH);

    // Alternate XMSN OIL PRESS and ENGINE OUT LEDs every 250ms
    unsigned long currentTime = millis();
    if (currentTime - lastFlipFlopTime >= 250) {
      flipFlopState = !flipFlopState;
      lastFlipFlopTime = currentTime;

      digitalWrite(PIN_XMSN_OIL_PRESS, flipFlopState ? HIGH : LOW);
      digitalWrite(PIN_ENGINE_OUT, flipFlopState ? LOW : HIGH);
    }
  } else {
    // Turn off all LEDs when not on battery power
    digitalWrite(PIN_GENERATOR_CUT, LOW);
    digitalWrite(PIN_XMSN_OIL_PRESS, LOW);
    digitalWrite(PIN_ENGINE_OUT, LOW);
  }
}
