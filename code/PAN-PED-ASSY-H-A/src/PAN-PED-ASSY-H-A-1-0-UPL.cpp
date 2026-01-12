/*
  OH-6A Pedestal Panel - Arduino MEGA 2560
  DCS-BIOS 0.2.11

  Pin assignments from pin_mapping.txt (updated)
*/

#define DCSBIOS_IRQ_SERIAL  // 250000 baud
#include "DcsBios.h"

/* Instantiate a ProtocolParser object to parse the DCS-BIOS export stream */
DcsBios::ProtocolParser parser;

unsigned long lastTickMillis;

// ====================================
// ELECTRIC SYSTEM SWITCHES
// ====================================

// Pin 53: Gyro/Magnetic Switch YEL
DcsBios::Switch2Pos gyro("GYRO", 53);

// Pin 50: Inverter Switch ORA
DcsBios::Switch2Pos inverter("INVERTER", 50);

// Pin 51: Auxiliary Tank Switch RED
DcsBios::Switch2Pos auxTank("AUX_TANK", 51);

// Pin 48: Generator Switch BRN
DcsBios::Switch2Pos gen("GEN", 48);

// Pin 49: Fuel Pump Switch BLK
DcsBios::Switch2Pos fuelPump("FUEL_PUMP", 49);

// Pins 46, 47: Power Switch (BATT/OFF/EXT) - 3 position selector
// 46 WHT
// 47 GRA
DcsBios::Switch3Pos powerSwitch("POWER_SWITCH", 47, 46);

// ====================================
// FUEL SYSTEM
// ====================================

// Pin 44: Fuel Valve Lever PUR
DcsBios::Switch2Pos fuelValve("FUEL_VALVE", 44);

// ====================================
// ROCKETS PANEL
// ====================================

// Pin 45: Weapon Select (GUN/ROCKETS) - 7.62/40 switch BLU
DcsBios::Switch2Pos weaponSelect("WEAPON_SELECT", 45);

// Pins 43,42,41,40,38,39,36,37: Rocket Pairs Selector (8 positions: 0-7)
//
// Each pin represents one position
const byte rocketPairsPins[8] = {42, 43, 40, 41, 38, 39, 36, 37};
DcsBios::SwitchMultiPos rocketPairs("ROCKET_PAIRS", rocketPairsPins, 8);

// Pin 4: Jettison Cover RED
DcsBios::Switch2Pos jettisonCover("JETTISON_COVER", 4, true);


// Pin 34: Jettison Switch PUR
DcsBios::Switch2Pos jettison("JETTISON", 34);

// ====================================
// LIGHTS
// ====================================

// Pin 22: Anti-Collision Light YEL
DcsBios::Switch2Pos anticolLight("ANTICOL_LIGHT", 23);

// Pins 2, 3: Position Light (DIM/OFF/BRT) - 3 position selector
// Pin 2 = DIM (position 0), Pin 3 = BRT (position 2), neither = OFF (position 1)
DcsBios::Switch3Pos posLight("POS_LIGHT", 2, 3);

// ====================================
// ANALOG POTENTIOMETERS
// ====================================

// A8 (Pin 62): Instrument/Engine Lights Brightness
DcsBios::Potentiometer lightEngine("LIGHT_ENGINE", A12);

// A9 (Pin 63): Flight Lights Brightness
DcsBios::Potentiometer lightFlight("LIGHT_FLIGHT", A11);

// A10 (Pin 64): Radio Lights Brightness
DcsBios::Potentiometer lightRadio("LIGHT_RADIO", A10);

// A11 (Pin 65): Panel Lights Brightness
DcsBios::Potentiometer lightPanel("LIGHT_PANEL", A9);



// ====================================
// INTERCOM SYSTEM
// ====================================

// A12 (Pin 66): Intercom Volume
DcsBios::Potentiometer intercom2Vol("INTERCOM2_VOL", A8);

// Pins 32,33,30,31,28,29: Intercom 2 Selector (6 positions)
// 28 BRN PVT
// 31 RED INT
// 30 ORA 1
// 33 YEL 2
// 32 GRN 3
// 35 BLU 4
// PVT INT 1 2 3 4
const byte intercom2SelectPins[7] = {28, 28, 31, 30, 33, 32, 35};
DcsBios::SwitchMultiPos intercom2Select("INTERCOM2_SELECT", intercom2SelectPins, 7);

// Intercom 2 Separate Channel Switches
// RCVR 1 BLK
DcsBios::Switch2Pos intercom2_1("INTERCOM2_1", 29);

// RCVR 2 WHT
DcsBios::Switch2Pos intercom2_2("INTERCOM2_2", 26);

// RCVR 3 GRA
DcsBios::Switch2Pos intercom2_3("INTERCOM2_3", 27);

// RCVR 4 PUR
DcsBios::Switch2Pos intercom2_4("INTERCOM2_4", 24);

// RCVR 6 BLU
DcsBios::Switch2Pos intercom2Int("INTERCOM2_INT", 25);

// RCVR 5 GRN
DcsBios::Switch2Pos intercom2Nav("INTERCOM2_NAV", 22);

// ====================================

void setup() {
  DcsBios::setup();
  lastTickMillis = millis();
}

void timerTick()
{
  // The timer has expired.  Issue a mass reset to all controls.  Safe, but may generate additional
  // traffic if you have many controls.
  DcsBios::resetAllStates();
}

void loop() {
  DcsBios::loop();

  unsigned long now = millis();
  if(now - lastTickMillis > 10000)
  {
    timerTick();
    lastTickMillis = now;
  }
}

// This is the recommended approach and the ideal if we can work out all the kinks:
// If the mission time changes backwards, we have entered a new aircraft; Resync everything
unsigned long uLastModelTimeS = 0xFFFFFFFF; // Start big, to ensure the first step triggers a resync

void onModTimeChange(char* newValue) {
  unsigned long currentModelTimeS = atol(newValue);

  if( currentModelTimeS < uLastModelTimeS )
  {
    if( currentModelTimeS > 20 )// Delay to give time for DCS to finish loading and become stable and responsive
    {
      DcsBios::resetAllStates();
      uLastModelTimeS = currentModelTimeS;
    }
  }
  else
  {
    uLastModelTimeS = currentModelTimeS;
  }
}
DcsBios::StringBuffer<5> modTimeBuffer(0x043e, onModTimeChange);
