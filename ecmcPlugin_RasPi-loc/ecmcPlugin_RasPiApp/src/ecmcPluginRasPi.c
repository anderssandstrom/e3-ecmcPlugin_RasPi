/*************************************************************************\
* Copyright (c) 2019 European Spallation Source ERIC
* ecmc is distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution. 
*
*  ecmcPluginExample.cpp
*
*  Created on: Mar 21, 2020
*      Author: anderssandstrom
*
\*************************************************************************/

// Needed to get headers in ecmc right...
#define ECMC_IS_PLUGIN
#define ECMC_RASPI_PLUGIN_VERSION 1
#define ECMC_RASPI_PLUGIN_NAME "ecmcRasPi"
#define ECMC_RASPI_PLUGIN_PLC_FUNC_PREFIX "rpi_"

#ifdef __cplusplus
extern "C" {
#endif  // ifdef __cplusplus

#include <stdio.h>
#include "ecmcPluginDefs.h"
#include "ecmcRasPiGPIO.h"
#include <wiringPi.h>

static double ecmcSampleRate = -1;
static void*  ecmcDataRefs   = 0;  //ecmcRefs form raspiEnterRT()
static int    lastEcmcError  = 0;
static void*  ecmcAsynPort   = NULL;
static int    wiringPiSetupDone = 0;

#define EXE_SETUP_IF_NOT_DONE()              \
  {                                          \
    if (!wiringPiSetupDone) {                \
      wiringPiSetup ();                      \
      wiringPiSetupDone = 1;                 \
    }                                        \
  }                                          \

/** Optional. 
 *  Will be called once just before ecmc goes into realtime mode.
 *  Return value other than 0 will be considered error.
 **/
int rpi_Construct(void)
{
  printf("Ecmc plugin, "ECMC_RASPI_PLUGIN_NAME", for RasPi GPIO support initiating...\n");
  printf("Note: Defaults to WiringPi pin numbering if not another setup function is called.\n");
  return 0;
}

/** Optional function.
 *  Will be called once at unload.
 **/
void rpi_Destruct(void)
{
  printf("Plugin "ECMC_RASPI_PLUGIN_NAME" unloading...\n");
}

/** Optional function.
 *  Will be called each realtime cycle if definded
 *  ecmcError: Error code of ecmc. Makes it posible for 
 *  this plugin to react on ecmc errors
 *  Return value other than 0 will be considered error.
 **/
int rpi_Realtime(int ecmcError)
{
  lastEcmcError = ecmcError;
  return 0;
}

/** Optional function.
 *  Will be called once just before going to realtime mode
 *  Return value other than 0 will be considered error.
 *  ecmcRefs is only valid after "raspiEnterRT()"
 **/
int rpi_EnterRT(void* ecmcRefs){  
  // Save ecmcRefs if needed
  printf("Plugin "ECMC_RASPI_PLUGIN_NAME" enters realtime...\n");
  ecmcDataRefs   = ecmcRefs;
  ecmcSampleRate = getSampleRate(ecmcRefs);
  ecmcAsynPort   = getAsynPort(ecmcRefs);    
  return 0;
}

/** Optional function.,ECMC_RASPI_PLUGIN_NAME
 *  Will be called once just before leaving realtime mode
 *  Return value other than 0 will be considered error.
 **/
int rpi_ExitRT(void){
  printf("Plugin "ECMC_RASPI_PLUGIN_NAME" exits realtime...\n");
  return 0;
}

/** WiringPi wrapper functions below 
 *
 *  "Setup functions":
 */
double rpi_wiringPiSetup() {
  wiringPiSetupDone = 1;
  return (double)wiringPiSetup();
}

double rpi_wiringPiSetupGpio() {
  wiringPiSetupDone = 1;
  return (double)wiringPiSetupGpio();
}

double rpi_wiringPiSetupPhys() {
  wiringPiSetupDone = 1;
  return (double)wiringPiSetupPhys();
}

double rpi_wiringPiSetupSys() {
  wiringPiSetupDone = 1;
  return (double)wiringPiSetupSys();
}

/**
 *  "Core functions":
 */
double rpi_digitalWrite(double pin, double value) {
  EXE_SETUP_IF_NOT_DONE();
  digitalWrite((int)pin, (int)value);
  return 0;
}

double rpi_digitalRead(double pin) {
  EXE_SETUP_IF_NOT_DONE();
  return (double)digitalRead ((int)pin);
}

double rpi_pinMode(double pin, double mode) {
  EXE_SETUP_IF_NOT_DONE();
  pinMode ((int)pin,(int)mode);
  return 0;
}

double rpi_pullUpDnControl(double pin, double pud) {
  EXE_SETUP_IF_NOT_DONE();
  pullUpDnControl ((int)pin,(int)pud);
  return 0;
}

double rpi_pwmWrite(double pin, double value) {
  EXE_SETUP_IF_NOT_DONE();
  pwmWrite ((int)pin,(int)value);
  return 0;
}

double rpi_analogRead(double pin) {
  EXE_SETUP_IF_NOT_DONE();
  return (double)analogRead ((int)pin);
}

double rpi_analogWrite(double pin, double value) {
  EXE_SETUP_IF_NOT_DONE();
  analogWrite ((int)pin,(int)value);
  return 0;
}

/**
  "Raspberry Pi Specifics" functions
*/
double rpi_digitalWriteByte(double value) {
  EXE_SETUP_IF_NOT_DONE();
  digitalWriteByte((int)value) ;
  return 0;
}

double rpi_pwmSetMode(double mode) {
  EXE_SETUP_IF_NOT_DONE();
  pwmSetMode((int)mode);
  return 0;
}

double rpi_pwmSetRange(double range) {
  EXE_SETUP_IF_NOT_DONE();
  pwmSetRange((unsigned int)range);
  return 0;
}

double rpi_pwmSetClock(double divisor) {
  EXE_SETUP_IF_NOT_DONE();
  pwmSetClock((int)divisor);
  return 0;
}

double rpi_piBoardRev(void) {
  EXE_SETUP_IF_NOT_DONE();
  return (double)piBoardRev();
}

double rpi_wpiPinToGpio(double wPiPin) {
  EXE_SETUP_IF_NOT_DONE();
  return (double)wpiPinToGpio((int) wPiPin);
}

double rpi_physPinToGpio(double physPin) {
  EXE_SETUP_IF_NOT_DONE();
  return (double)physPinToGpio((int) physPin);
}

double rpi_setPadDrive(double group, double value) {
  EXE_SETUP_IF_NOT_DONE();
  setPadDrive((int)group, (int)value);
  return 0;
}

// Compile data for lib so ecmc now what to use
struct ecmcPluginData pluginDataDef = {
  // Name 
  .name = ECMC_RASPI_PLUGIN_NAME,
  // Description 
  .desc = "ecmc plugin for GPIO access on RasPi (wrapper to WiringPi)",
  // Plugin version
  .version = ECMC_RASPI_PLUGIN_VERSION,
  // Allways use ECMC_PLUG_VERSION_MAGIC
  .ifVersion = ECMC_PLUG_VERSION_MAGIC, 
  // Optional construct func, called once at load. NULL if not definded.
  .constructFnc = rpi_Construct,
  // Optional destruct func, called once at unload. NULL if not definded.
  .destructFnc = rpi_Destruct,
  // Optional func that will be called each rt cycle. NULL if not definded.
  .realtimeFnc = rpi_Realtime,
  // Optional func that will be called once just before enter realtime mode
  .realtimeEnterFnc = rpi_EnterRT,
  // Optional func that will be called once just before exit realtime mode
  .realtimeExitFnc = rpi_ExitRT,

  // Allow max ECMC_PLUGIN_MAX_FUNC_COUNT custom funcs
  .funcs[0] =      
      { /*----rpi_digitalWrite----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_digitalWrite",
        // Function description
        .funcDesc = "WiringPi: void digitalWrite(pin,level)",
        // Number of arguments in the function prototytpe
        .argCount = 2,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = NULL,
        .funcArg2 = rpi_digitalWrite, // Func 1 has 2 args
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,                
        .funcArg6 = NULL,        
      },
  .funcs[1] =
      { /*----rpi_digitalRead----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_digitalRead",
        // Function description
        .funcDesc = "WiringPi: level=digitalRead(pin)",
        // Number of arguments in the function prototytpe
        .argCount = 1,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = rpi_digitalRead, // 1 Arg
        .funcArg2 = NULL,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,                
        .funcArg6 = NULL,
      },
  .funcs[2] =
      { /*----rpi_pinMode----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_pinMode",
        // Function description
        .funcDesc = "WiringPi: void pinMode(pin,mode)",        
        // Number of arguments in the function prototytpe
        .argCount = 2,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = NULL,
        .funcArg2 = rpi_pinMode,  // 2 Arg
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,                
        .funcArg6 = NULL,
      },
  .funcs[3] =
      { /*----rpi_pullUpDnControl----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_pullUpDnControl",
        // Function description
        .funcDesc = "WiringPi: void pullUpDnControl(pin,pud)",        
        // Number of arguments in the function prototytpe
        .argCount = 2,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = NULL,
        .funcArg2 = rpi_pullUpDnControl,  // 2 Arg
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL,
      },
  .funcs[4] =
      { /*----rpi_pwmWrite----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_pwmWrite",
        // Function description
        .funcDesc = "WiringPi: void pwmWrite(pin,value)",        
        // Number of arguments in the function prototytpe
        .argCount = 2,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = NULL,
        .funcArg2 = rpi_pwmWrite,  // 2 Arg
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
  .funcs[5] =
      { /*----rpi_analogRead----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_analogRead",
        // Function description
        .funcDesc = "WiringPi: value=analogRead(pin)",        
        // Number of arguments in the function prototytpe
        .argCount = 1,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = rpi_analogRead,  // 1 Arg
        .funcArg2 = NULL, 
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
  .funcs[6] =
      { /*----rpi_analogWrite----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_analogWrite",
        // Function description
        .funcDesc = "WiringPi: void analogWrite(pin,value)",
        // Number of arguments in the function prototytpe
        .argCount = 2,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = NULL,
        .funcArg2 = rpi_analogWrite,   // 2 Arg
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
  .funcs[7] =
      { /*----rpi_digitalWriteByte----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_digitalWriteByte",
        // Function description
        .funcDesc = "WiringPi: void digitalWriteByte(value)",
        // Number of arguments in the function prototytpe
        .argCount = 1,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = rpi_digitalWriteByte,
        .funcArg2 = NULL,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
  .funcs[8] =
      { /*----rpi_pwmSetMode----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_pwmSetMode",
        // Function description
        .funcDesc = "WiringPi: void pwmSetMode(mode)",
        // Number of arguments in the function prototytpe
        .argCount = 1,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = rpi_pwmSetMode,
        .funcArg2 = NULL,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },

  .funcs[9] =
      { /*----rpi_pwmSetRange----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_pwmSetRange",
        // Function description
        .funcDesc = "WiringPi: void pwmSetRange(range)",
        // Number of arguments in the function prototytpe
        .argCount = 1,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = rpi_pwmSetRange,
        .funcArg2 = NULL,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
  .funcs[10] =
      { /*----rpi_pwmSetClock----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_pwmSetClock",
        // Function description
        .funcDesc = "WiringPi: void pwmSetClock(divisor)",
        // Number of arguments in the function prototytpe
        .argCount = 1,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = rpi_pwmSetClock,
        .funcArg2 = NULL,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
  .funcs[11] =
      { /*----rpi_piBoardRev----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_piBoardRev",
        // Function description
        .funcDesc = "WiringPi: int piBoardRev()",
        // Number of arguments in the function prototytpe
        .argCount = 0,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = rpi_piBoardRev,
        .funcArg1 = NULL,
        .funcArg2 = NULL,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
  .funcs[12] =
      { /*----rpi_wpiPinToGpio----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_wpiPinToGpio",
        // Function description
        .funcDesc = "WiringPi: int wpiPinToGpio(wPiPin)",
        // Number of arguments in the function prototytpe
        .argCount = 1,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = rpi_wpiPinToGpio,
        .funcArg2 = NULL,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
  .funcs[13] =
      { /*----rpi_physPinToGpio----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_physPinToGpio",
        // Function description
        .funcDesc = "WiringPi: int physPinToGpio(physPin)",
        // Number of arguments in the function prototytpe
        .argCount = 1,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = rpi_physPinToGpio,
        .funcArg2 = NULL,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
  .funcs[14] =
      { /*----rpi_setPadDrive----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_setPadDrive",
        // Function description
        .funcDesc = "WiringPi: int setPadDrive(group, value)",
        // Number of arguments in the function prototytpe
        .argCount = 2,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = NULL,
        .funcArg2 = rpi_setPadDrive,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
  .funcs[15] =
      { /*----rpi_wiringPiSetup----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_wiringPiSetup",
        // Function description
        .funcDesc = "WiringPi: int wiringPiSetup()",
        // Number of arguments in the function prototytpe
        .argCount = 0,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = rpi_wiringPiSetup,
        .funcArg1 = NULL,
        .funcArg2 = NULL,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
  .funcs[16] =
      { /*----rpi_wiringPiSetupGpio----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_wiringPiSetupGpio",
        // Function description
        .funcDesc = "WiringPi: int wiringPiSetupGpio()",
        // Number of arguments in the function prototytpe
        .argCount = 0,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = rpi_wiringPiSetupGpio,
        .funcArg1 = NULL,
        .funcArg2 = NULL,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
  .funcs[17] =
      { /*----rpi_wiringPiSetupPhys----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_wiringPiSetupPhys",
        // Function description
        .funcDesc = "WiringPi: int wiringPiSetupPhys()",
        // Number of arguments in the function prototytpe
        .argCount = 0,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = rpi_wiringPiSetupPhys,
        .funcArg1 = NULL,
        .funcArg2 = NULL,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
  .funcs[18] =
      { /*----rpi_wiringPiSetupSys----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_wiringPiSetupSys",
        // Function description
        .funcDesc = "WiringPi: int wiringPiSetupSys()",
        // Number of arguments in the function prototytpe
        .argCount = 0,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = rpi_wiringPiSetupSys,
        .funcArg1 = NULL,
        .funcArg2 = NULL,
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
  .funcs[19] = {0}, //last element set all to zero..

  /** Plugin specific constants (add prefix to not risc collide with other modules)
   *  Constants from wiringPi
   */
  /* LOW = 0 */
  .consts[0] = {
        .constName = "rpi_LOW",
        .constDesc = "WiringPi: Signal level LOW (=0)",
        .constValue = LOW
      },
  /* HIGH = 1 */
  .consts[1] = {
        .constName = "rpi_HIGH",
        .constDesc = "WiringPi: Signal level HIGH (=1)",
        .constValue = HIGH
      },
  /* INPUT = 0 */
  .consts[2] = {
        .constName = "rpi_INPUT",
        .constDesc = "WiringPi: Pin mode INPUT (=0)",
        .constValue = INPUT
      },
  /* OUTPUT = 1 */
  .consts[3] = {
        .constName = "rpi_OUTPUT",
        .constDesc = "WiringPi: Pin mode OUTPUT (=1)",
        .constValue = OUTPUT
      },
  /* PWM_OUTPUT = 2 */
  .consts[4] = {
        .constName = "rpi_PWM_OUTPUT",
        .constDesc = "WiringPi: Pin mode PWM_OUTPUT (=2)",
        .constValue = PWM_OUTPUT
      },
  /* GPIO_CLOCK = 3 */
  .consts[5] = {
        .constName = "rpi_GPIO_CLOCK",
        .constDesc = "WiringPi: Pin mode GPIO_CLOCK (=3)",
        .constValue = GPIO_CLOCK
      },
  /* SOFT_PWM_OUTPUT = 4 */
  .consts[6] = {
        .constName = "rpi_SOFT_PWM_OUTPUT",
        .constDesc = "WiringPi: Pin mode SOFT_PWM_OUTPUT (=4)",
        .constValue = SOFT_PWM_OUTPUT
      },
  /* SOFT_TONE_OUTPUT = 5 */
  .consts[7] = {
        .constName = "rpi_SOFT_TONE_OUTPUT",
        .constDesc = "WiringPi: Pin mode SOFT_TONE_OUTPUT (=5)",
        .constValue = SOFT_TONE_OUTPUT
      },
  /* PWM_TONE_OUTPUT = 6 */
  .consts[8] = {
        .constName = "rpi_PWM_TONE_OUTPUT",
        .constDesc = "WiringPi: Pin mode PWM_TONE_OUTPUT (=6)",
        .constValue = PWM_TONE_OUTPUT
      },
  /* PUD_OFF = 0 */
  .consts[9] = {
        .constName = "rpi_PUD_OFF",
        .constDesc = "WiringPi: Pull up/down resistor mode, PUD_OFF (=0)",
        .constValue = PUD_OFF
      },
  /* PUD_DOWN = 1 */
  .consts[10] = {
        .constName = "rpi_PUD_DOWN",
        .constDesc = "WiringPi: Pull up/down resistor mode, PUD_DOWN (=1)",
        .constValue = PUD_DOWN
      },
  /* PUD_UP = 2 */
  .consts[11] = {
        .constName = "rpi_PUD_UP",
        .constDesc = "WiringPi: Pull up/down resistor mode, PUD_UP (=2)",
        .constValue = PUD_UP
      },
  /* PWM_MODE_MS = 0 */
  .consts[12] = {
        .constName = "rpi_PWM_MODE_MS",
        .constDesc = "WiringPi: PWM mode PWM_MODE_MS (=0)",
        .constValue = PWM_MODE_MS
      },
  /* PWM_MODE_BAL = 1 */
  .consts[13] = {
        .constName = "rpi_PWM_MODE_BAL",
        .constDesc = "WiringPi: PWM mode PWM_MODE_BAL (=1)",
        .constValue = PWM_MODE_BAL
      },
   /* WPI_MODE_PINS = 0 */
  .consts[14] = {
        .constName = "rpi_WPI_MODE_PINS",
        .constDesc = "WiringPi: Mode WPI_MODE_PINS (=0)",
        .constValue = WPI_MODE_PINS
      },
  /* WPI_MODE_GPIO = 1 */
  .consts[15] = {
        .constName = "rpi_WPI_MODE_GPIO",
        .constDesc = "WiringPi: Mode WPI_MODE_GPIO (=1)",
        .constValue = WPI_MODE_GPIO
      },
  /* WPI_MODE_GPIO_SYS = 2 */
  .consts[16] = {
        .constName = "rpi_WPI_MODE_GPIO_SYS",
        .constDesc = "WiringPi: Mode WPI_MODE_GPIO_SYS (=2)",
        .constValue = WPI_MODE_GPIO_SYS
      },
  /* WPI_MODE_PIFACE = 3 */
  .consts[17] = {
        .constName = "rpi_WPI_MODE_PHYS",
        .constDesc = "WiringPi: Mode WPI_MODE_PHYS (=3)",
        .constValue = WPI_MODE_PHYS
      },
  /* WPI_MODE_PIFACE = 4 */
  .consts[18] = {
        .constName = "rpi_WPI_MODE_PIFACE",
        .constDesc = "WiringPi: Mode WPI_MODE_PIFACE (=4)",
        .constValue = WPI_MODE_PIFACE
      },
  // End with a NULL
  .consts[19] = {0}

};

ecmc_plugin_register(pluginDataDef);

# ifdef __cplusplus
}
# endif  // ifdef __cplusplus
