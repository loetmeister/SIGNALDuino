/*
 * hardware.h
 *
 *  Created on: 23.05.2018
 *      Author: loetmeister.de
 */

#ifndef _hardware_h
#define _hardware_h


#if defined (ARDUINO_ARCH_RP2040)
  // #include <Wire.h>
  #include "extras/EEPROM24.h"
  class EEPROM24;    // forward declare class
  extern EEPROM24* EepromPtr;

  #ifndef NOT_A_PIN
  #define NOT_A_PIN 0xFF
  #endif
#else
  #include <EEPROM.h>
  extern EEPROMClass* EepromPtr;
#endif

/* watchdog macros, config, reboot and reset*/
#if defined (__AVR__)
  // #include "avr/wdt.h"
  // // if watchdog is used & active, just run into infinite loop to force reset
  // #define RESET_HARDWARE() while(1){}
  // #define ENABLE_WATCHDOG() wdt_enable(WDTO_1S)
  // #define RESET_WATCHDOG() wdt_reset()
  // // Arduino Reset via Software function declaration, point to address 0 (reset vector)
  // #define RESET_SOFTWARE() resetSoftware()

#elif defined (ARDUINO_ARCH_RP2040)
  #include <hardware/watchdog.h>
  #define ENABLE_WATCHDOG() watchdog_enable(1000, 0)
  #define RESET_WATCHDOG() watchdog_update()
//watchdog_reboot(0, 0, 10);  // watchdog fire after 10us and busy waits // or watchdog_reboot(0, SRAM_END, 0) ??
  #define RESET_HARDWARE() watchdog_reboot(0, SRAM_END, 10);\
    for (;;) { }
  // always reboot via watchdog
  #define RESET_SOFTWARE() RESET_HARDWARE()
#endif


#endif /* _hardware_h */
