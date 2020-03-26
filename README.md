e3-ecmcPlugin_RasPi
======
ESS Site-specific EPICS module : ecmcPlugin_RasPi
RasPi GPIO support for ecmc.

# Preparations
## Uprading wiring pi for RasPi 4B
```
$ cd /tmp
$ wget https://project-downloads.drogon.net/wiringpi-latest.deb
$ sudo dpkg -i wiringpi-latest.deb
```


## Notes
Uses wiringPI pin numbering
This is just for fun....

SOurces at mirror (original seems down):
https://github.com/WiringPi/WiringPi




## ecmc plugin info output
## Load plugin:
#require ecmcPlugin_Simple master # do not require then loaded twice..
ecmcConfigOrDie "Cfg.LoadPlugin(/epics/base-7.0.3.1/require/3.1.2/siteMods/ecmcPlugin_RasPi/master/lib/linux-arm/libecmcPlugin_RasPi.so)"
Ecmc plugin, ecmcRasPi, for RasPi GPIO support initiating...
Note: Defaults to WiringPi pin numbering if not another setup function is called.
Plugin info: 
  Name                 = ecmcRasPi
  Description          = ecmc plugin for GPIO access on RasPi (wrapper to WiringPi)
  Version              = 1
  Interface version    = 512 (ecmc = 512)
      max plc funcs    = 64
      max plc consts   = 64
  Construct func       = @0xb5bcd108
  Enter realtime func  = @0xb5bcd160
  Exit realtime func   = @0xb5bcd144
  Realtime func        = @0xb5bcd100
  Destruct func        = @0xb5bcd134
  dlhandle             = @0xa33ef8
  Plc functions:
    funcs[00]:
      Name       = "rpi_digitalWrite(arg0, arg1);"
      Desc       = WiringPi: void digitalWrite(pin,level)
      Arg count  = 2
      func       = @0xb5bcd230
    funcs[01]:
      Name       = "rpi_digitalRead(arg0);"
      Desc       = WiringPi: level=digitalRead(pin)
      Arg count  = 1
      func       = @0xb5bcd294
    funcs[02]:
      Name       = "rpi_pinMode(arg0, arg1);"
      Desc       = WiringPi: void pinMode(pin,mode)
      Arg count  = 2
      func       = @0xb5bcd2e4
    funcs[03]:
      Name       = "rpi_pullUpDnControl(arg0, arg1);"
      Desc       = WiringPi: void pullUpDnControl(pin,pud)
      Arg count  = 2
      func       = @0xb5bcd344
    funcs[04]:
      Name       = "rpi_pwmWrite(arg0, arg1);"
      Desc       = WiringPi: void pwmWrite(pin,value)
      Arg count  = 2
      func       = @0xb5bcd3a4
    funcs[05]:
      Name       = "rpi_analogRead(arg0);"
      Desc       = WiringPi: value=analogRead(pin)
      Arg count  = 1
      func       = @0xb5bcd404
    funcs[06]:
      Name       = "rpi_analogWrite(arg0, arg1);"
      Desc       = WiringPi: void analogWrite(pin,value)
      Arg count  = 2
      func       = @0xb5bcd454
    funcs[07]:
      Name       = "rpi_digitalWriteByte(arg0);"
      Desc       = WiringPi: void digitalWriteByte(value)
      Arg count  = 1
      func       = @0xb5bcd4b4
    funcs[08]:
      Name       = "rpi_pwmSetMode(arg0);"
      Desc       = WiringPi: void pwmSetMode(mode)
      Arg count  = 1
      func       = @0xb5bcd50c
    funcs[09]:
      Name       = "rpi_pwmSetRange(arg0);"
      Desc       = WiringPi: void pwmSetRange(range)
      Arg count  = 1
      func       = @0xb5bcd564
    funcs[10]:
      Name       = "rpi_pwmSetClock(arg0);"
      Desc       = WiringPi: void pwmSetClock(divisor)
      Arg count  = 1
      func       = @0xb5bcd5bc
    funcs[11]:
      Name       = "rpi_piBoardRev();"
      Desc       = WiringPi: int piBoardRev()
      Arg count  = 0
      func       = @0xb5bcd614
    funcs[12]:
      Name       = "rpi_wpiPinToGpio(arg0);"
      Desc       = WiringPi: int wpiPinToGpio(wPiPin)
      Arg count  = 1
      func       = @0xb5bcd650
    funcs[13]:
      Name       = "rpi_physPinToGpio(arg0);"
      Desc       = WiringPi: int physPinToGpio(physPin)
      Arg count  = 1
      func       = @0xb5bcd6a0
    funcs[14]:
      Name       = "rpi_setPadDrive(arg0, arg1);"
      Desc       = WiringPi: int setPadDrive(group, value)
      Arg count  = 2
      func       = @0xb5bcd6f0
    funcs[15]:
      Name       = "rpi_wiringPiSetup();"
      Desc       = WiringPi: int wiringPiSetup()
      Arg count  = 0
      func       = @0xb5bcd190
    funcs[16]:
      Name       = "rpi_wiringPiSetupGpio();"
      Desc       = WiringPi: int wiringPiSetupGpio()
      Arg count  = 0
      func       = @0xb5bcd1b8
    funcs[17]:
      Name       = "rpi_wiringPiSetupPhys();"
      Desc       = WiringPi: int wiringPiSetupPhys()
      Arg count  = 0
      func       = @0xb5bcd1e0
    funcs[18]:
      Name       = "rpi_wiringPiSetupSys();"
      Desc       = WiringPi: int wiringPiSetupSys()
      Arg count  = 0
      func       = @0xb5bcd208
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

2020/03/26 12:14:19.077 OK





# Old below.. Keep for later use


Example illustrating a plugin for use with ecmc.
Shows use of callbacks and implementation, custom ecmc plc-functions and how to access the
ecmcAsynPort object.

# Interface
The interface is defined in the structure ecmcPluginData in ecmcPluginDefs.h:
```
struct ecmcPluginData {
  // Name 
  const char *name;
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
  // Allow max ECMC_PLUGIN_MAX_FUNC_COUNT custom plc functions
  struct ecmcOnePlcFunc funcs[ECMC_PLUGIN_MAX_PLC_FUNC_COUNT];
};
```
## Callbacks:

### int  constructFnc(), optional
This callback is called once when the plugin is loaded into ecmc. This is a good place to put code for any initialization needed in the plugin module.
If not used then set "ecmcPluginData.constructFnc=NULL".

Return value: 0 for success or error code.

### void destructFnc(), optional
This callback is called once when the plugin is unloaded. This is a good place to put cleanup code needed by the plugin module.
If not used then set "ecmcPluginData.destructFnc=NULL".

### int realtimeFnc(int ecmcErrorId), optional
This callback is called once in each realtime loop (sync to ecmc). This is a good place to put any cyclic processing needed by the plugin module.
If not used then set "ecmcPluginData.realtimeFnc=NULL".

Parameters: ecmcErrorId: reflects the current errorstate of ecmc.

Return value: 0 for success or error code.

### int realtimeEnterFnc(void* ecmcRefs), optional
This callback is called once just before ecmc enters realtime mode (starts rt-thread). This is a good place to make any prepartions needed before cyclic processing starts.
If not used then set "ecmcPluginData.enterRealTimeFnc=NULL".

Parameters: ecmcRefs: ref to ecmcdata that can be cast to ecmcPluginDataRefs
```
struct ecmcPluginDataRefs {
  double sampleTimeMS;
  ecmcAsynPortDriver *ecmcAsynPort;
};
```
IMPORTANT! This structure is only valid the time between calls of "realtimeEnterFnc()" and "realtimeExitFnc()".

Return value: 0 for success or error code.

### int realtimeExitFnc(), optional
This callback is called once just before ecmc exits realtime mode (exits rt-thread).
If not used then set "ecmcPluginData.exitRealTimeFnc=NULL".

Return value: 0 for success or error code.

### Example:
```
struct ecmcPluginData pluginDataDef = {
  // Name 
  .name = "ecmcExamplePlugin",
  // Plugin version
  .version = ECMC_EXAMPLE_PLUGIN_VERSION,
  // ECMC_PLUG_VERSION_MAGIC
  .ifVersion = ECMC_PLUG_VERSION_MAGIC, 
  // Optional construct func, called once at load. NULL if not definded.
  .constructFnc = exampleConstruct,
  // Optional destruct func, called once at unload. NULL if not definded.
  .destructFnc = exampleDestruct,
  // Optional func that will be called each rt cycle. NULL if not definded.
  .realtimeFnc = exampleRealtime,
  // Optional func that will be called once just before enter realtime mode
  .realtimeEnterFnc = exampleEnterRT,
  // Optional func that will be called once just before exit realtime mode
  .realtimeExitFnc = exampleExitRT,
...
...

```
## PLC functions:
Custom ecmc PLC-functions can be implemnted in plugins. Currentlly the interface supports implementation of up to 32 plc functions. Each plc function needs to be defined by the struct "ecmcOnePlcFunc":
```
struct ecmcOnePlcFunc {
  // Function name (this is the name you use in ecmc plc-code)
  const char *funcName;
  // Number of arguments in the function prototytpe
  int argCount;
  /**
   * 7 different prototypes allowed (only doubles since reg in plc).
   * Only funcArg${argCount} func shall be assigned the rest set to NULL
   * funcArg${argCount}. These need to match. 
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
        .funcName = "ex_plugin_func_1",
        // Number of arguments in the function prototytpe
        .argCount = 2,
        /**
        * 7 different prototypes allowed (only doubles since reg in plc).
        * Only funcArg${argCount} func shall be assigned the rest set to NULL.
        * funcArg${argCount}. These need to match. 
        **/
        .funcArg0 = NULL,
        .funcArg1 = NULL,
        .funcArg2 = customPlcFunc1, // Func 1 has 2 args
        .funcArg3 = NULL,
        .funcArg4 = NULL,
        .funcArg6 = NULL,
        .funcArg6 = NULL
      },
  
```
Note: Only the funcArg${argCount} pointer will be used, so set the rest to NULL.

## Dependencies:

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
