e3-ecmcPlugin_RasPi
======
WiringPi, http://wiringpi.com, RasPi GPIO support for ecmc (https://github.com/icshwi/ecmc).

This module is basically a wrapper to some parts of WiringPi (functions and constants):
- http://wiringpi.com/reference/setup/
- http://wiringpi.com/reference/core-functions/
- http://wiringpi.com/reference/raspberry-pi-specifics/

## ecmc plugins
See this repo for some more doc on how to implement a ecmc plugin: 

https://github.com/anderssandstrom/e3-ecmcPlugin_Advanced

## ecmc plc functions

### Setup functions (http://wiringpi.com/reference/setup/)

#### rpi_wiringPiSetup();
WiringPi: int wiringPiSetup()

#### rpi_wiringPiSetupGpio();
WiringPi: int wiringPiSetupGpio()

#### rpi_wiringPiSetupPhys();
WiringPi: int wiringPiSetupPhys()

#### rpi_wiringPiSetupSys();
WiringPi: int wiringPiSetupSys()

### Core functions (http://wiringpi.com/reference/core-functions/)

#### rpi_digitalWrite(arg0, arg1);
WiringPi: void digitalWrite(pin,level)

#### rpi_digitalRead(arg0);
WiringPi: level=digitalRead(pin)

#### rpi_pinMode(arg0, arg1);
 WiringPi: void pinMode(pin,mode)

#### rpi_pullUpDnControl(arg0, arg1);
WiringPi: void pullUpDnControl(pin,pud)

#### rpi_pwmWrite(arg0, arg1);
WiringPi: void pwmWrite(pin,value)

#### rpi_analogRead(arg0);
WiringPi: value=analogRead(pin)

#### rpi_analogWrite(arg0, arg1);
WiringPi: void analogWrite(pin,value)

### RasPi specifics (http://wiringpi.com/reference/raspberry-pi-specifics/)

#### rpi_digitalWriteByte(arg0);
WiringPi: void digitalWriteByte(value)

#### rpi_pwmSetMode(arg0);
WiringPi: void pwmSetMode(mode)

#### rpi_pwmSetRange(arg0);
WiringPi: void pwmSetRange(range)

#### rpi_pwmSetClock(arg0);
WiringPi: void pwmSetClock(divisor)

#### rpi_piBoardRev();
WiringPi: int piBoardRev()

#### rpi_wpiPinToGpio(arg0);
WiringPi: int wpiPinToGpio(wPiPin)

#### rpi_physPinToGpio(arg0);
WiringPi: int physPinToGpio(physPin)

#### rpi_setPadDrive(arg0, arg1);
WiringPi: int setPadDrive(group, value)

## ecmc plc constants

#### rpi_LOW = 0
WiringPi: Signal level LOW (=0)
#### rpi_HIGH = 1
WiringPi: Signal level HIGH (=1)
#### rpi_INPUT = 0
WiringPi: Pin mode INPUT (=0)
#### rpi_OUTPUT = 1
WiringPi: Pin mode OUTPUT (=1)
#### "rpi_PWM_OUTPUT = 2
WiringPi: Pin mode PWM_OUTPUT (=2)
#### rpi_GPIO_CLOCK = 3
WiringPi: Pin mode GPIO_CLOCK (=3)
#### rpi_SOFT_PWM_OUTPUT = 4
WiringPi: Pin mode SOFT_PWM_OUTPUT (=4)
#### rpi_SOFT_TONE_OUTPUT = 5
WiringPi: Pin mode SOFT_TONE_OUTPUT (=5)
#### rpi_PWM_TONE_OUTPUT = 6
WiringPi: Pin mode PWM_TONE_OUTPUT (=6)
#### rpi_PUD_OFF = 0
WiringPi: Pull up/down resistor mode, PUD_OFF (=0)
#### rpi_PUD_DOWN = 1
WiringPi: Pull up/down resistor mode, PUD_DOWN (=1)
#### rpi_PUD_UP = 2
WiringPi: Pull up/down resistor mode, PUD_UP (=2)
#### "rpi_PWM_MODE_MS = 0
WiringPi: PWM mode PWM_MODE_MS (=0)
#### rpi_PWM_MODE_BAL = 1
WiringPi: PWM mode PWM_MODE_BAL (=1)
#### rpi_WPI_MODE_PINS = 0
WiringPi: Mode WPI_MODE_PINS (=0)
#### rpi_WPI_MODE_GPIO = 1
WiringPi: Mode WPI_MODE_GPIO (=1)
#### rpi_WPI_MODE_GPIO_SYS = 2
WiringPi: Mode WPI_MODE_GPIO_SYS (=2)
#### rpi_WPI_MODE_PHYS = 3
WiringPi: Mode WPI_MODE_PHYS (=3)
#### rpi_WPI_MODE_PIFACE = 4
WiringPi: Mode WPI_MODE_PIFACE (=4)
# Preparations
## Uprading wiring pi for RasPi 4B
```
$ cd /tmp
$ wget https://project-downloads.drogon.net/wiringpi-latest.deb
$ sudo dpkg -i wiringpi-latest.deb
```

## Notes
### Pin numbering
Can be a bit confusing. This module defaults to the wiringPi pin numbering but can be changed with the different setup functions.

### WiringPi deprecated
Seems the library is deprecated.
http://wiringpi.com/wiringpi-deprecated/
However sources are still available at this mirror:
https://github.com/WiringPi/WiringPi
Not sure how to handle this. Since wiringPi is installed in the raspian dist I guess there will be solution.


## ecmc plugin info output (for ecmcPlugin_RasPi)
```
## Load plugin:
epicsEnvSet(ECMC_PLUGIN_FILNAME,"/epics/base-7.0.3.1/require/3.1.2/siteMods/ecmcPlugin_RasPi/master/lib/linux-arm/libecmcPlugin_RasPi.so")
epicsEnvSet(ECMC_PLUGIN_CONFIG,"DBG_PRINT=1")  # Enable printouts from plugin
iocshLoad /epics/base-7.0.3.1/require/3.1.2/siteMods/ecmccfg/plugins/loadPlugin.cmd, "PLUGIN_ID=0,FILE=/epics/base-7.0.3.1/require/3.1.2/siteMods/ecmcPlugin_RasPi/master/lib/linux-arm/libecmcPlugin_RasPi.so,CONFIG='DBG_PRINT=1', REPORT=1"
#==============================================================================
# pluginLoad.cmd
ecmcConfigOrDie "Cfg.LoadPlugin(0,/epics/base-7.0.3.1/require/3.1.2/siteMods/ecmcPlugin_RasPi/master/lib/linux-arm/libecmcPlugin_RasPi.so,DBG_PRINT=1)"
../ecmcPlugin_RasPiApp/src/ecmcPluginRasPi.c/rpi_Construct:67: ConfigStr="DBG_PRINT=1"
Ecmc plugin, ecmcRasPi, for RasPi GPIO support loading...
Note: Defaults to WiringPi pin numbering if not another setup function is called.
2020/03/29 12:19:56.366 OK
ecmcEpicsEnvSetCalcTenary("ECMC_PLUGIN_REPORT", "1>0","","#")
ecmcConfigOrDie "Cfg.ReportPlugin(0)"
Plugin info: 
  Index                = 0
  Name                 = ecmcRasPi
  Description          = ecmc plugin for GPIO access on RasPi (wrapper to WiringPi)
  Option description   = DBG_PRINT=1/0 : Enables/disables printouts from plugin.
  Filename             = /epics/base-7.0.3.1/require/3.1.2/siteMods/ecmcPlugin_RasPi/master/lib/linux-arm/libecmcPlugin_RasPi.so
  Config string        = DBG_PRINT=1
  Version              = 1
  Interface version    = 512 (ecmc = 512)
     max plc funcs     = 64
     max plc func args = 10
     max plc consts    = 64
  Construct func       = @0xb5014224
  Enter realtime func  = @0xb5014370
  Exit realtime func   = @0xb5014f3c
  Realtime func        = @0xb50141c0
  Destruct func        = @0xb5014308
  dlhandle             = @0x1f00f18
  Plc functions:
    funcs[00]:
      Name       = "rpi_digitalWrite(arg0, arg1);"
      Desc       = WiringPi: void digitalWrite(pin,level)
      Arg count  = 2
      func       = @0xb50145ac
    funcs[01]:
      Name       = "rpi_digitalRead(arg0);"
      Desc       = WiringPi: level=digitalRead(pin)
      Arg count  = 1
      func       = @0xb501465c
    funcs[02]:
      Name       = "rpi_pinMode(arg0, arg1);"
      Desc       = WiringPi: void pinMode(pin,mode)
      Arg count  = 2
      func       = @0xb50146f8
    funcs[03]:
      Name       = "rpi_pullUpDnControl(arg0, arg1);"
      Desc       = WiringPi: void pullUpDnControl(pin,pud)
      Arg count  = 2
      func       = @0xb50147a4
    funcs[04]:
      Name       = "rpi_pwmWrite(arg0, arg1);"
      Desc       = WiringPi: void pwmWrite(pin,value)
      Arg count  = 2
      func       = @0xb5014854
    funcs[05]:
      Name       = "rpi_analogRead(arg0);"
      Desc       = WiringPi: value=analogRead(pin)
      Arg count  = 1
      func       = @0xb5014904
    funcs[06]:
      Name       = "rpi_analogWrite(arg0, arg1);"
      Desc       = WiringPi: void analogWrite(pin,value)
      Arg count  = 2
      func       = @0xb50149a0
    funcs[07]:
      Name       = "rpi_digitalWriteByte(arg0);"
      Desc       = WiringPi: void digitalWriteByte(value)
      Arg count  = 1
      func       = @0xb5014a4c
    funcs[08]:
      Name       = "rpi_pwmSetMode(arg0);"
      Desc       = WiringPi: void pwmSetMode(mode)
      Arg count  = 1
      func       = @0xb5014aec
    funcs[09]:
      Name       = "rpi_pwmSetRange(arg0);"
      Desc       = WiringPi: void pwmSetRange(range)
      Arg count  = 1
      func       = @0xb5014b8c
    funcs[10]:
      Name       = "rpi_pwmSetClock(arg0);"
      Desc       = WiringPi: void pwmSetClock(divisor)
      Arg count  = 1
      func       = @0xb5014c2c
    funcs[11]:
      Name       = "rpi_piBoardRev();"
      Desc       = WiringPi: int piBoardRev()
      Arg count  = 0
      func       = @0xb5014ccc
    funcs[12]:
      Name       = "rpi_wpiPinToGpio(arg0);"
      Desc       = WiringPi: int wpiPinToGpio(wPiPin)
      Arg count  = 1
      func       = @0xb5014d54
    funcs[13]:
      Name       = "rpi_physPinToGpio(arg0);"
      Desc       = WiringPi: int physPinToGpio(physPin)
      Arg count  = 1
      func       = @0xb5014df0
    funcs[14]:
      Name       = "rpi_setPadDrive(arg0, arg1);"
      Desc       = WiringPi: int setPadDrive(group, value)
      Arg count  = 2
      func       = @0xb5014e8c
    funcs[15]:
      Name       = "rpi_wiringPiSetup();"
      Desc       = WiringPi: int wiringPiSetup()
      Arg count  = 0
      func       = @0xb50143dc
    funcs[16]:
      Name       = "rpi_wiringPiSetupGpio();"
      Desc       = WiringPi: int wiringPiSetupGpio()
      Arg count  = 0
      func       = @0xb5014450
    funcs[17]:
      Name       = "rpi_wiringPiSetupPhys();"
      Desc       = WiringPi: int wiringPiSetupPhys()
      Arg count  = 0
      func       = @0xb50144c4
    funcs[18]:
      Name       = "rpi_wiringPiSetupSys();"
      Desc       = WiringPi: int wiringPiSetupSys()
      Arg count  = 0
      func       = @0xb5014538
  Plc constants:
    consts[00]:
      Name     = "rpi_LOW" = 0.000
      Desc     = WiringPi: Signal level LOW (=0)
    consts[01]:
      Name     = "rpi_HIGH" = 1.000
      Desc     = WiringPi: Signal level HIGH (=1)
    consts[02]:
      Name     = "rpi_INPUT" = 0.000
      Desc     = WiringPi: Pin mode INPUT (=0)
    consts[03]:
      Name     = "rpi_OUTPUT" = 1.000
      Desc     = WiringPi: Pin mode OUTPUT (=1)
    consts[04]:
      Name     = "rpi_PWM_OUTPUT" = 2.000
      Desc     = WiringPi: Pin mode PWM_OUTPUT (=2)
    consts[05]:
      Name     = "rpi_GPIO_CLOCK" = 3.000
      Desc     = WiringPi: Pin mode GPIO_CLOCK (=3)
    consts[06]:
      Name     = "rpi_SOFT_PWM_OUTPUT" = 4.000
      Desc     = WiringPi: Pin mode SOFT_PWM_OUTPUT (=4)
    consts[07]:
      Name     = "rpi_SOFT_TONE_OUTPUT" = 5.000
      Desc     = WiringPi: Pin mode SOFT_TONE_OUTPUT (=5)
    consts[08]:
      Name     = "rpi_PWM_TONE_OUTPUT" = 6.000
      Desc     = WiringPi: Pin mode PWM_TONE_OUTPUT (=6)
    consts[09]:
      Name     = "rpi_PUD_OFF" = 0.000
      Desc     = WiringPi: Pull up/down resistor mode, PUD_OFF (=0)
    consts[10]:
      Name     = "rpi_PUD_DOWN" = 1.000
      Desc     = WiringPi: Pull up/down resistor mode, PUD_DOWN (=1)
    consts[11]:
      Name     = "rpi_PUD_UP" = 2.000
      Desc     = WiringPi: Pull up/down resistor mode, PUD_UP (=2)
    consts[12]:
      Name     = "rpi_PWM_MODE_MS" = 0.000
      Desc     = WiringPi: PWM mode PWM_MODE_MS (=0)
    consts[13]:
      Name     = "rpi_PWM_MODE_BAL" = 1.000
      Desc     = WiringPi: PWM mode PWM_MODE_BAL (=1)
    consts[14]:
      Name     = "rpi_WPI_MODE_PINS" = 0.000
      Desc     = WiringPi: Mode WPI_MODE_PINS (=0)
    consts[15]:
      Name     = "rpi_WPI_MODE_GPIO" = 1.000
      Desc     = WiringPi: Mode WPI_MODE_GPIO (=1)
    consts[16]:
      Name     = "rpi_WPI_MODE_GPIO_SYS" = 2.000
      Desc     = WiringPi: Mode WPI_MODE_GPIO_SYS (=2)
    consts[17]:
      Name     = "rpi_WPI_MODE_PHYS" = 3.000
      Desc     = WiringPi: Mode WPI_MODE_PHYS (=3)
    consts[18]:
      Name     = "rpi_WPI_MODE_PIFACE" = 4.000
      Desc     = WiringPi: Mode WPI_MODE_PIFACE (=4)

2020/03/29 12:19:56.368 OK

```

# Plugin interface description
The interface is defined in the structure ecmcPluginData in ecmcPluginDefs.h:
```
struct ecmcPluginData {
  // Name 
  const char *name;
  // Description
  const char *desc;
  // Plugin version
  int version;
  // ECMC_PLUG_VERSION_MAGIC
  int ifVersion;
  // Optional construct func, called once at load
  int (*constructFnc)(void);
  // Optional destruct func, called once at unload
  void (*destructFnc)(void);
  // Optional func that will be called once just before enter realtime mode
  int (*realtimeEnterFnc)(void*);
  // Optional func that will be called once just before exit realtime mode
  int (*realtimeExitFnc)(void);
  // Optional func that will be called each realtime cycle
  int (*realtimeFnc)(int);
  // Allow max ECMC_PLUGIN_MAX_PLC_FUNC_COUNT custom plc functions
  struct ecmcOnePlcFunc  funcs[ECMC_PLUGIN_MAX_PLC_FUNC_COUNT];
  // Allow max ECMC_PLUGIN_MAX_PLC_CONST_COUNT custom plc constants
  struct ecmcOnePlcConst consts[ECMC_PLUGIN_MAX_PLC_CONST_COUNT];
};
```
## Callbacks:
All callbacks are optional. If the callbacks are not used then set the func pointer to NULL 
("ecmcPluginData.*Fnc=NULL").

Example:
```
ecmcPluginData.destructFnc=NULL
ecmcPluginData.constructFnc=NULL
...
```

### int  constructFnc(), optional
This callback is called once when the plugin is loaded into ecmc. This is a good place to put code for any initialization needed in the plugin module.

Return value: 0 for success or error code.

### void destructFnc(), optional
This callback is called once when the plugin is unloaded. This is a good place to put cleanup code needed by the plugin module.

### int realtimeFnc(int ecmcErrorId), optional
This callback is called once in each realtime loop (sync to ecmc). This is a good place to put any cyclic processing needed by the plugin module.

Parameters: ecmcErrorId: reflects the current errorstate of ecmc.

Return value: 0 for success or error code.

### int realtimeEnterFnc(void* ecmcRefs), optional
This callback is called once just before ecmc enters realtime mode (starts rt-thread). This is a good place to make any prepartions needed before cyclic processing starts.

Parameters: ecmcRefs: ref to ecmcdata that can be cast to ecmcPluginDataRefs
```
struct ecmcPluginDataRefs {
  double sampleTimeMS;
  ecmcAsynPortDriver *ecmcAsynPort;
};
```
Return value: 0 for success or error code.

### int realtimeExitFnc(), optional
This callback is called once just before ecmc exits realtime mode (exits rt-thread).

Return value: 0 for success or error code.

### Example:
```
// Compile data for lib so ecmc now what to use
struct ecmcPluginData pluginDataDef = {
  // Name 
  .name = "ecmcExamplePlugin",
  // Description
  .desc = "Advanced example with use of asynport obj.",
  // Plugin version
  .version = ECMC_EXAMPLE_PLUGIN_VERSION,
  // ECMC_PLUG_VERSION_MAGIC
  .ifVersion = ECMC_PLUG_VERSION_MAGIC, 
  // Optional construct func, called once at load. NULL if not definded.
  .constructFnc = adv_exampleConstruct,
  // Optional destruct func, called once at unload. NULL if not definded.
  .destructFnc = adv_exampleDestruct,
  // Optional func that will be called each rt cycle. NULL if not definded.
  .realtimeFnc = adv_exampleRealtime,
  // Optional func that will be called once just before enter realtime mode
  .realtimeEnterFnc = adv_exampleEnterRT,
  // Optional func that will be called once just before exit realtime mode
  .realtimeExitFnc = adv_exampleExitRT,
...
...

```
## PLC functions:
Custom ecmc PLC-functions can be implemented in plugins. Currentlly the interface supports implementation of up to 64 plc functions. Each plc function needs to be defined by the struct "ecmcOnePlcFunc":
```
struct ecmcOnePlcFunc {
  // Function name (this is the name you use in ecmc plc-code)
  const char *funcName;
  // Function description
  const char *funcDesc;
  /**
   * 7 different prototypes allowed (only doubles since reg in plc).
   * Only one funcArg<argCount> func shall be assigned the rest set to NULL 
   **/
  double (*funcArg0)();
  double (*funcArg1)(double);
  double (*funcArg2)(double,double);
  double (*funcArg3)(double,double,double);
  double (*funcArg4)(double,double,double,double);
  double (*funcArg5)(double,double,double,double,double);
  double (*funcArg6)(double,double,double,double,double,double);
};

```
Example:
```
.funcs[0] =      
      { /*----customPlcFunc1----*/
        // Function name (this is the name you use in ecmc plc-code)
        .funcName = "adv_plugin_func_1",
        // Function description
        .funcDesc = "Multiply arg0 with arg1.",
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg<argCount> one func shall be assigned the rest set to NULL.
        **/
        .funcArg0 = NULL,
        .funcArg1 = NULL,
        .funcArg2 = adv_customPlcFunc1, // Func 1 has 2 args
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg5 = NULL,
        .funcArg6 = NULL
      },
```
Note: Only the first non NULL function will be used (starting from funcArg0...)

## PLC constants
Custom ecmc PLC-constants can be implemented in plugins. Currentlly the interface supports implementation of up to 64 plc constants. Each plc constant needs to be defined by the struct "ecmcOnePlcFunc":
```
struct ecmcOnePlcConst{
  const char *constName;
  const char *constDesc;
  double      constValue;
};

```
Example:
```
.consts[0] = {
        .constName = "adv_CONST_1",
        .constDesc = "Test constant \"adv_CONST_1\" = 1.234567890",
        .constValue = 1.234567890,
      },
```
## Dependencies:

All needed headers are available in ecmc (https://github.com/icshwi/ecmc)

### Simple plugins 

Only the "ecmcPluginDefs.h" header is needed.

### Advanced plugins 
When using the "void* ecmcRefs" param (cast to ecmcPluginDataRefs)in the "realtimeEnterFnc()" these additional headers are needed:
* from ecmc:
  * ecmcAsynPortDriver.h
  * ecmcAsynDataItem.h
  * ecmcAsynPortDriverUtils.h
  * ecmcDefinitions.h
  * ecmcErrorsList.h
  * ecmcPluginDataRefs.h
* from asyn:
  * asynPortDriver.h
  
Note: This define is needed in the plugin sources:
```
#define ECMC_IS_PLUGIN
```


