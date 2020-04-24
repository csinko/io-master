#ifndef __IOM_COMMAND_H
#define __IOM_COMMAND_H
#ifdef __cplusplus
extern "C" {
#endif

#include "core.h"

//Command sizes (in bytes)
#define IOM_STATE_CMD_GET_SIZE 2
#define IOM_STATE_CMD_SET_CONFIG_SIZE 2
#define IOM_STATE_CMD_SET_DATA_SIZE 2
#define IOM_STATE_CMD_SET_RUN_SIZE 2
#define IOM_STATE_CMD_SET_STOP_SIZE 2

#define IOM_CONFIG_CMD_GET_TARGET_DEVICE_VOLTAGE_SIZE 2
#define IOM_CONFIG_CMD_SET_TARGET_DEVICE_VOLTAGE_SIZE 4
#define IOM_CONFIG_CMD_GET_PIN_PARAMETERS_SIZE 3
#define IOM_CONFIG_CMD_SET_PIN_PARAMETERS_SIZE 4
#define IOM_CONFIG_CMD_GET_DATA_SPEED_SIZE 2
#define IOM_CONFIG_CMD_SET_DATA_SPEED_SIZE 4
#define IOM_CONFIG_CMD_GET_DIFFERENTIAL_MODE_SIZE 3
#define IOM_CONFIG_CMD_SET_DIFFERENTIAL_MODE_SIZE 4
#define IOM_CONFIG_CMD_GET_PIN_MODE_SIZE 3
#define IOM_CONFIG_CMD_SET_PIN_MODE_SIZE 4
#define IOM_CONFIG_CMD_GET_DATA_PARAMETERS_SIZE 3
#define IOM_CONFIG_CMD_SET_DATA_PARAMETERS_SIZE 4
#define IOM_CONFIG_CMD_GET_PIN_LOGIC_LEVELS_SIZE 3
#define IOM_CONFIG_CMD_SET_PIN_LOGIC_LEVELS_SIZE 7

#define IOM_DATA_CMD_SET_DATA_SIZE 4
#define IOM_DAT_CMD_SET_RECEIVE_BYTES_SIZE 3


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

typedef enum {
    IOM_CMD_TYPE_STATE = 0x01,
    IOM_CMD_TYPE_CONFIGURATION = 0x02,
    IOM_CMD_TYPE_DATA = 0x03,
} IOM_CMD_TYPE;

typedef enum {
    IOM_STATE_CMD_GET = 0x00,
    IOM_STATE_CMD_SET_CONFIG = 0x01,
    IOM_STATE_CMD_SET_DATA = 0x02,
    IOM_STATE_CMD_SET_RUN = 0x03,
    IOM_STATE_CMD_SET_STOP = 0x04,
} IOM_STATE_CMD;

typedef enum {
    IOM_CONFIG_CMD_GET_TARGET_DEVICE_VOLTAGE = 0x00,
    IOM_CONFIG_CMD_SET_TARGET_DEVICE_VOLTAGE = 0x01,
    IOM_CONFIG_CMD_GET_PIN_PARAMETERS = 0x02,
    IOM_CONFIG_CMD_SET_PIN_PARAMETERS = 0x03,
    IOM_CONFIG_CMD_GET_DATA_SPEED = 0x04,
    IOM_CONFIG_CMD_SET_DATA_SPEED = 0x05,
    IOM_CONFIG_CMD_GET_DIFFERENTIAL_MODE = 0x06,
    IOM_CONFIG_CMD_SET_DIFFERENTIAL_MODE = 0x07,
    IOM_CONFIG_CMD_GET_PIN_MODE = 0x08,
    IOM_CONFIG_CMD_SET_PIN_MODE = 0x09,
    IOM_CONFIG_CMD_GET_DATA_PARAMETERS = 0x0A,
    IOM_CONFIG_CMD_SET_DATA_PARAMETERS = 0x0B,
    IOM_CONFIG_CMD_GET_PIN_LOGIC_LEVELS = 0x0C,
    IOM_CONFIG_CMD_SET_PIN_LOGIC_LEVELS = 0x0D,
} IOM_CONFIG_CMD;

typedef enum {
    IOM_DATA_CMD_SET_DATA = 0x00,
    IOM_DATA_CMD_SET_RECEIVE_BYTES = 0x01,
} IOM_DATA_CMD;

volatile uint8_t command_buf_queue[COMMAND_BUF_QUEUE_MAX_SIZE];
uint16_t command_buf_in_ptr;
uint16_t command_buf_out_ptr;
volatile uint16_t command_buf_queue_size;

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
