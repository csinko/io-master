#ifndef __IOM_COMMAND_H
#define __IOM_COMMAND_H
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    targetDeviceVolt,
    pin1Params,         
    pin2Params,         
    pin3Params,        
    pin4Params,
    dataSpeed,
    signalMode,    
} CommandTag;

void RunCommand(uint8_t* comm);
void SetPinParams(uint8_t pinNum, uint8_t* comm);
void SetTargetDeviceVolt(uint8_t* comm);
void SetSignalMode(uint8_t* comm);
void SetDataSpeed(uint8_t* comm);
void GetPinParams(uint8_t pinNum, uint8_t* comm);
void GetTargetDeviceVolt(uint8_t* comm);
void GetSignalMode(uint8_t* comm);
void GetDataSpeed(uint8_t* comm);



#ifdef __cplusplus
}
#endif
#endif
