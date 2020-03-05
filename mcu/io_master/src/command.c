#include "core.h"
#include "command.h"
#include "mcu_conf.h"
#include "stm32h7xx_hal.h"
#include "uart.h"
#include <string.h>
#include <stdlib.h>
#include "dac.h"
#include "iopin.h"
#include "data.h"

uint8_t current_command[128] = {0};
IOM_COMMAND_STATUS command_status = IOM_CS_NEW;

void ProcessCommand(IOM_Output_Buffer buffer) {
    switch (command_status) {
        case IOM_CS_NEW:
            if (buffer.length != 2) {
                //Garbage
                free(buffer.data);
                uint8_t* pData = malloc(2);
                UARTQueueRXData(pData, 2);
                return;
            }
            current_command[0] = *(buffer.data);
            switch(current_command[0]) {
                case 1:
                    ProcessStateCommand(buffer);
                    return;
                case 2:
                    ProcessConfigurationCommand(buffer);
                    return;
                case 3:
                    ProcessDataCommand(buffer); 
                    return;
                default:
                    free(buffer.data);
                    uint8_t* pData = malloc(2);
                    UARTQueueRXData(pData, 2);
                    return;
            }
            break;
        case IOM_CS_STATE:
            ProcessStateCommand(buffer);
            break;
        case IOM_CS_CONFIGURATION:
            ProcessConfigurationCommand(buffer);
            break;
        case IOM_CS_DATA:
        case IOM_CS_DATA_INC:
        case IOM_CS_DATA_LOAD:
            ProcessDataCommand(buffer);
            break;
        default:
            free(buffer.data);
            uint8_t* pData = malloc(2);
            UARTQueueRXData(pData, 2);
            return;
    }
}

void ProcessConfigurationCommand(IOM_Output_Buffer buffer) {
    if(command_status == IOM_CS_NEW) {
        current_command[1] = *(buffer.data + 1);
        free(buffer.data);
        uint8_t commTag = (current_command[1] & 0b01110000) >> 4;
        uint8_t bytesToGet = 1;
        if (commTag > 0 && commTag < 5) {
            command_status = IOM_CS_CONFIGURATION;
            bytesToGet = 4;
        } else if (commTag == 0) {
            command_status = IOM_CS_CONFIGURATION;
            bytesToGet = 2;
        }
        uint8_t* pData = malloc(bytesToGet);
        UARTQueueRXData(pData, bytesToGet);
        return;
    }
    if (command_status == IOM_CS_CONFIGURATION) {
       if (buffer.length > 4) {
           //Garbage
           free(buffer.data);
           uint8_t* pData = malloc(2);
           UARTQueueRXData(pData, 2);
           return;
       } 
       memcpy(&current_command[2], buffer.data, buffer.length);
       free(buffer.data);
       command_status = IOM_CS_NEW;
       RunConfigurationCommand(&current_command[1]);
       uint8_t* pData = malloc(2);
       UARTQueueRXData(pData, 2);
       return;
    }
}

void ProcessDataCommand(IOM_Output_Buffer buffer) {
    uint8_t* pData;
    switch(command_status) {
        case IOM_CS_NEW:
            current_command[1] = *(buffer.data + 1);
            free(buffer.data);
            switch(current_command[1]) {
                case 1:
                    command_status = IOM_CS_DATA_INC;
                    pData = malloc(1);
                    UARTQueueRXData(pData, 1);
                    return;
                case 2:
                    command_status = IOM_CS_DATA;
                    pData = malloc(1);
                    UARTQueueRXData(pData, 1);
                    return;
                default:
                //Garbage
                    pData = malloc(2);
                    UARTQueueRXData(pData, 2);
                    return;
            }
            break;
        case IOM_CS_DATA_INC:
            if (buffer.length != 1) {
                //Garbage
                free(buffer.data);
                pData = malloc(2);
                UARTQueueRXData(pData, 2);
                return;
            }
            command_status = IOM_CS_DATA_LOAD;
            pData = malloc(*(buffer.data));
            free(buffer.data);
            UARTQueueRXData(pData, 1);
            return;
        case IOM_CS_DATA:
            if (buffer.length != 1) {
                //Garbage
                free(buffer.data);
                pData = malloc(2);
                UARTQueueRXData(pData, 2);
            }
            command_status = IOM_CS_NEW;
            dataToReceive = *(buffer.data);
            free(buffer.data);
            pData = malloc(2);
            UARTQueueRXData(pData, 2);
            return;
        case IOM_CS_DATA_LOAD:
            command_status = IOM_CS_NEW;
            *(buffer.data) = 0b10101010;
            QueueOutputDataToSend(buffer.data, buffer.length, 2);
            free(buffer.data);
            pData = malloc(2);
            UARTQueueRXData(pData, 2);
            return;
        default:
            //Garbage
            command_status = IOM_CS_NEW;
            free(buffer.data);
            pData = malloc(2);
            UARTQueueRXData(pData, 2);
            return;
    }
}

void ProcessStateCommand(IOM_Output_Buffer buffer) {
    current_command[1] = *(buffer.data + 1);
    free(buffer.data);
    switch(current_command[1]) {
        case 1:
            IOMState = IOM_STATE_CONF;
            break;
        case 2:
            IOMState = IOM_STATE_READY;
            break;
        case 3:
            IOMState = IOM_STATE_BUSY;
            break;
        case 4:
            IOMState = IOM_STATE_READY;
            break;
        default:
            break;
    }
    command_status = IOM_CS_NEW;
    uint8_t* pData = malloc(2);
    UARTQueueRXData(pData, 2);
    return;
}


void RunConfigurationCommand(uint8_t* comm)
{
    uint8_t readWrite = (*(comm) & 0b10000000) >> 7;
    uint8_t commTag = (*(comm) & 0b01110000) >> 4;

    if(readWrite != 0)
    {
        //Set cases
        switch(commTag)
        {
            case 0:
                SetTargetDeviceVoltage(comm);
                break;
            case pin1Params:
            case pin2Params:
            case pin3Params:
            case pin4Params:
                SetPinParams(commTag, comm);
                break;
            case dataSpeed:
                SetDataSpeed(comm);
                break;
            case signalMode:
                SetSignalMode(comm);
                break;
            case pinStates:
                SetPinStates(comm);
            default:
                //error case
                break;
        }        
    }
    else
    {
        //Get cases
        switch(commTag)
        {
            case targetDeviceVolt:
                GetTargetDeviceVoltage(comm);
                break;
            case pin1Params:
            case pin2Params:
            case pin3Params:
            case pin4Params:
                GetPinParams(commTag, comm);
                break;
            case dataSpeed:
                GetDataSpeed(comm);
                break;
            case signalMode:
                GetSignalMode(comm);
                break;
            default:
                //error case
                break;
        }        
    }
    
    return;
}

IOM_ERROR SetPinParams(uint8_t pinNum, uint8_t* comm)
{
    uint8_t pullDown = comm[0] & 0b0001;
    uint8_t pullUp = (comm[0] & 0b0010) >> 1;
    //If pullDown and pullUp are enabled, then board is in tristate mode
    uint8_t triState = pullDown & pullUp;
    uint16_t VH = (comm[1]<<8) | comm[2];
    uint16_t VL = (comm[3]<<8) | comm[4];

    GPIO_TypeDef* pullDownPort = 0;
    uint16_t pullDownPin = 0;
    GPIO_TypeDef* pullUpPort = 0;
    uint16_t pullUpPin = 0;

    GPIO_TypeDef* triStatePort = 0;
    uint16_t triStatePin = 0;

    switch(pinNum) {
        case 1:
            pullDownPort = IO_1_PD_N_GPIO_Port;
            pullDownPin = IO_1_PD_N_Pin;
            pullUpPort = IO_1_PU_GPIO_Port;
            pullUpPin = IO_1_PU_Pin;
            triStatePort = IO_1_TRIS_N_GPIO_Port;
            triStatePin = IO_1_TRIS_N_Pin;
            break;
        case 2:
            pullDownPort = IO_2_PD_N_GPIO_Port;
            pullDownPin = IO_2_PD_N_Pin;
            pullUpPort = IO_2_PU_GPIO_Port;
            pullUpPin = IO_2_PU_Pin;
            triStatePort = IO_2_TRIS_N_GPIO_Port;
            triStatePin = IO_2_TRIS_N_Pin;
            break;
        case 3:
            pullDownPort = IO_3_PD_N_GPIO_Port;
            pullDownPin = IO_3_PD_N_Pin;
            pullUpPort = IO_3_PU_GPIO_Port;
            pullUpPin = IO_3_PU_Pin;
            triStatePort = IO_3_TRIS_N_GPIO_Port;
            triStatePin = IO_3_TRIS_N_Pin;
            break;
        case 4:
            pullDownPort = IO_4_PD_N_GPIO_Port;
            pullDownPin = IO_4_PD_N_Pin;
            pullUpPort = IO_4_PU_GPIO_Port;
            pullUpPin = IO_4_PU_Pin;
            triStatePort = IO_4_TRIS_N_GPIO_Port;
            triStatePin = IO_4_TRIS_N_Pin;
            break;
        default:
            return IOM_ERROR_INVALID;
    }

    if (triState != 0) {
        //Dsiable the Pulldown and Pullup Pins
        HAL_GPIO_WritePin(pullDownPort, pullDownPin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(pullUpPort, pullUpPin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(triStatePort, triStatePin, GPIO_PIN_RESET);

    } else if (pullDown != 0) {
        HAL_GPIO_WritePin(triStatePort, triStatePin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(pullUpPort, pullUpPin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(pullDownPort, pullDownPin, GPIO_PIN_RESET);

    } else if (pullUp != 0) {
        HAL_GPIO_WritePin(triStatePort, triStatePin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(pullDownPort, pullDownPin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(pullUpPort, pullUpPin, GPIO_PIN_SET);
    } else if (pullDown == 0 && pullUp == 0 && triState == 0) {
        HAL_GPIO_WritePin(triStatePort, triStatePin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(pullDownPort, pullDownPin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(pullUpPort, pullUpPin, GPIO_PIN_RESET);
    } else {
        return IOM_ERROR_INVALID;
    }

    WriteRegExtDAC(IOM_REGISTER_HIGH, pinNum, VH);
    WriteRegExtDAC(IOM_REGISTER_LOW, pinNum, VL);
    return IOM_OK;

}

void SetTargetDeviceVoltage(uint8_t* comm)
{
    uint16_t voltage = (comm[1]<<8) | comm[2];
    WriteMCUDAC(1, voltage);
}

void SetSignalMode(uint8_t* comm)
{
    uint8_t pin12Mode = comm[0] & 0x01;
    uint8_t pin34Mode = (comm[0] >> 1) & 0x01;
    #ifdef IOM_8_IO_PINS
    uint8_t pin56Mode = (comm[0] >> 2) & 0x01;
    uint8_t pin78Mode = (comm[0] >> 3) & 0x01;
    #endif

    HAL_GPIO_WritePin(IO_1_2_DIFF_GPIO_Port, IO_1_2_DIFF_Pin, (pin12Mode != 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IO_3_4_DIFF_GPIO_Port, IO_3_4_DIFF_Pin, (pin34Mode != 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    #ifdef IOM_8_IO_PINS
    HAL_GPIO_WritePin(IO_5_6_DIFF_GPIO_Port, IO_5_6_DIFF_Pin, (pin56Mode != 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IO_7_8_DIFF_GPIO_Port, IO_7_8_DIFF_Pin, (pin78Mode != 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    #endif

    HAL_GPIO_WritePin(IO_1_2_TERM_N_GPIO_Port, IO_1_2_TERM_N_Pin, (pin12Mode == 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IO_3_4_TERM_N_GPIO_Port, IO_3_4_TERM_N_Pin, (pin34Mode == 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    #ifdef IOM_8_IO_PINS
    HAL_GPIO_WritePin(IO_5_6_TERM_N_GPIO_Port, IO_5_6_TERM_N_Pin, (pin56Mode == 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IO_7_8_TERM_N_GPIO_Port, IO_7_8_TERM_N_Pin, (pin78Mode == 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    #endif

    return;
}

void SetDataSpeed(uint8_t* comm)
{
    //uint speed;//TODO: Update when Set Data Speed Commmand established

    //return;
}

IOM_ERROR SetPinStates(uint8_t* comm) {
    uint8_t pin1State = *(comm+1) & 0b11;
    uint8_t pin2State = (*(comm+1) & 0b1100) >> 2;
    uint8_t pin3State = (*(comm+1) & 0b110000) >> 4;
    uint8_t pin4State = (*(comm+1) & 0b110000) >> 6;
    IOCFG_DATA_STATE dataState = IOCFG_DATA_STATE_DISABLED;
    IOM_ERROR err;
    err = GetDataState(pin1State, &dataState);
    if (err != IOM_OK) {
        return err;
    }
    SetIOPinDataState(pin1State, dataState);

    err = GetDataState(pin2State, &dataState);
    if (err != IOM_OK) {
        return err;
    }
    SetIOPinDataState(pin2State, dataState);

    err = GetDataState(pin3State, &dataState);
    if (err != IOM_OK) {
        return err;
    }
    SetIOPinDataState(pin3State, dataState);

    err = GetDataState(pin4State, &dataState);
    if (err != IOM_OK) {
        return err;
    }
    SetIOPinDataState(pin4State, dataState);

    return IOM_OK;

}

IOM_ERROR GetPinParams(uint8_t pinNum, uint8_t* comm)
{
    GPIO_TypeDef* pullDownPort = 0;
    uint16_t pullDownPin = 0;
    GPIO_TypeDef* pullUpPort = 0;
    uint16_t pullUpPin = 0;

    GPIO_TypeDef* triStatePort = 0;
    uint16_t triStatePin = 0;

    switch(pinNum) {
        case 1:
            pullDownPort = IO_1_PD_N_GPIO_Port;
            pullDownPin = IO_1_PD_N_Pin;
            pullUpPort = IO_1_PU_GPIO_Port;
            pullUpPin = IO_1_PU_Pin;
            triStatePort = IO_1_TRIS_N_GPIO_Port;
            triStatePin = IO_1_TRIS_N_Pin;
            break;
        case 2:
            pullDownPort = IO_2_PD_N_GPIO_Port;
            pullDownPin = IO_2_PD_N_Pin;
            pullUpPort = IO_2_PU_GPIO_Port;
            pullUpPin = IO_2_PU_Pin;
            triStatePort = IO_2_TRIS_N_GPIO_Port;
            triStatePin = IO_2_TRIS_N_Pin;
            break;
        case 3:
            pullDownPort = IO_3_PD_N_GPIO_Port;
            pullDownPin = IO_3_PD_N_Pin;
            pullUpPort = IO_3_PU_GPIO_Port;
            pullUpPin = IO_3_PU_Pin;
            triStatePort = IO_3_TRIS_N_GPIO_Port;
            triStatePin = IO_3_TRIS_N_Pin;
            break;
        case 4:
            pullDownPort = IO_4_PD_N_GPIO_Port;
            pullDownPin = IO_4_PD_N_Pin;
            pullUpPort = IO_4_PU_GPIO_Port;
            pullUpPin = IO_4_PU_Pin;
            triStatePort = IO_4_TRIS_N_GPIO_Port;
            triStatePin = IO_4_TRIS_N_Pin;
            break;
        default:
            return IOM_ERROR_INVALID;
    }
    uint8_t pullUp = (HAL_GPIO_ReadPin(pullUpPort, pullUpPin) == GPIO_PIN_SET) ? 1 : 0;
    uint8_t pullDown = (HAL_GPIO_ReadPin(pullDownPort, pullDownPin) == GPIO_PIN_SET) ? 1 : 0;
    uint8_t triState = (HAL_GPIO_ReadPin(triStatePort, triStatePin) == GPIO_PIN_SET) ? 1 : 0;

    *comm = pinNum << 4 & 0x30;
    if (pullDown != 0) {
        *comm |= 0x01;
    } else if (pullUp!= 0) {
        *comm |= 0x02;
    } else if (triState != 0) {
        *comm |= 0x03;
    }

    //get VH
    uint16_t* pVComm = (uint16_t*)(comm+1);
    *pVComm = ReadExtDAC(IOM_REGISTER_HIGH, pinNum);
    pVComm = (uint16_t*)(comm+3);
    *pVComm = ReadExtDAC(IOM_REGISTER_LOW, pinNum);

    return IOM_OK;
}

void GetTargetDeviceVoltage(uint8_t* comm)
{
    //device volt is on Dac channel 1
    // last 12 bits are the channel 1 output
    //uint16_t Volt = HAL_DAC_GetValue(&hdac1, DAC1_CHANNEL_1); // & 0x00000FFF
    //return;
}

void GetSignalMode(uint8_t* comm)
{
    //comm[0] = comm[0] & HAL_GPIO_ReadPin(IO_1_2_DIFF_GPIO_Port, IO_1_2_DIFF_Pin);
    //return;
}

void GetDataSpeed(uint8_t* comm)
{
    //uint8_t speed;//TODO: Update when Get Data Speed Commmand established
    //return;
}

