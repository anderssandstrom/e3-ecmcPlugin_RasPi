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

/** Optional. 
 *  Will be called once just before ecmc goes into realtime mode.
 *  Return value other than 0 will be considered error.
 **/
int rpi_Construct(void)
{
  printf("Ecmc plugin, "ECMC_RASPI_PLUGIN_NAME", for RasPi GPIO support initiating...\n");
  wiringPiSetup ();  // Use wiringPi pin numbering
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

/** rpi_digitalWrite*/
double rpi_digitalWrite(double pin, double value)
{
  printf("rpi_digitalWrite %lf, %lf.\n",pin,value);
  digitalWrite((int)pin, (int)value);
  return 0;
}

/** rpi_digitalRead*/
double rpi_digitalRead(double pin)
{
  printf("rpi_digitalRead %lf.\n",pin);
  return (double)digitalRead ((int)pin);
}

// Compile data for lib so ecmc now what to use
struct ecmcPluginData pluginDataDef = {
  // Name 
  .name = ECMC_RASPI_PLUGIN_NAME,
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
      { /*----customPlcFunc1----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_digitalWrite",
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
        .funcArg6 = NULL,
        .funcArg6 = NULL
      },
    .funcs[1] =
      { /*----customPlcFunc2----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "rpi_digitalRead",
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
        .funcArg6 = NULL,
        .funcArg6 = NULL
      },
      .funcs[2] = {0} //last element set all to zero..
};

ecmc_plugin_register(pluginDataDef);

# ifdef __cplusplus
}
# endif  // ifdef __cplusplus
