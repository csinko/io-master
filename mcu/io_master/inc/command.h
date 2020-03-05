#ifndef __IOM_COMMAND_H
#define __IOM_COMMAND_H
#ifdef __cplusplus
extern "C" {
#endif

#include "core.h"

typedef enum {
    targetDeviceVolt = 0,
    pin1Params,         
    pin2Params,         
    pin3Params,        
    pin4Params,
    dataSpeed,
    signalMode,    
    pinStates,
} CommandTag;

typedef enum {
    IOM_CS_NEW,
    IOM_CS_STATE,
    IOM_CS_CONFIGURATION,
    IOM_CS_DATA_INC,
    IOM_CS_DATA_LOAD,
    IOM_CS_DATA,
} IOM_COMMAND_STATUS;

uint8_t current_command[128];

IOM_COMMAND_STATUS command_status;
void ProcessCommand(IOM_Output_Buffer buffer);
void ProcessStateCommand(IOM_Output_Buffer buffer);
void ProcessConfigurationCommand(IOM_Output_Buffer buffer);
void ProcessDataCommand(IOM_Output_Buffer buffer);
void RunConfigurationCommand(uint8_t* comm);
IOM_ERROR SetPinParams(uint8_t pinNum, uint8_t* comm);
void SetTargetDeviceVoltage(uint8_t* comm);
void SetSignalMode(uint8_t* comm);
void SetDataSpeed(uint8_t* comm);
IOM_ERROR SetPinStates(uint8_t* comm);
IOM_ERROR GetPinParams(uint8_t pinNum, uint8_t* comm);
void GetTargetDeviceVoltage(uint8_t* comm);
void GetSignalMode(uint8_t* comm);
void GetDataSpeed(uint8_t* comm);



#ifdef __cplusplus
}
#endif
#endif
